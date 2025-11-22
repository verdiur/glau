#pragma once
#include "glau/glaugl/_util.hh"
#include <glad/gl.h>
namespace glaugl {

  // _util
  enum struct BufferUsage : unsigned int;


  // shader
  template <int ShaderType> class Shader;
  using VertexShader = Shader<GL_VERTEX_SHADER>;
  using FragmentShader = Shader<GL_FRAGMENT_SHADER>;
  using GeometryShader = Shader<GL_GEOMETRY_SHADER>;

  // vao
  template <IsVertex Vertex> class VertexArray;

  // vbo
  template <IsVertex Vertex> class VertexBuffer;

} // namespace glaugl
