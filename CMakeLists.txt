cmake_minimum_required(VERSION 2.6)

project(FinalYearProject)

include_directories(
	contrib/include
)

link_directories(
	${CMAKE_SOURCE_DIR}/contrib/lib
)

add_executable(FYP
	src/Building.cpp
	src/Building.h
	src/Faction.cpp
	src/Faction.h
	src/Game.cpp
	src/Game.h
	src/GameState.cpp
	src/GameState.h
	src/Input.cpp
	src/Input.h
	src/main.cpp
	src/Map.cpp
	src/Map.h
	src/Node.cpp
	src/Node.h
	src/Object.h
	src/Player.h
	src/Player.cpp
	src/ProtoFactory.cpp
	src/ProtoFactory.h
	src/SelectableObject.cpp
	src/SelectableObject.h
	src/Unit.cpp
	src/Unit.h
)

target_link_libraries(FYP SDL2 SDL2main)

add_custom_command(TARGET FYP
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		"${PROJECT_SOURCE_DIR}/contrib/lib/SDL2.dll"
		$<TARGET_FILE_DIR:FYP>
)
