.set LOCALID_Grub, 1
.set LOCALID_WALLY, 10
.set LOCALID_WALLYS_Grub, 11

PetalburgCity_Gym_MapScripts:: @ 8204889
	map_script MAP_SCRIPT_ON_LOAD, PetalburgCity_Gym_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgCity_Gym_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_Gym_OnFrame
	.byte 0

PetalburgCity_Gym_OnLoad: @ 820489E
	compare VAR_PETALBURG_GYM_STATE, 6
	goto_if_eq PetalburgCity_Gym_EventScript_OpenUnlockedDoors
	compare VAR_PETALBURG_GYM_STATE, 7
	call_if_ge PetalburgCity_Gym_EventScript_UnlockAllDoors
	end

@ NOTE: Strength and OHKO rooms are misleading. Both are more accurately Critical-Hit
PetalburgCity_Gym_EventScript_OpenUnlockedDoors:: @ 82048B5
	setvar VAR_0x8005, 1
	call PetalburgCity_Gym_EventScript_OpenGymEntranceDoors
	call_if_defeated TRAINER_RANDALL, PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors
	call_if_defeated TRAINER_MARY, PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors
	call_if_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors
	call_if_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors
	call_if_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors
	call_if_defeated TRAINER_JODY, PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors
	call_if_defeated TRAINER_BERKE, PetalburgCity_Gym_EventScript_OpenOHKORoomDoors
	end

PetalburgCity_Gym_EventScript_UnlockAllDoors:: @ 82048FF
	setvar VAR_0x8005, 1
	call PetalburgCity_Gym_EventScript_OpenGymEntranceDoors
	call PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors
	call PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors
	call PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors
	call PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors
	call PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors
	call PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors
	call PetalburgCity_Gym_EventScript_OpenOHKORoomDoors
	return

PetalburgCity_Gym_OnTransition: @ 820492D
	compare VAR_PETALBURG_GYM_STATE, 1
	call_if_eq PetalburgCity_Gym_EventScript_MoveWallyToEntrance
	compare VAR_PETALBURG_GYM_STATE, 6
	call_if_lt PetalburgCity_Gym_EventScript_MoveGrubToEntrance
	call_if_set FLAG_SYS_GAME_CLEAR, PetalburgCity_Gym_EventScript_CheckGrubForRematch
	end

PetalburgCity_Gym_EventScript_MoveWallyToEntrance:: @ 820494D
	setobjectxyperm LOCALID_WALLY, 5, 108
	return

PetalburgCity_Gym_EventScript_MoveGrubToEntrance:: @ 8204955
	setobjectxyperm LOCALID_Grub, 4, 107
	return

PetalburgCity_Gym_EventScript_CheckGrubForRematch:: @ 820495D
	goto_if_unset FLAG_DAILY_REMATCH_Grub, PetalburgCity_Gym_EventScript_DontMoveGrubToFront
	compare VAR_PETALBURG_GYM_STATE, 8
	goto_if_eq PetalburgCity_Gym_EventScript_DontMoveGrubToFront @ If var = 8 set var = 8? Why
	setobjectxyperm LOCALID_Grub, 4, 107
	return

PetalburgCity_Gym_EventScript_DontMoveGrubToFront:: @ 8204985
	setvar VAR_PETALBURG_GYM_STATE, 8
	end

PetalburgCity_Gym_OnWarp: @ 820498B
	map_script_2 VAR_PETALBURG_GYM_STATE, 1, PetalburgCity_Gym_EventScript_TurnPlayerNorth
	.2byte 0

PetalburgCity_Gym_EventScript_TurnPlayerNorth:: @ 8204995
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

PetalburgCity_Gym_OnFrame: @ 820499A
	map_script_2 VAR_PETALBURG_GYM_STATE, 1, PetalburgCity_Gym_EventScript_ReturnFromWallyTutorial
	.2byte 0

PetalburgCity_Gym_EventScript_ReturnFromWallyTutorial:: @ 82049A4
	lockall
	msgbox PetalburgCity_Gym_Text_GrubSoDidItWorkOut, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_WallyThankYouBye, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyExitGym
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_WALLY
	setflag FLAG_HIDE_PETALBURG_CITY_WALLY
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox PetalburgCity_Gym_Text_GrubGoCollectBadges, MSGBOX_DEFAULT
	setvar VAR_PETALBURG_GYM_STATE, 2
	releaseall
	end

PetalburgCity_Gym_Movement_WallyExitGym: @ 82049EC
	walk_down
	walk_down
	walk_down
	delay_16
	step_end

PetalburgCity_Gym_EventScript_Grub:: @ 82049F1
	lock
	faceplayer
	switch VAR_PETALBURG_GYM_STATE
	case 2, PetalburgCity_Gym_EventScript_GrubNoBadges
	case 3, PetalburgCity_Gym_EventScript_GrubOneBadge
	case 4, PetalburgCity_Gym_EventScript_GrubTwoBadges
	case 5, PetalburgCity_Gym_EventScript_GrubThreeBadges
	case 6, PetalburgCity_Gym_EventScript_GrubGiveKeystone
	case 7, PetalburgCity_Gym_EventScript_GrubPostBattle
	case 8, PetalburgCity_Gym_EventScript_GrubRematch
	msgbox PetalburgCity_Gym_Text_GrubYoureHereWithYourPokemon, MSGBOX_DEFAULT
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, PetalburgCity_Gym_EventScript_BeginWallyTutorialSouth
	case DIR_NORTH, PetalburgCity_Gym_EventScript_BeginWallyTutorialNorth
	case DIR_WEST, PetalburgCity_Gym_EventScript_BeginWallyTutorialWest
	case DIR_EAST, PetalburgCity_Gym_EventScript_BeginWallyTutorialEast
	end

PetalburgCity_Gym_EventScript_BeginWallyTutorialSouth:: @ 8204A80
	setvar VAR_0x8008, 0
	goto PetalburgCity_Gym_EventScript_BeginWallyTutorial
	end

PetalburgCity_Gym_EventScript_BeginWallyTutorialNorth:: @ 8204A8B
	setvar VAR_0x8008, 1
	goto PetalburgCity_Gym_EventScript_BeginWallyTutorial
	end

PetalburgCity_Gym_EventScript_BeginWallyTutorialWest:: @ 8204A96
	setvar VAR_0x8008, 2
	goto PetalburgCity_Gym_EventScript_BeginWallyTutorial
	end

PetalburgCity_Gym_EventScript_BeginWallyTutorialEast:: @ 8204AA1
	setvar VAR_0x8008, 3
	goto PetalburgCity_Gym_EventScript_BeginWallyTutorial
	end

