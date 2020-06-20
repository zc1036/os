
#include <string.h>

extern "C" {

size_t strlen(const char* c) {
  size_t length = 0;

  while (*c) {
    ++length;
    ++c;
  }

  return length;
}

}
