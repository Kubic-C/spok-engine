#ifndef _SPOK_ENGINE_PHYSICS_BODY_H_INCLUDED
#define _SPOK_ENGINE_PHYSICS_BODY_H_INCLUDED

#include "spok/physics.h"

void physics_box2D_update(comp_box2D_tt* p_box, comp_physics_tt* p_pc);
void physics_box3D_update(comp_box3D_tt* p_box, comp_physics_tt* p_pc);

#endif // _SPOK_ENGINE_PHYSICS_BODY_H_INCLUDED