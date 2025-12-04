ChronosMeadow_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, ChronosMeadow_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, ChronosMeadow_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, ChronosMeadow_OnWarp
	.byte 0

ChronosMeadow_OnResume::
	call_if_set FLAG_SYS_SPECIAL_WILD_BATTLE, ChronosMeadow_EventScript_TryRemoveCelebi
	end

ChronosMeadow_EventScript_TryRemoveCelebi::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, EventScript_Return
	removeobject VAR_LAST_TALKED
	return

ChronosMeadow_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_CHRONOS_ISLE
	setflag FLAG_SYS_SEVII_MAP_CHRONOS
	call_if_unset FLAG_FOUGHT_CELEBI, ChronosMeadow_EventScript_ShowCelebi
	call_if_eq VAR_MAP_SCENE_CHRONOS_ISLE, 1, ChronosMeadow_EventScript_HideBrendan
	end

ChronosMeadow_EventScript_HideBrendan::
	setflag FLAG_TEMP_2
	return

ChronosMeadow_EventScript_ShowCelebi::
	clearflag FLAG_HIDE_CELEBI
	return

ChronosMeadow_OnWarp::
	map_script_2 VAR_TEMP_0, 0, ChronosMeadow_EventScript_TurnPlayerNorth
	.2byte 0

ChronosMeadow_EventScript_TurnPlayerNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	setvar VAR_TEMP_0, 1
	end

ChronosMeadow_EventScript_Celebi::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CELEBI, CRY_MODE_ENCOUNTER
	message ChronosMeadow_Text_Celebi
	waitmessage
	waitmoncry
	delay 20
	playbgm MUS_ENCOUNTER_GYM_LEADER, 0
	waitbuttonpress
	setwildbattle SPECIES_CELEBI, 50
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	special StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, ChronosMeadow_EventScript_DefeatedCelebi
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, ChronosMeadow_EventScript_RanFromCelebi
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, ChronosMeadow_EventScript_RanFromCelebi
	setflag FLAG_FOUGHT_CELEBI
	release
	end

ChronosMeadow_EventScript_DefeatedCelebi::
	setflag FLAG_FOUGHT_CELEBI
	goto EventScript_RemoveStaticMon
	end

ChronosMeadow_EventScript_RanFromCelebi::
	setvar VAR_0x8004, SPECIES_CELEBI
	goto EventScript_MonFlewAway
	end

ChronosMeadow_EventScript_BrendanBattle::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, ChronosMeadow_Movement_PlayerFaceSouth
	waitmovement 0
	delay 30
	clearflag FLAG_TEMP_2
	addobject 2
	playbgm MUS_ENCOUNTER_RIVAL, 0
	applymovement 2, ChronosMeadow_Movement_BrendanApproach
	waitmovement 0
	msgbox ChronosMeadow_Text_BrendanNoWay, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_BRENDAN_CHRONOS_MEADOW, ChronosMeadow_Text_BrendanDefeat
	msgbox ChronosMeadow_Text_BrendanPostBattle, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RIVAL_EXIT, 0
	applymovement 2, ChronosMeadow_Movement_BrendanLeave
	waitmovement 0
	fadedefaultbgm
	setflag FLAG_TEMP_2
	removeobject 2
	setvar VAR_MAP_SCENE_CHRONOS_ISLE, 2
	releaseall
	end

ChronosMeadow_EventScript_BrendanBattleLeft::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, ChronosMeadow_Movement_PlayerFaceSouth
	waitmovement 0
	delay 30
	clearflag FLAG_TEMP_2
	addobject 2
	playbgm MUS_ENCOUNTER_RIVAL, 0
	applymovement 2, ChronosMeadow_Movement_BrendanApproachLeft
	waitmovement 0
	msgbox ChronosMeadow_Text_BrendanNoWay, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_BRENDAN_CHRONOS_MEADOW, ChronosMeadow_Text_BrendanDefeat
	msgbox ChronosMeadow_Text_BrendanPostBattle, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RIVAL_EXIT, 0
	applymovement 2, ChronosMeadow_Movement_BrendanLeaveLeft
	waitmovement 0
	fadedefaultbgm
	setflag FLAG_TEMP_2
	removeobject 2
	setvar VAR_MAP_SCENE_CHRONOS_ISLE, 2
	releaseall
	end

