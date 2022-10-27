# CMakeList.txt : CMake project for SDL_cmake_template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.7.2)

project(SDL_cmake_template)
set(CMAKE_CXX_STANDARD 11)

# TODO: Add tests and install targets if needed.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(BIN_DIR ${SDL_cmake_template_SOURCE_DIR}/bin)

# This path is used by FindSDL2 module. 
# It will find include and lib folders under this directory.
# This is because find command doesn't include any path for Windows.
# So it can't find anything using default paths.
# SDL2_PATH is already expected in module file. I'm using the same variable.
IF (WIN32)
  set(SDL2_PATH "C:/Users/sufia/Downloads/Zip/Extracted/SDL2-2.24.1")
ENDIF()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(SOURCE_FILES "src/main.cpp")

add_executable(TeatrisYt 
	${SOURCE_FILES}
)

target_link_libraries(TeatrisYt 
	${SDL2_LIBRARY}
)

install(TARGETS TeatrisYt RUNTIME DESTINATION ${BIN_DIR}/)
set_target_properties(TeatrisYt PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIR}/debug/
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIR}/release/ )

if(CMAKE_SIZEOF_VOID_P EQUAL 8) 
	add_custom_command( TARGET TeatrisYt POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
		${SDL2_PATH}/lib/x64/SDL2.dll 
		${BIN_DIR}/debug/SDL2.dll  )
	add_custom_command( TARGET TeatrisYt POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${SDL2_PATH}/lib/x64/SDL2.dll
		${BIN_DIR}/debug/SDL2.dll  )
elseif()
	add_custom_command( TARGET TeatrisYt POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
		${SDL2_PATH}/lib/x86/SDL2.dll 
		${BIN_DIR}/debug/SDL2.dll  )
	add_custom_command( TARGET TeatrisYt POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${SDL2_PATH}/lib/x86/SDL2.dll
		${BIN_DIR}/debug/SDL2.dll  )
endif()
