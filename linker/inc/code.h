#ifndef CODE_H_
#define CODE_H_

#include <stdbool.h>

#include "section.h"
#include "util.h"

typedef struct code_s {
  section_s **secs;
  int secnum;
  int symndx;
  int strndx;
	bool first;
	int old_strsize;
	int cur_secnum;
	bool *placed;
} code_s;

unsigned char *get_name(code_s *code, int off);
void print_symbols(code_s *code);
void print_strtab(code_s *code);
void print_relocs(code_s *code, int id);
void add_strtab(code_s *code, section_s *newstr);
void fix_relocs(code_s *code, int oldid, int newid);
void add_symbol(code_s *code, symbol_s *sym, int id, char *name);
void add_symtab(code_s *code, section_s *newsym, char *names);
void write_elf(code_s *code, const char *fn);
void concat_section(code_s *code, int oldid, int newid, int off);
void add_file(code_s *code, FILE *in);
void relocate(code_s *code, place_s *place, int place_num);
void write_hex(code_s *code, char *outfile);
void print_code(code_s *code);
int add_str(code_s *code, char *name);

#endif

