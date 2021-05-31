#include "symtable.h"

#include <iomanip>

using namespace std;

extern std::vector<char> *code;

void SymTable::addReloc(string section, string label, int off, bool rel) {
  relocs[section].push_back(Reloc(off, label, section, rel));
}

void SymTable::addSymbol(string label, string section, vector<int> *loc, bool global) {
  symbols[label] = Symbol(label, section, 0, loc, global);
	if (loc == NULL)
    return;
}

void SymTable::addSymbol(string label, string section, int val, bool global) {
  if (label == section) relocs[section] = vector<Reloc>();
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

int SymTable::resolveSymbol(string label, string section, int loc, bool rel) {
	  addReloc(section, label, loc - symbols[section].value, rel);
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
  cout << hex;
  cout << "SYBOLS:" << endl;
  for (const auto &s : symbols) {
    printSymbol(s.second);
  }
  cout << "RELOCS:" << endl;
	for (const auto &s : relocs) {
    for (const auto &r : s.second) {
      cout << left << setw(20) << s.first << setw(10) << r.off << setw(20) << r.label << setw(5) << (r.rel ? "rel" : "abs") << endl;
		}
	}
}

void SymTable::printSymbol(const Symbol &s) {
    cout << left << setw(20) << s.label << setw(10) << s.value << setw(20) << s.section << setw(5) << (s.global ? 'g' : 'l') << endl;
}

void SymTable::reduce() {
	for (auto &s : relocs) {
    for (auto r = s.second.begin(); r != s.second.end(); ) {
      if ((symbols[r->label].section == "ABS" && r->rel == false) ||
				(symbols[r->label].section == s.first && r->rel == true)) {
				s.second.erase(r);
				continue;
			}
			if (!symbols[r->label].global)
				r->label = symbols[r->label].section;
			++r;
		}
	}
}
