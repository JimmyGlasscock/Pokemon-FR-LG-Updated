EightIsland_Harbor_MapScripts::
	.byte 0

EightIsland_Harbor_EventScript_Sailor::
	lock
	faceplayer
	msgbox EightIsland_Harbor_Text_SailorWelcome, MSGBOX_DEFAULT
	release
	end
