cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET "inverted_google")

project(${TARGET})

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra -Wpedantic
         -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op
         -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept
         -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow
         -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel
         -Wstrict-overflow=2 -Wswitch-default -Wundef -Wno-unused
		 -g -Og)
	 
find_program(CLANG_TIDY_EXISTS "clang-tidy")
IF(CLANG_TIDY_EXISTS)
set(CMAKE_CXX_CLANG_TIDY
  clang-tidy;
  -header-filter=.*;
  -use-color;)
ENDIF()

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${TARGET} ${SOURCES})

unset(CMAKE_CXX_CLANG_TIDY)

set(TEST_TARGET "run_tests")

file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
file(GLOB_RECURSE NO_MAIN_SOURCES src/*.cpp)
list(REMOVE_ITEM NO_MAIN_SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp)

find_package(Catch2 REQUIRED PATHS "${PROJECT_SOURCE_DIR}/lib")

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address,leak,undefined")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address,leak,undefined")

add_executable(${TEST_TARGET} ${NO_MAIN_SOURCES} ${TEST_SOURCES})
target_link_libraries(${TEST_TARGET} PRIVATE Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(${TEST_TARGET})