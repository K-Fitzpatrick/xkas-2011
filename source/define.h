#pragma once

#include "file.h"

namespace xkas
{
	struct define_item
	{
		string *name;
		string *value;
		byte hold;
	};

	class define_list : public list<define_item>
	{
	public:
		void add(const char *name, const char *value, const byte hold = 0);
		void add(const string *name, const string *value, const byte hold = 0);
		define_item *find(const char *name);
		define_item *find(const string *name);
	};

	void resolvedefines(string *block);
	extern void errorwa(byte t, byte pass, const char* s, ...);
}