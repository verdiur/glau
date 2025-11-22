#pragma once
#include "glau/glaufw/_fwd.hh"
namespace glaufw {

  /**
   * @class Context
   * @brief GL context control class. You can activate a GL context by creating
   * a Context instance. GL function pointers will be populated until the
   * instance is destroyed or deactivated. All context-level GL operations
   * should preferrably be achieved through this class.
   *
   * @warning Only one context can be active at a time. Unfortunately, there is
   * currently no way to know if an instance has been deactivated by another,
   * you will have to ensure this yourself.
   *
   * @thread-safe This is constructible on any thread. However, only one context
   * can be active at once across the entire program.
   *
   */
  class Context {
    bool valid;
    bool vsync;
    Window &window;

  public:
    Context(Window &window);
    ~Context();

    Context(Context &) = delete;
    Context operator=(Context &) = delete;
    Context(Context &&) = delete;
    Context &operator=(Context &&) = delete;

    bool get_valid() { return valid; }
    bool get_vsync() { return vsync; }
    void set_vsync(bool vsync);
    void deactivate();

    void swap_buffers();
  };

} // namespace glaufw
