#pragma once

#include "string.h"
#include "list.h"

namespace xkas
{
	class strlist : public list<string>
	{
	};
	
	void strlisttrim(strlist *str);

	void split(strlist *dest, const char key, const char *src);
	void split(strlist *dest, const char *key, const char *src, const int ssl);
	void split(strlist *dest, const char *key, const char *src);
	void split(strlist *dest, const char key, const string *src);
	void split(strlist *dest, const char *key, const string *src);
	void split(strlist *dest, const char key, strlist *src, const int src_num = 0);
	void split(strlist *dest, const char *key, strlist *src, const int src_num = 0);
	void split(strlist *dest, const char key, const int src_num = 0);
	void split(strlist *dest, const char *key, const int src_num = 0);
	void split_eq(strlist *dest, const char key, const char *src);
	void split_eq(strlist *dest, const char *key, const char *src, const int ssl);
	void split_eq(strlist *dest, const char *key, const char *src);
	void split_eq(strlist *dest, const char key, const string *src);
	void split_eq(strlist *dest, const char *key, const string *src);
	void split_eq(strlist *dest, const char key, strlist *src, const int src_num = 0);
	void split_eq(strlist *dest, const char *key, strlist *src, const int src_num = 0);
	void split_eq(strlist *dest, const char key, const int src_num = 0);
	void split_eq(strlist *dest, const char *key, const int src_num = 0);

	int split_eqc(const string *src, const char key);

	inline void strset(strlist *str, const int pos = 0, const char c = 0, const int str_num = 0)
	{
		strset(str->get(str_num), pos, c);
	}

	inline void strcpy(strlist *str, const char *key, const int str_num = 0)
	{
		strcpy(str->get(str_num), key);
	}
	inline void strcpy(strlist *str, const string *key, const int str_num = 0)
	{
		strcpy(str->get(str_num), key);
	}
	inline void strcpy(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		strcpy(str->get(str_num), key->get(key_num));
	}
	inline void strcpyseg(strlist *str, const char *key, const int length, const int str_num = 0)
	{
		strcpyseg(str->get(str_num), key, length);
	}
	inline void strcpyseg(strlist *str, const string *key, const int length, const int str_num = 0)
	{
		strcpyseg(str->get(str_num), key, length);
	}
	inline void strcpyseg(strlist *str, strlist *key, const int length, const int str_num , const int key_num = 0)
	{
		strcpyseg(str->get(str_num), key->get(key_num), length);
	}

	inline void strcat(strlist *str, const char *key, const int str_num = 0)
	{
		strcat(str->get(str_num), key);
	}
	inline void strcat(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		strcat(str->get(str_num), key->get(key_num));
	}

	inline byte strcmp(strlist *str, const char *key, const int str_num = 0)
	{
		return strcmp(str->get(str_num), key);
	}
	inline byte strcmp(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		return strcmp(str->get(str_num), key->get(key_num));
	}
	inline byte stricmp(strlist *str, const char *key, const int str_num = 0)
	{
		return stricmp(str->get(str_num), key);
	}
	inline byte stricmp(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		return stricmp(str->get(str_num), key->get(key_num));
	}

	inline int strpos(strlist *str, const char key, const int str_num = 0)
	{
		return strpos(str->get(str_num), key);
	}
	inline int strpos(strlist *str, const char *key, const int str_num = 0)
	{
		return strpos(str->get(str_num), key);
	}
	inline int strpos(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		return strpos(str->get(str_num), key->get(key_num));
	}
	inline int stripos(strlist *str, const char key, const int str_num = 0)
	{
		return stripos(str->get(str_num), key);
	}
	inline int stripos(strlist *str, const char *key, const int str_num = 0)
	{
		return stripos(str->get(str_num), key);
	}
	inline int stripos(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		return stripos(str->get(str_num), key->get(key_num));
	}
	inline int strpos_eq(strlist *str, const char key, const int str_num = 0)
	{
		return strpos_eq(str->get(str_num), key);
	}
	inline int strpos_eq(strlist *str, const char *key, const int str_num = 0)
	{
		return strpos_eq(str->get(str_num), key);
	}
	inline int strpos_eq(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		return strpos_eq(str->get(str_num), key->get(key_num));
	}
	inline int stripos_eq(strlist *str, const char key, const int str_num = 0)
	{
		return stripos_eq(str->get(str_num), key);
	}
	inline int stripos_eq(strlist *str, const char *key, const int str_num = 0)
	{
		return stripos_eq(str->get(str_num), key);
	}
	inline int stripos_eq(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		return stripos_eq(str->get(str_num), key->get(key_num));
	}

