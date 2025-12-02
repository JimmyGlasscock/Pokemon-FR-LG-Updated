EightIsland_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EightIsland_OnTransition
	.byte 0

EightIsland_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_EIGHT_ISLAND
	end

EightIsland_EventScript_IslandSign::
	msgbox EightIsland_Text_IslandSign, MSGBOX_SIGN
	end

EightIsland_EventScript_Lass::
	msgbox EightIsland_Text_LassWelcome, MSGBOX_NPC
	end

EightIsland_EventScript_Gentleman::
	msgbox EightIsland_Text_GentlemanHistory, MSGBOX_NPC
	end

EightIsland_EventScript_Beauty::
	msgbox EightIsland_Text_BeautyMysticSprings, MSGBOX_NPC
	end
