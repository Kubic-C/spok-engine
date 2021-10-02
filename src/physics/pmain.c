#include "pmain.h"
#include "graphics/render.h"
#include "core/state.h"
#include "components.h"

bool physics_init() {
  active_tt* p_active = g_state.p_active;

  physics_component_init(p_active->world);

  return true;
}

void physics_update() {
}

void physics_term() {
  physics_component_term(g_state.p_active->world);
}
