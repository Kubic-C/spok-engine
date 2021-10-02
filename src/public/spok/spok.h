#ifndef _SPOK_SPOK_H_INCLDUED
#define _SPOK_SPOK_H_INCLDUED

#include "spok/gfx.h"
#include "spok/physics.h"

typedef bool(*spok_init_func_tt)(void);
typedef bool(*spok_update_func_tt)(void);
typedef void(*spok_term_func_tt)(void);

bool spok_init(spok_init_func_tt user_init, spok_update_func_tt user_update, spok_term_func_tt user_term);
void spok_entity_free(euid_tt id); // not neccessary to call in terminate functions!
GLFWwindow* spok_get_window(void);
ecs_world_t* spok_get_world(void);
uint32_t spok_get_ups(void);
uint32_t spok_get_fps(void);
double spok_get_delta(void);
double spok_get_time(void);
int spok_run(void);

#endif // _SPOK_SPOK_H_INCLDUED
