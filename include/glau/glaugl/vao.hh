#pragma once
#include "glau/glaugl/_util.hh"
#include "glau/glaugl/vbo.hh"
#include <GL/gl.h>
#include <cstddef>
#include <utility>
namespace glaugl {


  /**
   * @brief Vertex Array Object generic template.
   * @note This template is simply a wrapper. It does not hold any actual data.
   *
   */
  template <IsVertex Vertex> class VertexArray {
    unsigned int id;


  public:
    VertexArray(VertexArray &other) = delete;           // no copy construction
    VertexArray operator=(VertexArray &other) = delete; // no copy assignment


    VertexArray()
        : id(0) {
      glCreateVertexArrays(1, &id);
    }


    ~VertexArray() {
      if (id != 0) glDeleteVertexArrays(1, &id);
    }


    VertexArray(VertexArray &&other) noexcept // move construction
        : id(std::exchange(other.id, 0)) {}


    VertexArray &operator=(VertexArray &&other) noexcept { // move assignment
      if (this != &other) {
        if (id != 0) {
          glDeleteVertexArrays(1, &id);
        }
        id = std::exchange(other.id, 0);
      }
      return *this;
    }


    unsigned int get_id() const { return id; }


    /**
     * @brief Bind a VBO to a buffer slot in the VAO.
     * @param slot
     * @param vbo
     * @param offset
     * @param stride
     */
    void bind_vbo(unsigned int slot, VertexBuffer<Vertex> &vbo, size_t offset,
                  size_t stride) {
      glVertexArrayVertexBuffer(id, slot, vbo.get_id(), offset, stride);
    }


    /**
     * @brief Bind a vertex attribute to a buffer slot in the VAO.
     * @param attribute
     * @param slot
     */
    void bind_attribute(unsigned int slot, unsigned int attribute) {
      glBindBuffer(attribute, slot);
    }


    /**
     * @brief Specify how an attribute should be read from the VBO bound to the
     * same slot. This is for float attributes.
     *
     * @param attribute
     * @param size
     * @param normalized
     * @param relative_offset
     */
    void format_attribute_float(unsigned int attribute, int size,
                                bool normalized, unsigned int relative_offset) {
      glVertexArrayAttribFormat(id, attribute, size, GL_FLOAT, normalized,
                                relative_offset);
    }


    /**
     * @brief Specify how an attribute should be read from the VBO bound to the
     * same slot. This is for int attributes.
     *
     * @param attribute
     * @param size
     * @param relative_offset
     */
    void format_attribute_int(unsigned int attribute, int size,
                              unsigned int relative_offset) {
      glVertexArrayAttribIFormat(id, attribute, size, GL_INT, relative_offset);
    }


    /**
     * @brief Enable an attribute
     * @param attribute
     */
    void enable_attribute(unsigned int attribute) {
      glEnableVertexArrayAttrib(id, attribute);
    }


    /**
     * @brief Disable an attribute
     * @param attribute
     */
    void disable_attribute(unsigned int attribute) {
      glDisableVertexArrayAttrib(id, attribute);
    }


    /**
     * @brief Placeholder
     * TODO:
     */
    void draw() {
      glBindVertexArray(this->id);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glBindVertexArray(0);
    }
  };


} // namespace glaugl
