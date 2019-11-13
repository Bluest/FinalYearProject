cmake_minimum_required(VERSION 2.6)

project(FinalYearProject)

include_directories(
	contrib/include
)

link_directories(
	${CMAKE_SOURCE_DIR}/contrib/lib
)

add_executable(FinalYearProject
	src/main.cpp
)

target_link_libraries(FinalYearProject SDL2 SDL2main SDL2_image)

add_custom_command(TARGET FinalYearProject
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		"${PROJECT_SOURCE_DIR}/contrib/lib/SDL2.dll"
		$<TARGET_FILE_DIR:FinalYearProject>
	COMMAND ${CMAKE_COMMAND} -E copy
		"${PROJECT_SOURCE_DIR}/contrib/lib/SDL2_image.dll"
		$<TARGET_FILE_DIR:FinalYearProject>
	COMMAND ${CMAKE_COMMAND} -E copy
		"${PROJECT_SOURCE_DIR}/contrib/lib/zlib1.dll"
		$<TARGET_FILE_DIR:FinalYearProject>
	COMMAND ${CMAKE_COMMAND} -E copy
		"${PROJECT_SOURCE_DIR}/contrib/lib/libpng16-16.dll"
		$<TARGET_FILE_DIR:FinalYearProject>
)