PetalburgCity_Gym_EventScript_BeginWallyTutorial:: @ 8204AAC
	addobject LOCALID_WALLY
	playse SE_DOOR
	compare VAR_0x8008, 0
	call_if_eq PetalburgCity_Gym_EventScript_WallyArriveSouth
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_WallyArriveNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_WallyArriveWestEast
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_WallyArriveWestEast
	msgbox PetalburgCity_Gym_Text_WallyIdLikeAPokemon, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_GrubOhYoureWallyRight, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_WallyIveNeverCaughtAPokemon, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_GrubHmISee, MSGBOX_DEFAULT
	compare VAR_0x8008, 0
	call_if_eq PetalburgCity_Gym_EventScript_GrubAddressPlayerSouth
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_GrubAddressPlayerNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_GrubAddressPlayerWest
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_GrubAddressPlayerEast
	msgbox PetalburgCity_Gym_Text_GrubPlayerGoWithWally, MSGBOX_DEFAULT
	compare VAR_0x8008, 0
	call_if_eq PetalburgCity_Gym_EventScript_GrubAddressWallySouth
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_GrubAddressWallyNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_GrubAddressWallyWest
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_GrubAddressWallyEast
	msgbox PetalburgCity_Gym_Text_IllLoanYouMyZigzagoon, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_WallyThankYouAndGrubGivesPokeBall, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_Text_WallyOhWowThankYou, MSGBOX_DEFAULT
	compare VAR_0x8008, 0
	call_if_eq PetalburgCity_Gym_EventScript_GrubFaceDoorSouth
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_GrubFaceDoorNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_GrubFaceDoorWest
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_GrubFaceDoorEast
	compare VAR_0x8008, 0
	call_if_eq PetalburgCity_Gym_EventScript_WallyFacePlayer
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_WallyFaceDown
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_WallyFacePlayer
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_WallyFacePlayer
	msgbox PetalburgCity_Gym_Text_WouldYouReallyComeWithMe, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_DONT_TRANSITION_MUSIC
	playbgm MUS_FOLLOW_ME, FALSE
	compare VAR_0x8008, 0
	call_if_eq PetalburgCity_Gym_EventScript_ExitGymWithWallySouth
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_ExitGymWithWallyNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_ExitGymWithWallyWest
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_ExitGymWithWallyEast
	removeobject LOCALID_WALLY
	setflag FLAG_HIDE_PETALBURG_CITY_WALLYS_MOM
	setvar VAR_PETALBURG_GYM_STATE, 1
	setvar VAR_PETALBURG_CITY_STATE, 2
	clearflag FLAG_HIDE_PETALBURG_CITY_WALLY
	clearflag FLAG_HIDE_PETALBURG_GYM_WALLY
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	special InitBirchState
	warp MAP_PETALBURG_CITY, 255, 15, 8
	waitstate
	release
	end

PetalburgCity_Gym_EventScript_WallyArriveSouth:: @ 8204C31
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestDown
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyArrive
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallyArriveNorth:: @ 8204C43
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyArriveNorth
	waitmovement 0
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallyArriveWestEast:: @ 8204C5F
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestDown
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyArrive
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallySouth:: @ 8204C78
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestDown
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyExitSouthWest
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallySouth
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallyNorth:: @ 8204C91
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyExitNorth
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallyNorth
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallyWest:: @ 8204CA3
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyExitSouthWest
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallyWest
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallyEast:: @ 8204CB5
	applymovement LOCALID_WALLY, PetalburgCity_Gym_Movement_WallyExitEast
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallyEast
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_GrubAddressPlayerSouth:: @ 8204CC7
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_GrubAddressPlayerNorth:: @ 8204CD2
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestDown
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_GrubAddressPlayerWest:: @ 8204CE4
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_GrubAddressPlayerEast:: @ 8204CF6
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestLeft
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_GrubAddressWallySouth:: @ 8204D08
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_GrubAddressWallyNorth:: @ 8204D13
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_GrubAddressWallyWest:: @ 8204D1E
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_GrubAddressWallyEast:: @ 8204D29
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallyFacePlayer:: @ 8204D34
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallyFaceDown:: @ 8204D3F
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_GrubNoBadges:: @ 8204D4A
	msgbox PetalburgCity_Gym_Text_GrubGoToRustboro, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_GrubOneBadge:: @ 8204D54
	msgbox PetalburgCity_Gym_Text_GrubGoToDewford, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_GrubTwoBadges:: @ 8204D5E
	msgbox PetalburgCity_Gym_Text_YouHaveGottenStronger, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_GrubThreeBadges:: @ 8204D68
	msgbox PetalburgCity_Gym_Text_YouHaveGottenStronger, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_GrubFaceDoorSouth:: @ 8204D72
	return

@ For all other GrubFaceDoorX, Grub is already facing the door from GrubAddressWallyX
PetalburgCity_Gym_EventScript_GrubFaceDoorNorth:: @ 8204D73
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_GrubFaceDoorWest:: @ 8204D7E
	return

PetalburgCity_Gym_EventScript_GrubFaceDoorEast:: @ 8204D7F
	return

PetalburgCity_Gym_EventScript_GrubPostBattle:: @ 8204D80
	call PetalburgCity_Gym_EventScript_ShouldGiveEnigmaBerry
	compare VAR_RESULT, TRUE
	goto_if_eq PetalburgCity_Gym_EventScript_GiveEnigmaBerry
	goto_if_unset FLAG_RECEIVED_TM42, PetalburgCity_Gym_EventScript_GiveFacade2
	goto_if_set FLAG_SYS_GAME_CLEAR, PetalburgCity_Gym_EventScript_NoAmountOfTrainingIsEnough
	msgbox PetalburgCity_Gym_Text_GrubGoingToKeepTraining, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_GiveFacade2:: @ 8204DAC
	call PetalburgCity_Gym_EventScript_GiveFacade
	release
	end

PetalburgCity_Gym_EventScript_GrubRematch::
	message PetalburgCity_Gym_Text_GrubChooseFormat
	waitmessage
	multichoice 17, 6, MULTI_REMATCH_BATTLE_MODE, 0
	switch VAR_RESULT
	case 0, PetalburgCity_Gym_EventScript_SetSingles
	case 1, PetalburgCity_Gym_EventScript_SetDoubles
	case 2, PetalburgCity_Gym_EventScript_Exit
	case 127, PetalburgCity_Gym_EventScript_Exit
	releaseall
	end

PetalburgCity_Gym_EventScript_SetSingles::
	msgbox PetalburgCity_Gym_Text_GrubAllowLegends, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_GrubSinglesRematch
	trainerbattle_no_intro TRAINER_Grub_4, PetalburgCity_Gym_Text_GrubRematchDefeat
	setflag FLAG_DAILY_REMATCH_Grub
	releaseall
	end

PetalburgCity_Gym_EventScript_SetDoubles::
	msgbox PetalburgCity_Gym_Text_GrubAllowLegends, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_GrubDoublesRematch
	trainerbattle_no_intro TRAINER_Grub_5, PetalburgCity_Gym_Text_GrubRematchDefeat
	setflag FLAG_DAILY_REMATCH_Grub
	releaseall
	end

PetalburgCity_Gym_EventScript_GrubSinglesRematch::
	trainerbattle_no_intro TRAINER_Grub_2, PetalburgCity_Gym_Text_GrubRematchDefeat
	setflag FLAG_DAILY_REMATCH_Grub
	releaseall
	end

PetalburgCity_Gym_EventScript_GrubDoublesRematch::
	trainerbattle_no_intro TRAINER_Grub_3, PetalburgCity_Gym_Text_GrubRematchDefeat
	setflag FLAG_DAILY_REMATCH_Grub
	releaseall
	end

PetalburgCity_Gym_EventScript_AlreadyRematched::
	msgbox PetalburgCity_Gym_Text_GrubPostRematch, MSGBOX_AUTOCLOSE
	releaseall
	end

PetalburgCity_Gym_EventScript_Exit::
	releaseall
	end

