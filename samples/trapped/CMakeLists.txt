cmake_minimum_required (VERSION 3.0)

project (trapped)

set (trapped_sources
		"prec.cpp"

		"src/game/game_stage.cpp"
		"src/game/trapped_game.cpp"

		"src/systems/mob_system.cpp"
		"src/systems/movement_system.cpp"
		"src/systems/player_input_system.cpp"
		"src/systems/sprite_animation_system.cpp"
		"src/systems/sprite_render_system.cpp"
		)

set (trapped_headers
		"prec.h"
		
		"gen_src/trapped.yaml"
		
		"src/game/game_stage.h"
		)

halleyProject(trapped "${trapped_sources}" "${trapped_headers}" ${CMAKE_CURRENT_SOURCE_DIR}/bin)
