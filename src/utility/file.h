#ifndef _SPOK_UTILITY_FILE_H_INCLUDED
#define _SPOK_UTILITY_FILE_H_INCLUDED

#include "spok/_include.h"

bool util_file_read(const char* dir, size_t* p_size, char** pp_data);

INLINE void util_file_cleanup_read(char* p_data) {
  free(p_data);
}

#endif // _SPOK_UTILITY_FILE_H_INCLUDED