PetalburgCity_Gym_EventScript_ShouldGiveEnigmaBerry:: @ 8204DCE
	specialvar VAR_RESULT, IsEnigmaBerryValid
	compare VAR_RESULT, FALSE
	goto_if_eq PetalburgCity_Gym_EventScript_DontGiveEnigmaBerry
	checkitem ITEM_ENIGMA_BERRY, 1
	compare VAR_RESULT, TRUE
	goto_if_eq PetalburgCity_Gym_EventScript_DontGiveEnigmaBerry
	checkpcitem ITEM_ENIGMA_BERRY, 1
	compare VAR_RESULT, TRUE
	goto_if_eq PetalburgCity_Gym_EventScript_DontGiveEnigmaBerry
	compare VAR_ENIGMA_BERRY_AVAILABLE, 0
	goto_if_eq PetalburgCity_Gym_EventScript_DontGiveEnigmaBerry
	msgbox PetalburgCity_Gym_Text_GiveEnigmaBerry, MSGBOX_DEFAULT
	setvar VAR_RESULT, TRUE
	return

PetalburgCity_Gym_EventScript_DontGiveEnigmaBerry:: @ 8204E17
	setvar VAR_RESULT, FALSE
	return

PetalburgCity_Gym_EventScript_GiveEnigmaBerry:: @ 8204E1D
	giveitem ITEM_ENIGMA_BERRY
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setvar VAR_ENIGMA_BERRY_AVAILABLE, 0
	release
	end

PetalburgCity_Gym_EventScript_GrubGiveKeystone::
	goto_if_set FLAG_SYS_RECEIVED_KEYSTONE, PetalburgCity_Gym_EventScript_GrubBattle
	msgbox PetalburgCity_Gym_Text_GrubIntro, MSGBOX_DEFAULT
	giveitem ITEM_MEGA_BRACELET
	setflag FLAG_SYS_RECEIVED_KEYSTONE
	msgbox PetalburgCity_Gym_Text_GrubMegaBracelet, MSGBOX_DEFAULT
	giveitem ITEM_SCEPTILITE
	waitmessage
	giveitem ITEM_BLAZIKENITE
	waitmessage
	giveitem ITEM_SWAMPERTITE
	waitmessage
	msgbox PetalburgCity_Gym_Text_GrubWheneverReady, MSGBOX_DEFAULT
	closemessage
	end
	
PetalburgCity_Gym_EventScript_GrubBattle::
	msgbox PetalburgCity_Gym_Text_GrubBattleIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_Grub_1, PetalburgCity_Gym_Text_GrubDefeat
	message PetalburgCity_Gym_Text_ReceivedBalanceBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox PetalburgCity_Gym_Text_ExplainBalanceBadgeTakeThis, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox PetalburgCity_Gym_Text_RegisteredExploud, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	msgbox PetalburgCity_Gym_Text_TakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_PETALBURG_GYM
	setvar VAR_PETALBURG_GYM_STATE, 7
	setflag FLAG_BADGE05_GET
	special ResetHealLocationFromDewford
	call EventScript_HideMrBriney
	setflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	clearflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setvar VAR_0x8008, 5
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_DEWFORD_HALL_SLUDGE_BOMB_MAN
	call PetalburgCity_Gym_EventScript_UnlockAllDoors
	special DrawWholeMapView
	call PetalburgCity_Gym_EventScript_GiveFacade
	delay 30
	msgbox PetalburgCity_Gym_Text_GrubHappyAndSad, MSGBOX_DEFAULT
	closemessage
	delay 40
	playse SE_DOOR
	delay 10
	addobject LOCALID_WALLYS_Grub
	switch VAR_FACING
	case DIR_NORTH, PetalburgCity_Gym_EventScript_WallysGrubArrivesNorth
	case DIR_WEST, PetalburgCity_Gym_EventScript_WallysGrubArrivesWest
	case DIR_EAST, PetalburgCity_Gym_EventScript_WallysGrubArrivesEast
	end

PetalburgCity_Gym_EventScript_GiveFacade:: @ 8204ED2
	giveitem ITEM_TM42_FACADE
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_BagIsFull
	setflag FLAG_RECEIVED_TM42
	msgbox PetalburgCity_Gym_Text_ExplainFacade, MSGBOX_DEFAULT
	return

PetalburgCity_Gym_EventScript_WallysGrubArrivesNorth:: @ 8204EF5
	setvar VAR_0x8008, 1
	goto PetalburgCity_Gym_EventScript_WallysGrubArrives

PetalburgCity_Gym_EventScript_WallysGrubArrivesEast:: @ 8204EFF
	setvar VAR_0x8008, 2
	goto PetalburgCity_Gym_EventScript_WallysGrubArrives

PetalburgCity_Gym_EventScript_WallysGrubArrivesWest:: @ 8204F09
	setvar VAR_0x8008, 3
	goto PetalburgCity_Gym_EventScript_WallysGrubArrives

PetalburgCity_Gym_EventScript_WallysGrubArrives:: @ 8204F13
	applymovement LOCALID_WALLYS_Grub, PetalburgCity_Gym_Movement_WallysGrubEnterGym
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WALLYS_Grub, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLYS_Grub, Common_Movement_Delay48
	waitmovement 0
	delay 10
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_WallysGrubApproachPlayerNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_WallysGrubApproachPlayerEast
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_WallysGrubApproachPlayerWest
	msgbox PetalburgCity_Gym_Text_PleaseComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 20
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_WallysGrubFaceGrubNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_WallysGrubFaceGrubEast
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_WallysGrubFaceGrubWest
	msgbox PetalburgCity_Gym_Text_LetMeBorrowPlayer, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_DONT_TRANSITION_MUSIC
	playbgm MUS_FOLLOW_ME, FALSE
	compare VAR_0x8008, 1
	call_if_eq PetalburgCity_Gym_EventScript_ExitGymWithWallysGrubNorth
	compare VAR_0x8008, 2
	call_if_eq PetalburgCity_Gym_EventScript_ExitGymWithWallysGrubEast
	compare VAR_0x8008, 3
	call_if_eq PetalburgCity_Gym_EventScript_ExitGymWithWallysGrubWest
	removeobject LOCALID_WALLYS_Grub
	setvar VAR_PETALBURG_CITY_STATE, 4
	clearflag FLAG_HIDE_PETALBURG_CITY_WALLYS_Grub
	warp MAP_PETALBURG_CITY, 255, 15, 8
	waitstate
	release
	end

PetalburgCity_Gym_EventScript_WallysGrubFaceGrubNorth:: @ 8204FCC
	applymovement LOCALID_WALLYS_Grub, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallysGrubFaceGrubEast:: @ 8204FD7
	applymovement LOCALID_WALLYS_Grub, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallysGrubFaceGrubWest:: @ 8204FE2
	applymovement LOCALID_WALLYS_Grub, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallysGrubApproachPlayerNorth:: @ 8204FED
	applymovement LOCALID_WALLYS_Grub, PetalburgCity_Gym_Movement_WallysGrubApproachPlayerNorth
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallysGrubApproachPlayerEast:: @ 8205009
	applymovement LOCALID_WALLYS_Grub, PetalburgCity_Gym_Movement_WallysGrubApproachPlayerEast
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_WallysGrubApproachPlayerWest:: @ 8205025
	applymovement LOCALID_WALLYS_Grub, PetalburgCity_Gym_Movement_WallysGrubApproachPlayerWest
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallysGrubNorth:: @ 8205041
	applymovement LOCALID_WALLYS_Grub, PetalburgCity_Gym_Movement_WallysGrubExitNorth
	applymovement LOCALID_Grub, Common_Movement_WalkInPlaceFastestDown
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallysGrubNorth
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallysGrubEast:: @ 820505A
	applymovement LOCALID_WALLYS_Grub, PetalburgCity_Gym_Movement_WallysGrubExitEast
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallysGrubEast
	waitmovement 0
	return

