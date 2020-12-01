cmake_minimum_required(VERSION 3.16)

project(AdventOfCode2020)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


file(GLOB_RECURSE DATA_FILES data/*)
source_group("Data/" FILES ${DATA_FILES})
foreach(DATA ${DATA_FILES})
    get_filename_component(FILE_NAME ${DATA} NAME)
    get_filename_component(PATH_NAME ${DATA} DIRECTORY)
    get_filename_component(EXTENSION ${DATA} EXT)
    file(RELATIVE_PATH PATH_NAME "${PROJECT_SOURCE_DIR}" ${PATH_NAME})
    set(DATA_OUTPUT "${PROJECT_BINARY_DIR}/${PATH_NAME}/${FILE_NAME}")
    add_custom_command(
            OUTPUT ${DATA_OUTPUT}
            DEPENDS ${DATA}
            DEPENDS
            COMMAND ${CMAKE_COMMAND} -E copy ${DATA} "${PROJECT_BINARY_DIR}/${PATH_NAME}/${FILE_NAME}"
    )
    list(APPEND DATA_BINARY_FILES ${DATA_OUTPUT})
endforeach()

add_custom_target(
        DataTarget
        DEPENDS ${DATA_BINARY_FILES} ${DATA_FILES})

file(GLOB_RECURSE src_files src/*.cpp)

foreach(file ${src_files})
    get_filename_component(main_project_name ${file} NAME_WE)
    add_executable(${main_project_name} ${file})
    add_dependencies(${main_project_name} DataTarget)
endforeach()
