cmake_minimum_required(VERSION 3.10...3.31)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(glau
  LANGUAGES CXX
)

option(GLAU_BUILD_EXAMPLES OFF)

# DEPENDENCIES --------------------------------------------------------------- #

include(FetchContent)
FetchContent_Declare(spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog
  GIT_TAG v1.16.0
  GIT_SHALLOW ON
  SYSTEM
)
FetchContent_Declare(glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG 1.0.2
  GIT_SHALLOW ON
  SYSTEM
)
FetchContent_Declare(glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG 3.4
  GIT_SHALLOW ON
  SYSTEM
)
FetchContent_Declare(miniaudio
  GIT_REPOSITORY https://github.com/mackron/miniaudio
  GIT_TAG 0.11.23
  GIT_SHALLOW ON
  SYSTEM
)

FetchContent_MakeAvailable(spdlog)
FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(miniaudio)

# TARGETS -------------------------------------------------------------------- #

# compile options

add_library(compile_options INTERFACE)
if(MSVC)
  target_compile_options(compile_options INTERFACE /permissive- /W3)
else()
  target_compile_options(compile_options INTERFACE -Wall -Wextra)
endif()

# subdirectories

add_subdirectory(external/glad)
add_subdirectory(src/glaufw)
add_subdirectory(src/glaugl)

# main library

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE
  glaufw
  glaugl
)

# examples

if(GLAU_BUILD_EXAMPLES)
  message("examples")
  add_subdirectory(examples)
endif()