PetalburgCity_Gym_EventScript_ExitGymWithWallysGrubWest:: @ 820506C
	applymovement LOCALID_WALLYS_Grub, PetalburgCity_Gym_Movement_WallysGrubExitWest
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerExitWithWallysGrubWest
	waitmovement 0
	return

PetalburgCity_Gym_Movement_WallysGrubExitNorth: @ 820507E
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_fastest_up
	delay_8
	walk_in_place_down
	set_invisible
	step_end

PetalburgCity_Gym_Movement_WallysGrubExitEast: @ 8205089
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_fastest_up
	delay_8
	walk_in_place_down
	set_invisible
	step_end

PetalburgCity_Gym_Movement_WallysGrubExitWest: @ 8205094
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_fastest_up
	delay_8
	walk_in_place_down
	set_invisible
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallysGrubNorth: @ 82050A1
	delay_16
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallysGrubEast: @ 82050A9
	delay_16
	walk_down
	walk_down
	walk_left
	walk_down
	walk_down
	walk_down
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallysGrubWest: @ 82050B1
	delay_16
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

PetalburgCity_Gym_Movement_WallysGrubEnterGym: @ 82050BB
	walk_up
	delay_8
	walk_in_place_fastest_right
	delay_8
	walk_in_place_fastest_left
	delay_16
	walk_in_place_fastest_up
	step_end

PetalburgCity_Gym_Movement_WallysGrubApproachPlayerNorth: @ 82050C3
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_right
	step_end

PetalburgCity_Gym_Movement_WallysGrubApproachPlayerEast: @ 82050CA
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

PetalburgCity_Gym_Movement_WallysGrubApproachPlayerWest: @ 82050D0
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	step_end

PetalburgCity_Gym_Movement_Unused: @ 82050D8
	walk_in_place_fastest_up
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_fastest_down
	step_end

PetalburgCity_Gym_Movement_WallyArriveNorth: @ 82050E1
	delay_16
	walk_up
	delay_16
	delay_8
	walk_up
	walk_right
	walk_up
	walk_up
	walk_in_place_fastest_left
	step_end

PetalburgCity_Gym_Movement_WallyArrive: @ 82050EB
	delay_16
	walk_up
	delay_16
	delay_8
	walk_up
	walk_up
	step_end

PetalburgCity_Gym_Movement_WallyExitNorth: @ 82050F2
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_fastest_up
	delay_16
	walk_in_place_down
	step_end

PetalburgCity_Gym_Movement_WallyExitEast: @ 82050FA
	walk_down
	walk_down
	walk_right
	walk_down
	walk_in_place_fastest_up
	delay_16
	walk_in_place_down
	step_end

PetalburgCity_Gym_Movement_WallyExitSouthWest: @ 8205102
	walk_down
	walk_down
	walk_down
	walk_in_place_fastest_up
	delay_16
	walk_in_place_down
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallyNorth: @ 8205109
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallySouth: @ 8205111
	delay_16
	delay_16
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallyWest: @ 820511B
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

PetalburgCity_Gym_Movement_PlayerExitWithWallyEast: @ 8205123
	walk_in_place_fastest_down
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_right
	walk_down
	delay_8
	step_end

PetalburgCity_Gym_EventScript_NoAmountOfTrainingIsEnough:: @ 820512D
	msgbox PetalburgCity_Gym_Text_GrubNoAmountOfTrainingIsEnough, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_SpeedRoomDoor:: @ 8205137
	lockall
	compare VAR_PETALBURG_GYM_STATE, 6
	goto_if_lt PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 85
	msgbox PetalburgCity_Gym_Text_EnterSpeedRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_EnterRoom:: @ 820516C
	closemessage
	delay 30
	warpdoor MAP_PETALBURG_CITY_GYM, 255, VAR_0x8008, VAR_0x8009
	waitstate
	releaseall
	end

PetalburgCity_Gym_EventScript_DontEnterRoom:: @ 820517B
	releaseall
	end

PetalburgCity_Gym_EventScript_DoorLocked:: @ 820517D
	msgbox PetalburgCity_Gym_Text_DoorAppearsLocked, MSGBOX_DEFAULT
	releaseall
	end

