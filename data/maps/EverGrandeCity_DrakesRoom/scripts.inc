EverGrandeCity_RaysRoom_MapScripts:: @ 822869C
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_RaysRoom_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_RaysRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_DansRoom_OnWarp
	.byte 0

@ Unused, Ray uses Dans identical OnWarp for some reason
EverGrandeCity_RaysRoom_OnWarp: @ 82286AC
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_RaysRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_RaysRoom_EventScript_PlayerTurnNorth:: @ 82286B6
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_RaysRoom_OnFrame: @ 82286BB
	map_script_2 VAR_ELITE_4_STATE, 3, EverGrandeCity_RaysRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_RaysRoom_EventScript_WalkInCloseDoor:: @ 82286C5
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 4
	releaseall
	end

EverGrandeCity_RaysRoom_OnLoad: @ 82286D2
	call_if_set FLAG_DEFEATED_ELITE_4_Ray, EverGrandeCity_RaysRoom_EventScript_ResetAdvanceToNextRoom
	compare VAR_ELITE_4_STATE, 4
	call_if_eq EverGrandeCity_RaysRoom_EventScript_CloseDoor
	end

EverGrandeCity_RaysRoom_EventScript_ResetAdvanceToNextRoom:: @ 82286E7
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_RaysRoom_EventScript_CloseDoor:: @ 82286ED
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_RaysRoom_EventScript_Ray:: @ 82286F3
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, EverGrandeCity_RaysRoom_EventScript_RayRematch
	goto_if_set FLAG_DEFEATED_ELITE_4_Ray, EverGrandeCity_RaysRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_RaysRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_Ray, EverGrandeCity_RaysRoom_Text_Defeat
	goto EverGrandeCity_RaysRoom_EventScript_Defeated
	end

EverGrandeCity_RaysRoom_EventScript_RayRematch::
	goto_if_set FLAG_DEFEATED_ELITE_4_Ray, EverGrandeCity_RaysRoom_EventScript_PostBattleSpeechRematch
	playbgm MUS_ENCOUNTER_ELITE_FOUR, 0
	msgbox EverGrandeCity_RaysRoom_Text_IntroSpeechRematch, MSGBOX_DEFAULT
	switch VAR_ELITE_4_MODE
	case 0, EverGrandeCity_RaysRoom_EventScript_RaySingles
	case 1, EverGrandeCity_RaysRoom_EventScript_RaySinglesLegends
	case 2, EverGrandeCity_RaysRoom_EventScript_RayDoubles
	case 3, EverGrandeCity_RaysRoom_EventScript_RayDoublesLegends
	end

EverGrandeCity_RaysRoom_EventScript_RaySingles::
	trainerbattle_no_intro TRAINER_Ray, EverGrandeCity_RaysRoom_Text_Defeat
	goto EverGrandeCity_RaysRoom_EventScript_DefeatedRematch
	end

EverGrandeCity_RaysRoom_EventScript_RaySinglesLegends::
	trainerbattle_no_intro TRAINER_Ray_3, EverGrandeCity_RaysRoom_Text_Defeat
	goto EverGrandeCity_RaysRoom_EventScript_DefeatedRematch
	end

EverGrandeCity_RaysRoom_EventScript_RayDoubles::
	trainerbattle_no_intro TRAINER_Ray_2, EverGrandeCity_RaysRoom_Text_Defeat
	goto EverGrandeCity_RaysRoom_EventScript_DefeatedRematch
	end

EverGrandeCity_RaysRoom_EventScript_RayDoublesLegends::
	trainerbattle_no_intro TRAINER_Ray_4, EverGrandeCity_RaysRoom_Text_Defeat
	goto EverGrandeCity_RaysRoom_EventScript_DefeatedRematch
	end

EverGrandeCity_RaysRoom_EventScript_PostBattleSpeech:: @ 822871A
	msgbox EverGrandeCity_RaysRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_RaysRoom_EventScript_PostBattleSpeechRematch::
	msgbox EverGrandeCity_RaysRoom_Text_PostBattleSpeechRematch, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_RaysRoom_EventScript_Defeated:: @ 8228724
	setvar VAR_0x8004, FANCOUNTER_DEFEATED_Ray
	special Script_TryGainNewFanFromCounter
	setflag FLAG_DEFEATED_ELITE_4_Ray
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_RaysRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_RaysRoom_EventScript_DefeatedRematch::
	setvar VAR_0x8004, FANCOUNTER_DEFEATED_Ray
	special Script_TryGainNewFanFromCounter
	setflag FLAG_DEFEATED_ELITE_4_Ray
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_RaysRoom_Text_PostBattleSpeechRematch, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_RaysRoom_Text_IntroSpeech: @ 822873E
	.string "I am the last of the Pokémon League\n"
	.string "Elite Four, Ray the Dragon master!\p"
	.string "In their natural state, Pokémon are\n"
	.string "wild living things. They are free.\p"
	.string "At times, they hinder us.\n"
	.string "At times, they help us.\p"
	.string "For us to battle with Pokémon as\n"
	.string "partners, do you know what it takes?\p"
	.string "Do you know what is needed?\p"
	.string "If you don't, then you will never\n"
	.string "prevail over me!$"

EverGrandeCity_RaysRoom_Text_Defeat: @ 8228895
	.string "Superb, it should be said.$"

EverGrandeCity_RaysRoom_Text_PostBattleSpeech: @ 82288B0
	.string "You deserve every credit for coming\n"
	.string "this far as a Trainer of Pokémon.\p"
	.string "You do seem to know what is needed.\p"
	.string "Yes, what a Trainer needs is a\n"
	.string "virtuous heart.\p"
	.string "Pokémon touch the good hearts of\n"
	.string "Trainers and learn good from wrong.\p"
	.string "They touch the good hearts of\n"
	.string "Trainers and grow strong.\p"
	.string "Go! Go onwards!\n"
	.string "The Champion is waiting!$"

EverGrandeCity_RaysRoom_Text_IntroSpeechRematch:
	.string "Oh, I've been waitin' for you!\p"
	.string "My Pokémon and I are going to\n"
	.string "show you everything we've got!\p"
	.string "Well then, you had better\n"
	.string "get ready to try and stop me!$"

EverGrandeCity_RaysRoom_Text_PostBattleSpeechRematch:
	.string "I got a glimpse inside your heart!\n"
	.string "There's nothing for me to say to you!\p"
	.string "Go forth, Trainer!\p"
	.string "Go on to your next challenge\n"
	.string "with your head held high!$"
