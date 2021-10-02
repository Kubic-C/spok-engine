#include "state.h"
#include "cmain.h"
#include "graphics/gmain.h"
#include "physics/pmain.h"
#include "body.h"

#define FPS_LIMITER (1.0 / SPOK_TICKS_PER_SECOND)

#ifdef NDEBUG
#define DO_IF_DEBUG(x)
#else // !NDEBUG
#define DO_IF_DEBUG(x) x
#endif // NDEBUG

bool spok_init(spok_init_func_tt user_init, spok_update_func_tt user_update, spok_term_func_tt user_term) {
  if(!spok_state_init(_spok_init, _spok_render, _spok_update, _spok_term))
    return false;

  g_state.p_active->user_update = user_update;
  g_state.p_init->user_term = user_term;
  user_init();
  return true;
}

void spok_term(void) {
  g_state.p_init->user_term(); 
  g_state.term();
}

INLINE void update_delta_time() {
  active_tt* p_active = g_state.p_active;
  float curret_frame = glfwGetTime();
  
  p_active->delta_time = (curret_frame - p_active->time_since_last_frame);
  p_active->how_many_updates += p_active->delta_time / FPS_LIMITER;
  p_active->time_since_last_frame = curret_frame;
}

int spok_run() {
  active_tt* p_active = g_state.p_active;
  double timer = p_active->time_since_last_frame;
  int frames = 0, updates = 0;

  while (!glfwWindowShouldClose(p_active->window)) {
    glfwPollEvents();
    update_delta_time();

    while(p_active->how_many_updates >= 1.0) { // one repersents second
      p_active->how_many_updates--;

      g_state.update();
      if (!p_active->user_update()) {
        break;
      }

      updates++;
    }

    g_state.render();
    frames++;

    if(glfwGetTime() - timer > 1.0) {
      timer++;
      p_active->frames = frames,  p_active->updates = updates;
      printf("FPS: %4u | UPS: %3u | DELTA: %1.8f\n", frames, updates, p_active->delta_time);
      frames = 0, updates = 0;
    }
  }

  spok_term();
  return EXIT_SUCCESS;
}

void spok_entity_free(euid_tt id) {
  ecs_world_t* p_world = g_state.p_active->world;

  ecs_delete(p_world, id);
}

GLFWwindow* spok_get_window(void) {
  return g_state.p_active->window;
}

ecs_world_t* spok_get_world(void) {
  return g_state.p_active->world;
}

uint32_t spok_get_ups(void) {
  return g_state.p_active->updates;
}

uint32_t spok_get_fps(void) {
  return g_state.p_active->frames;
}

double spok_get_delta(void) {
  return g_state.p_active->delta_time;
}

double spok_get_time(void) {
  return glfwGetTime();
}