@ VAR_0x8008 and VAR_0x8009 below are the x and y coordinates of the warp
PetalburgCity_Gym_EventScript_AccuracyRoomDoor:: @ 8205187
	lockall
	compare VAR_PETALBURG_GYM_STATE, 6
	goto_if_lt PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 98
	msgbox PetalburgCity_Gym_Text_EnterAccuracyRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_ConfusionRoomDoor:: @ 82051BC
	lockall
	goto_if_not_defeated TRAINER_RANDALL, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 46
	msgbox PetalburgCity_Gym_Text_EnterConfusionRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftDefenseRoomDoor:: @ 82051EF
	lockall
	goto_if_not_defeated TRAINER_RANDALL, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 59
	msgbox PetalburgCity_Gym_Text_EnterDefenseRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightDefenseRoomDoor:: @ 8205222
	lockall
	goto_if_not_defeated TRAINER_MARY, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 59
	msgbox PetalburgCity_Gym_Text_EnterDefenseRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RecoveryRoomDoor:: @ 8205255
	lockall
	goto_if_not_defeated TRAINER_MARY, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 72
	msgbox PetalburgCity_Gym_Text_EnterRecoveryRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftStrengthRoomDoor:: @ 8205288
	lockall
	goto_if_not_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 20
	msgbox PetalburgCity_Gym_Text_EnterStrengthRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightStrengthRoomDoor:: @ 82052BB
	lockall
	goto_if_not_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 20
	msgbox PetalburgCity_Gym_Text_EnterStrengthRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftOHKORoomDoor:: @ 82052EE
	lockall
	goto_if_not_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 33
	msgbox PetalburgCity_Gym_Text_EnterOHKORoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightOHKORoomDoor:: @ 8205321
	lockall
	goto_if_not_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 33
	msgbox PetalburgCity_Gym_Text_EnterOHKORoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftGymLeadersRoomDoor:: @ 8205354
	lockall
	goto_if_not_defeated TRAINER_JODY, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 7
	msgbox PetalburgCity_Gym_Text_EnterGymLeadersRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightGymLeadersRoomDoor:: @ 8205387
	lockall
	goto_if_not_defeated TRAINER_BERKE, PetalburgCity_Gym_EventScript_DoorLocked
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 7
	msgbox PetalburgCity_Gym_Text_EnterGymLeadersRoom, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PetalburgCity_Gym_EventScript_EnterRoom
	compare VAR_RESULT, NO
	goto_if_eq PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_Randall:: @ 82053BA
	trainerbattle_single TRAINER_RANDALL, PetalburgCity_Gym_Text_RandallIntro, PetalburgCity_Gym_Text_RandallDefeat, PetalburgCity_Gym_EventScript_SlideOpenSpeedRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_RandallPostBadge
	msgbox PetalburgCity_Gym_Text_RandallPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenSpeedRoomDoors:: @ 82053DE
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_RandallPostBadge:: @ 82053ED
	msgbox PetalburgCity_Gym_Text_RandallPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Parker:: @ 82053F6
	trainerbattle_single TRAINER_PARKER, PetalburgCity_Gym_Text_ParkerIntro, PetalburgCity_Gym_Text_ParkerDefeat, PetalburgCity_Gym_EventScript_SlideOpenConfusionRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_ParkerPostBadge
	msgbox PetalburgCity_Gym_Text_ParkerPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenConfusionRoomDoors:: @ 820541A
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_ParkerPostBadge:: @ 8205429
	msgbox PetalburgCity_Gym_Text_ParkerPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_George:: @ 8205432
	trainerbattle_single TRAINER_GEORGE, PetalburgCity_Gym_Text_GeorgeIntro, PetalburgCity_Gym_Text_GeorgeDefeat, PetalburgCity_Gym_EventScript_SlideOpenRecoveryRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_GeorgePostBadge
	msgbox PetalburgCity_Gym_Text_GeorgePostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenRecoveryRoomDoors:: @ 8205456
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_GeorgePostBadge:: @ 8205465
	msgbox PetalburgCity_Gym_Text_GeorgePostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Berke:: @ 820546E
	trainerbattle_single TRAINER_BERKE, PetalburgCity_Gym_Text_BerkeIntro, PetalburgCity_Gym_Text_BerkeDefeat, PetalburgCity_Gym_EventScript_SlideOpenOHKORoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_BerkePostBadge
	msgbox PetalburgCity_Gym_Text_BerkePostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenOHKORoomDoors:: @ 8205492
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenOHKORoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_BerkePostBadge:: @ 82054A1
	msgbox PetalburgCity_Gym_Text_BerkePostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Mary:: @ 82054AA
	trainerbattle_single TRAINER_MARY, PetalburgCity_Gym_Text_MaryIntro, PetalburgCity_Gym_Text_MaryDefeat, PetalburgCity_Gym_EventScript_SlideOpenAccuracyRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_MaryPostBadge
	msgbox PetalburgCity_Gym_Text_MaryPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenAccuracyRoomDoors:: @ 82054CE
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_MaryPostBadge:: @ 82054DD
	msgbox PetalburgCity_Gym_Text_MaryPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Alexia:: @ 82054E6
	trainerbattle_single TRAINER_ALEXIA, PetalburgCity_Gym_Text_AlexiaIntro, PetalburgCity_Gym_Text_AlexiaDefeat, PetalburgCity_Gym_EventScript_SlideOpenDefenseRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_AlexiaPostBadge
	msgbox PetalburgCity_Gym_Text_AlexiaPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenDefenseRoomDoors:: @ 820550A
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_AlexiaPostBadge:: @ 8205519
	msgbox PetalburgCity_Gym_Text_AlexiaPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Jody:: @ 8205522
	trainerbattle_single TRAINER_JODY, PetalburgCity_Gym_Text_JodyIntro, PetalburgCity_Gym_Text_JodyDefeat, PetalburgCity_Gym_EventScript_SlideOpenStrengthRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_JodyPostBadge
	msgbox PetalburgCity_Gym_Text_JodyPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenStrengthRoomDoors:: @ 8205546
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_JodyPostBadge:: @ 8205555
	msgbox PetalburgCity_Gym_Text_JodyPostBadge, MSGBOX_NPC
	end

@ VAR_0x8004 below is the room number
@ VAR_0x8005 below is 0 when the door should be slid open and 1 when it should be unlocked immediately
PetalburgCity_Gym_EventScript_OpenGymEntranceDoors:: @ 820555E
	setvar VAR_0x8004, 1
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetEntranceRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors:: @ 820557F
	setvar VAR_0x8004, 2
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetSpeedRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors:: @ 82055A0
	setvar VAR_0x8004, 3
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetAccuracyRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors:: @ 82055C1
	setvar VAR_0x8004, 4
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetConfusionRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors:: @ 82055E2
	setvar VAR_0x8004, 5
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetDefenseRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors:: @ 8205603
	setvar VAR_0x8004, 6
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetRecoveryRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors:: @ 8205624
	setvar VAR_0x8004, 7
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetStrengthRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenOHKORoomDoors:: @ 8205645
	setvar VAR_0x8004, 8
	compare VAR_0x8005, 0
	call_if_eq PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	compare VAR_0x8005, 1
	call_if_eq PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetOHKORoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_SetEntranceRoomDoorMetatiles:: @ 8205666
	setmetatile 6, 85, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 7, 85, METATILE_PetalburgGym_RoomEntrance_Right, 0
	setmetatile 1, 98, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 2, 98, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SetSpeedRoomDoorMetatiles:: @ 820568B
	setmetatile 6, 46, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 7, 46, METATILE_PetalburgGym_RoomEntrance_Right, 0
	setmetatile 1, 59, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 2, 59, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SetAccuracyRoomDoorMetatiles:: @ 82056B0
	setmetatile 6, 59, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 7, 59, METATILE_PetalburgGym_RoomEntrance_Right, 0
	setmetatile 1, 72, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 2, 72, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SetConfusionRoomDoorMetatiles:: @ 82056D5
	setmetatile 1, 20, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 2, 20, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SetDefenseRoomDoorMetatiles:: @ 82056E8
	setmetatile 6, 20, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 7, 20, METATILE_PetalburgGym_RoomEntrance_Right, 0
	setmetatile 1, 33, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 2, 33, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SetRecoveryRoomDoorMetatiles:: @ 820570D
	setmetatile 6, 33, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 7, 33, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SetStrengthRoomDoorMetatiles:: @ 8205720
	setmetatile 1, 7, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 2, 7, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SetOHKORoomDoorMetatiles:: @ 8205733
	setmetatile 6, 7, METATILE_PetalburgGym_RoomEntrance_Left, 0
	setmetatile 7, 7, METATILE_PetalburgGym_RoomEntrance_Right, 0
	return

PetalburgCity_Gym_EventScript_SlideOpenRoomDoors:: @ 8205746
	special PetalburgGymSlideOpenRoomDoors
	waitstate
	return

PetalburgCity_Gym_EventScript_UnlockRoomDoors:: @ 820574B
	special PetalburgGymUnlockRoomDoors
	return

PetalburgCity_Gym_EventScript_GymGuide:: @ 820574F
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_GymGuidePostVictory
	goto_if_set FLAG_PETALBURG_GYM_CHILAN_BERRIES, PetalburgCity_Gym_EventScript_GymGuide2
	msgbox PetalburgCity_Gym_Text_GymGuideAdvice1, MSGBOX_DEFAULT
	giveitem ITEM_CHILAN_BERRY, 15
	setflag FLAG_PETALBURG_GYM_CHILAN_BERRIES
	msgbox PetalburgCity_Gym_Text_GymGuideAdvice2, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_GymGuide2::
	msgbox PetalburgCity_Gym_Text_GymGuideAdvice2, MSGBOX_DEFAULT
	release
	end	

PetalburgCity_Gym_EventScript_GymGuidePostVictory:: @ 8205764
	msgbox PetalburgCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_LeftGymStatue:: @ 820576E
	lockall
	goto_if_set FLAG_BADGE05_GET, PetalburgCity_Gym_EventScript_GymStatueCertified
	goto PetalburgCity_Gym_EventScript_GymStatue
	end

