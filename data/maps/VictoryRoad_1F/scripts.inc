.set LOCALID_Guy_ENTRANCE, 4

VictoryRoad_1F_MapScripts:: @ 8235D7A
	map_script MAP_SCRIPT_ON_TRANSITION, VictoryRoad_1F_OnTransition
	.byte 0

VictoryRoad_1F_OnTransition: @ 8235D80
	compare VAR_VICTORY_ROAD_1F_STATE, 1
	call_if_eq VictoryRoad_1F_EventScript_SetEntranceGuyPos1
	compare VAR_VICTORY_ROAD_1F_STATE, 2
	call_if_eq VictoryRoad_1F_EventScript_SetEntranceGuyPos2
	end

VictoryRoad_1F_EventScript_SetEntranceGuyPos1:: @ 8235D97
	setobjectxyperm LOCALID_Guy_ENTRANCE, 2, 24
	setobjectmovementtype LOCALID_Guy_ENTRANCE, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_SetEntranceGuyPos2:: @ 8235DA3
	setobjectxyperm LOCALID_Guy_ENTRANCE, 3, 24
	setobjectmovementtype LOCALID_Guy_ENTRANCE, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_GuyBattleTrigger1:: @ 8235DAF
	lockall
	setvar VAR_0x8008, 1
	addobject LOCALID_Guy_ENTRANCE
	applymovement LOCALID_Guy_ENTRANCE, VictoryRoad_1F_Movement_GuyApproachPlayer1
	waitmovement 0
	goto VictoryRoad_1F_EventScript_GuyEntranceBattle
	end

VictoryRoad_1F_EventScript_GuyBattleTrigger2:: @ 8235DC8
	lockall
	setvar VAR_0x8008, 2
	addobject LOCALID_Guy_ENTRANCE
	applymovement LOCALID_Guy_ENTRANCE, VictoryRoad_1F_Movement_GuyApproachPlayer2
	waitmovement 0
	goto VictoryRoad_1F_EventScript_GuyEntranceBattle
	end

VictoryRoad_1F_EventScript_GuyEntranceBattle:: @ 8235DE1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox VictoryRoad_1F_Text_GuyNotGoingToLoseAnymore, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_Guy_VR_1, VictoryRoad_1F_Text_GuyEntranceDefeat
	msgbox VictoryRoad_1F_Text_GuyPostEntranceBattle, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_Guy
	copyobjectxytoperm LOCALID_Guy_ENTRANCE
	setflag FLAG_DEFEATED_Guy_VICTORY_ROAD
	copyvar VAR_VICTORY_ROAD_1F_STATE, VAR_0x8008
	releaseall
	end

VictoryRoad_1F_Movement_GuyApproachPlayer1: @ 8235E15
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

VictoryRoad_1F_Movement_GuyApproachPlayer2: @ 8235E21
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

@ This Guy appears near the entrance once his battle is triggered and remains there until the Hall of Fame is entered
VictoryRoad_1F_EventScript_EntranceGuy:: @ 8235E2C
	msgbox VictoryRoad_1F_Text_GuyPostEntranceBattle, MSGBOX_NPC
	end

@ This Guy appears and remains at the exit after the Hall of Fame is entered 
VictoryRoad_1F_EventScript_ExitGuy:: @ 8235E35
	trainerbattle_single TRAINER_Guy_VR_2, VictoryRoad_1F_Text_GuyIntro, VictoryRoad_1F_Text_GuyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq VictoryRoad_1F_EventScript_RematchGuy
	msgbox VictoryRoad_1F_Text_GuyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_RematchGuy:: @ 8235E5C
	trainerbattle_rematch TRAINER_Guy_VR_2, VictoryRoad_1F_Text_GuyIntro, VictoryRoad_1F_Text_GuyDefeat
	msgbox VictoryRoad_1F_Text_GuyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Edgar:: @ 8235E73
	trainerbattle_single TRAINER_EDGAR, VictoryRoad_1F_Text_EdgarIntro, VictoryRoad_1F_Text_EdgarDefeat
	msgbox VictoryRoad_1F_Text_EdgarPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Albert:: @ 8235E8A
	trainerbattle_single TRAINER_ALBERT, VictoryRoad_1F_Text_AlbertIntro, VictoryRoad_1F_Text_AlbertDefeat
	msgbox VictoryRoad_1F_Text_AlbertPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Hope:: @ 8235EA1
	trainerbattle_single TRAINER_HOPE, VictoryRoad_1F_Text_HopeIntro, VictoryRoad_1F_Text_HopeDefeat
	msgbox VictoryRoad_1F_Text_HopePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Quincy:: @ 8235EB8
	trainerbattle_single TRAINER_QUINCY, VictoryRoad_1F_Text_QuincyIntro, VictoryRoad_1F_Text_QuincyDefeat
	msgbox VictoryRoad_1F_Text_QuincyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Katelynn:: @ 8235ECF
	trainerbattle_single TRAINER_KATELYNN, VictoryRoad_1F_Text_KatelynnIntro, VictoryRoad_1F_Text_KatelynnDefeat
	msgbox VictoryRoad_1F_Text_KatelynnPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_Text_GuyNotGoingToLoseAnymore: @ 8235EE6
	.string "Guy: Hi! {PLAYER}!\p"
	.string "I bet you're surprised to see me here!\p"
	.string "I made it all the way here, and it's\n"
	.string "all thanks to you!\p"
	.string "{PLAYER}, losing to you that time\n"
	.string "made me stronger!\p"
	.string "But I'm not going to lose anymore!\p"
	.string "I'm going to win! For the Pokémon who\n"
	.string "gave me courage and strength!\p"
	.string "Okay… Here I come!$"

