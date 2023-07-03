cmake_minimum_required(VERSION 3.10)
project(CppGame)

set(CMAKE_CXX_STANDARD 14)

set(SI "/opt/homebrew/include")
set(SL "/opt/homebrew/lib/libSDL2.dylib")

set(SLT "/opt/homebrew/lib/libSDL2_ttf.dylib")
# Locate the SDL2 library
find_package(SDL2 REQUIRED)

# Locate the SDL2_ttf library
include_directories(src ${SI})

# Add your source file
add_executable(CppGame src/main.cpp)

# Link the SDL2 and SDL2_ttf libraries to your project
target_link_libraries(CppGame ${SL} ${SLT})
