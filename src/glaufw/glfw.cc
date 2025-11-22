#include "glau/glaufw/glfw.hh"
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>


glaufw::GLFW::GLFW()
    : valid(true) {
  if (this->exists) {
    spdlog::error("[GL] GLFW context already exists");
    return;
  }
  if (!glfwInit()) {
    this->valid = false;
    return;
  }
  glfwSetErrorCallback([](int error, const char *desc) {
    spdlog::error("[GL] GLFW error {}: {}", error, desc);
  });
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->exists = true;
}


glaufw::GLFW::~GLFW() {
  glfwTerminate();
  this->exists = false;
}


void glaufw::GLFW::set_gl_version(int major, int minor) {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


void glaufw::GLFW::poll_events() { glfwPollEvents(); }
