#ifndef _SPOK_ENGINE_COMPONENT_H_INCLUDED
#define _SPOK_ENGINE_COMPONENT_H_INCLUDED

#include "_include.h"

// all structures/components to be used by the private
// and publice API go here:

/* non-components: */
typedef struct {
  vec3 scale;
  vec3 rot;
  float angle;
} transform_tt;

typedef struct {
  float speed;
  vec3 dir;
} dynamics_tt;

/* components: */
typedef struct {
  vec2 bl, tr;
  mat4 model;
} comp_box2D_tt;

typedef struct {
  vec3 bl, tr;
  mat4 model;
} comp_box3D_tt;

typedef struct {
  vec3 pos;
  transform_tt transform;
  dynamics_tt dynamics;
} comp_physics_tt;

extern ECS_COMPONENT_DECLARE(comp_box2D_tt);
extern ECS_COMPONENT_DECLARE(comp_box3D_tt);
extern ECS_COMPONENT_DECLARE(comp_physics_tt);

#endif // _SPOK_ENGINE_COMPONENT_H_INCLUDED