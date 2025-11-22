#pragma once
#include "glau/glaugl/_util.hh"
#include <glad/gl.h>
#include <utility>
#include <vector>
namespace glaugl {


  /**
   * @brief VBO generic template.
   * @note This template is simply a wrapper. It does not hold any actual vertex
   * data.
   *
   */
  template <IsVertex Vertex> class VertexBuffer {
    unsigned int id;


  public:
    VertexBuffer(VertexBuffer &other) = delete; // no copy construction
    VertexBuffer operator=(VertexBuffer &other) = delete; // no copy assignment


    VertexBuffer(std::vector<Vertex> data, unsigned int flags)
        : id(0) {
      glCreateBuffers(1, &id);
      glNamedBufferStorage(id, data.size() * sizeof(Vertex), data.data(),
                           flags);
    }


    ~VertexBuffer() {
      if (id != 0) glDeleteBuffers(1, &id);
    }


    // move construction
    VertexBuffer(VertexBuffer &&other) noexcept
        : id(std::exchange(other.id, 0)) {}

    // move assignment
    VertexBuffer &operator=(VertexBuffer &&other) noexcept {
      if (this != &other) {
        if (id != 0) {
          glDeleteBuffers(1, &id);
        }
        id = std::exchange(other.id, 0);
      }
      return *this;
    }


    unsigned int get_id() const { return id; }


    /**
     * @brief Update a subset of the buffer.
     * @param new_data
     * @param offset
     */
    void update(std::vector<Vertex> new_data, size_t offset) {
      glNamedBufferSubData(id, GL_ARRAY_BUFFER, offset * sizeof(Vertex),
                           new_data.size() * sizeof(Vertex), new_data.data());
    }
  };


} // namespace glaugl
