#define GLFW_INCLUDE_NONE
#include "glau/glaufw/context.hh"
#include "glau/glaufw/window.hh"
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <spdlog/spdlog.h>


glaufw::Context::Context(Window &window)
    : valid(true)
    , window(window) {
  glfwMakeContextCurrent(window.get());
  if (!gladLoadGL(glfwGetProcAddress)) {
    spdlog::warn("[GL] OpenGL context could not be activated");
    valid = false;
    return;
  }

  int wwidth, wheight;
  glfwGetFramebufferSize(window.get(), &wwidth, &wheight);
  glViewport(0, 0, wwidth, wheight);
  glfwSetFramebufferSizeCallback(
      window.get(), []([[maybe_unused]] GLFWwindow *window, int wwidth,
                       int wheight) { glViewport(0, 0, wwidth, wheight); });
}


glaufw::Context::~Context() { glfwMakeContextCurrent(nullptr); }


void glaufw::Context::set_vsync(bool vsync) {
  (vsync) ? glfwSwapInterval(1) : glfwSwapInterval(0);
}


void glaufw::Context::deactivate() { glfwMakeContextCurrent(nullptr); }


void glaufw::Context::swap_buffers() { glfwSwapBuffers(window.get()); }
