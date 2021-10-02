#ifndef _SPOK_ENGINE_CORE_INCLUDE_H_INCLUDED
#define _SPOK_ENGINE_CORE_INCLUDE_H_INCLUDED

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <flecs.h>
#include <assert.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h> //  | CGLM may also include these, they put here to insure it
#include <stdint.h> //  |
#include <stdbool.h> // |

#define INLINE CGLM_INLINE
#define TYPEDEF_FORWARD_DECLARE(name) typedef struct name name;
#define SPOK_TICKS_PER_SECOND 60.0

// (mimic api macro) use with ECS_COMPONENT_DECLARE
#define ECS_COMPONENT_INIT(world, T) \
    ecs_id(T) = ecs_component_init(world, &(ecs_component_desc_t){\
        .entity = {\
            .entity = ecs_id(T),\
            .name = #T,\
            .symbol = #T\
        },\
        .size = sizeof(T),\
        .alignment = ECS_ALIGNOF(T)\
    });

typedef ecs_entity_t euid_tt;
typedef ecs_entity_t compid_tt;

#endif // _SPOK_ENGINE_CORE_INCLUDE_H_INCLUDED