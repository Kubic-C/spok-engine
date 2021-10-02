/** components.h:
 * ecs component init, DO NOT INCLUDE IN OTHER FOLDERS(e.g. physics, core, etc.)
*/

#ifndef _SPOK_ENGINE_PHYSICS_COMPONENTS_H_INCLUDED
#define _SPOK_ENGINE_PHYSICS_COMPONENTS_H_INCLUDED

#include "body.h"

void physics_component_init(ecs_world_t* p_world);
void physics_component_term(ecs_world_t* p_world);

#endif // _SPOK_ENGINE_PHYSICS_COMPONENTS_H_INCLUDED