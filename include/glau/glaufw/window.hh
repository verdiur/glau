#pragma once
#define GLFW_INCLUDE_NONE
#include "glau/glaufw/_fwd.hh"
#include <GLFW/glfw3.h>
#include <string>
namespace glaufw {

  /**
   * @class Window
   * @brief GLFWwindow RAII wrapper. Creating a Window does not activate its GL
   * context, you will have to do that with @ref Context.
   *
   */
  class Window {
    bool valid;
    bool visible;
    int width;
    int height;
    std::string title;
    GLFWwindow *window;

  public:
    Window([[maybe_unused]] const GLFW &glfw, int width, int height,
           std::string title, bool visible = true);
    ~Window();

    Window(Window &) = delete;
    Window operator=(Window &) = delete;
    Window(Window &&) = delete;
    Window &operator=(Window &&) = delete;

    bool get_valid() { return valid; }
    bool get_visible() { return visible; }
    int get_width() { return width; }
    int get_height() { return height; }
    std::string get_title() { return title; }
    GLFWwindow *get() { return window; }
    bool should_close();
  };

} // namespace glaufw
