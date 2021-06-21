#include "code.h"

#include <stdlib.h>
#include <string.h>

#include "util.h"

unsigned char *get_name(code_s *code, int off) {
  return code->secs[code->strndx]->data + off;
}

void print_symbols(code_s *code) {
  section_s *symtab = code->secs[code->symndx];
  symbol_s *syms = (symbol_s *) symtab->data;
  int n = symtab->size / symtab->entsize;
  for (int i = 0; i < n; ++i)
    print_symbol(code, syms + i, i);
}

void print_strtab(code_s *code) {
  section_s *strtab = code->secs[code->strndx];
  printf("%04X: ", 0);
  for (int i = 0; i < strtab->size; ++i) {
    if (strtab->data[i] == '\0') printf("\n%04X: ", i + 1);
    else printf("%c", strtab->data[i]);
  }
}

void print_relocs(code_s *code, int id) {
  section_s *reloctab = code->secs[id];
  reloc_s *relocs = (reloc_s *) reloctab->data;
  int n = reloctab->size / reloctab->entsize;
  // printf("relocation section for: %d (%s)\n", reloctab->info, get_name(code, code->secs[reloctab->info]->name));
  for (int i = 0; i < n; ++i)
    print_reloc(code, relocs + i);
}

void add_strtab(code_s *code, section_s *newstr) {
  section_s *str = code->secs[code->strndx];
  str->data = (unsigned char *) erealloc(str->data, str->size + newstr->size, sizeof(unsigned char));
  for (int i = 0; i < newstr->size; ++i)
    str->data[i + str->size] = newstr->data[i];
  str->size += newstr->size;
}

void fix_all_relocs(code_s *code) {
  for (int i = code->secnum; i < code->cur_secnum; ++i) {
    section_s *s = code->secs[i];
    if (s->type != 0x09) continue;
    reloc_s *relocs = (reloc_s *) s->data;
    for (int i = 0; i < s->size / s->entsize; ++i) {
      reloc_s *r = relocs + i;
      r->info = (code->symmap[r->info >> 8] << 8) + (r->info & 0xff);
    }
  }
}


void fix_relocs(code_s *code, int oldid, int newid) {
  for (int i = code->secnum; i < code->cur_secnum; ++i) {
    section_s *s = code->secs[i];
    if (s->type != 0x09) continue;
    reloc_s *relocs = (reloc_s *) s->data;
    for (int i = 0; i < s->size / s->entsize; ++i) {
      reloc_s *r = relocs + i;
      if ((r->info >> 8) == oldid) {
        r->info = (newid << 8) + (r->info & 0xff);
      }
    }
  }
}

void add_symbol(code_s *code, symbol_s *sym, int id, char *name) {
  sym->name = add_str(code, name);
  if (sym->shndx != 0) sym->shndx += code->secnum;
  section_s *symtab = code->secs[code->symndx];
  int n = symtab->size / symtab->entsize;
  symbol_s *syms = (symbol_s *) symtab->data;
  // print_symbol(code, sym, 0);
  for (int i = 0; i < n && (sym->info & 0xf) != 0x03 /* section */; ++i) {
    symbol_s *cur = syms + i;
    if (strcmp((char *) get_name(code, cur->name), (char *) get_name(code, sym->name)) == 0) {
      if (sym->shndx == 0) {
        code->symmap[id] = i;
        //fix_relocs(code, id, i);
        return;
      }
      if (sym->shndx != 0 && cur->shndx == 0) {
        cur->shndx = sym->shndx;
        cur->value = sym->value;
        cur->size = sym->size;
        cur->info = sym->info;
        code->symmap[id] = i;
        //fix_relocs(code, id, i);
        return;
      }
      if (sym->shndx != 0 && cur->shndx != 0) {
        printf("Multiple definitions of symbol %s", get_name(code, cur->name));
        exit(-1);
      }
    }
  }
  code->symmap[id] = symtab->info;
  symtab->data = (unsigned char *) erealloc(symtab->data, symtab->size + symtab->entsize, sizeof(unsigned char *));
  unsigned char *symdata = (unsigned char*) sym;
  for (int i = 0; i < symtab->entsize; ++i)
    symtab->data[symtab->size + i] = symdata[i];
  symtab->size += symtab->entsize;
  symtab->info += 1;
  // fix_relocs(code, id, n);
}

