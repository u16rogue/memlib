cmake_minimum_required(VERSION 3.18)

project(memlib)

add_library(${PROJECT_NAME} STATIC
  "include/memlib/memcalc.hh"         "src/memcalc.cc"
  "include/memlib/memwalker.hh"       "src/memwalker.cc"
  "include/memlib/pattern_scanner.hh" "src/pattern_scanner.cc"
)

target_include_directories(${PROJECT_NAME} PUBLIC "include/")

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 20
)

target_compile_options(${PROJECT_NAME}
  PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall -Wextra -Wpedantic -Werror -Wsign-conversion>
    $<$<CXX_COMPILER_ID:MSVC>: /W4 /WX>
)

target_link_libraries(${PROJECT_NAME} PUBLIC metapp)
