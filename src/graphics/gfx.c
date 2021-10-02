#include "spok/gfx.h"
#include "core/state.h"
#include "render.h"

void spok_set_fov(float fov) {
  render_state_tt* p_render_state = ((render_state_tt*)g_state.p_active->render_data);
  int width, height;

  p_render_state->fov = fov;
  glfwGetWindowSize(g_state.p_active->window, &width, &height);
  glm_perspective(glm_rad(p_render_state->fov), (float)width / (float)height, NEARZ, FARZ, p_render_state->proj);  
}
