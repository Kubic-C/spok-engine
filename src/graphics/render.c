#include "render.h"
#include "core/state.h"

bool render_batch_arrays_new(render_batch_arrays_tt* p_batch, uint32_t draw_mode, uint32_t program, size_t max_vertices) {
  p_batch->program = program;
  p_batch->vertice_count = 0;
  p_batch->max_vertices = max_vertices;
  p_batch->draw_mode = draw_mode;

  glGenVertexArrays(1, &p_batch->sl.vao);
  glGenBuffers(2, p_batch->sl.vbos); // model matrix arrays not used in array buffers

  {
    glBindVertexArray(p_batch->sl.vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // POSITIONS
    glBindBuffer(GL_ARRAY_BUFFER, p_batch->sl.vbos[SPOK_VERTEX_BUFFER_POSITIONS]);
    glBufferData(GL_ARRAY_BUFFER, max_vertices * sizeof(vec3), NULL, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL);

    // TEXTURE COORDS
    glBindBuffer(GL_ARRAY_BUFFER, p_batch->sl.vbos[SPOK_VERTEX_BUFFER_TEX_COORDS]);
    glBufferData(GL_ARRAY_BUFFER, max_vertices * sizeof(vec2), NULL, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * (2 + 3), NULL);
  }

  return true;
}

void render_batch_arrays_set(render_batch_arrays_tt* p_batch, size_t bytevert, size_t offset, size_t size, float* pos, float* tex) {
  assert((size / bytevert) + (offset / bytevert) < p_batch->max_vertices);

  if(pos) {
    glBindBuffer(GL_ARRAY_BUFFER, p_batch->sl.vbos[SPOK_VERTEX_BUFFER_POSITIONS]);
    glBufferSubData(GL_ARRAY_BUFFER, offset * bytevert, size * bytevert, pos);
  }
  if(tex) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_batch->sl.vbos[SPOK_VERTEX_BUFFER_POSITIONS]);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * bytevert, size * bytevert, tex);
  }
} 

void render_batch_arrays_free(render_batch_arrays_tt* p_batch) {
  glDeleteBuffers(2, p_batch->sl.vbos);
  glDeleteVertexArrays(1, &p_batch->sl.vao);
}

bool render_batch_instance_indexed_new(render_batch_instance_indexed_tt* p_batch, 
                                       uint32_t draw_mode,
                                       uint32_t program, 
                                       size_t max_instances, 
                                       size_t vertice_count, 
                                       float* pos, 
                                       float* tex_coords, 
                                       uint32_t* indices) {
  p_batch->program = program;
  p_batch->vertice_count = vertice_count;
  p_batch->max_instances = max_instances;
  p_batch->draw_mode = draw_mode;
  p_batch->instance_count = 0;

  glGenVertexArrays(1, &p_batch->sl.vao);
  glGenBuffers(3, p_batch->sl.vbos);
  glGenBuffers(1, &p_batch->index_buffer);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_batch->index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertice_count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

  {
    glBindVertexArray(p_batch->sl.vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);

    // POSITIONS
    glBindBuffer(GL_ARRAY_BUFFER, p_batch->sl.vbos[SPOK_VERTEX_BUFFER_POSITIONS]);
    glBufferData(GL_ARRAY_BUFFER, vertice_count * sizeof(vec3), pos, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL);

    // TEXTURE COORDS
    glBindBuffer(GL_ARRAY_BUFFER, p_batch->sl.vbos[SPOK_VERTEX_BUFFER_TEX_COORDS]);
    glBufferData(GL_ARRAY_BUFFER, vertice_count * sizeof(vec2), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * (2 + 3), NULL);

    // MATRIX
    glBindBuffer(GL_ARRAY_BUFFER, p_batch->sl.vbos[SPOK_VERTEX_BUFFER_MODEL_MATRIX]);
    glBufferData(GL_ARRAY_BUFFER, max_instances * sizeof(mat4) , NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 0));
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 4));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 8));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 12));
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
  }

  return true;
}

void render_batch_instance_indexed_set_instance(render_batch_instance_indexed_tt* p_batch, uint32_t index, mat4 model) {
  assert(index < p_batch->max_instances + 1);

  glBindVertexArray(p_batch->sl.vao);
  glBindBuffer(GL_ARRAY_BUFFER, p_batch->sl.vbos[SPOK_VERTEX_BUFFER_MODEL_MATRIX]);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(mat4) * index, sizeof(mat4), &model[0][0]);
}

void render_batch_instance_indexed_set_instances(render_batch_instance_indexed_tt* p_batch, uint32_t starting_index, size_t count, mat4* p_model) {
  assert((starting_index + count) < p_batch->max_instances + 1);

  glBindVertexArray(p_batch->sl.vao);
  glBindBuffer(GL_ARRAY_BUFFER, p_batch->sl.vbos[SPOK_VERTEX_BUFFER_MODEL_MATRIX]);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(mat4) * starting_index, sizeof(mat4) * count, &(*p_model)[0][0]);
}

void render_batch_instance_indexed_free(render_batch_instance_indexed_tt* p_batch) {
  glDeleteBuffers(3, p_batch->sl.vbos);
  glDeleteBuffers(1, &p_batch->index_buffer);
  glDeleteVertexArrays(1, &p_batch->sl.vao);
}

vec3 color_ = {1.0f, 1.0f, 0.0f}; // temp

void render_batch_arrays(render_batch_arrays_tt* p_batch) {
  active_tt* p_active = g_state.p_active;
  render_state_tt* p_render_state = (render_state_tt*)p_active->render_data;

  if(p_batch->vertice_count != 0) {
    glUseProgram(p_batch->program);
    glUniformMatrix4fv(glGetUniformLocation(p_batch->program, "vp"), 1, GL_FALSE, &p_render_state->vp[0][0]);
    glUniform3fv(glGetUniformLocation(p_batch->program, "color"), 1, color_);
    glBindVertexArray(p_batch->sl.vao);
    glDrawArrays(p_batch->draw_mode, 0, p_batch->vertice_count);
  }
}

void render_batch_indexed(render_batch_indexed_tt* p_batch) {
  if(p_batch->vertice_count != 0) {
    glUseProgram(p_batch->program);
    glBindVertexArray(p_batch->sl.vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_batch->index_buffer);
    glDrawElements(p_batch->draw_mode, p_batch->vertice_count, SPOK_ELEMENT_ARRAY_TYPE, 0);
  }
}

void render_batch_instance_indexed(render_batch_instance_indexed_tt* p_batch) {
  if(p_batch->instance_count != 0) {
    glUseProgram(p_batch->program);
    glBindVertexArray(p_batch->sl.vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_batch->index_buffer);
    glDrawElementsInstanced(p_batch->draw_mode, p_batch->vertice_count, SPOK_ELEMENT_ARRAY_TYPE, 0, p_batch->instance_count);
  }
}