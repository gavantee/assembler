#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "emulator.h"

#include "timer.h"
#include "terminal.h"


#define LOG 0

const unsigned short masks[] = {0x0, 0x0, 0x4000, 0x2000};

typedef unsigned short ushort;
typedef unsigned char uchar;

uchar mem[65536] = {0};
ushort reg[16] = {0};

unsigned short int_reqs = 0;

int get_word(int addr) {
  return mem[addr] + (mem[addr + 1] << 8);
}


void load_hex(char *fn) {
  FILE *in = fopen(fn, "r");
	if (in == NULL) {
    printf("Failed to open %s\n", fn);
		exit(-1);
	}
	int addr;
	char line[32];
	while(!feof(in)) {
    fscanf(in, "%X: ", &addr);
		fgets(line, 32, in);
		int n = strlen(line);
		for (int i = 0; i < n; i += 3) {
      int val = strtol(line + i, NULL, 16);
      mem[addr++] = val;
		}
	}
	/*
	for (int i = 0; i < 0x6C; ++i) {
    if (i % 8 == 0) printf("\n");
    printf("%02X ", mem[i]);
	}
	*/
}

void push(uchar reg_num) {
  int val = reg[reg_num];
  mem[--reg[6]] = val >> 8;
	mem[--reg[6]] = val & 0xff;
}

void pop(uchar reg_num) {
	reg[reg_num] = get_word(reg[6]);
	reg[6] += 2;
}


void int_call(int ivt_ent) {
	push(7);
	push(8);
	reg[7] = mem[ivt_ent * 2];
  reg[8] |= 1 << 15;
}

void int_req(int ivt_ent) {
  // printf("requesting: %d\n", ivt_ent);
	int_reqs |= 1 << ivt_ent;
  // int_call(ivt_ent);
}

void interrupts() {
  if ((reg[8] >> 15) != 0) return;
  for (int i = 2; i < 4; ++i) {
    if ((int_reqs & (1 << i)) != 0 && (reg[8] & masks[i]) == 0) {
      int_reqs &= ~(1 << i);
      int_call(i);
		}
	}
}

void psw_set(unsigned int val, ushort flags /*ncoz*/) {
  // printf("psw_set: %0X\n", val);
  int zb = (val & 0xffff) == 0;
	int nb = (val & 0x00008000) != 0;
	int cb = (val & 0x00010000) != 0;
	if ((flags >> 3) & 1) {
    reg[8] &= 0xfff7;
		reg[8] += nb << 3;
	}
	if ((flags >> 2) & 1) {
    reg[8] &= 0xfffb;
		reg[8] += cb << 2;
	}
	if ((flags >> 0) & 1) {
    reg[8] &= 0xfffe;
		reg[8] += zb << 0;
	}
}

bool psw_n() {
  return (reg[8] >> 3) & 1;
}

bool psw_z() {
  return reg[8] & 1;
}

bool psw_o() {
  return (reg[8] >> 1) & 1;
}

bool psw_c() {
  return (reg[8] >> 2) & 1;
}

void psw_setc(int c) {
  reg[8] &= 0xfffb;
  reg[8] += c << 2;
}

void psw_seto(int o) {
  reg[8] &= 0xfffd;
  reg[8] += o << 1;
}

