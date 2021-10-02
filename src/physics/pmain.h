/** pmain.h:
 * physics main
 * 
 * declerations for (physics_) init, update, term
*/

#ifndef _SPOK_PHYSICS_PMAIN_H_INCLUDED
#define _SPOK_PHYSICS_PMAIN_H_INCLUDED

#include "spok/spok.h"

bool physics_init();
void physics_update();
void physics_term();

#endif // _SPOK_PHYSICS_PMAIN_H_INCLUDED