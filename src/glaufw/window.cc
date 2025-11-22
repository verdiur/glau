#include "glau/glaufw/window.hh"
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>


glaufw::Window::Window([[maybe_unused]] const GLFW &glfw, int width, int height,
                       std::string title, bool visible)
    : valid(true)
    , visible(visible)
    , width(width)
    , height(height)
    , title(title)
    , window(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)) {
  if (!window) {
    spdlog::error("[GL] could not create window");
    this->valid = false;
    this->width = 0;
    this->height = 0;
    this->title = "";
  }
}


glaufw::Window::~Window() { glfwDestroyWindow(window); }


bool glaufw::Window::should_close() { return glfwWindowShouldClose(window); }
