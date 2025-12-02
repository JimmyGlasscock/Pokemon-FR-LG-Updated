.set LOCALID_CELEBI, 1

NavelRock_CelebiChamber_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NavelRock_CelebiChamber_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, NavelRock_CelebiChamber_OnResume
	.byte 0

NavelRock_CelebiChamber_OnTransition::
	call_if_set FLAG_FOUGHT_CELEBI, NavelRock_CelebiChamber_EventScript_HideCelebi
	call_if_unset FLAG_FOUGHT_CELEBI, NavelRock_CelebiChamber_EventScript_TryShowCelebi
	end

NavelRock_CelebiChamber_EventScript_HideCelebi::
	setvar VAR_TEMP_1, 1
	setflag FLAG_HIDE_CELEBI
	return

NavelRock_CelebiChamber_EventScript_TryShowCelebi::
	setvar VAR_TEMP_1, 1
	goto_if_set FLAG_CELEBI_FLEW_AWAY, EventScript_Return
	setvar VAR_TEMP_1, 0
	clearflag FLAG_HIDE_CELEBI
	return

NavelRock_CelebiChamber_OnResume::
	call_if_set FLAG_SYS_SPECIAL_WILD_BATTLE, NavelRock_CelebiChamber_EventScript_TryRemoveCelebi
	end

NavelRock_CelebiChamber_EventScript_TryRemoveCelebi::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, EventScript_Return
	removeobject LOCALID_CELEBI
	return

NavelRock_CelebiChamber_EventScript_Celebi::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	lockall
	setvar VAR_TEMP_1, 1
	applymovement LOCALID_CELEBI, Movement_CelebiFloat
	waitmovement 0
	delay 50
	playmoncry SPECIES_CELEBI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	delay 20
	seteventmon SPECIES_CELEBI, 30
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	special StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	setvar VAR_LAST_TALKED, LOCALID_CELEBI
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, NavelRock_CelebiChamber_EventScript_DefeatedCelebi
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NavelRock_CelebiChamber_EventScript_RanFromCelebi
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, NavelRock_CelebiChamber_EventScript_RanFromCelebi
	setflag FLAG_FOUGHT_CELEBI
	releaseall
	end

NavelRock_CelebiChamber_EventScript_DefeatedCelebi::
	setflag FLAG_CELEBI_FLEW_AWAY
	setvar VAR_0x8004, SPECIES_CELEBI
	goto EventScript_MonFlewAway
	end

NavelRock_CelebiChamber_EventScript_RanFromCelebi::
	setvar VAR_0x8004, SPECIES_CELEBI
	goto EventScript_MonFlewAway
	end

Movement_CelebiFloat:
	walk_in_place_down
	delay_16
	delay_16
	step_end
