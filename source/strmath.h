#pragma once

#include "strlist.h"

namespace xkas
{
	int strmath(const char *str, const int ssl);
	byte strmathentity(const char *str);
    byte strmathparenth(const char *str);

	inline int strmath(const char *str)
	{
		return strmath(str, strlen(str));
	}
	inline int strmath(const string *str)
	{
		return strmath(str->text, str->length);
	}
	inline int strmath(strlist *str, const int str_num = 0)
	{
		return strmath(str->get(str_num));
	}

	inline byte strmathentity(const string *str)
	{
		return strmathentity(str->text);
	}
	inline byte strmathentity(strlist *str, const int str_num = 0)
	{
		return strmathentity(str->get(str_num));
	}
	
	extern void errorwa(byte t, byte pass, const char* s, ...);
}