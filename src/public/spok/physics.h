#ifndef _SPOK_PHYSICS_H_INCLUDED
#define _SPOK_PHYSICS_H_INCLUDED

#include "spok/_include.h"
#include "spok/components.h"

#define FLOAT_MAX ((float)340282346638528859811704183484516925440.0000000000000000f)

// entity creation ( w/ physics comp attached)
euid_tt spok_box2D_add(vec2 pos, vec2 bl, vec2 tr);
euid_tt spok_box3D_add(vec3 pos, vec3 bl, vec3 tr);

// physics_set_...(ID, ...)
void spok_physics_set_dir(euid_tt id, vec3 dir, float speed);
void spok_physics_set_rot(euid_tt id, vec3 rot, float angle); 
void spok_physics_set_scale(euid_tt id, vec3 scale);
void spok_physics_set_pos(euid_tt id, vec3 pos);

#endif // _SPOK_PHYSICS_H_INCLUDED