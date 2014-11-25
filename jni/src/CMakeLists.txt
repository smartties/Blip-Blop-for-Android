cmake_minimum_required(VERSION 2.8)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED SDL2)
pkg_search_module(SDL2_mixer REQUIRED SDL2_mixer)

project(blipblop)

include_directories(Engine)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_mixer_INCLUDE_DIRS})

aux_source_directory(. SRC)
aux_source_directory(Engine ENGINE_SRC)

add_executable(blipblop ${SRC} ${ENGINE_SRC})
target_link_libraries(blipblop ${SDL2_LIBRARIES})
target_link_libraries(blipblop ${SDL2_mixer_LIBRARIES})
set_target_properties(blipblop PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

add_custom_target(astyle COMMAND
    astyle --indent=tab --indent-preprocessor --style=kr
    --pad-oper --pad-header --unpad-paren -S -n
    --recursive ${CMAKE_SOURCE_DIR}"/*.cpp" ${CMAKE_SOURCE_DIR}"/*.h"
)
