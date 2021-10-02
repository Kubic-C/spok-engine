#ifndef _SPOK_ENGINE_CORE_STATE_H_INCLUDED
#define _SPOK_ENGINE_CORE_STATE_H_INCLUDED

#include "spok/spok.h"

typedef void(*core_func_tt)(void);
typedef bool(*init_func_tt)(void);

typedef struct {
  spok_term_func_tt user_term;
} init_tt;

typedef struct {
  ecs_query_t* body2D_phys_comp;
  ecs_query_t* body3D_phys_comp;
} querys_tt;

typedef struct active_tt {
  spok_update_func_tt user_update;
  ecs_world_t* world;
  GLFWwindow* window;
  void* render_data;
  void* physics_data;
  uint32_t frames, updates;
  double time_since_last_frame;
  double how_many_updates; // how many updates to call to acheive TICKS_PER_SECOND
  double delta_time;
  querys_tt querys;
} active_tt;

typedef struct {
  core_func_tt render, update, term;
  init_tt* p_init;
  active_tt* p_active;
} state_tt;

extern state_tt g_state;

// allocates init and active data, calls init function, DOES NOT INITIALZIE SPOK!
bool spok_state_init(init_func_tt init, 
                     core_func_tt render, 
                     core_func_tt update, 
                     core_func_tt term);
                     
// calls terminate, then frees all data
void spok_state_terminate(state_tt* p_state);

#endif  // _SPOK_ENGINE_CORE_STATE_H_INCLUDED