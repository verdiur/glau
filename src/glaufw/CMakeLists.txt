include(sources.cmake)
set(LIB_NAME glaufw)
add_library(${LIB_NAME} ${SOURCES})
target_compile_features(${LIB_NAME} PUBLIC cxx_std_20)
target_include_directories(${LIB_NAME}
PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
PRIVATE
  ${CMAKE_SOURCE_DIR}/external
  ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(${LIB_NAME} PUBLIC
  compile_options
  spdlog
  glfw
  glad
)
