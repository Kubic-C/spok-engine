#include "gmain.h"
#include "render.h"
#include "shader.h"
#include "utility/utils.h"
#include "core/state.h"

vec3 color = { 1.0f, 1.0f, 1.0f };

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
  active_tt* p_active = g_state.p_active;
  render_state_tt* p_render_state = p_active->render_data;

  if(width != 0 && height != 0) {
    glm_perspective(glm_rad(p_render_state->fov), (float)width / (float)height, NEARZ, FARZ, p_render_state->proj); 
    glViewport(0, 0, width, height);
  }
}

bool gfx_init() {
  uint32_t program;
  mat4 vp;
  active_tt* p_active = g_state.p_active;
  p_active->render_data = malloc(sizeof(render_state_tt));
  render_state_tt* p_render_state = p_active->render_data;
  assert(p_active->render_data != NULL);

  glfwSetFramebufferSizeCallback(p_active->window, framebuffer_resize_callback);
  glEnable(GL_DEPTH_TEST);

  {
    int width, height;
    
    glfwGetWindowSize(p_active->window, &width, &height);
    p_render_state->fov = 45.0f;
    glm_perspective(glm_rad(p_render_state->fov), (float)width / (float)height, NEARZ, FARZ, p_render_state->proj);  
    glm_lookat((vec3){0.0f, 0.0f, 1.0f}, (vec3){0.0f, 0.0f, 0.0f}, (vec3){0.0f, 1.0f, 0.0f}, p_render_state->view);
  }

  program = program_new_dir("./shaders/array.vert.glsl", "./shaders/array.frag.glsl");
  if(!render_batch_arrays_new(&p_render_state->batch, GL_TRIANGLES, program, 10000))
    return false;

  return true;
}

void gfx_update() {
  active_tt* p_active = g_state.p_active;
  render_state_tt* p_render_state = (render_state_tt*)p_active->render_data;
  int glerror;

  glm_mul(p_render_state->proj, p_render_state->view, p_render_state->vp);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  render_batch_arrays(&p_render_state->batch);
  glfwSwapBuffers(p_active->window);

  glerror = glGetError();
  if(glerror != 0) {
    printf("glerror: %i\n", glerror);
    glfwSetWindowShouldClose(p_active->window, 1);
  }
}

void gfx_term() {
  active_tt* p_active = g_state.p_active;

  free(p_active->render_data);
}