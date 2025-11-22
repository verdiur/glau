#pragma once
#include "glau/glaugl/_fwd.hh"
#include <spdlog/spdlog.h>
namespace glaugl {

  /**
   * @class ShaderProgram
   * @brief ShaderProgram class
   *
   */
  class ShaderProgram {
    unsigned int id;
    const VertexShader *vert;
    const FragmentShader *frag;
    const GeometryShader *geom;

    /**
     * @brief Get link status of shader program
     * @param log If true, log to the console in case of error
     * @return Link status
     */
    bool get_link_status(bool log);

  public:
    ShaderProgram(VertexShader *vert, FragmentShader *frag,
                  GeometryShader *geom);

    ShaderProgram(ShaderProgram &other);
    ShaderProgram operator=(ShaderProgram &other);

    ~ShaderProgram();

    const VertexShader *try_get_vert() const { return vert; }
    const FragmentShader *try_get_frag() const { return frag; }
    const GeometryShader *try_get_geom() const { return geom; }

    bool swap_vert(const VertexShader *new_vert);
    bool swap_frag(const FragmentShader *new_frag);
    bool swap_geom(const GeometryShader *new_geom);

    void use();
  };

} // namespace glaugl
