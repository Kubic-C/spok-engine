#include "file.h"

bool util_file_read(const char* dir, size_t* p_size, char** pp_data) {
  FILE* file;

  file = fopen(dir, "r");
  if (!file) {
    *pp_data = NULL;
    *p_size = 0;
    return false;
  }

  fseek(file, 0, SEEK_END);
  *p_size = ftell(file);
  fseek(file, 0, SEEK_SET);
  *pp_data = malloc(*p_size);
  assert(*pp_data != NULL);
  fread(*pp_data, sizeof(char), *p_size, file);
  fclose(file);

  return true;
}