PetalburgCity_Gym_EventScript_RightGymStatue:: @ 820577E
	lockall
	goto_if_set FLAG_BADGE05_GET, PetalburgCity_Gym_EventScript_GymStatueCertified
	goto PetalburgCity_Gym_EventScript_GymStatue
	end

PetalburgCity_Gym_EventScript_GymStatueCertified:: @ 820578E
	msgbox PetalburgCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

PetalburgCity_Gym_EventScript_GymStatue:: @ 8205798
	msgbox PetalburgCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

PetalburgCity_Gym_Text_GrubYoureHereWithYourPokemon: @ 82057A2
	.string "Grub: Hm?\p"
	.string "Well, if it isn't {PLAYER}!\n"
	.string "So you're all finished moving in?\p"
	.string "I'm surprised that you managed to\n"
	.string "get here by yourself.\p"
	.string "Oh, I see.\n"
	.string "You're with your Pokémon.\p"
	.string "Hm… Then I guess you're going to\n"
	.string "become a Trainer like me, {PLAYER}.\p"
	.string "That's great news!\n"
	.string "I'll be looking forward to it!$"

PetalburgCity_Gym_Text_WallyIdLikeAPokemon: @ 82058B1
	.string "Um… I…\n"
	.string "I'd like to get a Pokémon, please…$"

PetalburgCity_Gym_Text_GrubOhYoureWallyRight: @ 82058DB
	.string "Grub: Hm? You're… Uh… Oh, right.\n"
	.string "You're Wally, right?$"

PetalburgCity_Gym_Text_WallyIveNeverCaughtAPokemon: @ 8205910
	.string "Wally: I'm going to go stay with my\n"
	.string "relatives in Verdanturf Town.\p"
	.string "I thought I would be lonely by myself,\n"
	.string "so I wanted to take a Pokémon along.\p"
	.string "But I've never caught a Pokémon before.\n"
	.string "I don't know how…$"

PetalburgCity_Gym_Text_GrubHmISee: @ 82059D8
	.string "Grub: Hm. I see.$"

PetalburgCity_Gym_Text_GrubPlayerGoWithWally: @ 82059E8
	.string "Grub: {PLAYER}, you heard that,\n"
	.string "right?\p"
	.string "Go with Wally and make sure that he\n"
	.string "safely catches a Pokémon.$"

PetalburgCity_Gym_Text_IllLoanYouMyZigzagoon: @ 8205A46
	.string "Wally, here, I'll loan you my Pokémon.\p"
	.string "Wally received a Zigzagoon!$"

PetalburgCity_Gym_Text_WallyThankYouAndGrubGivesPokeBall: @ 8205A89
	.string "Wally: Oh, wow!\n"
	.string "A Pokémon!\p"
	.string "Grub: Hm. I'll give you a Poké Ball, too.\n"
	.string "Go for it!\p"
	.string "Wally received a Poké Ball!$"

PetalburgCity_Gym_Text_WallyOhWowThankYou: @ 8205AF4
	.string "Wally: Oh, wow!\n"
	.string "Thank you!$"

PetalburgCity_Gym_Text_WouldYouReallyComeWithMe: @ 8205B0F
	.string "{PLAYER}… Would you really come\n"
	.string "with me?$"

PetalburgCity_Gym_Text_GrubSoDidItWorkOut: @ 8205B32
	.string "Grub: So, did it work out?$"

PetalburgCity_Gym_Text_WallyThankYouBye: @ 8205B4C
	.string "Wally: Thank you, yes, it did.\n"
	.string "Here's your Pokémon back.\p"
	.string "{PLAYER}, thank you for coming along\n"
	.string "with me.\p"
	.string "You two are why I was able to catch\n"
	.string "my Pokémon.\p"
	.string "I promise I'll take really good\n"
	.string "care of it.\p"
	.string "Oh! My mom's waiting for me,\n"
	.string "so I have to go!\p"
	.string "Bye, {PLAYER}!$"

PetalburgCity_Gym_Text_GrubGoCollectBadges: @ 8205C40
	.string "Grub: Now…\p"
	.string "{PLAYER}, if you want to become a\n"
	.string "strong Trainer, here's my advice.\p"
	.string "Head for Rustboro City beyond this\n"
	.string "town.\p"
	.string "There, you should challenge\n"
	.string "the Gym Leader, Roxanne.\p"
	.string "After her, go on to other Pokémon\n"
	.string "Gyms and defeat their Leaders.\p"
	.string "Collect Badges from them,\n"
	.string "understood?\p"
	.string "Of course, I'm a Gym Leader, too.\n"
	.string "We'll battle one day, {PLAYER}.\p"
	.string "But that's only after you become\n"
	.string "stronger.$"

PetalburgCity_Gym_Text_GrubGoToRustboro: @ 8205DB4
	.string "Grub: Hm? Aren't you going to the\n"
	.string "Pokémon Gym in Rustboro City?\p"
	.string "There's no challenge for me to\n"
	.string "battle a greenhorn Trainer.\p"
	.string "{PLAYER}, I want you to challenge me\n"
	.string "when you become a lot stronger.\p"
	.string "I'll battle you, {PLAYER}, when you\n"
	.string "can show me four Gym Badges, okay?$"

PetalburgCity_Gym_Text_GrubGoToDewford: @ 8205EAE
	.string "Grub: I see… So, you've beaten\n"
	.string "the Gym Leader in Rustboro City.\p"
	.string "But there are many more Trainers\n"
	.string "who are stronger than you, {PLAYER}.\p"
	.string "Across the sea in Dewford Town is a\n"
	.string "Gym Leader named Brawly.\p"
	.string "You should go challenge him.$"

PetalburgCity_Gym_Text_YouHaveGottenStronger: @ 8205F87
	.string "Grub: Hm… {PLAYER}, you have gotten\n"
	.string "stronger.\p"
	.string "I can tell by the number of Badges\n"
	.string "that you've earned.$"

PetalburgCity_Gym_Text_GrubIntro: @ 8205FE5
	.string "Grub: Hm…\n"
	.string "So, you did get four Gym Badges.\p"
	.string "Fine, as I promised, we will have\n"
	.string "a Pokémon battle.\p"
	.string "But first, let me give you this.$"

PetalburgCity_Gym_Text_GrubMegaBracelet:
	.string "That Mega Bracelet will allow certain\n"
	.string "Pokémon to Mega Evolve in battle.\p"
	.string "It's no good on its own, though.\p"
	.string "To Mega Evolve a Pokémon, you must\n"
	.string "also let it hold its Mega Stone.\p"
	.string "Then, press START before choosing a\n"
	.string "move.\p"
	.string "Mega Evolution is a very powerful\n"
	.string "technique, but I think you and your\l"
	.string "Pokémon are ready for it.\p"
	.string "If you can, give it a try in our\n"
	.string "battle!\p"
	.string "Here, take these Mega Stones too.$"

PetalburgCity_Gym_Text_GrubWheneverReady:
	.string "Now then, {PLAYER}!\n"
	.string "I'm ready when you are!$"