void add_symtab(code_s *code, section_s *newsym, char *names) {
  if (code->symmap)
    free(code->symmap);
  section_s *symtab = code->secs[code->symndx];
  code->symmap = ecalloc(symtab->info, sizeof(int));
  for (int i = 0; i < newsym->size / newsym->entsize; ++i) {
    symbol_s *sym = (symbol_s *) (newsym->data + i * newsym->entsize);
    add_symbol(code, sym, i, names + sym->name);
  }
}

void write_elf(code_s *code, const char *fn) {
  FILE *outfile = fopen(fn, "wb");
  if (outfile == NULL) {
    printf("Cant open: %s\n", fn);
    exit(-1);
  }
  const char magic[] = "\x7f\x45\x4c\x46\x01\x01\x01\x03" \
                       "\x00\x00\x00\x00\x00\x00\x00\x00" \
                       "\x01\x00\x28\x00\x01\x00\x00\x00" \
                       "\x00\x00\x00\x00\x00\x00\x00";

  fwrite(magic, sizeof(magic), 1, outfile);
  int off = 0x34;
  for (int i = 0; i < code->secnum; ++i) {
    code->secs[i]->off = off;
    off += code->secs[i]->size;
  }
  write_int(off, 4, outfile);   // e_shoff
  write_int(0, 4, outfile);     // e_flags
  write_int(0x34, 2, outfile);  // e_ehsize
  write_int(0, 2, outfile);     // e_phentsize
  write_int(0, 2, outfile);     // e_phnum
  write_int(0x28, 2, outfile);  // e_shentsize
  write_int(code->secnum, 2, outfile);   // e_shnum
  write_int(code->strndx, 2, outfile); // e_shstrndx
  for (int i = 0; i < code->secnum; ++i)
    fwrite(code->secs[i]->data, code->secs[i]->size, 1, outfile);
  for (int i = 0; i < code->secnum; ++i) {
    section_s *s = code->secs[i];
    write_int(s->name, 4, outfile);
    write_int(s->type, 4, outfile);
    write_int(0, 8, outfile);
    write_int(s->off, 4, outfile);
    write_int(s->size, 4, outfile);
    write_int(s->link, 4, outfile);
    write_int(s->info, 4, outfile);
    write_int(1, 4, outfile);
    write_int(s->entsize, 4, outfile);
  }
}

void remap_section(code_s *code, int oldid, int newid, int off) {
  if ((oldid == newid) && (off == 0)) return;
  symbol_s *sym = (symbol_s *) code->secs[code->symndx]->data;
  int n = code->secs[code->symndx]->info;
  for (int i = 0; i < n; ++i) {
    if (sym[i].shndx == oldid) {
      sym[i].shndx = newid;
      sym[i].value += off;
    }
  }
  for (int i = code->secnum; i < code->cur_secnum; ++i) {
    section_s *s = code->secs[i];
    if (s->type != 0x09) continue;
    if (s->info == oldid) {
      s->info = newid;
      // printf("reloc fix on:%s\n", get_name(code, s->name));
      reloc_s *relocs = (reloc_s *) s->data;
      for (int j = 0; j < s->size / s->entsize; ++j) {
        relocs[j].off += off;
        // print_reloc(code, relocs + j);
      }
    }
    reloc_s *reloc = (reloc_s *) s->data;
    for (int j = 0; j < s->size / s->entsize; ++j) {
      if ((reloc[j].info >> 8) == oldid) {
        reloc[j].info = reloc[j].info & 0xff + (newid << 8);
        int *addend = (int *) (code->secs[s->info]->data + reloc[j].off);
        *addend += off;
      }
    }
  }
}

int add_str(code_s *code, char *name) {
  section_s *strtab = code->secs[code->strndx];
  for (int i = 0; i < strtab->size; i += strlen(strtab->data + i) + 1)
    if (strcmp((char *) strtab->data + i, name) == 0)
      return i;
  int ret = strtab->size;
  strtab->size += strlen(name) + 1;
  strtab->data = erealloc(strtab->data, strtab->size, sizeof(unsigned char));
  strcpy(strtab->data + ret, name);
  return ret;
}