	inline int strrpos(strlist *str, const char key, const int str_num = 0)
	{
		return strrpos(str->get(str_num), key);
	}
	inline int strrpos(strlist *str, const char *key, const int str_num = 0)
	{
		return strrpos(str->get(str_num), key);
	}
	inline int strrpos(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		return strrpos(str->get(str_num), key->get(key_num));
	}
	inline int strirpos(strlist *str, const char key, const int str_num = 0)
	{
		return strirpos(str->get(str_num), key);
	}
	inline int strirpos(strlist *str, const char *key, const int str_num = 0)
	{
		return strirpos(str->get(str_num), key);
	}
	inline int strirpos(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		return strirpos(str->get(str_num), key->get(key_num));
	}
	inline int strrpos_eq(strlist *str, const char key, const int str_num = 0)
	{
		return strrpos_eq(str->get(str_num), key);
	}
	inline int strrpos_eq(strlist *str, const char *key, const int str_num = 0)
	{
		return strrpos_eq(str->get(str_num), key);
	}
	inline int strrpos_eq(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		return strrpos_eq(str->get(str_num), key->get(key_num));
	}
	inline int strirpos_eq(strlist *str, const char key, const int str_num = 0)
	{
		return strirpos_eq(str->get(str_num), key);
	}
	inline int strirpos_eq(strlist *str, const char *key, const int str_num = 0)
	{
		return strirpos_eq(str->get(str_num), key);
	}
	inline int strirpos_eq(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		return strirpos_eq(str->get(str_num), key->get(key_num));
	}

	inline byte strbegin(strlist *str, const char key, const int str_num = 0)
	{
		return strbegin(str->get(str_num), key);
	}
	inline byte strbegin(strlist *str, const char *key, const int str_num = 0)
	{
		return strbegin(str->get(str_num), key);
	}
	inline byte strbegin(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		return strbegin(str->get(str_num), key->get(key_num));
	}
	inline byte stribegin(strlist *str, const char key, const int str_num = 0)
	{
		return stribegin(str->get(str_num), key);
	}
	inline byte stribegin(strlist *str, const char *key, const int str_num = 0)
	{
		return stribegin(str->get(str_num), key);
	}
	inline byte stribegin(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		return stribegin(str->get(str_num), key->get(key_num));
	}

	inline byte strend(strlist *str, const char key, const int str_num = 0)
	{
		return strend(str->get(str_num), key);
	}
	inline byte strend(strlist *str, const char *key, const int str_num = 0)
	{
		return strend(str->get(str_num), key);
	}
	inline byte strend(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		return strend(str->get(str_num), key->get(key_num));
	}
	inline byte striend(strlist *str, const char key, const int str_num = 0)
	{
		return striend(str->get(str_num), key);
	}
	inline byte striend(strlist *str, const char *key, const int str_num = 0)
	{
		return striend(str->get(str_num), key);
	}
	inline byte striend(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		return striend(str->get(str_num), key->get(key_num));
	}

	inline void strinsert(strlist *str, const char *key, const int str_num = 0)
	{
		strinfuse(str->get(str_num), key);
	}
	inline void strinsert(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		strinfuse(str->get(str_num), key->get(key_num));
	}
	inline void strinsert(strlist *str, const char *key, const int index, const int str_num = 0)
	{
		strinsert(str->get(str_num), key, index);
	}
	inline void strinsert(strlist *str, strlist *key, const int index, const int str_num = 0, const int key_num = 0)
	{
		strinsert(str->get(str_num), key->get(key_num), index);
	}

	inline void strtrim(strlist *str, const int start, const int end, const int str_num = 0)
	{
		strtrim(str->get(str_num), start, end);
	}
	inline void strltrim(strlist *str, const int start, const int str_num = 0)
	{
		strltrim(str->get(str_num), start);
	}
	inline void strrtrim(strlist *str, const int end, const int str_num = 0)
	{
		strrtrim(str->get(str_num), end);
	}

