#include <cstdio>
#include <vector>
#include <cstring>

#include "code.h"

extern FILE *yyin;
extern int yyparse();
Code code;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("usage: %s [-o <output_file>] <input_file>", argv[0]);
		return 0;
	}
  char *outfn = NULL;
  char *infn;
  if (strcmp(argv[1], "-o") == 0) {
    outfn = argv[2];
		infn = argv[3];
	}
	else infn = argv[1];
  FILE *myfile = fopen(infn, "r");
  if (!myfile) {
    printf("error: cat open %s", infn);
    return -1;
  }
  yyin = myfile;

  yyparse();

	code.check();
	code.reduce();
	code.filterSymbols();
	code.addStandardSections();
	code.dump();
	if (outfn != NULL)
	  code.write(outfn);
	else code.write("out.o");
}