void add_file(code_s *code, FILE *in) {
    fseek(in, 0x20, SEEK_SET);
    int sht = read_int(in, 4);
    fseek(in, 0x2E, SEEK_SET);
    int shsize = read_int(in, 2);
    int shnum = read_int(in, 2);
    int shstrndx = read_int(in, 2);
    if (code->first) code->strndx = shstrndx;
    fseek(in, sht + shstrndx * shsize + 0x10, SEEK_SET);
    int stroff = read_int(in, 4);
    int strsize = read_int(in, 4);
    // printf("%x %x %x %x %x %x %x\n", sht + shstrndx * shsize + 0x10, sht, shsize, shnum, shstrndx, stroff, strsize);
    char *names = (char *) ecalloc(strsize, sizeof(char));
    fseek(in, stroff, SEEK_SET);
    fread(names, strsize, 1, in);

    int secndx_off = 0;
    for (int j = 0; j < shnum; ++j) {
      fseek(in, sht + j * shsize, SEEK_SET);
      section_s *tmp = read_section(in);
      for (int l = 0; l < code->secnum; ++l) {
        if (strcmp((char *) get_name(code, code->secs[l]->name), names + tmp->name) == 0 && (code->secs[l]->type != 0x09)) {
          ++secndx_off;
        }
      }
    }

    if (code->first) {
      code->secs = (section_s **) ecalloc(shnum, sizeof(section_s *));
      code->strndx = shstrndx;
      fseek(in, sht + shstrndx * shsize, SEEK_SET);
      code->secs[shstrndx] = read_section(in);
    }

    else code->secs = (section_s **) erealloc(code->secs, shnum + code->secnum - secndx_off, sizeof(section_s *));

    for (int j = code->secnum, k = 0; k < shnum; ++k) {
      fseek(in, sht + k * shsize, SEEK_SET);
      section_s *tmp = read_section(in);
      if (!code->first && tmp->type == 0x03) {
        // add_strtab(code, tmp);
        continue;
      }
      /*
      if (!code->first && tmp->type == 0x00) {
        continue;
      }
      */
      if (!code->first && tmp->type == 0x02) {
        add_symtab(code, tmp, names);
        continue;
      }
      if (!code->first && tmp->type == 0x09) {
        tmp->info = tmp->info + code->secnum;
        tmp->link = code->symndx;
      }
      bool concat = false;
      for (int l = 0; l < code->secnum; ++l) {
        if (strcmp((char *) names + tmp->name, (char *) get_name(code, code->secs[l]->name)) == 0 && tmp->type != 0x09) {
          section_s *sec = code->secs[l];
          if (tmp->size > 0)
            sec->data = (unsigned char *) erealloc(sec->data, sec->size + tmp->size, sizeof(unsigned char));
          for (int p = 0; p < tmp->size; ++p)
            sec->data[sec->size + p] = tmp->data[p];
          remap_section(code, code->secnum + k, l, sec->size);
          sec->size += tmp->size;
          concat = true;
        }
      }
      if (!concat) {
        code->secs[j] = tmp;
        tmp->name = add_str(code, names + tmp->name);
        if (tmp->type == 0x01) remap_section(code, code->secnum + k, j, 0);
        if(code->secs[j]->type == 0x02 && code->first == true)
          code->symndx = j;
        ++j;
        ++(code->cur_secnum);
      }
      //tmp->name += code->old_strsize;
    }
    if (!code->first) fix_all_relocs(code);
    code->secnum = code->cur_secnum;
    code->old_strsize = code->secs[code->strndx]->size;
    code->first = false;
    free(names);
}

void print_code(code_s *code) {
  for (int i = 0; i < code->secnum; ++i)
    print_section(code, i);
}

int placecmp(const void *p1, const void *p2) {
  place_s *place1 = (place_s *) p1;
  place_s *place2 = (place_s *) p2;
  return place1->off - place2->off;
}