VictoryRoad_1F_Text_GuyEntranceDefeat: @ 8235FFC
	.string "Wow!\n"
	.string "{PLAYER}, you are strong, after all!$"

VictoryRoad_1F_Text_GuyPostEntranceBattle: @ 8236020
	.string "Guy: I couldn't beat you today,\n"
	.string "{PLAYER}, but one of these days, I'll\l"
	.string "catch up to you!$"

VictoryRoad_1F_Text_GuyIntro: @ 8236073
	.string "Guy: Hi! {PLAYER}!\p"
	.string "I've gotten stronger since that last\n"
	.string "time! I wanted to show you, {PLAYER}!\p"
	.string "Okay… Here I come!$"

VictoryRoad_1F_Text_GuyDefeat: @ 82360DA
	.string "Wow!\n"
	.string "{PLAYER}, you are strong, after all!$"

VictoryRoad_1F_Text_GuyPostBattle: @ 82360FE
	.string "Guy: I couldn't beat you this time,\n"
	.string "too… But one of these days, {PLAYER},\l"
	.string "I'm going to catch up to you…\p"
	.string "And challenge the Pokémon League!$"

VictoryRoad_1F_Text_EdgarIntro: @ 8236184
	.string "I've made it this far a couple times,\n"
	.string "but the last stretch is so long…$"

VictoryRoad_1F_Text_EdgarDefeat: @ 82361CB
	.string "My dream ends here again…$"

VictoryRoad_1F_Text_EdgarPostBattle: @ 82361E5
	.string "You've made it this far. Keep the\n"
	.string "momentum going and become the\l"
	.string "Champion! If anyone can, it's you!$"

VictoryRoad_1F_Text_AlbertIntro: @ 8236248
	.string "I didn't come all this way to lose now.\n"
	.string "That possibility doesn't exist!$"

VictoryRoad_1F_Text_AlbertDefeat: @ 8236290
	.string "Impossible…\n"
	.string "I lost?$"

VictoryRoad_1F_Text_AlbertPostBattle: @ 82362A4
	.string "I lost here…\p"
	.string "That means I lack the qualifications\n"
	.string "to become the Champion…$"

VictoryRoad_1F_Text_HopeIntro: @ 82362EE
	.string "This seemingly infinite and harsh road\n"
	.string "lives up to its name of Victory.$"

VictoryRoad_1F_Text_HopeDefeat: @ 8236336
	.string "Your battle style is fantastic…$"

VictoryRoad_1F_Text_HopePostBattle: @ 8236356
	.string "You seem to have the potential for\n"
	.string "becoming the Champion.$"

VictoryRoad_1F_Text_QuincyIntro: @ 8236390
	.string "What is the Victory Road?\n"
	.string "I'll tell you if you win!$"

VictoryRoad_1F_Text_QuincyDefeat: @ 82363C4
	.string "Okay!\n"
	.string "Well done!$"

VictoryRoad_1F_Text_QuincyPostBattle: @ 82363D5
	.string "Getting through here safely--that's\n"
	.string "the final test for any Trainer aiming\l"
	.string "to become the Pokémon Champion.\p"
	.string "That's why it's called the Victory\n"
	.string "Road.$"

VictoryRoad_1F_Text_KatelynnIntro: @ 8236468
	.string "I have nothing to say to anyone\n"
	.string "that's come this far. Come on!$"

VictoryRoad_1F_Text_KatelynnDefeat: @ 82364A7
	.string "This is a disgrace…$"

VictoryRoad_1F_Text_KatelynnPostBattle: @ 82364BB
	.string "Humph, go right on ahead.\n"
	.string "See if I care.$"
