#ifndef SYMTABLE_H_
#define SYMTABLE_H_

#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

typedef struct Symbol {
  string label = "de znam";
	int value;
	string section;
	vector<int> *locations = NULL;
	bool global = false;
	Symbol() {
    label = "nemoj";
	}
	Symbol(string l, string s, int v, vector<int> *loc, bool g = false) {
		label = l;
		section = s;
		value = v;
		locations = loc;
		global = g;
	}
} Symbol;

typedef struct Reloc {
  int off;
	string label;
	bool rel;
	string section;
	Reloc(int o, string l, string s, bool r) {
    label = l;
		section = s;
		off = o;
		rel = r;
	}
} Reloc;

class SymTable {
private:
  map<string, Symbol> symbols;
	map<string, vector<Reloc>> relocs;
public:
	void addSymbol(string label, string section, vector<int> *loc, bool global);
	void addSymbol(string label, string section, int val, bool global = false);
	int resolveSymbol(string label, string section, int loc, bool rel = false);
  void dump();
  void printSymbol(const Symbol &s);
	void addReloc(string section, string label, int off, bool rel);
	void reduce();
};

#endif

