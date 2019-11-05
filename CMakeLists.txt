cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

include_directories(src)

include_directories(lib)
link_directories("lib/xed")

file (GLOB SOURCES "src/*.cpp" "src/*.h")
file (GLOB SWMODS "cwmods/*.cpp" "cwmods/*.h")
file (GLOB CUBE "cwmods/cube/*.cpp" "cwmods/common/*.cpp" "cwmods/gfx/*.cpp" "cwmods/msvc/*.cpp" "cwmods/plasma/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "-m64 -masm=intel -static -static-libgcc -static-libstdc++ -Wall -Wextra")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

add_library(newclass SHARED ${SWMODS} ${SOURCES} ${CUBE})
set_target_properties(newclass PROPERTIES SUFFIX ".dll")

target_link_libraries(newclass psapi xed)
