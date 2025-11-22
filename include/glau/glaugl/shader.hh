#pragma once
#include "glau/glaugl/_def.hh"
#include <glad/gl.h>
#include <spdlog/spdlog.h>
#include <string>
#include <string_view>
#include <utility>
namespace glaugl {


  template <int ShaderType> class Shader {
    unsigned int id;
    std::string src;


    /**
     * @brief Get compilation status of shader
     * @param log If true, log to the console in case of error
     * @return Compilation status
     */
    int get_compile_status(bool log) {
      int success;
      glGetShaderiv(id, GL_COMPILE_STATUS, &success);

      if (!success && log) {
        char logstr[GLAUGL_LOG_SIZE];
        glGetShaderInfoLog(id, GLAUGL_LOG_SIZE, nullptr, logstr);
        spdlog::error("[GL] Shader compilation failed: {}", logstr);
      }
      return success;
    }


  public:
    /**
     * @brief Class constructor
     * @param src
     */
    Shader(std::string src)
        : id(glCreateShader(ShaderType))
        , src(src) {
      const char *cstr = this->src.c_str();
      glShaderSource(id, 1, &cstr, nullptr);
      glCompileShader(id);

      if (!get_compile_status(true)) {
        glDeleteShader(id);
        this->id = 0;
        this->src = "";
      }

      this->src = src;
    }


    /**
     * @brief Copy constructor. Deep copies the shader with a new id.
     * @param other
     */
    Shader(Shader &other) noexcept {
      if (other.id == 0) return;

      this->id = glCreateShader(ShaderType);
      this->src = other.src;

      // no need to check compile status because we know the copy will also
      // compile
      const char *cstr = this->src.c_str();
      glShaderSource(id, 1, &cstr, nullptr);
      glCompileShader(id);
    }


    /**
     * @brief Copy assignment operator. Deep copies the shader with a new id.
     * @param other
     * @return Copied shader
     */
    Shader operator=(Shader &other) noexcept {
      if (other.id == 0) {
        return Shader{};
      } else {
        return Shader(other.src);
      }
    }


    /**
     * @brief Move constructor. The underlying shader is left untouched,
     * this simply moves the @ref Shader handle class.
     *
     * @param other
     */
    Shader(Shader &&other) noexcept
        : id(std::exchange(other.id, 0))
        , src(std::exchange(other.src, "")) {}


    /**
     * @brief Move assignment operator. The underlying shader is left untouched,
     * this simply moves the @ref Shader handle class.
     *
     * @param other
     * @return Moved Shader handle
     */
    Shader &operator=(Shader &&other) noexcept {
      if (this != &other) {
        if (this->id != 0) {
          glDeleteShader(this->id);
        }
        this->id = std::exchange(other.id, 0);
        this->src = std::exchange(other.src, "");
      }
      return *this;
    }


    unsigned int get_id() const { return id; }
    std::string_view get_src() const { return src; }
  };


  using VertexShader = Shader<GL_VERTEX_SHADER>;
  using FragmentShader = Shader<GL_FRAGMENT_SHADER>;
  using GeometryShader = Shader<GL_GEOMETRY_SHADER>;


} // namespace glaugl
