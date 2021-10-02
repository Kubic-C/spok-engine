#ifndef _SPOK_ENGINE_GRAPHICS_RENDER_H_INCLUDED
#define _SPOK_ENGINE_GRAPHICS_RENDER_H_INCLUDED

#include "spok/spok.h"

#define SPOK_ELEMENT_ARRAY_TYPE GL_UNSIGNED_INT

#define NEARZ 0.1f
#define FARZ 100.0f

typedef enum {
  SPOK_VERTEX_BUFFER_POSITIONS = 0,
  SPOK_VERTEX_BUFFER_TEX_COORDS = 1,
  SPOK_VERTEX_BUFFER_MODEL_MATRIX = 2
} vertex_buffer_index_tt;

typedef struct {
  uint32_t vao;
  uint32_t vbos[8];
} shader_layout_tt;

typedef struct {
  size_t vertice_count;
  size_t max_vertices;
  uint32_t draw_mode;
  uint32_t program;
  shader_layout_tt sl;
} render_batch_arrays_tt;

typedef struct {
  size_t vertice_count;
  uint32_t index_buffer;
  uint32_t draw_mode;
  uint32_t program;
  shader_layout_tt sl;
} render_batch_indexed_tt;

typedef struct {
  size_t max_instances;
  size_t instance_count;
  size_t vertice_count;
  uint32_t index_buffer;
  uint32_t draw_mode;
  uint32_t program;
  shader_layout_tt sl;
} render_batch_instance_indexed_tt;

typedef struct {
  float fov;
  mat4 view;
  mat4 proj;
  mat4 vp;
  render_batch_arrays_tt batch;
} render_state_tt;
 
/** @brief creates a new batch render with arrays 
 * @param max_vertices: the maximum allowed vertices to be rendered
*/
bool render_batch_arrays_new(render_batch_arrays_tt* p_batch, uint32_t draw_mode, uint32_t program, size_t max_vertices);
void render_batch_arrays_set(render_batch_arrays_tt* p_batch, size_t bytevert, size_t offset, size_t size, float* pos, float* tex);
void render_batch_arrays_free(render_batch_arrays_tt* p_batch);

/** @brief creates a new render batch instance indexed "object"(not really an object)
 * @param pos: must be in vec3 component in floating point
 * @param indices: must be a uint32_t
*/ 
bool render_batch_instance_indexed_new(render_batch_instance_indexed_tt* p_batch, 
                                       uint32_t draw_mode,
                                       uint32_t program, 
                                       size_t max_instances, 
                                       size_t vertice_count, 
                                       float* pos, 
                                       float* tex_coords, 
                                       uint32_t* indices);
void render_batch_instance_indexed_set_instance(render_batch_instance_indexed_tt* p_batch, uint32_t index, mat4 model);
void render_batch_instance_indexed_set_instances(render_batch_instance_indexed_tt* p_batch, uint32_t starting_index, size_t count, mat4* model);
void render_batch_instance_indexed_free(render_batch_instance_indexed_tt* p_batch);

void render_batch_arrays(render_batch_arrays_tt* p_batch);
void render_batch_indexed(render_batch_indexed_tt* p_batch);
void render_batch_instance_indexed(render_batch_instance_indexed_tt* p_batch);

#endif // _SPOK_ENGINE_GRAPHICS_RENDER_H_INCLUDED