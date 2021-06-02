#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void *ecalloc(size_t nmemb, size_t size)
{
	void *p;
	if (!(p = calloc(nmemb, size))) {
    printf("calloc error");
		exit(-1);
	}
	return p;
}

void *erealloc(void *p, size_t nmemb, size_t size)
{
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

typedef struct code_s {
  section_s **secs;
  int secnum;
  int symndx;
  int strndx;
	bool first;
	int old_strsize;
	int cur_secnum;
} code_s;

section_s *read_section(FILE* in, code_s *code) {
  section_s *sec = (section_s *) ecalloc(1, sizeof(section_s));
	sec->name = read_int(in, 4);
	sec->name += code->old_strsize;
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

unsigned char *get_name(code_s *code, int off) {
  return code->secs[code->strndx]->data + off;
}

void print_symbol(code_s *code, symbol_s *sym, int id) {
  printf("%02x: %-16s %04X %02X %02X %02X %-16s\n", id, get_name(code, sym->name), sym->value, sym->size, sym->info, sym->other, get_name(code, code->secs[sym->shndx]->name));
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

void print_reloc(code_s *code, reloc_s *reloc) {
  symbol_s *sym =(symbol_s *) (code->secs[code->symndx]->data + (reloc->info >> 8) * 0x10);
  printf("%02X %-10s %c\n", reloc->off, get_name(code, sym->name), ((reloc->info & 0xff) == 2) ? 'a' : 'r');
}

void print_relocs(code_s *code, int id) {
  section_s *reloctab = code->secs[id];
	reloc_s *relocs = (reloc_s *) reloctab->data;
	int n = reloctab->size / reloctab->entsize;
	printf("relocation section for: %d (%s)\n", reloctab->info, get_name(code, code->secs[reloctab->info]->name));
	for (int i = 0; i < n; ++i)
    print_reloc(code, relocs + i);
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

void add_strtab(code_s *code, section_s *newstr) {
  section_s *str = code->secs[code->strndx];
	str->data = (unsigned char *) erealloc(str->data, str->size + newstr->size, sizeof(unsigned char));
	for (int i = 0; i < newstr->size; ++i)
    str->data[i + str->size] = newstr->data[i];
	str->size += newstr->size;
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

void add_symbol(code_s *code, symbol_s *sym, int id) {
  sym->name += code->old_strsize;
	if (sym->shndx != 0) sym->shndx += code->secnum - 2;
  section_s *symtab = code->secs[code->symndx];
	int n = symtab->size / symtab->entsize;
	symbol_s *syms = (symbol_s *) symtab->data;
	for (int i = 0; i < n && (sym->info & 0xf) != 0x03 /* section */; ++i) {
    symbol_s *cur = syms + i;
		if (strcmp((char *) get_name(code, cur->name), (char *) get_name(code, sym->name)) == 0) {
      if (sym->shndx == 0) {
				fix_relocs(code, id, i);
				return;
			}
			if (sym->shndx != 0 && cur->shndx == 0) {
				cur->shndx = sym->shndx;
				cur->value = sym->value;
				cur->size = sym->size;
				cur->info = sym->info;
				fix_relocs(code, id, i);
				return;
			}
			if (sym->shndx != 0 && cur->shndx != 0) {
				printf("Multiple definitions of symbol %s", get_name(code, cur->name));
				exit(-1);
			}
		}
	}
	symtab->data = (unsigned char *) erealloc(symtab->data, symtab->size + symtab->entsize, sizeof(unsigned char *));
	unsigned char *symdata = (unsigned char*) sym;
	for (int i = 0; i < symtab->entsize; ++i)
    symtab->data[symtab->size + i] = symdata[i];
	symtab->size += symtab->entsize;
	symtab->info += 1;
  fix_relocs(code, id, n);
}

void add_symtab(code_s *code, section_s *newsym) {
  section_s *symtab = code->secs[code->symndx];
	for (int i = 0; i < newsym->size / newsym->entsize; ++i) {
    symbol_s *sym = (symbol_s *) (newsym->data + i * newsym->entsize);
		add_symbol(code, sym, i);
	}
}

void write_int(int val, int n, FILE *f) {
 for (int i = 0; i < n; ++i)
  fprintf(f, "%c", val >> (i * 8));
}

void write_elf(code_s *code, const char *fn) {
  FILE *outfile = fopen(fn, "wb");
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

int main(int argc, char *argv[]) {
  FILE *in;
	code_s *code = (code_s *) ecalloc(1, sizeof(code_s));
	code->first = true;
	for (int i = 1; i < argc; ++i) {
    in = fopen(argv[i], "rb");
		if (in == NULL) {
      printf("Cant open %s\n", argv[i]);
			exit(-1);
		}

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
		printf("%x %x %x %x %x %x %x\n", sht + shstrndx * shsize + 0x10, sht, shsize, shnum, shstrndx, stroff, strsize);
		char *names = (char *) ecalloc(strsize, sizeof(char));
		fseek(in, stroff, SEEK_SET);
		fread(names, strsize, 1, in);

		if (code->first) code->secs = (section_s **) ecalloc(shnum, sizeof(section_s *));
		else code->secs = (section_s **) erealloc(code->secs, shnum + code->secnum - 2, sizeof(section_s *));
		int n = code->secnum + shnum;
		if (!code->first) n -= 2;
		for (int j = code->secnum, k = 0; k < shnum; ++k) {
      fseek(in, sht + k * shsize, SEEK_SET);
			section_s *tmp = read_section(in, code);
			if (!code->first && tmp->type == 0x03) {
				add_strtab(code, tmp);
				continue;
			}
			/*
			if (!code->first && tmp->type == 0x00) {
				continue;
			}
			*/
			if (!code->first && tmp->type == 0x02) {
				add_symtab(code, tmp);
				continue;
			}
			if (!code->first && tmp->type == 0x09) {
				tmp->info += code->secnum - 2;
				tmp->link = code->symndx;
			}
		  code->secs[j] = tmp;
			if(code->secs[j]->type == 0x02 && code->first == true)
				code->symndx = j;
			++j;
			++(code->cur_secnum);
		}
		code->secnum = n;
		code->old_strsize = code->secs[code->strndx]->size;
		code->first = false;
		free(names);
	}
  for (int j = 0; j < code->secnum; ++j)
    print_section(code, j);

	write_elf(code, "out.o");
}
