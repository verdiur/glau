#pragma once
#include <glad/gl.h>
#include <type_traits>
namespace glaugl {

  // enum struct BufferUsage : GLenum {
  //   STATIC_DRAW = GL_STATIC_DRAW,
  //   STATIC_READ = GL_STATIC_READ,
  //   STATIC_COPY = GL_STATIC_COPY,
  //
  //   DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
  //   DYNAMIC_READ = GL_DYNAMIC_READ,
  //   DYNAMIC_COPY = GL_DYNAMIC_COPY,
  //
  //   STREAM_DRAW = GL_STREAM_DRAW,
  //   STREAM_READ = GL_STREAM_READ,
  //   STREAM_COPY = GL_STREAM_COPY,
  // };

  enum struct BufferFlag : GLbitfield {
    DYNAMIC_STORAGE = GL_DYNAMIC_STORAGE_BIT, // buffer can be updated
    MAP_READ = GL_MAP_READ_BIT,               // cpu can read in buffer
    MAP_WRITE = GL_MAP_WRITE_BIT,             // cpu can write to buffer
    MAP_PERSISTENT = GL_MAP_PERSISTENT_BIT,
    MAP_COHERENT = GL_MAP_COHERENT_BIT,
    CLIENT_STORAGE = GL_CLIENT_STORAGE_BIT, // buffer is stored in cpu mem
  };

  template <class T>
  concept IsVertex = std::is_constructible_v<T>;

} // namespace glaugl
