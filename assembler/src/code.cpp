#include "code.h"

#include <iomanip>
#include <cstring>

using namespace std;

void Code::addReloc(const string &section, const string &label, int off, bool rel) {
  if (relocs.find(section) == relocs.end())
    relocs[section] = vector<Reloc>();
  relocs[section].push_back(Reloc(off, label, section, rel));
}

void Code::addSymbol(const string &label, const string &section, vector<Location> *loc, bool global) {
  symbols[label] = Symbol(label, section, 0, loc, global);
}

void Code::addSymbol(const string &label, const string &section, int val, bool global) {
  if (label == section) {
		code[section] = vector<char>();
		this->section = section;
	}
  if (symbols.find(label) == symbols.end()) {
    symbols[label] = Symbol(label, section, val, NULL, global);
		return;
	}
	Symbol sym = symbols[label];
	for (const Location &loc : *(sym.locations)) {
    unsigned int tmp = code[loc.section][loc.off] + (code[loc.section][loc.off + 1] << 8);
    tmp += val;
		code[loc.section][loc.off] = val & 0xff;
		code[loc.section][loc.off + 1] = val >> 8;
	}
	if (global)
    sym.global = true;
	sym.value = val;
	sym.section = section;
	symbols[label] = sym;
}

int Code::resolveSymbol(const string &label, const string &section, int loc, bool rel) {
	  addReloc(section, label, loc - symbols[section].value, rel);
  if (symbols.find(label) == symbols.end()) {
    vector<Location> *locs = new vector<Location>();
		locs->push_back(Location(section, loc));
    symbols[label] = Symbol(label, "UND", 0, locs, false);
		return 0;
	}
	if (symbols[label].locations == NULL) {
    return symbols[label].value;
	}
	symbols[label].locations->push_back(Location(section, loc));
	return 0;
}

