cmake_minimum_required(VERSION 2.6)

project(FinalYearProject)

include_directories(
	include
	src/Engine
)

link_directories(
	${CMAKE_SOURCE_DIR}/lib
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
	src/Engine/Time.cpp
	src/Engine/Time.h
)
target_link_libraries(Engine SDL2 SDL2main)

add_executable(Game
	src/Game/CircleRenderer.cpp
	src/Game/CircleRenderer.h
	src/Game/Command.cpp
	src/Game/Command.h
	src/Game/Commandable.cpp
	src/Game/Commandable.h
	src/Game/CommandCreateUnit.cpp
	src/Game/CommandCreateUnit.h
	src/Game/CommandManager.cpp
	src/Game/CommandManager.h
	src/Game/CommandMove.cpp
	src/Game/CommandMove.h
	src/Game/CommandStop.cpp
	src/Game/CommandStop.h
	src/Game/CommandUnitRightClick.cpp
	src/Game/CommandUnitRightClick.h
	src/Game/Constants.h
	src/Game/InputManager.cpp
	src/Game/InputManager.h
	src/Game/Game.cpp
	src/Game/Game.h
	src/Game/GameManager.cpp
	src/Game/GameManager.h
	src/Game/main.cpp
	src/Game/Map.cpp
	src/Game/Map.h
	src/Game/Navigation.cpp
	src/Game/Navigation.h
	src/Game/Node.cpp
	src/Game/Node.h
	src/Game/Projectile.cpp
	src/Game/Projectile.h
	src/Game/ProtoFactory.cpp
	src/Game/ProtoFactory.h
	src/Game/Selectable.cpp
	src/Game/Selectable.h
	src/Game/SelectionManager.cpp
	src/Game/SelectionManager.h
)
target_link_libraries(Game Engine)

add_custom_command(TARGET Game
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		"${PROJECT_SOURCE_DIR}/lib/SDL2.dll"
		$<TARGET_FILE_DIR:Game>
)