ChronosMeadow_EventScript_BrendanBattleRight::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, ChronosMeadow_Movement_PlayerFaceSouth
	waitmovement 0
	delay 30
	clearflag FLAG_TEMP_2
	addobject 2
	playbgm MUS_ENCOUNTER_RIVAL, 0
	applymovement 2, ChronosMeadow_Movement_BrendanApproachRight
	waitmovement 0
	msgbox ChronosMeadow_Text_BrendanNoWay, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_BRENDAN_CHRONOS_MEADOW, ChronosMeadow_Text_BrendanDefeat
	msgbox ChronosMeadow_Text_BrendanPostBattle, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_RIVAL_EXIT, 0
	applymovement 2, ChronosMeadow_Movement_BrendanLeaveRight
	waitmovement 0
	fadedefaultbgm
	setflag FLAG_TEMP_2
	removeobject 2
	setvar VAR_MAP_SCENE_CHRONOS_ISLE, 2
	releaseall
	end

ChronosMeadow_Movement_PlayerFaceSouth::
	face_down
	step_end

ChronosMeadow_Movement_BrendanApproach::
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

ChronosMeadow_Movement_BrendanLeave::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

ChronosMeadow_Movement_BrendanApproachLeft::
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

ChronosMeadow_Movement_BrendanLeaveLeft::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

ChronosMeadow_Movement_BrendanApproachRight::
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

ChronosMeadow_Movement_BrendanLeaveRight::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	step_end

ChronosMeadow_EventScript_ItemProtein::
	finditem ITEM_PROTEIN
	end

ChronosMeadow_EventScript_ItemPPMax::
	finditem ITEM_PP_MAX
	end

ChronosMeadow_EventScript_ItemRareCandy::
	finditem ITEM_RARE_CANDY
	end

ChronosMeadow_EventScript_ItemMaxRevive::
	finditem ITEM_MAX_REVIVE
	end

ChronosMeadow_EventScript_Healer::
	lock
	faceplayer
	msgbox ChronosMeadow_Text_HealerOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ChronosMeadow_EventScript_HealerDecline
	msgbox ChronosMeadow_Text_HealerAccept, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_WHITE
	special HealPlayerParty
	fadescreen FADE_FROM_WHITE
	msgbox ChronosMeadow_Text_HealerHealed, MSGBOX_DEFAULT
	release
	end

ChronosMeadow_EventScript_HealerDecline::
	msgbox ChronosMeadow_Text_HealerDecline, MSGBOX_DEFAULT
	release
	end

