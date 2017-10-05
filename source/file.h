#pragma once

#include "state.h"

#define FILE_RLIMIT 0x200

namespace xkas
{
	struct file_item
	{
		char *data;
		char *name;
		int size;
		int pfilenum, plinenum, pblocknum;
	};

	void loadasmfile(char *path);
	void setasmfile(char *path);
	
	void putb(byte x);
	void putw(ushort x);
	void putl(int x);
	void putd(int x);

	extern void errorna(byte pass, const char *s, ...);
}