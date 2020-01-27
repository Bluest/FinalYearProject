cmake_minimum_required(VERSION 2.6)

project(FinalYearProject)

include_directories(
	contrib/include
)

link_directories(
	${CMAKE_SOURCE_DIR}/contrib/lib
)

add_executable(FYP
	src/Unit.h
	src/Unit.cpp
	src/Game.h
	src/Game.cpp
	src/main.cpp
)

target_link_libraries(FYP SDL2 SDL2main)

add_custom_command(TARGET FYP
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		"${PROJECT_SOURCE_DIR}/contrib/lib/SDL2.dll"
		$<TARGET_FILE_DIR:FYP>
)
