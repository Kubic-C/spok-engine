#include "components.h"
#include "spok/physics.h"
#include "core/state.h"

void comp_physics_new(ecs_iter_t* it) {
  comp_physics_tt* pc_arr = ecs_term(it, comp_physics_tt, 1);

  for(size_t i = 0; i < it->count; i++) {
    comp_physics_tt* p_pc = &pc_arr[i];

    glm_vec3_zero(p_pc->pos);
    glm_vec3_zero(p_pc->dynamics.dir);
    glm_vec3_one(p_pc->transform.rot);
    glm_vec3_one(p_pc->transform.scale);
    p_pc->transform.angle = 0.0f;
    p_pc->dynamics.speed = 0.0f;
  }
}

void comp_box2D_new(ecs_iter_t* it) {
  comp_box2D_tt* pc_arr = ecs_term(it, comp_box2D_tt, 1);

  for(size_t i = 0; i < it->count; i++) {
    comp_box2D_tt* p_pc = &pc_arr[i];

    glm_vec3_zero(p_pc->bl);
    glm_vec3_zero(p_pc->tr);
    glm_mat4_identity(p_pc->model);
  }
}

void physics_component_init(ecs_world_t* p_world) {
  active_tt* p_active = g_state.p_active;
  querys_tt* p_querys = &g_state.p_active->querys;

  ECS_COMPONENT_INIT(p_world, comp_box2D_tt);
  ECS_COMPONENT_INIT(p_world, comp_box3D_tt);
  ECS_COMPONENT_INIT(p_world, comp_physics_tt);

  ECS_TRIGGER(p_world, comp_physics_new, EcsOnAdd, comp_physics_tt);
  ECS_TRIGGER(p_world, comp_box2D_new, EcsOnAdd, comp_box2D_tt);

  p_querys->body2D_phys_comp = ecs_query_init(p_world, &(ecs_query_desc_t) {
    .filter.terms = {
          { ecs_id(comp_box2D_tt) },
          { ecs_id(comp_physics_tt) }
      }
  });

  p_querys->body3D_phys_comp = ecs_query_init(p_world, &(ecs_query_desc_t) {
    .filter = {
       .terms = {
          { ecs_id(comp_box3D_tt) },
          { ecs_id(comp_physics_tt) }
        }
      }
  });
}

void physics_component_term(ecs_world_t* p_world) {
  active_tt* p_active = g_state.p_active;
  querys_tt* p_querys = &g_state.p_active->querys;

  ecs_query_fini(p_querys->body2D_phys_comp);
  ecs_query_fini(p_querys->body3D_phys_comp);
}