#include "body.h"
#include "core/state.h"
#include "physics/body.h"
#include "graphics/body.h"

void box2D_update() {
  active_tt* p_active = g_state.p_active;
  querys_tt* p_querys = &g_state.p_active->querys;
  ecs_iter_t iter;
  size_t index = 0;

  iter = ecs_query_iter(p_active->world, p_querys->body2D_phys_comp);
  while(ecs_query_next(&iter)) {
    comp_box2D_tt* box2D_arr = ecs_term(&iter, comp_box2D_tt, 1);
    comp_physics_tt* p_arr = ecs_term(&iter, comp_physics_tt, 2);
    vec3 mov;

    for(size_t i = 0; i < iter.count; i++) {
      comp_box2D_tt* p_box2D = box2D_arr + i;
      comp_physics_tt* p_p = p_arr + i;     

      physics_box2D_update(p_box2D, p_arr);
      gfx_update_box2D(p_box2D, index);
      index++;
    }
  }
}

void box3D_update() {
  active_tt* p_active = g_state.p_active;
  querys_tt* p_querys = &g_state.p_active->querys;
  ecs_iter_t iter;
  size_t index = 0;

  iter = ecs_query_iter(p_active->world, p_querys->body3D_phys_comp);
  while(ecs_query_next(&iter)) {
    comp_box3D_tt* box3D_arr = ecs_term(&iter, comp_box3D_tt, 1);
    comp_physics_tt* p_arr = ecs_term(&iter, comp_physics_tt, 2);
    vec3 mov;

    for(size_t i = 0; i < iter.count; i++) {
      comp_box3D_tt* p_box3D = box3D_arr + i;
      comp_physics_tt* p_p = p_arr + i;     

      physics_box3D_update(p_box3D, p_p);
      gfx_update_box3D(p_box3D, index);
      index++;
    }
  }
}
