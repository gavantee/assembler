#include "util.h"

#include <stdlib.h>

void *ecalloc(size_t nmemb, size_t size) {
	void *p;
	if (!(p = calloc(nmemb, size))) {
    printf("calloc error");
		exit(-1);
	}
	return p;
}

void *erealloc(void *p, size_t nmemb, size_t size) {
	if (!(p = realloc(p, nmemb * size))) {
    printf("realloc error");
		exit(-1);
	}
	return p;
}

int read_int(FILE *f, int size) {
  int val = 0;
	unsigned char ch;
	int pow = 1;
	for (int i = 0; i < size; ++i) {
    fscanf(f, "%c", &ch);
		val += ch * pow;
		pow *= 0x100;
	}
	return val;
}

void write_int(int val, int n, FILE *f) {
 for (int i = 0; i < n; ++i)
  fprintf(f, "%c", val >> (i * 8));
}

