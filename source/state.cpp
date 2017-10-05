 #include "state.h"

namespace xkas
{
	extern byte romdata[MAXROMSIZE];
	extern int romsize;

	extern strlist *opdata;
	extern byte pass,
				oparg_labels;
	extern state_data state;

	int getnum(string *oparg)
	{
		static char *s;

		strtrim(oparg, '#');
		strtrim(oparg, '[');
		strtrim(oparg, ']');
		strtrim(oparg, ' ');
		
		//resolvefreespace(oparg);
		resolvefget(oparg);
		xkas::oparg_labels = resolvelabels(oparg);

		if (strmathentity(oparg))
			return strmath(oparg);

		for (s = oparg->text; *s; ++s)
		{
			if (strisnum(*s))
				return strdectonum(s);
			if (*s == '$')
				if (oparg->length > 1)
					return strhextonum(s + 1);
				else
					errorwa(0, 0, "invalid opcode or expression");
			if (*s == '%')
				if (oparg->length > 1)
					return strbintonum(s + 1);
				else
					errorwa(0, 0, "invalid opcode or expression");
		}
		errorwa(0, 0, "invalid opcode or command");
		return 0;
	}

	byte setsize(int &v)
	{
		static int l, r;
		static string *op1, *op2;
		static char *str;
        static strlist *list = new strlist();

		op1 = xkas::opdata->data[0];
		op2 = xkas::opdata->data[1];
        
        if (strpos(op2, ',') != null)
        {
            v = 0;
            split_eq(list, ',', op2);
            for (int i = 0; i < list->count; i++)
                v |= (getnum(list->data[i]) & 0xFF) << (i << 3);
        }
        else
		    v = getnum(op2);

		if (!striend(op1, ".b"))
		{
			strrtrim(op1, 2);
			return opsize_byte; 
		}
		if (!striend(opdata, ".w"))
		{
			strrtrim(op1, 2);
			return opsize_ushort;
		}
		if (!striend(op1, ".l"))
		{
			strrtrim(op1, 2);
			return opsize_long;
		}
		if (!striend(op1, ".d"))
		{
			strrtrim(op1, 2);
			return opsize_dushort;
		}

		if (oparg_labels)
			return opsize_none;
	
		if (strmathentity(opdata, 1))
		{
			if (v <= 0xFF)
				return opsize_byte;
			if (v <= 0xFFFF)
				return opsize_ushort;
			if (v <= 0xFFFFFF)
				return opsize_long;
			return opsize_dushort;
		}

		for (str = op2->text; *str; ++str)
		{
			if (*str >= '0' && *str <= '9')	//we will guess by dec size
			{ 
				r = strdectonum(str);
				if (r <= 0xFF)
					return opsize_byte;
				if (r <= 0xFFFF)
					return opsize_ushort;
				if (r <= 0xFFFFFF)
					return opsize_long;
				return opsize_dushort;
			}

			if (*str == '$')	//we will guess by hex length
			{
				l = 0;
				while (*(++str))
				{
					if (*str >= '0' && *str <= '9')
						++l;
					else if (*str >= 'A' && *str <= 'F')
						++l;
					else if (*str >= 'a' && *str <= 'f')
						++l;
					else
						break;
				}

				if (l <= 2)
					return opsize_byte;
				if (l <= 4)
					return opsize_ushort;
				if (l <= 6)
					return opsize_long;
				return opsize_dushort;
			}

			if(*str == '%')	//we will guess by binary length
			{ 
				l = 0;
				while(*(++str))
				{
					if (*str == '0' || *str == '1')
						++l;
					else
						break;
				}
      
				if (l <= 8)
					return opsize_byte;
				if (l <= 16)
					return opsize_ushort;
				if (l <= 24)
					return opsize_long;
				return opsize_dushort;
			}
		}
		return opsize_byte; //this should be changed to opsize_null and print an error
	}

