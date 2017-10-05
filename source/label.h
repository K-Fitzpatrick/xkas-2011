#pragma once

#include "file.h"

namespace xkas
{
	struct label_item
	{
		char *name;
		int offset;
		byte pass;
		byte freespace;
	};

	class label_list : public list<label_item>
	{
	public:
		string *lprefix;
	
		label_list();
		~label_list();
		
		void add(string *name, int offset);
		label_item *find(string *name);
	};

	byte resolvelabels(string *oparg);

	extern void errorwa(byte t, byte pass, const char *s, ...);
}