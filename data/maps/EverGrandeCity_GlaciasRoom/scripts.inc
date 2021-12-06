EverGrandeCity_ChelssRoom_MapScripts:: @ 8228412
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_ChelssRoom_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_ChelssRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_ChelssRoom_OnWarp
	.byte 0

EverGrandeCity_ChelssRoom_OnWarp: @ 8228422
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChelssRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_ChelssRoom_EventScript_PlayerTurnNorth:: @ 822842C
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_ChelssRoom_OnFrame: @ 8228431
	map_script_2 VAR_ELITE_4_STATE, 2, EverGrandeCity_ChelssRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_ChelssRoom_EventScript_WalkInCloseDoor:: @ 822843B
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 3
	releaseall
	end

EverGrandeCity_ChelssRoom_OnLoad: @ 8228448
	call_if_set FLAG_DEFEATED_ELITE_4_Chels, EverGrandeCity_ChelssRoom_EventScript_ResetAdvanceToNextRoom
	compare VAR_ELITE_4_STATE, 3
	call_if_eq EverGrandeCity_ChelssRoom_EventScript_CloseDoor
	end

EverGrandeCity_ChelssRoom_EventScript_ResetAdvanceToNextRoom:: @ 822845D
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_ChelssRoom_EventScript_CloseDoor:: @ 8228463
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_ChelssRoom_EventScript_Chels:: @ 8228469
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, EverGrandeCity_ChelssRoom_EventScript_ChelsRematch
	goto_if_set FLAG_DEFEATED_ELITE_4_Chels, EverGrandeCity_ChelssRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_ChelssRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_Chels, EverGrandeCity_ChelssRoom_Text_Defeat
	goto EverGrandeCity_ChelssRoom_EventScript_Defeated
	end

EverGrandeCity_ChelssRoom_EventScript_ChelsRematch::
	goto_if_set FLAG_DEFEATED_ELITE_4_Chels, EverGrandeCity_ChelssRoom_EventScript_PostBattleSpeechRematch
	playbgm MUS_ENCOUNTER_ELITE_FOUR, 0
	msgbox EverGrandeCity_ChelssRoom_Text_IntroSpeechRematch, MSGBOX_DEFAULT
	switch VAR_ELITE_4_MODE
	case 0, EverGrandeCity_ChelssRoom_EventScript_ChelsSingles
	case 1, EverGrandeCity_ChelssRoom_EventScript_ChelsSinglesLegends
	case 2, EverGrandeCity_ChelssRoom_EventScript_ChelsDoubles
	case 3, EverGrandeCity_ChelssRoom_EventScript_ChelsDoublesLegends

EverGrandeCity_ChelssRoom_EventScript_ChelsSingles::
	trainerbattle_no_intro TRAINER_Chels, EverGrandeCity_ChelssRoom_Text_Defeat
	goto EverGrandeCity_ChelssRoom_EventScript_DefeatedRematch
	end

EverGrandeCity_ChelssRoom_EventScript_ChelsSinglesLegends::
	trainerbattle_no_intro TRAINER_Chels_3, EverGrandeCity_ChelssRoom_Text_Defeat
	goto EverGrandeCity_ChelssRoom_EventScript_DefeatedRematch
	end

EverGrandeCity_ChelssRoom_EventScript_ChelsDoubles::
	trainerbattle_no_intro TRAINER_Chels_2, EverGrandeCity_ChelssRoom_Text_Defeat
	goto EverGrandeCity_ChelssRoom_EventScript_DefeatedRematch
	end

EverGrandeCity_ChelssRoom_EventScript_ChelsDoublesLegends::
	trainerbattle_no_intro TRAINER_Chels_4, EverGrandeCity_ChelssRoom_Text_Defeat
	goto EverGrandeCity_ChelssRoom_EventScript_DefeatedRematch
	end

EverGrandeCity_ChelssRoom_EventScript_PostBattleSpeech:: @ 8228490
	msgbox EverGrandeCity_ChelssRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_ChelssRoom_EventScript_PostBattleSpeechRematch::
	msgbox EverGrandeCity_ChelssRoom_Text_PostBattleSpeechRematch, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_ChelssRoom_EventScript_Defeated:: @ 822849A
	setflag FLAG_DEFEATED_ELITE_4_Chels
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_ChelssRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_ChelssRoom_EventScript_DefeatedRematch::
	setflag FLAG_DEFEATED_ELITE_4_Chels
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_ChelssRoom_Text_PostBattleSpeechRematch, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_ChelssRoom_Text_IntroSpeech: @ 82284AC
	.string "Welcome, my name is Chels\n"
	.string "of the Elite Four.\p"
	.string "I've traveled from afar to Hoenn\n"
	.string "so that I may hone my ice skills.\p"
	.string "But all I have seen are challenges by\n"
	.string "weak Trainers and their Pokémon.\p"
	.string "What about you?\p"
	.string "It would please me to no end if I could\n"
	.string "go all out against you!$"

EverGrandeCity_ChelssRoom_Text_Defeat: @ 82285B4
	.string "You and your Pokémon…\n"
	.string "How hot your spirits burn!\p"
	.string "The all-consuming heat overwhelms.\p"
	.string "It's no surprise that my icy skills\n"
	.string "failed to harm you.$"

EverGrandeCity_ChelssRoom_Text_PostBattleSpeech: @ 8228640
	.string "Advance to the next room.\p"
	.string "And there, confirm the truly fearsome\n"
	.string "side of the Pokémon League.$"

EverGrandeCity_ChelssRoom_Text_IntroSpeechRematch:
	.string "I've been waiting for a Trainer\n"
	.string "with a burning-hot soul.\p"
	.string "How can you oppose Mega Evolution\n"
	.string "that can freeze everything?$"

EverGrandeCity_ChelssRoom_Text_PostBattleSpeechRematch:
	.string "Hmmph…\n"
	.string "Do you intend to thaw my very heart?\p"
	.string "That actually wouldn't bother me.\p"
	.string "Anyway, continue onward!\n"
	.string "Ray is waiting for you as well.$"
