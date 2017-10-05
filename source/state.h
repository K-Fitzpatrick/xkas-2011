#pragma once

#include "strmath.h"
#include "vector.h"

#define MODE_HIROM 0
#define MODE_LOROM 1
#define MODE_EXHIROM 2
#define MODE_EXLOROM 3

#define HEADERSIZE 0x200
#define MAXROMSIZE 0x1000000
#define MAXALLSIZE (HEADERSIZE+MAXROMSIZE)

namespace xkas
{
	struct state_data
	{
		int pc;				//rom position
		int fpc;			//rom position in file mode
		byte mode;			//lorom, hirom, exlorom, or exhirom
		byte header;		//whether or not to skip 512 byte header
		byte fillbyte;		//byte to write with 'fill' command
		byte padbyte;		//byte to write with 'pad' command
		int base;			//used for relocatable code
		int basepc;			//used for relocatable code
		int table[0x100];	//table for db strlists
		int rep;			//repeat counter for 'rep' command
		int bytecount;		//counter for bytes written
		int opcount;		//counter for opcodes written
		int inmacro;		//macro recursion counter
		int macronum;		//macro call counter used for macro labels
		byte retmacro;		//true only after first return from a macro
		byte retfile;		//return file flag
		vector<int> pbcount;	//plus branch counters
		vector<int> mbcount;	//minus branch counters

		byte infreespace;
		byte endfreespace;
	};

	struct assume_data
	{
		byte f_mx, mx;
		byte f_db, db;
		byte f_d, d;
	};

	enum
	{
		opsize_none = 0,
		opsize_byte,
		opsize_ushort,
		opsize_long,
		opsize_dushort
	};

	int getnum(string *oparg);
	byte setsize(int &v);
	void resolvefget(string *oparg);
	void resolvefreespace(string *oparg);
	int relative(int v, byte s);
	int findfreespace(vector<int> numbers, int length, int start = 0, int end = 0, byte crossbanks = 0, byte ignorerats = 0);

	int sfctopc(int v);
	void setpcfp();
	int basetopc(int pc);
	int pc2snes(int pc);
	void incpc(int x);

	extern byte resolvelabels(string *oparg);
	extern void errorwa(byte t, byte pass, const char *s, ...);
}