#include "shader.h"
#include "core/state.h"
#include "utility/utils.h"

uint32_t shader_new(uint32_t type, size_t size, char* src) {
  uint32_t shader = glCreateShader(type);
  int glsize = (int)size; // converting a unsigned to an int
  int success;

  glShaderSource(shader, 1, (const char* const*)&src, &glsize);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infolog[512];
    glGetShaderInfoLog(shader, 512, NULL, infolog);
    printf("SHADER COMPILATION FAILED: %s", infolog);
    glDeleteShader(shader);
    return UINT32_MAX;
  } else {
    return shader;
  }
}

uint32_t program_new_dir(const char* vert_dir, const char* frag_dir) {
  uint32_t program;
  uint32_t shaders[2];
  struct {
    size_t size;
    char* src;
  } shader_src[2];

  if(!util_file_read(vert_dir, &shader_src[0].size, &shader_src[0].src)) {
    return false;
  }
  if(!util_file_read(frag_dir, &shader_src[1].size, &shader_src[1].src)) {
    util_file_cleanup_read(shader_src[0].src);
    return false;
  }

  shaders[0] = shader_new(GL_VERTEX_SHADER, shader_src[0].size, shader_src[0].src);
  util_file_cleanup_read(shader_src[0].src);
  if(shaders[0] == UINT32_MAX) {
    util_file_cleanup_read(shader_src[1].src);
    return false;
  }
  shaders[1] = shader_new(GL_FRAGMENT_SHADER, shader_src[1].size, shader_src[1].src);
  util_file_cleanup_read(shader_src[1].src);
  if(shaders[1] == UINT32_MAX) {
    return false;
  }

  program = program_new(2, shaders);
  return program;
}

uint32_t program_new(size_t count, uint32_t* p_shaders) {
  uint32_t program = glCreateProgram();
  int success;

  for(size_t i = 0; i < count; i++) 
    glAttachShader(program, p_shaders[i]);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    char infolog[512];
    glGetProgramInfoLog(program, 512, NULL, infolog);
    printf("PROGRAM LINKING FAILED: %s", infolog);
    glDeleteProgram(program);
    return UINT32_MAX;
  } else {
    return program;
  }
}