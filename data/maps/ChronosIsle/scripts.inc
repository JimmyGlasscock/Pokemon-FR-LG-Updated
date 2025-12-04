ChronosIsle_MapScripts::
	.byte 0

ChronosIsle_EventScript_BrendanOneLeft::
	lockall
	clearflag FLAG_TEMP_1
	addobject 1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 1, ChronosIsle_Movement_BrendanApproachLeft
	waitmovement 0
	msgbox ChronosIsle_Text_BrendanIntro, MSGBOX_DEFAULT
	closemessage
	applymovement 1, ChronosIsle_Movement_BrendanLeaveLeft
	waitmovement 0
	setflag FLAG_TEMP_1
	removeobject 1
	setvar VAR_MAP_SCENE_CHRONOS_ISLE, 1
	releaseall
	end

ChronosIsle_EventScript_BrendanOne::
	lockall
	clearflag FLAG_TEMP_1
	addobject 1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 1, ChronosIsle_Movement_BrendanApproach
	waitmovement 0
	msgbox ChronosIsle_Text_BrendanIntro, MSGBOX_DEFAULT
	closemessage
	applymovement 1, ChronosIsle_Movement_BrendanLeave
	waitmovement 0
	setflag FLAG_TEMP_1
	removeobject 1
	setvar VAR_MAP_SCENE_CHRONOS_ISLE, 1
	releaseall
	end

ChronosIsle_EventScript_BrendanOneRight::
	lockall
	clearflag FLAG_TEMP_1
	addobject 1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 1, ChronosIsle_Movement_BrendanApproachRight
	waitmovement 0
	msgbox ChronosIsle_Text_BrendanIntro, MSGBOX_DEFAULT
	closemessage
	applymovement 1, ChronosIsle_Movement_BrendanLeaveRight
	waitmovement 0
	setflag FLAG_TEMP_1
	removeobject 1
	setvar VAR_MAP_SCENE_CHRONOS_ISLE, 1
	releaseall
	end

ChronosIsle_Movement_BrendanApproachLeft::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

ChronosIsle_Movement_BrendanApproach::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

ChronosIsle_Movement_BrendanApproachRight::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

ChronosIsle_Movement_BrendanLeaveLeft::
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

ChronosIsle_Movement_BrendanLeave::
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

ChronosIsle_Movement_BrendanLeaveRight::
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end
