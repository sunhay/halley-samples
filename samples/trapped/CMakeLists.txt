cmake_minimum_required (VERSION 3.0)

project (trapped)

set (trapped_sources
	"prec.cpp"

	"src/game/game_stage.cpp"
	"src/game/trapped_game.cpp"
	)

set (trapped_headers
	"prec.h"
	
	"src/game/game_stage.h"
	)
		
set (trapped_gen_definitions
	"gen_src/trapped.yaml"
	)

halleyProject(trapped "${trapped_sources}" "${trapped_headers}" "${trapped_gen_definitions}" ${CMAKE_CURRENT_SOURCE_DIR}/bin)