	void resolvefget(string* oparg)
	{
		int s = stripos(oparg, "_fget");
		if (s != null)
		{
			char *str = oparg->text;
			int p = s + strlen("_fget") + 1;
			if (str[p] != '(')
				return;

			int l;
			static char c;
			c = str[p - 1];
			if (c == 'b')
				l = 1;
			else if (c == 'w')
				l = 2;
			else if (c == 'l')
				l = 3;
			else if (c == 'd')
				l = 4;
			else
				return;

			static int ssl, pcount;
			ssl = oparg->length;
			int pend = p;
			pcount = 1;
			while (++pend < ssl)
			{
				if (str[pend] == '(')
					++pcount;
				else if (str[pend] == ')')
					--pcount;

				if (!pcount)
					break;
			}
			if (pcount)
				return errorwa(0, 0, "parentheses not closed");

			static int v;
			v = sfctopc(getnum(new string(oparg->text, p + 1, pend)));
			if (v < 0 || v >= xkas::romsize)
				return errorwa(0, 0, "attempt to read non-existant location");

			static int x;
			for (x = 0; l > 0; --l, ++v)
			{
				x <<= 8;
				x |= xkas::romdata[v];
			}

			static char val[0x100];
			sprintf(val, "$%x", x);
			strtrim(oparg, s, pend + 1);
			strinsert(oparg, val, s);
			resolvefget(oparg);
		}
	}

	void resolvefreespace(string *oparg)
	{
		int s = stripos(oparg, "__freespace(");
		if (s != null)
		{
			static int ssl, pcount, i, start, end, length, v;
			ssl = oparg->length;

			char *str = oparg->text;
			int p = s + strlen("__freespace(");
			int pend = p;
			pcount = 1;
			while (++pend < ssl)
			{
				if (str[pend] == '(')
					pcount++;
				else if (str[pend] == ')')
					pcount--;

				if (!pcount)
					break;
			}
			if (pcount)
				return errorwa(0, 0, "parentheses not closed");

			strlist *templist1 = new strlist(), *templist2 = new strlist();
			split_eq(templist1, ',', new string(str, p, pend));
			if (templist1->count != 6)
				return errorwa(0, 0, "invalid number of commands");

			if (!strisquote(templist1->data[0]))
				return errorwa(0, 0, "first argument must be in quotes");

			strltrim(templist1->data[0], 1);
			strrtrim(templist1->data[0], 1);
			split(templist2, ',', templist1->data[0]);
			
			vector<int> numbers = vector<int>();
			for (i = 0; i < templist2->count; ++i)
				numbers.push(getnum(templist2->data[i]));

			if (!stricmp(templist1->data[1], "\"pc\""))
				start = sfctopc(xkas::state.pc);
			else
				start = sfctopc(getnum(templist1->data[1]));

			if (!stricmp(templist1->data[2], "\"eof\""))
				end = xkas::romsize;
			else
				end = sfctopc(getnum(templist1->data[2]));

			length = getnum(templist1->data[3]);

			static byte crossbanks, ignorerats;
			
			if (!strcmp(templist1->data[4], "0"))
				crossbanks = 0;
			else if (!strcmp(templist1->data[4], "1"))
				crossbanks = 1;
			else
				return errorwa(0, 0, "fifth argument can only be 0 or 1");

			if (!strcmp(templist1->data[5], "0"))
				ignorerats = 0;
			else if (!strcmp(templist1->data[5], "1"))
				ignorerats = 1;
			else
				return errorwa(0, 0, "sixth argument can only be 0 or 1");

			v = findfreespace(numbers, start, end, length, crossbanks, ignorerats);
			if (v == null)
				return errorwa(0, 0, "could not find freespace under specified parameters");

			static char val[0x100];
			sprintf(val, "$%x", v);
			strtrim(oparg, s, pend + 1);
			strinsert(oparg, val, s);
			resolvefreespace(oparg);
		}
	}

	int relative(int v, byte s)
	{
		static int pc;
		if (!v)
			return v;

		pc = basetopc(xkas::state.pc) + s;
		if (xkas::pass)
		{
			if (s == 1)	//byte
			{
				if (pc > v) //negative branch
				{
					if ((v - pc) < 0xFFFFFF80)
						errorwa(0, 1, "negative branch too long, exceeded bounds");
				}
				else //positive branch
				{
					if ((v - pc) > 0x7F)
						errorwa(0, 1, "positive branch too long, exceeded bounds");
				}
			} 
			else //ushort
			{     
				if (pc > v) //negative branch
				{ 
					if((v - pc) < 0xFFFF8000)
						errorwa(0, 1, "negative branch too long, exceeded bounds");
				}
				else //positive branch
				{   
					if ((v - pc) > 0x00007FFF)
						errorwa(0, 1, "positive branch too long, exceeded bounds");
				}
			}
		}
		return v - pc;
	}

