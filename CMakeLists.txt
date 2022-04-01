cmake_minimum_required(VERSION 3.0.0)
project(dz2)

option(ASYNC "async libs" OFF)
option(TEST "test buidl" OFF)

if(ASYNC)
	add_subdirectory(dz2d)
	message("Build with async library")
else()
	add_subdirectory(dz2s)
	message("Build with static library")
endif()

add_executable(${PROJECT_NAME} main.c)

set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

target_include_directories(${PROJECT_NAME} PUBLIC ${DZ2_INCLUDE_DIRS}) 
target_link_libraries(${PROJECT_NAME} PRIVATE ${DZ2_LIBRARIES})

add_subdirectory(tests)
