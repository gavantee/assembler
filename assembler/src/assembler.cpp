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
  bool log = false;
  char *outfn = NULL;
  char *infn;
  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-o") == 0) { outfn = argv[++i]; }
    else if (strcmp(argv[i], "-v") == 0) { log = true; }
    else { infn = argv[i]; }
  }
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
  if (log) code.dump();
  if (outfn != NULL)
    code.write(outfn);
  else code.write("out.o");
}
