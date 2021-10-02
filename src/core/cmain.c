#include "cmain.h"
#include "body.h"
#include "graphics/gmain.h"
#include "physics/pmain.h"
#include "state.h"

#define INITIAL_WIDTH 1000
#define INITIAL_HEIGHT 500
#define INITIAL_NAME "spok engine"

bool _spok_init(void) {
  active_tt* p_active = g_state.p_active;
  init_tt* p_init = g_state.p_init;

  if (!glfwInit())
    return false;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  p_active->window = glfwCreateWindow(INITIAL_WIDTH, INITIAL_HEIGHT, INITIAL_NAME, NULL, NULL);
  if (!p_active->window) {
    glfwTerminate();
    return false;
  } else {
    glfwMakeContextCurrent(p_active->window);
    glfwSwapInterval(0);
  }
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    return false;
  } else {
    glViewport(0, 0, INITIAL_WIDTH, INITIAL_HEIGHT);
  }

  p_active->time_since_last_frame = glfwGetTime();

  p_active->world = ecs_init();
  if (!gfx_init()) {
    glfwTerminate();
    return false;
  }
  if (!physics_init()) {
    glfwTerminate();
    return false;
  }

  return true;
}

void _spok_render(void) {
  gfx_update();
}

void _spok_update(void) {
  physics_update();
  box2D_update();
  box3D_update();
}

void _spok_term(void) {
  (void)ecs_fini(g_state.p_active->world); // don't care about return value for now
  glfwTerminate();
}