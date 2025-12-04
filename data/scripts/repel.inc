EventScript_RepelWoreOff::
	specialvar VAR_RESULT, CheckForNextRepelInBag
	goto_if_eq VAR_RESULT, TRUE, EventScript_AskUseNextRepel
	msgbox Text_RepelWoreOff, MSGBOX_SIGN
	end

EventScript_AskUseNextRepel::
	msgbox Text_UseNextRepel, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, EventScript_UseNextRepel
	msgbox Text_RepelWoreOff, MSGBOX_SIGN
	end

EventScript_UseNextRepel::
	playse SE_REPEL
	special UseNextRepelFromBag
	msgbox Text_UsedRepel, MSGBOX_SIGN
	end

Text_RepelWoreOff::
	.string "REPEL's effect wore off…$"

Text_UseNextRepel::
	.string "The REPEL's effect wore off.\nUse another?$"

Text_UsedRepel::
	.string "{PLAYER} used the\n{STR_VAR_1}.$"
