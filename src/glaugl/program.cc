#include "glau/glaugl/program.hh"
#include "glau/glaugl/_fwd.hh"
#include "glau/glaugl/_util.hh"
#include "glau/glaugl/shader.hh"
#include <spdlog/spdlog.h>


bool glaugl::ShaderProgram::get_link_status(bool log) {
  int success;
  glGetProgramiv(this->id, GL_LINK_STATUS, &success);

  if (!success && log) {
    char logstr[GLAUGL_LOG_SIZE];
    glGetProgramInfoLog(this->id, GLAUGL_LOG_SIZE, nullptr, logstr);
    spdlog::error("[GL] Program linking failed: {}", logstr);
  }
  return success;
}


glaugl::ShaderProgram::ShaderProgram(VertexShader *vert, FragmentShader *frag,
                                     GeometryShader *geom)
    : id(glCreateProgram())
    , vert(vert)
    , frag(frag)
    , geom(geom) {
  bool has_vert = (vert && vert->get_id() != 0);
  bool has_frag = (frag && frag->get_id() != 0);
  bool has_geom = (geom && geom->get_id() != 0);

  (has_vert) ? glAttachShader(this->id, vert->get_id())
             : spdlog::warn("[GL] No vertex shader specified");
  (has_frag) ? glAttachShader(this->id, frag->get_id())
             : spdlog::warn("[GL] No fragment shader specified");
  (has_geom) ? glAttachShader(this->id, frag->get_id())
             : spdlog::info("[GL] No geometry shader specified");

  glLinkProgram(this->id);

  if (!get_link_status(true)) {
    glDeleteProgram(this->id);
    this->id = 0;
  }
}


glaugl::ShaderProgram::~ShaderProgram() {
  if (this->id != 0) glDeleteProgram(this->id);
}


bool glaugl::ShaderProgram::swap_vert(const VertexShader *new_vert) {
  const VertexShader *old_vert = vert;
  bool has_old_vert = (old_vert && old_vert->get_id() != 0);
  bool has_new_vert = (new_vert && new_vert->get_id() != 0);

  // if both are nullptr or invalid, do nothing
  if (!has_old_vert && !has_new_vert) return true;
  // if old and new are the same shader, do nothing
  if (old_vert == new_vert) return true;

  // swap attachments
  if (has_old_vert) glDetachShader(this->id, old_vert->get_id());
  if (has_new_vert) glAttachShader(this->id, new_vert->get_id());

  glLinkProgram(this->id); // try linking

  if (!get_link_status(true)) {
    // unswap
    if (has_new_vert) glDetachShader(this->id, new_vert->get_id());
    if (has_old_vert) glAttachShader(this->id, old_vert->get_id());

    glLinkProgram(this->id); // revert linking
    return false;
  }

  this->vert = new_vert;
  return true;
}


bool glaugl::ShaderProgram::swap_frag(const FragmentShader *new_frag) {
  const FragmentShader *old_frag = frag;
  bool has_old_frag = (old_frag && old_frag->get_id() != 0);
  bool has_new_frag = (new_frag && new_frag->get_id() != 0);

  if (!has_old_frag && !has_new_frag) return true;
  if (old_frag == new_frag) return true;

  if (has_old_frag) glDetachShader(this->id, old_frag->get_id());
  if (has_new_frag) glAttachShader(this->id, new_frag->get_id());

  glLinkProgram(this->id);

  if (!get_link_status(true)) {
    if (has_new_frag) glDetachShader(this->id, new_frag->get_id());
    if (has_old_frag) glAttachShader(this->id, old_frag->get_id());
    glLinkProgram(this->id);
    return false;
  }

  this->frag = new_frag;
  return true;
}


bool glaugl::ShaderProgram::swap_geom(const GeometryShader *new_geom) {
  const GeometryShader *old_geom = geom;
  bool has_old_geom = (old_geom && old_geom->get_id() != 0);
  bool has_new_geom = (new_geom && new_geom->get_id() != 0);

  if (!has_old_geom && !has_new_geom) return true;
  if (old_geom == new_geom) return true;

  if (has_old_geom) glDetachShader(this->id, old_geom->get_id());
  if (has_new_geom) glAttachShader(this->id, new_geom->get_id());

  glLinkProgram(this->id);

  if (!get_link_status(true)) {
    if (has_new_geom) glDetachShader(this->id, new_geom->get_id());
    if (has_old_geom) glAttachShader(this->id, old_geom->get_id());
    glLinkProgram(this->id);
    return false;
  }

  this->geom = new_geom;
  return true;
}


void glaugl::ShaderProgram::use() { glUseProgram(this->id); }
