#version 400 core
#extension GL_ARB_separate_shader_objects : require
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex_coords;
layout(location = 2) in mat4 model;

layout(location = 0) out vec2 o_tex_coords;
layout(location = 1) out vec3 o_color;

uniform mat4 vp;
uniform vec3 color;

void main() {
  gl_Position = vp * model * vec4(pos, 1.0);
  o_tex_coords = tex_coords;
  o_color = color;
}