	int findfreespace(vector<int> numbers, int start, int end, int length, byte crossbanks, byte ignorerats)
	{
		if (!length)
			return pc2snes(0);
		static int first, last;
		last = end - length;
		first = start;
		while (first < last)
		{
			if (!crossbanks && 0x8000 - (first & 0x7FFF) < length)
			{
				first += first & 0x7FFF;
				continue;
			}

			if (xkas::romdata[first + 3] == 'S' &&
				xkas::romdata[first + 2] == 'T' && 
				xkas::romdata[first + 1] == 'A' && 
				xkas::romdata[first + 0] == 'R' &&
				!ignorerats && first + 8 < last)
			{
				static ushort len, inv;
				len = xkas::romdata[first + 4];
				len |= xkas::romdata[first + 5] << 8;
				inv = xkas::romdata[first + 6];
				inv |= xkas::romdata[first + 7] << 8;
				if (len = (ushort)~inv)
				{
					first += len + 8;
					continue;
				}
			}

			static int i;
			static byte x;
			for (i = 0; i < numbers.count; ++i)
				if (numbers.data[i] == xkas::romdata[first])
					break;
			if (i == numbers.count)
			{
				++first;
				continue;
			}

			x = numbers.data[i];
			for (i = 1; i < length; ++i)
				if (x != xkas::romdata[++first])
					break;
			if (i >= length)
				return pc2snes(first - length + 1);
			
			++first;
		}
		return null;
	}

	int sfctopc(int v)
	{
		static int r;

		switch(xkas::state.mode)
		{
			case MODE_HIROM:
				r = v - (v < 0x800000 ? 0x400000 : 0xC00000);
				break;
			case MODE_LOROM:
				r = (v & 0x7F0000) >> 1 | (v & 0x7FFF);
				break;
			case MODE_EXHIROM:
				if (v < 0x400000)
					r = v + 0x400000;
				else if (v < 0x7E0000)
					r = v;
				else if (v < 0xC00000)
					r = v - 0x400000;
				else
					r = v - 0xC00000;
				break;
			case MODE_EXLOROM:
				r = ((v & 0x7F0000) >> 1 | (v & 0x7FFF)) + (v < 0x7E0000 ? 0x400000 : 0);
				break;
		}
		return r;
	}
	void setpcfp()
	{
		xkas::state.fpc = sfctopc(xkas::state.pc);
	}

	int basetopc(int pc)
	{
		if (xkas::state.base)
			return xkas::state.base + (xkas::state.pc - xkas::state.basepc);
		return xkas::state.pc;
	}

	int pc2snes(int pc)
	{
		return ((pc & 0xFF8000) << 1) | 0x8000 | (pc & 0x7FFF);
	}

	void incpc(int x)
	{
		if (xkas::pass)
			xkas::state.bytecount += x;

		switch (xkas::state.mode)
		{
		case MODE_HIROM:
			xkas::state.pc += x;
			break;
		case MODE_LOROM:
			while (x)
			{
				if (x >= 0x4000)
				{
					xkas::state.pc += 0x4000;
					x -= 0x4000;
				}
				else
				{
					xkas::state.pc += x;
					x = 0;
				}
				xkas::state.pc |= 0x8000;
			}
			break;
		case MODE_EXHIROM:
			xkas::state.pc += x;
			if (xkas::state.pc > 0xFFFFFF)
				xkas::state.pc -= 0xc00000;
			break;
		case MODE_EXLOROM:
			while (x)
			{
				if (x >= 0x4000)
				{
					xkas::state.pc += 0x4000;
					x -= 0x4000;
				}
				else
				{
					xkas::state.pc += x;
					x = 0;
				}
				xkas::state.pc |= 0x8000;
			}
			if (xkas::state.pc > 0xFFFFFF)
				xkas::state.pc -= 0x1000000;
			break;
		}
		
		static int a;
		a = sfctopc(xkas::state.pc);
		xkas::romsize = M_GETMAX(xkas::romsize, a);
	}
}