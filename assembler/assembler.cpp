#include <cstdio>
#include <vector>

#include "symtable.h"

extern FILE *yyin;
extern int yyparse();
extern std::vector<char> *code;
SymTable sym_table;

int main(int, char**) {
  // Open a file handle to a particular file:
  FILE *myfile = fopen("test.s", "r");
  // Make sure it is valid:
  if (!myfile) {
    return -1;
  }
  // Set Flex to read from it instead of defaulting to STDIN:
  yyin = myfile;

  // Parse through the input:
  yyparse();

	sym_table.reduce();
	sym_table.dump();
	FILE *outfile = fopen("test.o", "w");
  for (char ch : *code) {
    fprintf(outfile, "%c", ch);
  }

}
