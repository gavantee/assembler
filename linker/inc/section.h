#ifndef SECTION_H_
#define SECTION_H_

#include <stdio.h>

typedef struct code_s code_s;

typedef struct section_s {
  int name;
  int type;
  int addr;
  int off;
  int size;
  int link;
  int info;
  int entsize;
  unsigned char *data;
} section_s;

typedef struct symbol_s {
  int name;
  int value;
  int size;
  unsigned char info;
  unsigned char other;
  unsigned short shndx;
} symbol_s;

typedef struct reloc_s {
  int off;
  int info;
} reloc_s;

section_s *read_section(FILE* in);
void print_section(code_s *code, int id);
void print_symbol(code_s *code, symbol_s *sym, int id);
void print_reloc(code_s *code, reloc_s *reloc);

#endif

