.set LOCALID_GuyS_DAD, 1

PetalburgCity_GuysHouse_MapScripts:: @ 8204229
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_GuysHouse_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgCity_GuysHouse_OnWarp
	.byte 0

PetalburgCity_GuysHouse_OnWarp: @ 8204234
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_GuysHouse_EventScript_PlayerGuysDadFaceEachOther
	.2byte 0

PetalburgCity_GuysHouse_EventScript_PlayerGuysDadFaceEachOther:: @ 820423E
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	turnobject LOCALID_GuyS_DAD, DIR_WEST
	end

PetalburgCity_GuysHouse_OnFrame: @ 8204247
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_GuysHouse_EventScript_GiveHM03Surf
	.2byte 0

PetalburgCity_GuysHouse_EventScript_GiveHM03Surf:: @ 8204251
	lockall
	msgbox PetalburgCity_GuysHouse_Text_PleaseExcuseUs, MSGBOX_DEFAULT
	giveitem ITEM_HM03_SURF
	setflag FLAG_RECEIVED_HM03
	msgbox PetalburgCity_GuysHouse_Text_SurfGoAllSortsOfPlaces, MSGBOX_DEFAULT
	setvar VAR_PETALBURG_CITY_STATE, 5
	releaseall
	end

PetalburgCity_GuysHouse_EventScript_GuysDad:: @ 8204278
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_Guy_VICTORY_ROAD, PetalburgCity_GuysHouse_EventScript_DefeatedGuyInVictoryRoad
	goto_if_set FLAG_RECEIVED_HM03, PetalburgCity_GuysHouse_EventScript_ReceievedHM03Surf
	goto_if_set FLAG_THANKED_FOR_PLAYING_WITH_Guy, PetalburgCity_GuysHouse_EventScript_PlayedWithGuy
	msgbox PetalburgCity_GuysHouse_Text_ThanksForPlayingWithGuy, MSGBOX_DEFAULT
	setflag FLAG_THANKED_FOR_PLAYING_WITH_Guy
	release
	end

PetalburgCity_GuysHouse_EventScript_ReceievedHM03Surf:: @ 82042A2
	msgbox PetalburgCity_GuysHouse_Text_GuyIsComingHomeSoon, MSGBOX_DEFAULT
	release
	end

PetalburgCity_GuysHouse_EventScript_DefeatedGuyInVictoryRoad:: @ 82042AC
	msgbox PetalburgCity_GuysHouse_Text_YouMetGuyInEverGrandeCity, MSGBOX_DEFAULT
	release
	end

PetalburgCity_GuysHouse_EventScript_PlayedWithGuy:: @ 82042B6
	msgbox PetalburgCity_GuysHouse_Text_WonderHowGuyIsDoing, MSGBOX_DEFAULT
	release
	end

PetalburgCity_GuysHouse_EventScript_GuysMom:: @ 82042C0
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM03, PetalburgCity_GuysHouse_EventScript_ReceivedHM03Surf
	msgbox PetalburgCity_GuysHouse_Text_GuyWasReallyHappy, MSGBOX_DEFAULT
	release
	end

PetalburgCity_GuysHouse_EventScript_ReceivedHM03Surf:: @ 82042D5
	msgbox PetalburgCity_GuysHouse_Text_GuyLeftWithoutTelling, MSGBOX_DEFAULT
	release
	end

PetalburgCity_GuysHouse_Text_ThanksForPlayingWithGuy: @ 82042DF
	.string "You're…\n"
	.string "Ah, you must be {PLAYER}{KUN}, right?\p"
	.string "Thank you for playing with Guy a\n"
	.string "little while ago.\p"
	.string "He's been frail and sickly ever\n"
	.string "since he was a baby.\p"
	.string "We've sent him to stay with my relatives\n"
	.string "in Verdanturf Town for a while.\p"
	.string "The air is a lot cleaner there\n"
	.string "than it is here.\p"
	.string "What's that? Where's Guy?\n"
	.string "He's already left, our Guy.\p"
	.string "I wonder where he could have\n"
	.string "gotten by now?$"

PetalburgCity_GuysHouse_Text_WonderHowGuyIsDoing: @ 820444D
	.string "I wonder how our Guy is doing?$"

PetalburgCity_GuysHouse_Text_PleaseExcuseUs: @ 820446E
	.string "{PLAYER}{KUN}! Please excuse us for\n"
	.string "dragging you here this way.\p"
	.string "But our Guy's become very healthy\n"
	.string "since he went to Verdanturf Town.\p"
	.string "We owe it all to you!\p"
	.string "When Guy left town, you helped\n"
	.string "him catch a Pokémon, right?\p"
	.string "I think that made Guy really\n"
	.string "happy.\p"
	.string "Actually, not just Guy.\n"
	.string "It made me, his father, happy too.\p"
	.string "Happy that he's gained such a great\n"
	.string "friend as you.\p"
	.string "This isn't a bribe or anything, but\n"
	.string "I'd really like you to have this.$"

PetalburgCity_GuysHouse_Text_SurfGoAllSortsOfPlaces: @ 820461A
	.string "If your Pokémon can Surf, you'll be\n"
	.string "able to go to all sorts of places.$"

PetalburgCity_GuysHouse_Text_GuyIsComingHomeSoon: @ 8204661
	.string "Guy's coming home soon.\n"
	.string "I'm looking forward to that.$"

PetalburgCity_GuysHouse_Text_YouMetGuyInEverGrandeCity: @ 8204698
	.string "Oh? You met Guy in\n"
	.string "Ever Grande City?\p"
	.string "Oh, {PLAYER}{KUN}, don't be silly.\p"
	.string "He may have gotten healthy, but he\n"
	.string "can't go somewhere far away like\l"
	.string "that all by himself.$"

PetalburgCity_GuysHouse_Text_GuyWasReallyHappy: @ 8204732
	.string "Guy was really happy when he told\n"
	.string "us that he caught a Pokémon.\p"
	.string "It's been ages since I've seen him\n"
	.string "smile like that.$"

PetalburgCity_GuysHouse_Text_GuyLeftWithoutTelling: @ 82047A7
	.string "I want you to keep this a secret\n"
	.string "from my husband…\p"
	.string "But our Guy left Verdanturf Town\n"
	.string "without telling anyone.\p"
	.string "You know, Guy is frail, but\n"
	.string "he's surprisingly strong-willed.\p"
	.string "I'm sure that he'll come back safe\n"
	.string "and sound one day!$"