	inline void strtrim(strlist *str, const char key, const int str_num = 0)
	{
		strtrim(str->get(str_num), key);
	}
	inline void strtrim(strlist *str, const char *key, const int str_num = 0)
	{
		strtrim(str->get(str_num), key);
	}
	inline void strtrim(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		strtrim(str->get(str_num), key->get(key_num));
	}
	inline void stritrim(strlist *str, const char key, const int str_num = 0)
	{
		stritrim(str->get(str_num), key);
	}
	inline void stritrim(strlist *str, const char *key, const int str_num = 0)
	{
		stritrim(str->get(str_num), key);
	}
	inline void stritrim(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		stritrim(str->get(str_num), key->get(key_num));
	}

	inline void strltrim(strlist *str, const char key, const int str_num = 0)
	{
		strltrim(str->get(str_num), key);
	}
	inline void strltrim(strlist *str, const char *key, const int str_num = 0)
	{
		strltrim(str->get(str_num), key);
	}
	inline void strltrim(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		strltrim(str->get(str_num), key->get(key_num));
	}
	inline void striltrim(strlist *str, const char key, const int str_num = 0)
	{
		striltrim(str->get(str_num), key);
	}
	inline void striltrim(strlist *str, const char *key, const int str_num = 0)
	{
		striltrim(str->get(str_num), key);
	}
	inline void striltrim(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		striltrim(str->get(str_num), key->get(key_num));
	}

	inline void strrtrim(strlist *str, const char key, const int str_num = 0)
	{
		strrtrim(str->get(str_num), key);
	}
	inline void strrtrim(strlist *str, const char *key, const int str_num = 0)
	{
		strrtrim(str->get(str_num), key);
	}
	inline void strrtrim(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		strrtrim(str->get(str_num), key->get(key_num));
	}
	inline void strirtrim(strlist *str, const char key, const int str_num = 0)
	{
		strirtrim(str->get(str_num), key);
	}
	inline void strirtrim(strlist *str, const char *key, const int str_num = 0)
	{
		strirtrim(str->get(str_num), key);
	}
	inline void strirtrim(strlist *str, strlist *key, const int str_num = 0, const int key_num = 0)
	{
		strirtrim(str->get(str_num), key->get(key_num));
	}

	inline void strreplace(strlist *str, const char key, const char token, const int str_num = 0)
	{
		strreplace(str->get(str_num), key, token);
	}
	inline void strreplace(strlist *str, const char *key, const char token, const int str_num = 0)
	{
		strreplace(str->get(str_num), key, token);
	}
	inline void strreplace(strlist *str, const char key, const char *token, const int str_num = 0)
	{
		strreplace(str->get(str_num), key, token);
	}
	inline void strreplace(strlist *str, const char *key, const char *token, const int str_num = 0)
	{
		strreplace(str->get(str_num), key, token);
	}
	inline void strreplace_eq(strlist *str, const char key, const char token, const int str_num = 0)
	{
		strreplace_eq(str->get(str_num), key, token);
	}
	inline void strreplace_eq(strlist *str, const char *key, const char token, const int str_num = 0)
	{
		strreplace_eq(str->get(str_num), key, token);
	}
	inline void strreplace_eq(strlist *str, const char key, const char *token, const int str_num = 0)
	{
		strreplace_eq(str->get(str_num), key, token);
	}
	inline void strreplace_eq(strlist *str, const char *key, const char *token, const int str_num = 0)
	{
		strreplace_eq(str->get(str_num), key, token);
	}
	
	inline int strbintonum(strlist *str, const int str_num = 0)
	{
		return strbintonum(str->get(str_num));
	}
	inline int strocttonum(strlist *str, const int str_num = 0)
	{
		return strocttonum(str->get(str_num));
	}
	inline int strdectonum(strlist *str, const int str_num = 0)
	{
		return strdectonum(str->get(str_num));
	}
	inline int strhextonum(strlist *str, const int str_num = 0)
	{
		return strhextonum(str->get(str_num));
	}

	inline byte strissquote(strlist *str, const int str_num = 0)
	{
		return strissquote(str->get(str_num));
	}
	inline byte strisdquote(strlist *str, const int str_num = 0)
	{
		return strisdquote(str->get(str_num));
	}
	inline byte strisquote(strlist *str, const int str_num = 0)
	{
		return strisquote(str->get(str_num));
	}
	inline int strisrep(strlist *str, const char c, const int str_num = 0)
	{
		return strisrep(str->get(str_num), c);
	}
}