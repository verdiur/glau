#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
namespace glaufw {

  /**
   * @class GLFW
   * @brief GLFW context.
   *
   * @thread-safe Must live in the main thread. Only one instance can exist at a
   * time.
   *
   */
  class GLFW {
    static inline bool exists = false;
    bool valid;

  public:
    GLFW();
    ~GLFW();

    GLFW(GLFW &) = delete;
    GLFW operator=(GLFW &) = delete;
    GLFW(GLFW &&) = delete;
    GLFW &operator=(GLFW &&) = delete;

    bool get_valid() { return valid; }
    void set_gl_version(int major, int minor);

    void poll_events();
  };

} // namespace glaufw
