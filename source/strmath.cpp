#include "strmath.h"

namespace xkas
{
	int strmath(const char *str, const int ssl)
	{
		int i = 0, start = 0;
		int r, ar[128], array_size = 0;
		char array_gate[128], mode = 0;

		switch (*str)
		{
		case '-':
		case '~':
			mode = str[i];
		case '+':
			++start;
		case '%':
			++i;
			break;
		}
	
		while (i < ssl)
		{
			const char x = str[i++];
			switch (x)
			{
			case '<':
			case '>':
				if (x != str[i])
				{
					errorwa(0, 0, "invalid math operation");
					return 0;
				}
				break;
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case '&':
			case '|':
			case '^':
				break;
			case '(':
			{
				int pstart = i;
				int p = 1;
				while (i < ssl)
				{
					if (str[i] == '(')
						++p;
					else if (str[i] == ')')
						--p;
					if (!p)
						break;
					++i;
				}
				if (!p)
				{
					r = strmath(str + pstart, i++ - pstart);
					continue;
				}
				errorwa(0, 0, "parentheses not closed");
				return 0;
			}
			default:
				continue;
			}
			
			if (str[i - 2] != ')')
			{
				if (str[start] == '$')
					r = strhextonum(str + start + 1);	
				else if (str[start] == '%')	
					r = strbintonum(str + start + 1);	
				else
					r = strdectonum(str + start);
			
				if (mode == '-')
					r *= -1;
				else if (mode == '~')
					r =~ r;
			}
			ar[array_size] = r;
			array_gate[array_size++] = x;
			
			if (x == str[i])
				++i;
			start = i;

			mode = 0;
			switch (str[i])	
			{
			case '-':
			case '~':
				mode = str[i];
				++start;
			case '%':
				++i;
				break;
			}
		}

		if (str[ssl - 1] != ')')
		{
			if (str[start] == '$')
				r = strhextonum(str + start + 1);	
			else if (str[start] == '%')	
				r = strbintonum(str + start + 1);	
			else
				r = strdectonum(str + start);
			
			if (mode == '-')
				r *= -1;
			else if (mode == '~')
				r =~ r;
		}
		ar[array_size] = r;

		r = ar[0];
		for (i = 0; array_size--; )
		{
			switch (array_gate[i++])
			{
			case '+':
				r += ar[i];
				break;
			case '-':
				r -= ar[i];
				break;
			case '*':
				r *= ar[i];
				break;
			case '/':
				if (!ar[i])
				{
					errorwa(0, 0, "division by zero");
					return 0;
				}
				r /= ar[i];
				break;
			case '%':
				if (!ar[i])
				{
					errorwa(0, 0, "modulation by zero");
					return 0;
				}
				r %= ar[i];
				break;
			case '&':
				r &= ar[i];
				break;
			case '|':
				r |= ar[i];
				break;
			case '^':
				r ^= ar[i];
				break;
			case '<':
				r <<= ar[i];
				break;
			case '>':
				r >>= ar[i];
				break;
			}
		}
		return r;
	}

	byte strmathentity(const char *str)
	{
		if (*str == '+' || *str == '-' || *str == '~')
			return 1;
		while (*++str)
		{
			switch (*str)
			{
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case '&':
			case '|':
			case '^':
			case '~':
				return 1;
			case '<':
			case '>':
				if (str[1] == *str)
					return 1;
				break;
			}
		}
		return 0;
	}

    byte strmathparenth(const char *str)
    {
        if (*str != '(')
            return 1;

        int i = 1;
        int pstart = 0;
		int p = 1;
		while (str[i])
		{
			if (str[i] == '(')
				++p;
			else if (str[i] == ')')
				--p;
			if (!p)
            {
                i++;
				break;
            }
			i++;
		}
        return str[i] || p;
    }
}