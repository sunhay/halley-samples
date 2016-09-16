cmake_minimum_required (VERSION 3.0)

project (empty)

set (HOTRELOAD 1)

set (SOURCES
	"prec.cpp"

	"src/game/game_stage.cpp"
	"src/game/game.cpp"
	)

set (HEADERS
	"prec.h"
	
	"src/game/game_stage.h"
	)
		
set (GEN_DEFINITIONS
	)

halleyProject(empty "${SOURCES}" "${HEADERS}" "${GEN_DEFINITIONS}" ${CMAKE_CURRENT_SOURCE_DIR}/bin)
