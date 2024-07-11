cmake_minimum_required(VERSION 2.6.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_helpers/")

set(PROJ_NAME phobos2390)
set(REPO_NAME hex_grid_lib)

project("${PROJ_NAME}-${REPO_NAME}")

set(PROJ_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_ROOT_DIR ${PROJ_DIR}/src/${PROJ_NAME}/${REPO_NAME})

include_directories("${PROJ_DIR}/catch2/single_include")
include_directories("${PROJ_DIR}/src/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
#set(CMAKE_CXX_FLAGS "-Wa,-mbig-obj -g -std=c++14")
set(CMAKE_CXX_FLAGS " -g -std=c++14")

set(SOURCE_DIRECTORIES ${SRC_ROOT_DIR})

set(all_source_files "")
foreach(source_dir ${SOURCE_DIRECTORIES})
  message("Finding everything in ${source_dir}")
  file(GLOB dir_src_files ${source_dir}/*.c*)
  set(all_source_files ${all_source_files}
                       ${dir_src_files})
endforeach()

file(GLOB test_executable_files ${SRC_ROOT_DIR}/test/*_test.cpp)

set(LIB_NAME_SHARED ${PROJ_NAME}_${REPO_NAME})
set(LIB_NAME_STATIC ${PROJ_NAME}_${REPO_NAME}_s)
set(LIB_TEST_NAME "test_${PROJ_NAME}_${REPO_NAME}")

message("Building static library ${LIB_NAME_STATIC} with ${all_source_files}")
add_library(${LIB_NAME_STATIC} STATIC ${all_source_files})
target_link_libraries(${LIB_NAME_STATIC} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
message("Building shared library ${LIB_NAME_SHARED} with ${all_source_files}")
add_library(${LIB_NAME_SHARED} SHARED ${all_source_files})
target_link_libraries(${LIB_NAME_SHARED} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

add_executable(${LIB_TEST_NAME} ${test_executable_files})
target_link_libraries(${LIB_TEST_NAME} ${LIB_NAME_STATIC} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

add_executable(demo ${SRC_ROOT_DIR}/app/hex_grid_demo.cpp)
target_link_libraries(demo ${LIB_NAME_STATIC} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