symbol_s *get_sym(code_s *code, int symid) {
  symbol_s *sym = (symbol_s *) code->secs[code->symndx]->data;
  return sym + symid;
}

void solve_symbols(code_s *code) {
  section_s *symtab = code->secs[code->symndx];
  int n = symtab->info;
  symbol_s *sym = (symbol_s *) symtab->data;
  for (int i = 0; i < n; ++i) {
    sym[i].value += code->secs[sym[i].shndx]->addr;
  }
}

void solve_relocs(code_s *code) {
  for (int i = 0; i < code->secnum; ++i) {
    section_s *sec = code->secs[i];
    if (sec->type == 0x09) {
      reloc_s *relocs = (reloc_s *) sec->data;
      int n = sec->size / sec->entsize;
      for (int j = 0; j < n; ++j) {
        int symid = relocs[j].info >> 8;
        int type = relocs[j].info & 0xff;
        short *value = (short *) (code->secs[sec->info]->data + relocs[j].off);
        // print_symbol(code, get_sym(code, symid), symid);
        *value += get_sym(code, symid)->value;
        if (type == 0x03) {
          *value -= code->secs[sec->info]->addr + relocs[j].off;
        }
      }
    }
  }
}

void check_symbols(code_s *code) {
  section_s *symtab = code->secs[code->symndx];
  symbol_s *sym = (symbol_s *) symtab->data;
  for (int i = 0; i < symtab->info; ++i) {
    // print_symbol(code, sym + i, i);
    if(sym[i].shndx == 0 && strcmp((char *) get_name(code, sym[i].name), "ABS") != 0) {
      printf("Undefined symbol: %s", get_name(code, sym[i].name));
      exit(-1);
    }
  }
}

void relocate(code_s *code, place_s *place, int place_num) {
  qsort(place, place_num, sizeof(place_s), placecmp);
  int last_addr = 0;
  bool found;
  code->placed = (bool *) ecalloc(code->secnum, sizeof(bool));
  for (int i = 0; i < place_num; ++i) {
    if (last_addr > place[i].off) {
      printf("Sections collide\n");
      exit(-1);
    }
    found = false;
    for (int j = 0; j < code->secnum && !found; ++j) {
      if (strcmp(place[i].section, (char *) get_name(code, code->secs[j]->name)) == 0) {
        code->secs[j]->addr = place[i].off;
        last_addr = code->secs[j]->size + place[i].off;
        code->placed[j] = true;
        found = true;
      }
    }
  }
  for (int i = 0; i < code->secnum; ++i) {
    section_s *sec = code->secs[i];
    if (code->placed[i] == false && sec->type == 0x01) {
      sec->addr = last_addr;
      last_addr += sec->size;
      code->placed[i] = true;
    }
  }
  check_symbols(code);
  solve_symbols(code);
  solve_relocs(code);
  // print_code(code);
}

void write_hex(code_s *code, char *fn) {
  FILE *outfile = fopen(fn, "wb");
  if (outfile == NULL) {
    printf("Cant open: %s\n", fn);
    exit(-1);
  }
  int n = 0;
  for (int i = 0; i < code->secnum; ++i)
    if (code->secs[i]->type == 0x01) ++n;
  place_s *places = (place_s *) ecalloc(code->secnum, sizeof(places));
  n = 0;
  for (int i = 0; i < code->secnum; ++i) {
    if (code->secs[i]->type != 0x01) continue;
    places[n].section = (char *) ecalloc(code->secs[i]->size, sizeof(char));
    for (int j = 0; j < code->secs[i]->size; ++j)
      places[n].section[j] = code->secs[i]->data[j];
    places[n++].off = (code->secs[i]->addr << 16) + code->secs[i]->size;
  }
  qsort(places, n, sizeof(place_s), placecmp);
  for (int i = 0; i < n; ++i) {
    int size = places[i].off & 0xffff;
    int off = places[i].off >> 16;
    for (int j = 0; j < size; ++j) {
      if (j % 8 == 0) fprintf(outfile, "\n%04X: ", off + j);
      fprintf(outfile, "%02X ", places[i].section[j]);
    }
    // printf("\n");
  }
}

