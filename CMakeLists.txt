cmake_minimum_required(VERSION 3.0.0)
project(dz1)

set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

add_subdirectory(my_string)
add_subdirectory(device_type)
add_subdirectory(storage_device)
add_subdirectory(my_task)

option(LINTER "Linters" OFF)

IF(LINTER)
    set(CMAKE_C_CPPCHECK "cppcheck")
    message("LINTER IS ON TO MAKE IT OFF RUN CMAKE WITH -DLINTER=OFF")
ENDIF()

add_executable(${PROJECT_NAME} main.c)


target_include_directories(${PROJECT_NAME} 
PUBLIC ${MY_STRING_INCLUDE_DIRS}
PUBLIC ${DEVICE_TYPE_INCLUDE_DIRS}
PUBLIC ${STORAGE_DEVICE_INCLUDE_DIRS}
PUBLIC ${MY_TASK_INCLUDE_DIRS}
)
 
target_link_libraries(${PROJECT_NAME} 
PRIVATE ${MY_STRING_LIBRARIES}
PRIVATE ${DEVICE_TYPE_LIBRARIES}
PRIVATE ${STORAGE_DEVICE_LIBRARIES}
PRIVATE ${MY_TASK_LIBRARIES}
)

add_subdirectory(tests)


