# 1. Setup
cmake_minimum_required(VERSION 3.10)
project(anNaml VERSION 1.0 LANGUAGES CXX)

# 2. Compiler Options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Find Dependencies
# We only need to find raylib. raygui is header-only.
find_package(raylib REQUIRED)

# 4. Source Files
file(GLOB SOURCES "src/*.cpp")

# 5. Create Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# 6. Include Directories
# /usr/include is where yay puts raygui.h on Arch/EndeavourOS
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src/include
    /usr/include
)

# 7. Link Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# 8. Platform Specifics
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 gdi32 winmm)
endif()