/**
 * @file
 * @brief Hello triangle example using bare glaugl library.
 */

#include <glau/glaufw.hh>
#include <glau/glaugl.hh>
#include <glm/vec3.hpp>
#include <iostream>
#include <vector>


int main() {
  // init GLFW
  glaufw::GLFW glfw{};
  if (!glfw.get_valid()) {
    std::cerr << "failed to initialize GLFW" << std::endl;
    return 1;
  }

  // create window
  glaufw::Window window(glfw, 640, 480, "glaufw - triangle example");
  if (!window.get_valid()) {
    std::cerr << "failed to create window" << std::endl;
    return 1;
  }

  // activate context
  glaufw::Context ctx(window);
  if (!ctx.get_valid()) {
    std::cerr << "failed to activate GL context" << std::endl;
    return 1;
  }

  // create VBO
  std::vector<glm::vec3> vertices{
      {-0.5f, -0.5f, 0.0f},
      {0.5f, -0.5f, 0.0f},
      {0.0f, 0.5f, 0.0f},
  };
  glaugl::VertexBuffer<glm::vec3> vbo(vertices, 0);
  if (vbo.get_id() == 0) {
    std::cerr << "VBO could not be created" << std::endl;
    return 1;
  }

  // create and setup VAO
  glaugl::VertexArray<glm::vec3> vao{};
  if (vao.get_id() == 0) return 1;

  int attr = 0;
  int slot = 0;
  vao.format_attribute_float(attr, 3, false, 0);
  vao.bind_vbo(slot, vbo, 0, sizeof(glm::vec3));
  vao.bind_attribute(slot, attr);
  vao.enable_attribute(attr);

  // create vertex shader
  glaugl::VertexShader vert_shader("#version 450 core\n"
                                   "layout (location = 0) in vec3 aPos;\n"
                                   "void main() {\n"
                                   "  gl_Position = vec4(aPos, 1.0);\n"
                                   "}");
  if (vert_shader.get_id() == 0) return 1;

  // create fragment shader
  glaugl::FragmentShader frag_shader(
      "#version 450 core\n"
      "out vec4 FragColor;\n"
      "void main() {\n"
      "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "}");
  if (frag_shader.get_id() == 0) return 1;

  // create shader program
  glaugl::ShaderProgram shader_program(&vert_shader, &frag_shader, nullptr);

  while (!window.should_close()) {
    shader_program.use();
    vao.draw();
    ctx.swap_buffers();
    glfw.poll_events();
  }
}