PetalburgCity_Gym_Text_GrubBattleIntro:
	.string "{PLAYER}…\p"
	.string "I'm so happy that I can have\n"
	.string "a real battle with my own child.\p"
	.string "But, a battle is a battle!\p"
	.string "I will do everything in my power as\n"
	.string "a Gym Leader to win.\p"
	.string "{PLAYER}, you'd better give it your\n"
	.string "best shot, too!$"

PetalburgCity_Gym_Text_GrubDefeat: @ 8206107
	.string "…\p"
	.string "I… I can't…\p"
	.string "I can't believe it. {PLAYER}…\p"
	.string "I lost to {PLAYER}?\p"
	.string "But, rules are rules!\n"
	.string "Here, take this.$"

PetalburgCity_Gym_Text_ReceivedBalanceBadge: @ 8206162
	.string "{PLAYER} received the Balance Badge\n"
	.string "from Grub!$"

PetalburgCity_Gym_Text_ExplainBalanceBadgeTakeThis: @ 820618A
	.string "Grub: With that Badge, Pokémon that\n"
	.string "know the HM move Surf will be able\l"
	.string "to travel over water.\p"
	.string "If you like, you can borrow my Exploud\n"
	.string "to Surf if you don't want to teach the\l"
	.string "move to any of your own Pokémon.\p"
	.string "… … … … … …$"

PetalburgCity_Gym_Text_RegisteredExploud: @ 81FF517
	.string "Registered Grub's Exploud\n"
	.string "in the PokéNav.$"

PetalburgCity_Gym_Text_TakeThis:
	.string "This is my gift to you. {PLAYER}, I'm\n"
	.string "sure you can use it correctly.$"

PetalburgCity_Gym_Text_ExplainFacade: @ 8206254
	.string "Grub: TM42 contains Facade.\p"
	.string "It doubles in power if the Pokémon\n"
	.string "is poisoned, paralyzed, or burned.\p"
	.string "It might be able to turn a bad\n"
	.string "situation into an advantage.$"

PetalburgCity_Gym_Text_GrubHappyAndSad: @ 82062FB
	.string "Grub: As the Gym Leader, I can't\n"
	.string "express how upset I am…\p"
	.string "But as a father, it makes me both\n"
	.string "happy and a little sad. It's odd…$"

PetalburgCity_Gym_Text_PleaseComeWithMe: @ 8206377
	.string "Ah, there you are, {PLAYER}{KUN}!\p"
	.string "Please come with me.\n"
	.string "I have something I want you to have.$"

PetalburgCity_Gym_Text_LetMeBorrowPlayer: @ 82063CA
	.string "Grub, you don't mind, do you?\p"
	.string "Let me borrow your {PLAYER}{KUN} for\n"
	.string "a minute or two.$"

PetalburgCity_Gym_Text_GrubGoingToKeepTraining: @ 8206417
	.string "Grub: {PLAYER}, you should go visit\n"
	.string "your mother every so often.\p"
	.string "I'm going to stay here and redouble\n"
	.string "my training.\p"
	.string "It would bother me as a Trainer to\n"
	.string "not avenge my loss to you, {PLAYER}!$"

PetalburgCity_Gym_Text_GrubNoAmountOfTrainingIsEnough: @ 82064C3
	.string "Grub: {PLAYER}, how are things going?\p"
	.string "The world of Pokémon is deep.\p"
	.string "I honestly think that no amount of\n"
	.string "training would ever be enough.$"

PetalburgCity_Gym_Text_GymGuideAdvice1: @ 8206542
	.string "Hey, how's it going, Champion-\n"
	.string "bound {PLAYER}?\p"
	.string "Please, take these Chilan Berries\n"
	.string "to help with your challenge.$"

PetalburgCity_Gym_Text_GymGuideAdvice2:
	.string "The doors in this Gym open when you\n"
	.string "beat the awaiting Trainers.\p"
	.string "Whoops! The doors in this room are\n"
	.string "already open, so don't attack me!\p"
	.string "The door at the left leads to\n"
	.string "the Speed Room.\p"
	.string "The door at the right leads to\n"
	.string "the Accuracy Room.\p"
	.string "The room's name will be on\n"
	.string "the door, so choose carefully.\p"
	.string "Once you've chosen the door…\n"
	.string "Well, hey, go for it!\p"
	.string "Oh, and your Grub's got something\n"
	.string "special for you once you reach him!$"

PetalburgCity_Gym_Text_GymGuidePostVictory: @ 82066F3
	.string "{PLAYER}! Whoa! You've overcome even\n"
	.string "your own father!\p"
	.string "Like, whoa!\n"
	.string "What a stunning turn of events!$"

PetalburgCity_Gym_Text_RandallIntro: @ 820674F
	.string "The ability to attack before the\n"
	.string "opponent…\p"
	.string "Just that alone puts me at a great\n"
	.string "advantage, don't you agree?$"

PetalburgCity_Gym_Text_RandallDefeat: @ 82067B9
	.string "That was a magnificent battle!$"

PetalburgCity_Gym_Text_RandallPostBattle: @ 82067D8
	.string "Go on to the next room where a new\n"
	.string "challenge awaits you.\p"
	.string "At the left is the Confusion Room.\p"
	.string "The right door leads to the Defense\n"
	.string "Room.$"

PetalburgCity_Gym_Text_RandallPostBadge: @ 820685E
	.string "Whomever you beat, and whomever you\n"
	.string "may lose to, you never shirk from\l"
	.string "training yourself and your Pokémon.\p"
	.string "That's what I think being a\n"
	.string "Gym Leader is all about.$"

PetalburgCity_Gym_Text_ParkerIntro: @ 82068FD
	.string "This is the Confusion Room.\p"
	.string "Let me see how well bonded you are\n"
	.string "with your Pokémon!$"

PetalburgCity_Gym_Text_ParkerDefeat: @ 820694F
	.string "I couldn't confuse your team enough…\n"
	.string "You share a strong bond together.$"

PetalburgCity_Gym_Text_ParkerPostBattle: @ 8206996
	.string "The next room is the Strength Room.\n"
	.string "Can you withstand brute force?$"

PetalburgCity_Gym_Text_ParkerPostBadge: @ 82069D9
	.string "After you beat our Leader, the\n"
	.string "training has become a lot tougher.$"

PetalburgCity_Gym_Text_GeorgeIntro: @ 8206A1B
	.string "Just when you think you're going to\n"
	.string "win, your opponent restores HP…\p"
	.string "Can you just imagine how awful that\n"
	.string "must feel?\p"
	.string "I'll show you exactly how awful it\n"
	.string "feels!$"

PetalburgCity_Gym_Text_GeorgeDefeat: @ 8206AB8
	.string "I couldn't restore HP enough…\n"
	.string "What Attack power…$"

PetalburgCity_Gym_Text_GeorgePostBattle: @ 8206AE9
	.string "I should have expected no less from\n"
	.string "our Leader's kid.\p"
	.string "No, wait! A Trainer's abilities are\n"
	.string "earned only through effort.\p"
	.string "I lost because my own efforts\n"
	.string "weren't enough.\p"
	.string "Go on! The One-Hit KO Room is next.$"

PetalburgCity_Gym_Text_GeorgePostBadge: @ 8206BB1
	.string "I'm going to keep training at Gyms.\n"
	.string "One day, I'll become a Leader.$"

PetalburgCity_Gym_Text_BerkeIntro: @ 8206BF4
	.string "I'm not going to take it easy just\n"
	.string "because you're our Leader's kid.\p"
	.string "I'll show you how horrid it is for\n"
	.string "a Pokémon to take a critical hit!$"