void Code::dump() const {
  cout << hex;
	cout << "SECTIONS:" << endl;
	for (const auto &s : code) {
    //if(s.second.size() == 0)
      //continue;
    cout << "section " << s.first << endl;
		for (const auto &c : s.second) {
      printf("%02X ", c & 0xff);
		}
		cout << endl;
	}
  cout << "SYMBOLS:" << endl;
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

void Code::printSymbol(const Symbol &s) const {
    cout << left << setw(20) << s.label << setw(10) << s.value << setw(20) << s.section << setw(5) << (s.global ? 'g' : 'l') << endl;
}

void Code::reduce() {
	for (auto &s : relocs) {
    for (auto r = s.second.begin(); r != s.second.end(); ) {
      if ((symbols[r->label].section == "ABS" && r->rel == false) ||
				(symbols[r->label].section == s.first && r->rel == true)) {
				if (symbols[r->label].section == s.first && r->rel == true) {
				  unsigned int val = code[r->section][r->off] + ((unsigned char) code[r->section][r->off + 1] << 8);
					// printf("%0X%0X\n", code[r->section][r->off + 1], code[r->section][r->off]);
					val -= r->off + 2;
					code[r->section][r->off] = val & 0xff;
					code[r->section][r->off + 1] = val >> 8;
				}
				s.second.erase(r);
				continue;
			}
			if (!(symbols[r->label].section == "ABS" || symbols[r->label].section == "EXT"))
				r->label = symbols[r->label].section;
			++r;
		}
	}
}

void Code::addByte(char b) {
  code[section].push_back(b);
}

void Code::addInt(int val, int n, vector<char> &c, bool le) {
  if (le)
	  for (int i = n - 1; i >= 0; --i)
		  c.push_back(val >> (i * 8));
	else
	  for (int i = 0; i < n; ++i)
		  c.push_back(val >> (i * 8));
}

void Code::addInt(int val, int n, bool le) {
  addInt(val, n, code[section], le);
}

void push_string(vector<char> *code, const string &s) {
  for (auto const &ch : s)
    code->push_back(ch);
	code->push_back('\x00');
}

void Code::fillSymTable() {
  vector<char> *symtab = &code[".symtab"];
  addInt(0, 12, *symtab, false);
	addInt(1 << 4, 1, *symtab, false);
  addInt(0, 3, *symtab, false);
  idsym = map<string, int>();
	idsym["ABS"] = 0;
	int i = 0;
  for (const auto &s : symbols) {
    idsym[s.first] = ++i;
    addInt(id[s.first], 4, *symtab, false); // name
		addInt(s.second.value, 4, *symtab, false); // value
		addInt(2, 4, *symtab, false); // size
		int bind = s.second.global << 4;
		int type = 0;
		if (s.second.label == s.second.section)
      type = 3;
		addInt(bind + type, 1, *symtab, false); // bind and type
		addInt(0, 1, *symtab, false);
		//if (s.second.section == "EXT")
      //addInt(0xffff, 2, *symtab, false);
		addInt(idsec[s.second.section], 2, *symtab, false);
  }
}

void Code::fillRels() {
  vector<char> *rel;
  for (const auto &r : relocs) {
    rel = &code[".rel" + r.first];
		for (const auto &re : r.second) {
		  addInt(re.off, 4, *rel, false);
			addInt(re.rel + 2, 1, *rel, false);
		  addInt(idsym[re.label], 3, *rel, false);
		}
	}
}

void Code::filterSymbols() {
  map<string, Symbol> tmp = map<string, Symbol>();
	for (const auto &s : symbols) {
    if (s.second.global)
    tmp[s.first] = s.second;
	}
	symbols = tmp;
}

void Code::addStandardSections() {
	code[".strtab"] = vector<char>();
	code["ABS"] = vector<char>();
	vector<char> *strtab = &code[".strtab"];
	id = map<string, int>();
	int i = 0;
	push_string(strtab, "ABS");
	id["ABS"] = i;
	i += strlen("ABS") + 1;
	for (auto const &s : symbols) {
    push_string(strtab, s.first);
		id[s.first] = i;
		i += s.first.size() + 1;
	}
	code[".symtab"] = vector<char>();
	push_string(strtab, ".symtab");
	id[".symtab"] = i;
	i += strlen(".symtab") + 1;

	push_string(strtab, ".strtab");
	id[".strtab"] = i;
	i += strlen(".symtab") + 1;

  for (auto const &rel : relocs) {
    code[".rel" + rel.first] = vector<char>();
		push_string(strtab, ".rel" + rel.first);
		id[".rel" + rel.first] = i;
		i += rel.first.size() + 5;
	}

	i = 0;
	idsec = map<string, int>();
	for (auto const &s : code) {
    idsec[s.first] = i++;
	}

	fillSymTable();
	fillRels();
}

void writeInt(int val, int n, FILE *f) {
 for (int i = 0; i < n; ++i)
  fprintf(f, "%c", val >> (i * 8));
}

void Code::write(const char *fn) {

  const char magic[] = "\x7f\x45\x4c\x46\x01\x01\x01\x03" \
								       "\x00\x00\x00\x00\x00\x00\x00\x00" \
								       "\x01\x00\x28\x00\x01\x00\x00\x00" \
								       "\x00\x00\x00\x00\x00\x00\x00\x00";

	FILE *outfile = fopen(fn, "w");
  for (int i = 0; i < 0x20; ++i)
    fprintf(outfile, "%c", magic[i]);
	// fprintf(outfile, "%s", magic);
	int off = 0x34;
	int num = 0;
	int strid = 0;
  for (const auto &s : code) {
    off += s.second.size();
		if (s.first == ".strtab") strid = num;
		++num;
	}
	writeInt(off, 4, outfile);   // e_shoff
	writeInt(0, 4, outfile);     // e_flags
	writeInt(0x34, 2, outfile);  // e_ehsize
	writeInt(0, 2, outfile);     // e_phentsize
	writeInt(0, 2, outfile);     // e_phnum
	writeInt(0x28, 2, outfile);  // e_shentsize
	writeInt(num, 2, outfile);   // e_shnum
	writeInt(strid, 2, outfile); // e_shstrndx

  for (auto &s : code) {
    for (char ch : s.second)
      fprintf(outfile, "%c", ch);
  }
	off = 0x34;
  for (const auto &s : code) {
    writeInt(id[s.first], 4, outfile);
		int type = 1;
		int link = 0;
		int entsize = 0;
		int info = 0;
		if (s.first == ".symtab") {
      type = 2;
			entsize = 16;
			link = idsec[".strtab"];
			info = symbols.size() + 1;
		}
		else if (s.first == ".strtab") {
      type = 3;
		}
		else if (s.first.find(".rel") == 0) {
      type = 9;
			entsize = 8;
			info = idsec[s.first.substr(4)];
			link = idsec[".symtab"];
		}
		else if (s.first == "ABS") {
      type = 0;
		}
		writeInt(type, 4, outfile); // type
		writeInt(0, 8, outfile);
		writeInt(off, 4, outfile); // off
		writeInt(s.second.size(), 4, outfile); // size
		writeInt(link, 4, outfile); // link
		writeInt(info, 4, outfile); // info
		writeInt(1, 4, outfile);
		writeInt(entsize, 4, outfile);
    off += s.second.size();
	}
}
void Code::check() {
  for (const auto &s : symbols) {
    if (s.second.section == "UND") {
      cout << "Symbol " << s.first << " undefined";
		  exit(-1);
    }
  }
}
