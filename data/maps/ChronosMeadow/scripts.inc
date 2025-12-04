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
	call_if_unset FLAG_FOUGHT_CELEBI, ChronosMeadow_EventScript_ShowCelebi
	end

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
