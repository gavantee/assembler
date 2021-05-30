#include <cstdio>
#include <vector>

extern FILE *yyin;
extern int yyparse();
extern std::vector<char> *code;

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

  for (char ch : *code) {
    printf("%c", ch);
  }
}
