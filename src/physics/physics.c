#include "spok/physics.h"
#include "core/state.h"

euid_tt spok_box2D_add(vec2 pos, vec2 bl, vec2 tr) {
  ecs_world_t* p_world = g_state.p_active->world;
  comp_physics_tt* p_pc;
  comp_box2D_tt* p_b2D;
  euid_tt id;

  id = ecs_new_id(p_world);

  ecs_add_id(p_world, id, ecs_id(comp_box2D_tt));
  p_b2D = (comp_box2D_tt*)ecs_get_id(p_world, id, ecs_id(comp_box2D_tt));
  glm_vec2_copy(bl, p_b2D->bl);
  glm_vec2_copy(tr, p_b2D->tr);

  ecs_add_id(p_world, id, ecs_id(comp_physics_tt));
  p_pc = (comp_physics_tt*)ecs_get_id(p_world, id, ecs_id(comp_physics_tt));
  glm_vec3_copy((vec3){pos[0], pos[1], 0.0f}, p_pc->pos);

  return id;
} 

euid_tt spok_box3D_add(vec3 pos, vec3 bl, vec3 tr) {
  ecs_world_t* p_world = g_state.p_active->world;
  comp_physics_tt* p_pc;
  comp_box3D_tt* p_b3D;
  euid_tt id;

  id = ecs_new_id(p_world);
  ecs_add_id(p_world, id, ecs_id(comp_box3D_tt));
  p_b3D = (comp_box3D_tt*)ecs_get_id(p_world, id, ecs_id(comp_box3D_tt));
  glm_vec3_copy(bl, p_b3D->bl);
  glm_vec3_copy(tr, p_b3D->tr); 

  ecs_add_id(p_world, id, ecs_id(comp_physics_tt));
  p_pc = (comp_physics_tt*)ecs_get_id(p_world, id, ecs_id(comp_physics_tt));
  glm_vec3_copy((vec3){pos[0], pos[1], 0.0f}, p_pc->pos);

  return id;
}

void spok_physics_set_dir(euid_tt id, vec3 dir, float speed) {
  ecs_world_t* p_world = g_state.p_active->world;
  comp_physics_tt* p_p;

  p_p = (void*)ecs_get(p_world, id, comp_physics_tt);
  glm_vec3_copy(dir, p_p->dynamics.dir);
  if(p_p->dynamics.speed != FLOAT_MAX)
    p_p->dynamics.speed = speed;
}

void spok_physics_set_rot(euid_tt id, vec3 rot, float angle) {
  ecs_world_t* p_world = g_state.p_active->world;
  comp_physics_tt* p_p;

  p_p = (void*)ecs_get(p_world, id, comp_physics_tt);
  glm_vec3_copy(rot, p_p->transform.rot);
  if(angle != FLOAT_MAX)
    p_p->transform.angle = angle;
}

void spok_physics_set_scale(euid_tt id, vec3 scale) {
  ecs_world_t* p_world = g_state.p_active->world;
  comp_physics_tt* p_p;

  p_p = (void*)ecs_get(p_world, id, comp_physics_tt);
  glm_vec3_copy(scale, p_p->transform.scale);  
}

void spok_physics_set_pos(euid_tt id, vec3 pos) {
  ecs_world_t* p_world = g_state.p_active->world;
  comp_physics_tt* p_p;

  p_p = (void*)ecs_get(p_world, id, comp_physics_tt);
  glm_vec3_copy(pos, p_p->pos);    
}