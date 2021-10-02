#ifndef _SPOK_ENGINE_RENDER_SHADER_H_INCLUDED
#define _SPOK_ENGINE_RENDER_SHADER_H_INCLUDED

#include "spok/spok.h"

uint32_t shader_new(uint32_t type, size_t size, char* src);
INLINE void shader_free(uint32_t s) { glDeleteShader(s); }

uint32_t program_new_dir(const char* vert_dir, const char* frag_dir);
uint32_t program_new(size_t count, uint32_t* p_shaders);
INLINE void program_free(uint32_t pgm) { glDeleteProgram(pgm); }

#endif // _SPOK_ENGINE_RENDER_SHADER_H_INCLUDED