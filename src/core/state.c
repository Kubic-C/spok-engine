#include "state.h"
#include "spok/spok.h"

state_tt g_state;

bool spok_state_init(init_func_tt init,
                     core_func_tt render,
                     core_func_tt update,
                     core_func_tt term) {
  g_state.render = render;
  g_state.update = update;
  g_state.term = term;
  g_state.p_init = malloc(sizeof(init_tt));
  g_state.p_active = malloc(sizeof(active_tt));
  assert(g_state.p_init != NULL && g_state.p_active != NULL);
  *g_state.p_active = (active_tt){};
  *g_state.p_init = (init_tt){};
  return init();

}

void spok_state_terminate(state_tt* p_state) {
  p_state->term();
  free(g_state.p_init);
  free(g_state.p_active);
}