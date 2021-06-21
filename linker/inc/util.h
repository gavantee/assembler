#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>

typedef struct place_s {
  unsigned char *section;
  int off;
} place_s;

void *ecalloc(size_t nmemb, size_t size);
void *erealloc(void *p, size_t nmemb, size_t size);
int read_int(FILE *f, int size);
void write_int(int val, int n, FILE *f);

#endif

