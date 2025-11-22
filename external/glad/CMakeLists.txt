set(LIB_NAME glad)
project(${LIB_NAME} LANGUAGES C)

add_library(${LIB_NAME} src/gl.c)
target_include_directories(${LIB_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
