#include "macro.h"

namespace xkas
{
	using ::strcpy;
	using ::strcmp;
	using ::strlen;

	extern strlist *linedata;
	
	extern int filenum,
			   linenum,
			   blocknum;

	extern byte pass;

	extern state_data state;

	extern macro_list macros;

	extern list<file_item> files;
	
	extern list<macro_data> old_macros;
	extern macro_item *cmacro;
	extern macro_data *omacro;

	void macro_list::add(char *name, char *args, int start, int end, int argcount)
	{
		if (find(name))
			return errorwa(1, 0, "macro [%s] already defined");

		static macro_item *macro;
		macro = this->get(this->count);
		macro->name = (char*)malloc(strlen(name) + 1);
		strcpy(macro->name, name);
		macro->args = (char*)malloc(strlen(args) + 1);
		strcpy(macro->args, args);

		macro->filenum = xkas::filenum;
		macro->start = start;
		macro->end = end;
		macro->argcount = argcount;
	}

	macro_item *macro_list::find(char *name)
	{
		static int i;
		for (i = 0; i < this->count; ++i)
			if (!strcmp(this->data[i]->name, name))
				return this->data[i];
		return NULL;
	}
	
	void beginmacro(macro_item *macro, char *arglist, int argcount)
	{
		static int asl;

		xkas::cmacro = macro;
		asl = strlen(arglist);
		if (xkas::state.inmacro >= MACRO_RLIMIT - 1)
			return errorwa(0, 0, "macro recursion limit (%d) reached", MACRO_RLIMIT);

		if (argcount != xkas::cmacro->argcount)
			return errorwa(0, 0, "macro [%s] requires %d argument(s), %d specified", xkas::cmacro->name, xkas::cmacro->argcount, argcount);

		++xkas::state.macronum;
		xkas::omacro = xkas::old_macros.data[xkas::state.inmacro];
		xkas::omacro->filenum = xkas::filenum;
		xkas::omacro->linenum = xkas::linenum;
		xkas::omacro->blocknum = xkas::blocknum;
		xkas::omacro->macro = xkas::cmacro;
		xkas::omacro->args = (char*)malloc(asl + 1);
		strcpy(xkas::omacro->args, arglist);

		++xkas::state.inmacro;
		if (xkas::filenum ^ xkas::cmacro->filenum)
			setasmfile(xkas::files.data[xkas::cmacro->filenum]->name);

		xkas::linenum = xkas::cmacro->start;
		xkas::blocknum = 0;
	}

	byte continuemacro()
	{
		if (xkas::linenum > xkas::cmacro->end)
		{
			xkas::omacro = xkas::old_macros.data[--xkas::state.inmacro];
			if (xkas::omacro->filenum != xkas::cmacro->filenum)
				setasmfile(xkas::files.data[xkas::omacro->filenum]->name);

			xkas::linenum = xkas::omacro->linenum;
			xkas::blocknum = xkas::omacro->blocknum + 1;
			xkas::cmacro = xkas::omacro->macro;
			free(xkas::omacro->args);
			return 1;
		}
		return 0;
	}

	int getmacroargnum(char *arg)
	{
		static strlist *tempstr = new strlist();
		split(tempstr, ',', xkas::omacro->macro->args);

		static int i;
		for (i = 0; i < tempstr->count; ++i)
			if (!strcmp(tempstr, arg, i))
				return i;

		errorwa(1, 0, "argument [%s] not declared in macro [%s]", arg, xkas::omacro->args);
		return 0;
	}

	void resolvemacroargs(string *line)
	{
		static char *arglist, *args, *s;
		arglist = xkas::cmacro->args;
		args = xkas::omacro->args;
		s = line->text;

		static int i;
		for (i = 0; s[i]; )
		{
			if (s[i] == '<')
			{
				if (s[i + 1] == '<')
				{
					i += 2;
					continue;
				}

				static int start, end;
				start = i;
				while (s[++i] != '>')
					if (!s[i])
						return errorwa(0, 0, "broken macro argument");
				end = ++i;

				static int argnum;
				static string *tempstr1 = new string(), *tempstr2;
				static strlist *templist = new strlist();

				strcpyseg(tempstr1, s + start + 1, end - start - 2);
				argnum = getmacroargnum(tempstr1->text);
				split_eq(templist, ',', args);
				tempstr2 = templist->data[argnum];

				if (strisquote(tempstr2))
				{
					strltrim(tempstr2, 1);
					strrtrim(tempstr2, 1);
				}

				strtrim(line, start, end);
				strinsert(line, tempstr2, start);
				i += tempstr2->length - tempstr1->length - 2;
				continue;
			}
			i++;
		}
	}

	byte declaremacros()
	{
		static strlist *templist = new strlist();
		static string *line;
		line = xkas::linedata->data[xkas::linenum];
		strcpy(templist, line);
		split(templist, ' ', line);
		strlisttrim(templist);
		if (templist->count == 2)
		{
			static string *tempstr1, *tempstr2 = new string();
			tempstr1 = templist->data[1];
			if (!stricmp(templist->data[0], "macro"))
			{
				static int z;
				z = strpos_eq(tempstr1, '(');
				if (z == null || tempstr1->text[tempstr1->length - 1] != ')')
				{
					errorwa(1, 0, "invalid macro declaration");
					return 0;
				}

				strcpy(tempstr2, tempstr1->text + z);
				strset(tempstr1, z);
				strltrim(tempstr1, '%');
				strltrim(tempstr2, 1);
				strrtrim(tempstr2, 1);

				static int argcount, start;
				if (tempstr2->length)
					argcount = split_eqc(tempstr2, ',');
				else
					argcount = 0;

				start = ++xkas::linenum;
				while (xkas::linenum < xkas::linedata->count)
				{
					if (strpos(xkas::linedata->data[xkas::linenum], "endmacro") != null)
					{
						static string *tempstr3 = new string();
						strcpy(tempstr3, xkas::linedata->data[xkas::linenum]);
						strtrim(tempstr3, ' ');
						if (tempstr3->length == strlen("endmacro"))
							break;
					}
					++xkas::linenum;
				}

				if (xkas::linenum >= xkas::linedata->count)
				{
					errorwa(1, 0, "macro declaration without matching endmacro tag");
					return 0;
				}

				if (!xkas::pass)
					macros.add(tempstr1->text, tempstr2->text, start, xkas::linenum - 1, argcount);
				return 1;
			}
		}
		return 0;
	}
}