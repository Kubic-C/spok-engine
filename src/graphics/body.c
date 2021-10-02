#include "body.h"
#include "render.h"
#include "core/state.h"

void gfx_update_box2D(comp_box2D_tt* p_box, size_t index) {
  render_state_tt* p_render_state = g_state.p_active->render_data;
  render_batch_arrays_tt* p_batch = &p_render_state->batch;

  float vertices[] = {
    p_box->tr[0], p_box->tr[1], 0.0f,
    p_box->tr[0], p_box->bl[1], 0.0f,
    p_box->bl[0], p_box->tr[1], 0.0f,

    p_box->tr[0], p_box->bl[1], 0.0f,
    p_box->bl[0], p_box->bl[1], 0.0f,
    p_box->bl[0], p_box->tr[1], 0.0f,
  };  

  for(size_t i = 0; i < 18; i += 3) {
    glm_mat4_mulv3(p_box->model, (vec3){vertices[i], vertices[i + 1], vertices[i + 2]}, 1.0f, &vertices[i]);
  }

  render_batch_arrays_set(p_batch, sizeof(vertices), index, 1, vertices, NULL);
  p_batch->vertice_count = (18 / 3) * (index + 1);
}

void gfx_update_box3D(comp_box3D_tt* p_box, size_t index) {
  render_state_tt* p_render_state = g_state.p_active->render_data;
  render_batch_arrays_tt* p_batch = &p_render_state->batch;

  // certainly not the most efficient way to calculate vertices
  float vertices[] = {
    p_box->bl[0], p_box->bl[1], p_box->bl[2],
    p_box->tr[0], p_box->bl[1], p_box->bl[2],
    p_box->tr[0], p_box->tr[1], p_box->bl[2],
    p_box->tr[0], p_box->tr[1], p_box->bl[2],
    p_box->bl[0], p_box->tr[1], p_box->bl[2],
    p_box->bl[0], p_box->tr[1], p_box->bl[2],

    p_box->bl[0], p_box->bl[1], p_box->tr[2],
    p_box->tr[0], p_box->bl[1], p_box->tr[2],
    p_box->tr[0], p_box->tr[1], p_box->tr[2],
    p_box->tr[0], p_box->tr[1], p_box->tr[2],
    p_box->bl[0], p_box->tr[1], p_box->tr[2],
    p_box->bl[0], p_box->bl[1], p_box->bl[2],

    p_box->bl[0], p_box->tr[1], p_box->tr[2],
    p_box->bl[0], p_box->tr[1], p_box->bl[2],
    p_box->bl[0], p_box->bl[1], p_box->bl[2],
    p_box->bl[0], p_box->bl[1], p_box->bl[2],
    p_box->bl[0], p_box->bl[1], p_box->tr[2],
    p_box->bl[0], p_box->tr[1], p_box->tr[2],

    p_box->tr[0], p_box->tr[1], p_box->tr[2],
    p_box->tr[0], p_box->tr[1], p_box->bl[2],
    p_box->tr[0], p_box->bl[1], p_box->bl[2],
    p_box->tr[0], p_box->bl[1], p_box->bl[2],
    p_box->tr[0], p_box->bl[1], p_box->tr[2],
    p_box->tr[0], p_box->tr[1], p_box->tr[2],

    p_box->bl[0], p_box->bl[1], p_box->bl[2],
    p_box->tr[0], p_box->bl[1], p_box->bl[2],
    p_box->tr[0], p_box->bl[1], p_box->tr[2],
    p_box->tr[0], p_box->bl[1], p_box->tr[2],
    p_box->bl[0], p_box->bl[1], p_box->tr[2],
    p_box->bl[0], p_box->bl[1], p_box->bl[2],

    p_box->bl[0], p_box->tr[1], p_box->bl[2],
    p_box->tr[0], p_box->tr[1], p_box->bl[2],
    p_box->tr[0], p_box->tr[1], p_box->tr[2],
    p_box->tr[0], p_box->tr[1], p_box->tr[2],
    p_box->bl[0], p_box->tr[1], p_box->tr[2],
    p_box->bl[0], p_box->tr[1], p_box->bl[2]
  };  

  for(size_t i = 0; i < 108; i += 3) {
    glm_mat4_mulv3(p_box->model, (vec3){vertices[i], vertices[i + 1], vertices[i + 2]}, 1.0f, &vertices[i]);
  }

  render_batch_arrays_set(p_batch, sizeof(vertices), index, 1, vertices, NULL);
  p_batch->vertice_count = (108 / 3) * (index + 1);
}