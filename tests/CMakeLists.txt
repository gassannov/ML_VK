cmake_minimum_required(VERSION 3.14)
project(dz2_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${DZ2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${DZ2_LIBRARIES} GTest::GTest GTest::Main)
