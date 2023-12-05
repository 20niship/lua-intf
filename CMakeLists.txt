cmake_minimum_required(VERSION 3.10)
project(luaintf)

# force colored output
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options(-fcolor-diagnostics)
endif()

find_package(Lua REQUIRED)

# compile commands json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_WARNINGS "-Wall -Wextra -Wpedantic -Werror")
add_compile_options(${CXX_WARNINGS})

include_directories(${LUA_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/)
add_executable(luaintf-test tests/main.cpp)
target_link_libraries(luaintf-test PRIVATE ${LUA_LIBRARIES})

