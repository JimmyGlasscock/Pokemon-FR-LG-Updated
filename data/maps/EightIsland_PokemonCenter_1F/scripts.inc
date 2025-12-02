EightIsland_PokemonCenter_1F_MapScripts::
	.byte 0

EightIsland_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse
	release
	end

EightIsland_PokemonCenter_1F_EventScript_Woman::
	msgbox EightIsland_PokemonCenter_1F_Text_Woman, MSGBOX_NPC
	end
