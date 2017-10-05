#include "define.h"

namespace xkas
{
	extern define_list defines;
		
	void define_list::add(const char *name, const char *value, const byte hold)
	{
		if (strpos(value, name) == null)
		{
			define_item *di = find(name);
			if (!di)
			{
				di = this->get(this->count);
				di->name = new string();
				di->value = new string();
				di->hold = 0;
				strcpy(di->name, name);
			}
			else if (di->hold)
				return;
			strcpy(di->value, value);
			di->hold = hold;
		}
		else
			errorwa(0, 0, "define conatains its own value (infinite regression)");
	}

	void define_list::add(const string *name, const string *value, const byte hold)
	{
		add(name->text, value->text, hold);
	}

	define_item *define_list::find(const char *name)
	{
		for (int i = count; --i >= 0; )
			if (!strcmp(this->data[i]->name, name))
				return this->data[i];
		return NULL;
	}

	define_item *define_list::find(const string *name)
	{
		return find(name->text);
	}

	void resolvedefines(string *block)
	{
		static char *s, resolved;
		static int i, n;
		s = block->text;

		n = 0;
check_define:
		if (strpos_eq(s + n, '!') != null)
		{
			if (strpos_eq(s + n, " equ ") != null || strpos_eq(s + n, " = ") != null)
			{
				n = strpos_eq(s + n, " : ");
				if (n != null)
				{
					n += 3;
					goto check_define;
				}
				else
					return;
			}
		}

		for (i = n; s[i]; )
		{
			if (s[i] == '\"')
			{
				++i;
				while (s[i] && s[i] != '\"')
					++i;
				++i;
			}

			if (s[i] == '!')
			{
				static int start, end;
				start = i;
				while (s[++i])
					if (!strisdeftxt(s[i]))
						break;
				end = i;

				static string *tempstr = new string();
				strcpyseg(tempstr, s + start, end - start);

				if (s[i] == '(' && s[i + 1] == ')')
					end += 2;
				strtrim(block, start, end);

				static define_item *di;
				di = xkas::defines.find(tempstr);
				if (di)
				{
					strinsert(block, di->value, start);
					s = block->text;
				}
				else
					errorwa(1, 0, "define not declared (yet?)");
				i = start;
			}
			else
				++i;
		}
	}
}