void exec_inst(uchar opcode, uchar regs, uchar addr_mode, int operand) {
  uchar reg_s = regs & 0xf;
	uchar reg_d = regs >> 4;
	uchar am = addr_mode & 0xf;
	uchar up = addr_mode >> 4;
	if (LOG) printf("%02X %02X %02X %04X\n", opcode, regs, addr_mode, operand);
	switch(up) {
  case 1:
    reg[reg_s] -= 2;
		break;
  case 2:
		reg[reg_s] += 2;
		break;
	}
	int str_op;
	int legal = 1;
	switch(am) {
  case 0:
		str_op = 1 << 17;
    operand = operand;
		break;
  case 1:
		str_op = 1 << 17;
		operand = reg[reg_s];
		break;
  case 2:
		str_op = reg[reg_s];
		operand = mem[reg[reg_s]];
		break;
  case 3:
		str_op = reg[reg_s] + operand;
		operand = mem[reg[reg_s] + operand];
		break;
  case 4:
		str_op = operand;
		operand = mem[operand];
		break;
  case 5:
		str_op = 1 << 17;
		operand = reg[reg_s] + operand;
		break;
	}

	if (LOG) printf("izracunati operand: %02X\nStore operand: %02X\n", operand, str_op);

	switch(up) {
  case 3:
    reg[reg_s] -= 2;
		break;
  case 4:
		reg[reg_s] += 2;
		break;
	}

	switch(opcode) {
  case 0x00:
    exit(0);
		break;
  case 0x10:
		push(7);
		push(8);
		reg[7] = get_word((reg_d % 8) * 2);
		break;
  case 0x20:
		pop(8);
		pop(7);
		break;
  case 0x30:
		push(7);
		reg[7] = operand;
		break;
  case 0x40:
		pop(7);
		break;
  case 0x50:
		reg[7] = operand;
		break;
  case 0x51:
		if (psw_z()) reg[7] = operand;
		break;
  case 0x52:
		if (!psw_z()) reg[7] = operand;
		break;
  case 0x53:
		if (!psw_n() && !psw_z()) reg[7] = operand;
		break;
  case 0x60:
		unsigned short tmp = reg[reg_s];
		reg[reg_s] = reg[reg_d];
		reg[reg_d] = tmp;
		break;
  case 0x70:
		reg[reg_d] += reg[reg_s];
		break;
  case 0x71:
		reg[reg_d] -= reg[reg_s];
		break;
  case 0x72:
		reg[reg_d] *= reg[reg_s];
		break;
  case 0x73:
		reg[reg_d] /= reg[reg_s];
		break;
  case 0x74:
		psw_set(reg[reg_d] - reg[reg_s], 0xf);
		if (((reg[reg_d] & 0x8000) != (reg[reg_s] & 0x8000))) {
      psw_seto(((reg[reg_d] - reg[reg_s]) & 0x8000) != (reg[reg_d] & 0x8000));
		}
		else psw_seto(0);
		break;
	case 0x80:
    reg[reg_d] = ~reg[reg_d];
		break;
  case 0x81:
		reg[reg_d] &= reg[reg_s];
		break;
  case 0x82:
		reg[reg_d] |= reg[reg_s];
		break;
  case 0x83:
		reg[reg_d] ^= reg[reg_s];
		break;
  case 0x84:
		psw_set(reg[reg_d] & reg[reg_s], 0x9);
		break;
  case 0x90:
		psw_set((unsigned int) reg[reg_d] << reg[reg_s], 0xd);
		reg[reg_d] <<= reg[reg_s];
		break;
  case 0x91:
		psw_set((unsigned int) reg[reg_d] >> reg[reg_s], 0xd);
		psw_setc((reg[reg_d] >> (reg[reg_s] - 1)) & 1);
		reg[reg_d] >>= reg[reg_s];
		break;
  case 0xA0:
		reg[reg_d] = operand;
		break;
  case 0xB0:
		if (str_op == (1 << 17)) {
      reg[7] -= 5;
			int_call(1);
    }
		mem[str_op] = reg[reg_d];

		if (str_op == 0xff00)
      printf("%c", mem[str_op]);
		break;
  defalut:
		int_call(1);
		break;
	}
}

void read_inst() {
  if (LOG) printf("%04X: ", reg[7]);
  uchar opcode = mem[reg[7]++];
	uchar regs = 0;
	uchar addr_mode = 0;
	int operand = 0;
	switch(opcode >> 4) {
  case 0x0: case 0x2: case 0x4:
    break;
	case 0x6: case 0x7: case 0x8: case 0x9:
		regs = mem[reg[7]++];
		break;
	default:
		regs = mem[reg[7]++];
		addr_mode = mem[reg[7]++];
		switch (addr_mode & 0xf) {
    case 0x1: case 0x2:
      break;
    default:
			operand = get_word(reg[7]);
			reg[7] += 2;
		}
	}
	exec_inst(opcode, regs, addr_mode, operand);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <input_file>", argv[0]);
		exit(0);
	}

	char *fn = argv[1];
	int c;
	load_hex(fn);
	reg[7] = get_word(0);
	timer_init();
	terminal_init();
	int i = 0;
	while (true) {
    // printf("%02X\n", int_reqs);
		terminal_read(&mem[0xff02]);
    timer(mem[0xff10]);
    read_inst();
		interrupts();
		//if (++i > 5)
      //break;
	}
}

