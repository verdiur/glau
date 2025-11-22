set(PREFIX glauexample)

add_executable(${PREFIX}_triangle triangle.cc)
target_include_directories(${PREFIX}_triangle PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(${PREFIX}_triangle PRIVATE
  glau
  glm
)
