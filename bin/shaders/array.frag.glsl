#version 400 core
#extension GL_ARB_separate_shader_objects : require
layout(location = 0) in vec2 o_tex_coords;
layout(location = 1) in vec3 o_color;

void main() {
  gl_FragColor = vec4(o_color, 1.0);
}