#ifndef CODE_H_
#define CODE_H_

#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

typedef struct Location {
  string section;
	int off;
	Location(string s, int o) {
    section = s;
		off = o;
	}
} Location;

typedef struct Symbol {
  string label;
	int value;
	string section;
	vector<Location> *locations = NULL;
	bool global = false;
	Symbol() {
    label = "nemoj";
	}
	Symbol(string l, string s, int v, vector<Location> *loc, bool g = false) {
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

class Code {
private:
  map<string, Symbol> symbols;
	map<string, vector<Reloc>> relocs;
	map<string, vector<char>> code;
	map<string, int> id;
	map<string, int> idsec;
	map<string, int> idsym;
	string section;

	void fillSymTable();
	void fillRels();
public:
	void addSymbol(string label, string section, vector<Location> *loc, bool global);
	void addSymbol(string label, string section, int val, bool global = false);
	int resolveSymbol(string label, string section, int loc, bool rel = false);
  void dump();
  void printSymbol(const Symbol &s);
	void addReloc(string section, string label, int off, bool rel);
	void reduce();
	void addByte(char b);
	void addInt(int val, int n, bool le = true);
	void addInt(int val, int n, vector<char> &c, bool le = true);
	void write(char *fn);
	void addStandardSections();
	void filterSymbols();
	void check();
};

#endif

