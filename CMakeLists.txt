cmake_minimum_required(VERSION 3.0.0)
project(dz1)

add_subdirectory(storage_device)

add_executable(${PROJECT_NAME} main.c)

set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

target_include_directories(${PROJECT_NAME} PUBLIC ${STORAGE_DEVICE_INCLUDE_DIRS})
 
target_link_libraries(${PROJECT_NAME} PRIVATE ${STORAGE_DEVICE_LIBRARIES})

add_subdirectory(tests)


