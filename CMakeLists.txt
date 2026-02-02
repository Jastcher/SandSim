cmake_minimum_required(VERSION 3.13)
project(Sandbox VERSION 1.0 LANGUAGES C CXX)

# 1. Generate compile_commands.json for clangd LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 2. Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Add the executable
file(GLOB_RECURSE SRC_FILES src/*.cpp vendor/src/*)

add_executable(${PROJECT_NAME} ${SRC_FILES})

# 4. Include Directories
# This tells the compiler where to find glad/glad.h, GLFW/glfw3.h, and glm/common.hpp
target_include_directories(${PROJECT_NAME} PRIVATE 
    vendor/include
    vendor/include/imgui
    src
)

# 5. Link Libraries
# Assuming your library is named libglfw3.a or glfw3.lib inside vendor/libs
target_link_directories(${PROJECT_NAME} PRIVATE vendor/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw3)

# 6. Platform specific dependencies (OpenGL)
target_link_libraries(${PROJECT_NAME} PRIVATE GL)
