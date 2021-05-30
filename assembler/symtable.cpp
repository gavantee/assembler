#include "symtable.h"

#include <iomanip>

using namespace std;

extern std::vector<char> *code;

void SymTable::addSymbol(string label, string section, vector<int> *loc, bool global) {
  symbols[label] = Symbol(label, section, 0, loc, global);
}

void SymTable::addSymbol(string label, string section, int val, bool global) {
  if (symbols.find(label) == symbols.end()) {
    symbols[label] = Symbol(label, section, val, NULL, global);
		return;
	}
	Symbol sym = symbols[label];
	for (int loc : *(sym.locations)) {
    code->at(loc) += val;
	}
	sym.value = val;
	sym.section = section;
	symbols[label] = sym;
}

int SymTable::resolveSymbol(string label, string section, int loc) {
  if (symbols.find(label) == symbols.end()) {
    vector<int> *locs = new vector<int>();
		locs->push_back(loc);
    symbols[label] = Symbol(label, "???", 0, locs, false);
		return 0;
	}
	if (symbols[label].locations == NULL) {
    return symbols[label].value;
	}
	symbols[label].locations->push_back(loc);
	return 0;
}

void SymTable::dump() {
  for (const auto &p : symbols) {
    printSymbol(p.second);
  }
}

void SymTable::printSymbol(const Symbol &s) {
    cout << left << setw(20) << s.label << setw(10) << s.value << setw(20) << s.section << setw(5) << (s.global ? 'g' : 'l') << endl;
}
