#pragma once

#include "file.h"

#define MACRO_RLIMIT 0x200

namespace xkas
{
	struct macro_item
	{
		char *name;
		char *args;
		int filenum, start, end, argcount;
	};

	struct macro_data
	{
		char *args;
		int filenum;
		int linenum;
		int blocknum;
		macro_item *macro;
	};

	class macro_list : public list<macro_item>
	{
	public:
		void add(char *name, char *args, int start, int end, int argcount);
		macro_item *find(char *name);
	};

	void beginmacro(macro_item *macro, char *arglist, int argcount);
	byte continuemacro();
	int getmacroargnum(char *arg);
	void resolvemacroargs(string *line);
	byte declaremacros();
	extern void errorwa(byte t, byte pass, const char* s, ...);
}