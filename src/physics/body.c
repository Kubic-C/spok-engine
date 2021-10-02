#include "body.h"
#include "core/state.h"

void physics_box2D_update(comp_box2D_tt* p_box, comp_physics_tt* p_pc) {
  vec3 mov;

  glm_mat4_identity(p_box->model);
  glm_translate(p_box->model, p_pc->pos);
  glm_rotate(p_box->model, p_pc->transform.angle, p_pc->transform.rot);
  glm_scale(p_box->model, p_pc->transform.scale);

  // update pos
  glm_vec3_scale(p_pc->dynamics.dir, p_pc->dynamics.speed, mov);
  glm_vec3_add(p_pc->pos, mov, p_pc->pos);
}

void physics_box3D_update(comp_box3D_tt* p_box, comp_physics_tt* p_pc) { 
  vec3 mov;
  
  glm_mat4_identity(p_box->model);
  glm_translate(p_box->model, p_pc->pos);
  glm_rotate(p_box->model, p_pc->transform.angle, p_pc->transform.rot);
  glm_scale(p_box->model, p_pc->transform.scale);

  // update pos
  glm_vec3_scale(p_pc->dynamics.dir, p_pc->dynamics.speed, mov);
  glm_vec3_add(p_pc->pos, mov, p_pc->pos);
}
