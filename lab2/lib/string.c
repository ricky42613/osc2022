#include "string.h"
#include "stdint.h"

int strncmp(const char *s1, const char *s2, uint32_t len) {
  for (int i = 0; i < len; i++) {
    if (s1[i] > s2[i]) return 1;
    else if (s1[i] < s2[i]) return -1;
    else if (s1[i] == '\0' || s2[i] == '\0') break;
  }
  return 0;
}

void* memset(char *dst, char c, uint32_t len) {
  char* dup = dst;
  while (len--) {
    *dup++ = c;
  }
  return dst;
}


char* strncpy(char *dst, const char *src, uint32_t len) {
  for (uint32_t i = 0; i < len; i++) {
    dst[i] = src[i];
    if (src[i] == 0) break;
  }
  return dst;
}
