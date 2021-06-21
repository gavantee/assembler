#include "section.h"

#include <stdio.h>

#include "util.h"
#include "code.h"

section_s *read_section(FILE* in) {
  section_s *sec = (section_s *) ecalloc(1, sizeof(section_s));
  sec->name = read_int(in, 4);
  sec->type = read_int(in, 4);
  fseek(in, 4, SEEK_CUR);
  sec->addr = read_int(in, 4);
  sec->off  = read_int(in, 4);
  sec->size = read_int(in, 4);
  sec->link = read_int(in, 4);
  sec->info = read_int(in, 4);
  read_int(in, 4);
  sec->entsize = read_int(in, 4);
  sec->data = (unsigned char *) ecalloc(sec->size, sizeof(unsigned char));
  fseek(in, sec->off, SEEK_SET);
  fread(sec->data, sec->size, 1, in);
  return sec;
}

void print_section(code_s *code, int id) {
  printf("============================================\n");
  section_s *s = code->secs[id];
  printf("%-20s %02X %02X %02X %02X %02X %02X\n", get_name(code, s->name), s->type, s->addr, s->off, s->size, s->link, s->info);
  if (s->type == 0x02) {
    print_symbols(code);
    return;
  }
  if (s->type == 0x03) {
    print_strtab(code);
    return;
  }
  if (s->type == 0x09) {
    print_relocs(code, id);
    return;
  }
  for (int i = 0; i < s->size; ++i) {
    if (i % 16 == 0)
      printf("\n%04X: ", i);
    printf("%02X ", s->data[i]);
  }
  printf("\n");
}

void print_symbol(code_s *code, symbol_s *sym, int id) {
  printf("%02x: %-16s %04X %02X %02X %02X %02X\n", id, get_name(code, sym->name), sym->value, sym->size, sym->info, sym->other, sym->shndx);//, get_name(code, code->secs[sym->shndx]->name));
}

void print_reloc(code_s *code, reloc_s *reloc) {
  symbol_s *sym =(symbol_s *) (code->secs[code->symndx]->data + (reloc->info >> 8) * 0x10);
  printf("%02X %-10s (%02x) %c\n", reloc->off, get_name(code, sym->name), reloc->info >> 8, ((reloc->info & 0xff) == 2) ? 'a' : 'r');
}

