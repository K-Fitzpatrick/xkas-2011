#include "label.h"

namespace xkas
{
	using ::strcmp;
	using ::strcpy;

	extern byte pass,
				oparg_labels_unresolved;
	extern state_data state;
	extern string *lnamespace;

	extern label_list labels;

	label_list::label_list()
	{
		this->lprefix = new string();
	}

	label_list::~label_list()
	{
		delete this->lprefix;
	}

	void label_list::add(string *name, int offset)
	{
		if (!strbegin(name, '?'))
		{
			static char t[0x100];

			if (!xkas::state.inmacro)
				errorwa(0, 0, "macro label declared outiside of macro");

			strltrim(name, 1);
			strrtrim(name, ':');
			sprintf(t, "__macro_%d_", xkas::state.macronum);
			strinsert(name, t, 0);
		}
		else if (!strbegin(name, '.'))
		{
			strltrim(name, 1);
			strinfuse(name, this->lprefix);
		}
		else
		{
			strrtrim(name, ':');
			strrtrim(name, "()");
			strcpy(this->lprefix, name);
			strcat(this->lprefix, "_");
		}

		static label_item *label;
		label = find(name);

		if (xkas::pass)
			label->pass = 1;
		else if (label)
			errorwa(0, 0, "label [%s] already defined", name->text);
		else
		{
			label = this->get(this->count);
			label->name = (char*)malloc(name->length + 1);
			strcpy(label->name, name->text);

			label->offset = offset;
			label->pass = 0;
		}
	}

	label_item *label_list::find(string *name)
	{
		if (xkas::lnamespace->length)
			strinfuse(name, xkas::lnamespace);
		static int i;
		for (i = 0; i < this->count; ++i)
			if (!strcmp(this->data[i]->name, name->text))
				return this->data[i];
		return NULL;
	}
	
	byte resolvelabels(string *oparg)
	{
		static char *s, resolved;
		s = oparg->text;
		resolved = 0;

		xkas::oparg_labels_unresolved = 0;

		static int i;
		for (i = 0; s[i]; )
		{
			static char x;
			x = s[i];
			if (strisnum(x))
			{
				while (s[++i])
					if (!strisnum(s[i]))
						break;
				continue;
			}
			else if (x == '$')
			{
				while (s[++i])
					if (!strishex(s[i]))
						break;
				continue;
			}
			else if (x == '%')
			{
				while (s[++i])
					if (!strisbin(s[i]))
						break;
				continue;
			}

			if (strislbltxt(s[i]))
			{
				static int sublabel;
				if (x == '.')
					sublabel = 1;
				else if (x == '?')
					sublabel = 2;
				else
					sublabel = 0;

				static int start;
				start = i;
				while (s[++i])
					if (!strisdeftxt(s[i]))
						break;

				static string *tempstr = new string();
				static char t[0x100];

				strcpyseg(tempstr, s + start, i - start);
				if (sublabel == 1)
				{
					strltrim(tempstr, 1);
					strinfuse(tempstr, xkas::labels.lprefix);
				}
				else if (sublabel == 2)
				{
					strltrim(tempstr, 1);
					sprintf(t, "__macro_%d_", xkas::state.macronum);
					strinfuse(tempstr, t);
				}

				static label_item *label;
				static int v;

				label = xkas::labels.find(tempstr);
				if (label)
				{
					v = label->offset;
					if (xkas::pass && !label->pass)
						xkas::oparg_labels_unresolved = 1;
				}
				else
				{
					if (xkas::pass)
						errorwa(0, 1, "label [%s] not found", tempstr->text);

					xkas::oparg_labels_unresolved = 1;
					v = 0;
				}

				strtrim(oparg, start, i);
				sprintf(t, "%d", v);
				strinsert(oparg, t, start);
				s = oparg->text;
				i = start + strlen(t);
				resolved = 1;
				continue;
			}
			++i;
		}
		return resolved;
	}
}