ChronosMeadow_EventScript_Kaj::
	trainerbattle_single TRAINER_COOLTRAINER_KAJ, ChronosMeadow_Text_KajIntro, ChronosMeadow_Text_KajDefeat
	msgbox ChronosMeadow_Text_KajPostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Jason::
	trainerbattle_single TRAINER_COOLTRAINER_JASON, ChronosMeadow_Text_JasonIntro, ChronosMeadow_Text_JasonDefeat
	msgbox ChronosMeadow_Text_JasonPostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Kendra::
	trainerbattle_single TRAINER_COOLTRAINER_KENDRA, ChronosMeadow_Text_KendraIntro, ChronosMeadow_Text_KendraDefeat
	msgbox ChronosMeadow_Text_KendraPostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Kari::
	trainerbattle_single TRAINER_COOLTRAINER_KARI, ChronosMeadow_Text_KariIntro, ChronosMeadow_Text_KariDefeat
	msgbox ChronosMeadow_Text_KariPostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Jack::
	trainerbattle_single TRAINER_BIRD_KEEPER_JACK, ChronosMeadow_Text_JackIntro, ChronosMeadow_Text_JackDefeat
	msgbox ChronosMeadow_Text_JackPostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Andrew::
	trainerbattle_single TRAINER_BIRD_KEEPER_ANDREW, ChronosMeadow_Text_AndrewIntro, ChronosMeadow_Text_AndrewDefeat
	msgbox ChronosMeadow_Text_AndrewPostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Chuck::
	trainerbattle_single TRAINER_BIRD_KEEPER_CHUCK, ChronosMeadow_Text_ChuckIntro, ChronosMeadow_Text_ChuckDefeat
	msgbox ChronosMeadow_Text_ChuckPostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Nick::
	trainerbattle_single TRAINER_BIRD_KEEPER_NICK, ChronosMeadow_Text_NickIntro, ChronosMeadow_Text_NickDefeat
	msgbox ChronosMeadow_Text_NickPostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Rodney::
	trainerbattle_single TRAINER_HIKER_RODNEY, ChronosMeadow_Text_RodneyIntro, ChronosMeadow_Text_RodneyDefeat
	msgbox ChronosMeadow_Text_RodneyPostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_DeLeon::
	trainerbattle_single TRAINER_HIKER_DELEON, ChronosMeadow_Text_DeLeonIntro, ChronosMeadow_Text_DeLeonDefeat
	msgbox ChronosMeadow_Text_DeLeonPostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Andy::
	trainerbattle_single TRAINER_HIKER_ANDY, ChronosMeadow_Text_AndyIntro, ChronosMeadow_Text_AndyDefeat
	msgbox ChronosMeadow_Text_AndyPostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Marcus::
	trainerbattle_single TRAINER_HIKER_MARCUS, ChronosMeadow_Text_MarcusIntro, ChronosMeadow_Text_MarcusDefeat
	msgbox ChronosMeadow_Text_MarcusPostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Guy::
	trainerbattle_single TRAINER_PSYCHIC_GUY, ChronosMeadow_Text_GuyIntro, ChronosMeadow_Text_GuyDefeat
	msgbox ChronosMeadow_Text_GuyPostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Tre::
	trainerbattle_single TRAINER_PSYCHIC_TRE, ChronosMeadow_Text_TreIntro, ChronosMeadow_Text_TreDefeat
	msgbox ChronosMeadow_Text_TrePostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Seth::
	trainerbattle_single TRAINER_PSYCHIC_SETH, ChronosMeadow_Text_SethIntro, ChronosMeadow_Text_SethDefeat
	msgbox ChronosMeadow_Text_SethPostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Brooke::
	trainerbattle_single TRAINER_HEX_MANIAC_BROOKE, ChronosMeadow_Text_BrookeIntro, ChronosMeadow_Text_BrookeDefeat
	msgbox ChronosMeadow_Text_BrookePostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Oz::
	trainerbattle_single TRAINER_GENTLEMAN_OZ, ChronosMeadow_Text_OzIntro, ChronosMeadow_Text_OzDefeat
	msgbox ChronosMeadow_Text_OzPostBattle, MSGBOX_AUTOCLOSE
	end

ChronosMeadow_EventScript_Tourist::
	lock
	faceplayer
	msgbox ChronosMeadow_Text_Tourist, MSGBOX_DEFAULT
	release
	end

ChronosMeadow_EventScript_Researcher::
	lock
	faceplayer
	msgbox ChronosMeadow_Text_Researcher, MSGBOX_DEFAULT
	release
	end

ChronosMeadow_EventScript_OldWoman::
	lock
	faceplayer
	msgbox ChronosMeadow_Text_OldWoman, MSGBOX_DEFAULT
	release
	end

ChronosMeadow_EventScript_Sign::
	msgbox ChronosMeadow_Text_Sign, MSGBOX_SIGN
	end
