#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "code.h"
#include "section.h"

int main(int argc, char *argv[]) {
  FILE *in;
	char *outfile = NULL;
	place_s place[argc];
	int place_num;
	bool linkable = false;
	bool hex = false;
	bool log = false;

	code_s *code = (code_s *) ecalloc(1, sizeof(code_s));
	code->first = true;
	for (int i = 1, j = 0; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if (strcmp(argv[i], "-o") == 0) {
        outfile = argv[++i];
      }
      else if (strncmp(argv[i], "-place", 6) == 0) {
				place[j].section = (char *) ecalloc(100, sizeof(char));
        sscanf(argv[i], "-place=%[^@]@%x", place[j].section, &(place[j].off));
				place_num = ++j;
			}
			else if (strcmp(argv[i], "-linkable") == 0) {
        linkable = true;
      }
			else if (strcmp(argv[i], "-hex") == 0) {
        hex = true;
      }
			else if (strcmp(argv[i], "-v") == 0) {
        log = true;
      }
		}
		else {
      in = fopen(argv[i], "rb");
      add_file(code, in);
		  if (in == NULL) {
        printf("Cant open %s\n", argv[i]);
			  exit(-1);
		  }
		}
	}


	if (linkable && hex) {
    printf("Cant use both -hex and -linkable\n");
		exit(-1);
	}

	if (linkable) {
    if (outfile) write_elf(code, outfile);
		else write_elf(code, "out.o");
		if (log) print_code(code);
	}

	if (hex) {
    relocate(code, place, place_num);
		if (outfile) write_hex(code, outfile);
		else write_hex(code, "out.hex");
		 if (log) print_code(code);
	}
}