PetalburgCity_Gym_Text_BerkeDefeat: @ 8206C7D
	.string "Your power…\n"
	.string "You're the real deal.$"

PetalburgCity_Gym_Text_BerkePostBattle: @ 8206C9F
	.string "Your father really is strong.\n"
	.string "He's a Trainer worth my respect.\p"
	.string "And, I sense the same glow coming\n"
	.string "from you as your father.\p"
	.string "I hope that you'll stage a terrific\n"
	.string "battle with your father!$"

PetalburgCity_Gym_Text_BerkePostBadge: @ 8206D56
	.string "Since your Grub became the Leader,\n"
	.string "the Trainers of Petalburg City have\l"
	.string "become a lot tougher.$"

PetalburgCity_Gym_Text_MaryIntro: @ 8206DB2
	.string "Giggle…\n"
	.string "This is the Accuracy Room.\p"
	.string "It's pretty nasty when every attack\n"
	.string "lands without fail.$"

PetalburgCity_Gym_Text_MaryDefeat: @ 8206E0D
	.string "You were a cut above me…$"

PetalburgCity_Gym_Text_MaryPostBattle: @ 8206E26
	.string "There are some even stronger\n"
	.string "Trainers waiting for you.\p"
	.string "The left is the Defense Room, and\n"
	.string "the right is the Recovery Room.\p"
	.string "Your Pokémon's Attack power will be\n"
	.string "on trial either way.$"

PetalburgCity_Gym_Text_MaryPostBadge: @ 8206ED8
	.string "Do you know what we're trying to\n"
	.string "achieve as Trainers?\p"
	.string "We're striving to become soul mates\n"
	.string "with our Pokémon.$"

PetalburgCity_Gym_Text_AlexiaIntro: @ 8206F44
	.string "The higher the Defense, the more\n"
	.string "reckless I can be in attack.$"

PetalburgCity_Gym_Text_AlexiaDefeat: @ 8206F82
	.string "Our defenses weren't enough…$"

PetalburgCity_Gym_Text_AlexiaPostBattle: @ 8206F9F
	.string "I think you've taught me a valuable\n"
	.string "lesson here.\p"
	.string "Now, go on! The left door goes to\n"
	.string "the Strength Room.\p"
	.string "The right door opens to\n"
	.string "the One-Hit KO Room.\p"
	.string "Both of them have Trainers who are\n"
	.string "skilled at offense.$"

PetalburgCity_Gym_Text_AlexiaPostBadge: @ 8207069
	.string "Hi! Have you tried using Surf?$"

PetalburgCity_Gym_Text_JodyIntro: @ 8207088
	.string "Our Gym Leader told us to go all out\n"
	.string "and beat you.\p"
	.string "Even if you happen to be the\n"
	.string "Leader's kid!$"

PetalburgCity_Gym_Text_JodyDefeat: @ 82070E6
	.string "But… I went all out!$"

PetalburgCity_Gym_Text_JodyPostBattle: @ 82070FB
	.string "The way you use your Pokémon…\n"
	.string "It's like your father's style.\p"
	.string "Go on through! The Gym Leader, your\n"
	.string "father, is waiting!$"

PetalburgCity_Gym_Text_JodyPostBadge: @ 8207170
	.string "Sure, it's fine to make your Pokémon\n"
	.string "stronger.\p"
	.string "But what decides the winner?\p"
	.string "Why, it's the feelings Trainers have\n"
	.string "for their Pokémon.$"

PetalburgCity_Gym_Text_DoorAppearsLocked: @ 82071F4
	.string "This door appears to be locked\n"
	.string "right now…$"

PetalburgCity_Gym_Text_EnterSpeedRoom: @ 820721E
	.string "“Speed Room,” the sign says.\p"
	.string "Do you want to go through?$"

@ Unused
PetalburgCity_Gym_Text_DoorAppearsLocked2: @ 8207256
	.string "This door appears to be locked\n"
	.string "right now…$"

PetalburgCity_Gym_Text_EnterAccuracyRoom: @ 8207280
	.string "“Accuracy Room,” the sign says.\p"
	.string "Do you want to go through?$"

PetalburgCity_Gym_Text_EnterConfusionRoom: @ 82072BB
	.string "“Confusion Room,” the sign says.\p"
	.string "Do you want to go through?$"

PetalburgCity_Gym_Text_EnterDefenseRoom: @ 82072F7
	.string "“Defense Room,” the sign says.\p"
	.string "Do you want to go through?$"

PetalburgCity_Gym_Text_EnterRecoveryRoom: @ 8207331
	.string "“Recovery Room,” the sign says.\p"
	.string "Do you want to go through?$"

PetalburgCity_Gym_Text_EnterStrengthRoom: @ 820736C
	.string "“Strength Room,” the sign says.\p"
	.string "Do you want to go through?$"

PetalburgCity_Gym_Text_EnterOHKORoom: @ 82073A7
	.string "“One-Hit Ko Room,” the sign says.\p"
	.string "Do you want to go through?$"

PetalburgCity_Gym_Text_EnterGymLeadersRoom: @ 82073E4
	.string "“Gym Leader's Room.”\p"
	.string "“See for yourself what Pokémon await\n"
	.string "you!” the sign says.\p"
	.string "Do you want to go through?$"

PetalburgCity_Gym_Text_GymStatue: @ 820744C
	.string "Petalburg City Pokémon Gym$"

PetalburgCity_Gym_Text_GymStatueCertified: @ 8207467
	.string "Petalburg City Pokémon Gym\p"
	.string "Grub's Certified Trainers:\n"
	.string "{PLAYER}$"

PetalburgCity_Gym_Text_GrubPreRematch: @ 82074A2
	.string "Because we are parent and child,\n"
	.string "we owe it to each other to do the best\l"
	.string "we can. Isn't that right, {PLAYER}?$"

PetalburgCity_Gym_Text_GrubRematchDefeat: @ 82075CE
	.string "Uh… Haha…\n"
	.string "Maybe that was going too hard…$"

PetalburgCity_Gym_Text_GrubPostRematch: @ 82075F7
	.string "Grub: {PLAYER}…\n"
	.string "What is your dream?\p"
	.string "My dream…\n"
	.string "Hahaha…\l"
	.string "It has already come true, actually.$"

PetalburgCity_Gym_Text_GrubRematchNeedTwoMons: @ 820764A
	.string "Grub: Hm? Wait a second, {PLAYER}.\p"
	.string "Do you only have one Pokémon that is\n"
	.string "capable of battle?\p"
	.string "Sorry, but you'll have to come back\n"
	.string "with at least two Pokémon.$"

PetalburgCity_Gym_Text_GrubChooseFormat:
	.string "Grub: {PLAYER}…\n"
	.string "I had a feeling that you would come.\p"
	.string "I would never refuse to accept\n"
	.string "a challenge from you.\p"
	.string "You do understand, don't you?\p"
	.string "Inside a Gym, it doesn't matter that\n"
	.string "we are a parent and child.\p"
	.string "I'll let you set the rules for our\n"
	.string "rematch.\p"
	.string "So what'll it be: a single battle,\n"
	.string "or a double battle?$"

PetalburgCity_Gym_Text_GrubAllowLegends:
	.string "Grub: Do you want to try battling my\n"
	.string "Legendary Pokémon?$"
