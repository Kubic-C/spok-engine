/** cmain.h:
 * core main
 * 
 * spock engine's primary "functions"
 * declares (_spok) _init, _update, _render, _terminate 
 * 
 * why _spok, because spok.h defines functions such as spok_init, so
 * to not have the linker shit its self, we add _spok.
*/

#ifndef _SPOK_CORE_CMAIN_H_INCLUDED
#define _SPOK_CORE_CMAIN_H_INCLUDED

#include "spok/spok.h"

bool _spok_init(void);
void _spok_render(void); 
void _spok_update(void);
void _spok_term(void);

#endif // _SPOK_CORE_CMAIN_H_INCLUDED