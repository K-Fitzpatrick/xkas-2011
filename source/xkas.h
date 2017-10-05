#pragma once

#include <stdarg.h>
#include <time.h>
#include "define.h"
#include "label.h"
#include "macro.h"

#define MODE_HIROM 0
#define MODE_LOROM 1
#define MODE_EXHIROM 2
#define MODE_EXLOROM 3

namespace xkas
{
	extern byte printerrors,
				printwarnings,
				printdata,
				printtime;

	struct passarg
	{
		int filenum;
		int linenum;
		int blocknum;
		int argnum;
		int romoffset;
	};

	void initasmdata(const char *path);
	void initromdata(const char *path);
	
	void initialize(const char *asmpath, const char *srcpath, const char *destpath);
	void assemble(const char *asmpath, const char *srcpath, const char *destpath, byte write);

	void patch(byte init, byte end);
	
	void write(char *path);

	void assemble_op();

	void op1_immediate();
	void op1a();
	void op2constant();
	void op2stack_relative_indexed_indirect_y();
	void op2indirect_long_indexed_y();
	void op2indirect_long();
	void op2indirect_indexed_x();
	void op2indirect_indexed_y();
	void op2indirect();
	void op2stack_relative();
	void op2indexed_x();
	void op2indexed_y();
	void op2absolute();

	void as1n_fn(byte x, int v);
	void as2c_fn(byte x, byte t, int v, int size);
	void as2l_fn(byte x, int v, int size);
	void as2b_rs(byte v);
	void as2b_ss(byte v);
	void invalid_op();

	void errorwa(byte t, byte pass, const char* s, ...);
	void errorna(byte pass, const char *s, ...);
	void warningwa(byte t, const char* s, ...);
	void warningna(byte pass, const char *s, ...);
}