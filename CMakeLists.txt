cmake_minimum_required(VERSION 2.6)

project(FinalYearProject)

include_directories(
	contrib/include
	src/Engine
)

link_directories(
	${CMAKE_SOURCE_DIR}/contrib/lib
)

add_library(Engine
	src/Engine/Engine.h
	src/Engine/Component.cpp
	src/Engine/Component.h
	src/Engine/Core.cpp
	src/Engine/Core.h
	src/Engine/Entity.cpp
	src/Engine/Entity.h
	src/Engine/Input.cpp
	src/Engine/Input.h
)
target_link_libraries(Engine SDL2 SDL2main)

add_executable(Game
	src/Game/Building.cpp
	src/Game/Building.h
	src/Game/Faction.cpp
	src/Game/Faction.h
	src/Game/Game.cpp
	src/Game/Game.h
	src/Game/GameState.cpp
	src/Game/GameState.h
	src/Game/main.cpp
	src/Game/Map.cpp
	src/Game/Map.h
	src/Game/Node.cpp
	src/Game/Node.h
	src/Game/Object.h
	src/Game/Player.h
	src/Game/Player.cpp
	src/Game/ProtoFactory.cpp
	src/Game/ProtoFactory.h
	src/Game/SelectableObject.cpp
	src/Game/SelectableObject.h
	src/Game/Unit.cpp
	src/Game/Unit.h
)
target_link_libraries(Game Engine)

add_custom_command(TARGET Game
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		"${PROJECT_SOURCE_DIR}/contrib/lib/SDL2.dll"
		$<TARGET_FILE_DIR:Game>
)
