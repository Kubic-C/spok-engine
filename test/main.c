#include <spok/spok.h>

GLFWwindow* window = NULL;
euid_tt box;

bool init(void) {
  window = spok_get_window();
  glfwSetWindowTitle(window, "spok testing");
  glfwSetWindowSize(window, 700, 500);
  glClearColor(0.6f, 0.6f, 0.3f, 1.0f);
  spok_set_fov(90.0f);

  box = spok_box3D_add((vec3){0.0f, 0.0f, 0.0f}, (vec3){-0.1f, -0.1f, -0.1f}, (vec3){0.1f, 0.1f, 0.1f});
  comp_physics_tt* p_pc = (void*)ecs_get(spok_get_world(), box, comp_physics_tt);
  p_pc->dynamics.speed = 0.1f;
  //glm_vec3_copy((vec3){1.0f, 1.0f, 0.0f}, p_pc->transform.rot);
  
  spok_box3D_add((vec3){0.5f, 0.0f, 0.0f}, (vec3){-0.1f, -0.1f, -0.1f}, (vec3){0.1f, 0.1f, 0.1f});
  spok_box3D_add((vec3){0.0f, 0.5f, 0.0f}, (vec3){-0.1f, -0.1f, -0.1f}, (vec3){0.1f, 0.1f, 0.1f});
  spok_box3D_add((vec3){-0.5f, 0.0f, 0.0f}, (vec3){-0.1f, -0.1f, -0.1f}, (vec3){0.1f, 0.1f, 0.1f});
  spok_box3D_add((vec3){0.0f, -0.5f, 0.0f}, (vec3){-0.1f, -0.1f, -0.1f}, (vec3){0.1f, 0.1f, 0.1f});

  spok_box3D_add((vec3){1.0f, 0.0f, 0.0f}, (vec3){-0.1f, -0.1f, -0.1f}, (vec3){0.1f, 0.1f, 0.1f});
  spok_box3D_add((vec3){0.0f, 1.0f, 0.0f}, (vec3){-0.1f, -0.1f, -0.1f}, (vec3){0.1f, 0.1f, 0.1f});
  spok_box3D_add((vec3){-1.0f, 0.0f, 0.0f}, (vec3){-0.1f, -0.1f, -0.1f}, (vec3){0.1f, 0.1f, 0.1f});
  spok_box3D_add((vec3){0.0f, -1.0f, 0.0f}, (vec3){-0.1f, -0.1f, -0.1f}, (vec3){0.1f, 0.1f, 0.1f});

  spok_box3D_add((vec3){1.0f, 1.0f, 0.0f}, (vec3){-0.1f, -0.1f, -0.1f}, (vec3){0.1f, 0.1f, 0.1f});
  spok_box3D_add((vec3){1.0f, -1.0f, 0.0f}, (vec3){-0.1f, -0.1f, -0.1f}, (vec3){0.1f, 0.1f, 0.1f});
  spok_box3D_add((vec3){-1.0f, 1.0f, 0.0f}, (vec3){-0.1f, -0.1f, -0.1f}, (vec3){0.1f, 0.1f, 0.1f});
  spok_box3D_add((vec3){-1.0f, -1.0f, 0.0f}, (vec3){-0.1f, -0.1f, -0.1f}, (vec3){0.1f, 0.1f, 0.1f});

  return true;
}

bool update(void) {
  const float speed = 0.01f;
  comp_physics_tt* p_pc = (void*)ecs_get(spok_get_world(), box, comp_physics_tt);
  //p_pc->transform.angle += speed;

  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    p_pc->dynamics.dir[0] -= speed; 
  }
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    p_pc->dynamics.dir[0] += speed; 
  }
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    p_pc->dynamics.dir[1] += speed; 
  }
  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    p_pc->dynamics.dir[1] -= speed; 
  }

  return true;  
}

void term(void) {
}

int main() {
  if(!spok_init(init, update, term)) {
    return EXIT_FAILURE;
  }

  return spok_run();
}