#include "string.h"

namespace xkas
{
	using ::strcpy;
	using ::strcmp;
	using ::stricmp;

	string::string()
	{
		this->text = (char*)malloc(STRSTARTLEN + 1);
		this->capacity = STRSTARTLEN;
		*this->text = 0;
		this->length = 0;
	}
	string::string(const int size)
	{
		this->length = size;
		this->capacity = mallocresize(this->length);
		this->text = (char*)malloc(this->capacity + 1);
		*this->text = 0;
	}
	string::string(const char *str)
	{
		this->length = strlen(str);
		this->capacity = mallocresize(this->length);
		this->text = (char*)malloc(this->capacity + 1);
		strcpy(this->text, str);
	}
	string::string(const char *str, const int start, const int end)
	{
		this->length = end - start;
		this->capacity = mallocresize(this->length);
		this->text = (char*)malloc(this->capacity + 1);
		memcpy(this->text, str + start, this->length);
		this->text[this->length] = 0;
	}
	string::string(const string *str)
	{
		this->length = str->length;
		this->capacity = str->capacity;
		this->text = (char*)malloc(this->capacity + 1);
		strcpy(this->text, str->text);
	}
	string::~string()
	{
		free(this->text);
	}

	void string::strmalloc(const int size)
	{
		this->capacity = mallocresize(size);
		free(this->text);
		this->text = (char*)malloc(this->capacity + 1);
	}
	void string::strrealloc(const int size)
	{
		this->capacity = mallocresize(size);
		this->text = (char*)realloc(this->text, this->capacity + 1);
	}
	
	void strset(string *str, const int pos, const char c)
	{
		if (pos > str->capacity)
			str->strrealloc(pos);
		str->text[pos] = c;
		if (!c && str->length > pos)
			str->length = pos;
	}

	void strcpy(string *str, const char *key)
	{
		str->length = strlen(key);
		if (str->length > str->capacity)
			str->strmalloc(str->length);
		strcpy(str->text, key);
	}
	void strcpy(string *str, const string *key)
	{
		if (key->length > str->capacity)
			str->strmalloc(key->length);
		strcpy(str->text, key->text);
		str->length = key->length;
	}
	void strcpyseg(string *str, const char *key, const int length)
	{
		if (length > str->capacity)
			str->strmalloc(length);
		memcpy(str->text, key, length);
		str->text[length] = 0;
		str->length = length;
	}
	void strcpyseg(string *str, const string *key, const int length)
	{
		if (length > str->capacity)
			str->strmalloc(length);
		memcpy(str->text, key->text, length);
		str->text[length] = 0;
		str->length = length;
	}

	void strcat(string *str, const char *key)
	{
		static int len;

		len = str->length + strlen(key);
		if (len > str->capacity)
			str->strrealloc(len);
		strcpy(str->text + str->length, key);
		str->length = len;
	}
	void strcat(string *str, const string *key)
	{
		static int len;

		len = str->length + key->length;
		if (len > str->capacity)
			str->strrealloc(len);
		strcpy(str->text + str->length, key->text);
		str->length = len;
	}
	void strcat(string *str, const char *key, const int length)
	{
		static int len;

		len = str->length + length;
		if (len > str->capacity)
			str->strrealloc(len);
		strcpy(str->text + str->length, key);
		str->length = len;
	}
	void strcat(string *str, const string *key, const int length)
	{
		static int len;

		len = str->length + length;
		if (len > str->capacity)
			str->strrealloc(len);
		strcpy(str->text + str->length, key->text);
		str->length = len;
	}

	byte strcmp(const string *str, const char *key)
	{
		return strcmp(str->text, key);
	}
	byte strcmp(const string *str, const string *key)
	{
		return strcmp(str->text, key->text);
	}
	byte stricmp(const string *str, const char *key)
	{
		return stricmp(str->text, key);
	}
	byte stricmp(const string *str, const string *key)
	{
		return stricmp(str->text, key->text);
	}

	int strpos(const string *str, const char key)
	{
		return strpos(str->text, key);
	}
	int strpos(const string *str, const char *key)
	{
		return strpos(str->text, key, str->length, strlen(key));
	}
	int strpos(const string *str, const string *key)
	{
		return strpos(str->text, key->text, str->length, key->length);
	}
	int stripos(const string *str, const char key)
	{
		return stripos(str->text, key);
	}
	int stripos(const string *str, const char *key)
	{
		return stripos(str->text, key, str->length, strlen(key));
	}
	int stripos(const string *str, const string *key)
	{
		return stripos(str->text, key->text, str->length, key->length);
	}
	int strpos_eq(const string *str, const char key)
	{
		return strpos_eq(str->text, key);
	}
	int strpos_eq(const string *str, const char *key)
	{
		return strpos_eq(str->text, key, str->length, strlen(key));
	}
	int strpos_eq(const string *str, const string *key)
	{
		return strpos_eq(str->text, key->text);
	}
	int stripos_eq(const string *str, const char key)
	{
		return stripos_eq(str->text, key);
	}
	int stripos_eq(const string *str, const char *key)
	{
		return stripos_eq(str->text, key, str->length, strlen(key));
	}
	int stripos_eq(const string *str, const string *key)
	{
		return stripos_eq(str->text, key->text, str->length, key->length);
	}

	int strrpos(const string *str, const char key)
	{
		return strrpos(str->text, key, str->length);
	}
	int strrpos(const string *str, const char *key)
	{
		return strrpos(str->text, key, str->length, strlen(key));
	}
	int strrpos(const string *str, const string *key)
	{
		return strrpos(str->text, key->text, str->length, key->length);
	}
	int strirpos(const string *str, const char key)
	{
		return strrpos(str->text, key, str->length);
	}
	int strirpos(const string *str, const char *key)
	{
		return strirpos(str->text, key, str->length, strlen(key));
	}
	int strirpos(const string *str, const string *key)
	{
		return strirpos(str->text, key->text, str->length, key->length);
	}
	int strrpos_eq(const string *str, const char key)
	{
		return strrpos_eq(str->text, key, str->length);
	}
	int strrpos_eq(const string *str, const char *key)
	{
		return strrpos_eq(str->text, key, str->length, strlen(key));
	}
	int strrpos_eq(const string *str, const string *key)
	{
		return strrpos_eq(str->text, key->text, str->length, key->length);
	}
	int strirpos_eq(const string *str, const char key)
	{
		return strrpos_eq(str->text, key, str->length);
	}
	int strirpos_eq(const string *str, const char *key)
	{
		return strirpos_eq(str->text, key, str->length, strlen(key));
	}
	int strirpos_eq(const string *str, const string *key)
	{
		return strirpos_eq(str->text, key->text, str->length, key->length);
	}

	byte strbegin(const string *str, const char key)
	{
		return strbegin(str->text, key);
	}
	byte strbegin(const string *str, const char *key)
	{
		return strbegin(str->text, key);
	}
	byte strbegin(const string *str, const string *key)
	{
		return strbegin(str->text, key->text);
	}
	byte stribegin(const string *str, const char key)
	{
		return stribegin(str->text, key);
	}
	byte stribegin(const string *str, const char *key)
	{
		return stribegin(str->text, key);
	}
	byte stribegin(const string *str, const string *key)
	{
		return stribegin(str->text, key->text);
	}

	byte strend(const string *str, const char key)
	{
		return strend(str->text, key, str->length);
	}
	byte strend(const string *str, const char *key)
	{
		return strend(str->text, key, str->length, strlen(key));
	}
	byte strend(const string *str, const string *key)
	{
		return strend(str->text, key->text, str->length, key->length);
	}
	byte striend(const string *str, const char key)
	{
		return striend(str->text, key, str->length);
	}
	byte striend(const string *str, const char *key)
	{
		return striend(str->text, key, str->length, strlen(key));
	}
	byte striend(const string *str, const string *key)
	{
		return striend(str->text, key->text, str->length, key->length);
	}

	void strinfuse(string *str, const char *key, const int ksl)
	{
		const int len = str->length + ksl;
		if (len > str->capacity)
			str->strrealloc(len);
		memcpy(str->text + ksl, str->text, str->length);
		memcpy(str->text, key, ksl);
		str->text[len] = 0;
		str->length = len;
	}
	void strinfuse(string *str, const char *key)
	{
		strinfuse(str, key, strlen(key));
	}
	void strinfuse(string *str, const string *key)
	{
		strinfuse(str, key->text, key->length);
	}

	void strinsert(string *str, const char *key, const int index, const int ksl)
	{
		const int len = str->length + ksl;
		if (len > str->capacity)
			str->strrealloc(len);
		memcpy(str->text + index + ksl, str->text + index, str->length - index);
		memcpy(str->text + index, key, ksl);
		str->text[len] = 0;
		str->length = len;
	}
	void strinsert(string *str, const char *key, const int index)
	{
		strinsert(str, key, index, strlen(key));
	}
	void strinsert(string *str, const string *key, const int index)
	{
		strinsert(str, key->text, index, key->length);
	}

	void strtrim(string *str, const int start, const int end)
	{
		str->length = strtrim(str->text, start, end);
	}
	void strltrim(string *str, const int start)
	{
		str->length = strltrim(str->text, start);
	}
	void strrtrim(string *str, const int end)
	{
		str->length = strrtrim(str->text, end, str->length);
	}

	void strtrim(string *str, const char key)
	{
		str->length = strtrim(str->text, key);
	}
	void strtrim(string *str, const char *key)
	{
		str->length = strtrim(str->text, key);
	}
	void strtrim(string *str, const string *key)
	{
		str->length = strtrim(str->text, key->text, key->length);
	}
	void stritrim(string *str, const char key)
	{
		str->length = stritrim(str->text, key);
	}
	void stritrim(string *str, const char *key)
	{
		str->length = stritrim(str->text, key);
	}
	void stritrim(string *str, const string *key)
	{
		str->length = stritrim(str->text, key->text, key->length);
	}

	void strltrim(string *str, const char key)
	{
		str->length = strltrim(str->text, key, str->length);
	}
	void strltrim(string *str, const char *key)
	{
		str->length = strltrim(str->text, key, str->length, strlen(key));
	}
	void strltrim(string *str, const string *key)
	{
		str->length = strltrim(str->text, key->text, str->length, key->length);
	}
	void striltrim(string *str, const char key)
	{
		str->length = striltrim(str->text, key, str->length);
	}
	void striltrim(string *str, const char *key)
	{
		str->length = striltrim(str->text, key, str->length, strlen(key));
	}
	void striltrim(string *str, const string *key)
	{
		str->length = striltrim(str->text, key->text, str->length, key->length);
	}

	void strrtrim(string *str, const char key)
	{
		str->length = strrtrim(str->text, key, str->length);
	}
	void strrtrim(string *str, const char *key)
	{
		str->length = strrtrim(str->text, key, str->length, strlen(key));
	}
	void strrtrim(string *str, const string *key)
	{
		str->length = strrtrim(str->text, key->text, str->length, key->length);
	}
	void strirtrim(string *str, const char key)
	{
		str->length = strirtrim(str->text, key, str->length);
	}
	void strirtrim(string *str, const char *key)
	{
		str->length = strirtrim(str->text, key, str->length, strlen(key));
	}
	void strirtrim(string *str, const string *key)
	{
		str->length = strirtrim(str->text, key->text, str->length, key->length);
	}

	void strreplace(string *str, const char key, const char token)
	{
		for (char *c = str->text; *c; ++c)
			if (*c == key)
				*c = token;
	}
	void strreplace(string *str, const char *key, const char token, const int ksl)
	{
		int dif = str->length - ksl;
		for (int i = 0; i <= dif; ++i)
		{
			char *c = str->text + i;
			if (!strbegin(c, key))
			{
				*c = token;
				memcpy(c + 1, c + ksl, str->length - i);
				str->length -= ksl - 1;
				dif -= ksl;
			}
		}
	}
	void strreplace(string *str, const char *key, const char token)
	{
		strreplace(str, key, token, strlen(key));
	}
	void strreplace(string *str, const char key, const char *token, const int tsl)
	{
		int ssl = str->length;
		int i = ssl;
		char *c = str->text;
		int n = 1;
		while (i--)
		{
			if (c[i] == key)
			{
				ssl += tsl - 1;
				n = 0;
			}
		}
		if (n)
			return;
		if (ssl >= str->capacity)
			str->capacity = mallocresize(ssl + 1);
		char *temp = (char*)malloc(str->capacity + 1);
		do
		{
			if (c[i] == key)
			{
				memcpy(temp + n, token, tsl);
				n += tsl;
			}
			else
				temp[n++] = c[i];
		} while (++i < str->length);
		temp[ssl] = 0;
		free(str->text);
		str->text = temp;
		str->length = ssl;
	}
	void strreplace(string *str, const char key, const char *token)
	{
		strreplace(str, key, token, strlen(token));
	}
	void strreplace(string *str, const char *key, const char *token, const int ksl, const int tsl)
	{
		int ssl = str->length;
		const int dif = tsl - ksl;
		int i = ssl - ksl + 1;
		int *y = (int*)malloc(ssl * sizeof(int));
		int *t = y;
		char *c = str->text;
		while (i--)
		{
			if (!strbegin(c + i, key))
			{
				ssl += dif;
				*y++ = i;
			}
		}
		if (t == y--)
			return;
		if (ssl >= str->capacity)
			str->capacity = mallocresize(ssl + 1);
		char *temp = (char*)malloc(str->capacity + 1);
		for (int n = 0; i < str->length; )
		{
			if (i == *y)
			{
				memcpy(temp + n, token, tsl);
				i += ksl;
				n += tsl;
				--y;
			}
			else
				temp[n++] = str->text[i++];
		}
		temp[ssl] = 0;
		free(str->text);
		str->text = temp;
		str->length = ssl;
		free(t);
	}
	void strreplace(string *str, const char *key, const char *token)
	{
		strreplace(str, key, token, strlen(key), strlen(token));
	}
	void strreplace_eq(string *str, const char key, const char token)
	{
		for (char *c = str->text; *c; ++c)
		{
			const char x = *c;
			if (x == '\'' || x == '\"')
			{
				char *z = c++;
				while(*c ^ x && *c)
					++c;
				if (!*c)
					c = z;
			}
			if (x == key)
				*c = token;
		}
	}
	void strreplace_eq(string *str, const char *key, const char token, const int ksl)
	{
		int dif = str->length - ksl;
		for (int i = 0; i <= dif; ++i)
		{
			char *c = str->text + i;
			const char x = *c;
			if (x == '\'' || x == '\"')
			{
				char *z = c++;
				while(*c ^ x && *c)
					++c;
				if (!*c)
					c = z;
			}
			if (!strbegin(c, key))
			{
				*c = token;
				memcpy(c + 1, c + ksl, str->length - i);
				str->length -= ksl - 1;
				dif -= ksl;
			}
		}
	}
	void strreplace_eq(string *str, const char *key, const char token)
	{
		strreplace_eq(str, key, token, strlen(key));
	}
	void strreplace_eq(string *str, const char key, const char *token, const int tsl)
	{
		int ssl = str->length;
		int i = ssl;
		char *c = str->text;
		int n = 1;
		while (i--)
		{
			const char x = c[i];
			if (x == '\'' || x == '\"')
			{
				const int z = i--;
				while(c[i] ^ x && i >= 0)
					i--;
				if (i < 0)
					i = z;
			}
			if (c[i] == key)
			{
				ssl += tsl - 1;
				n = 0;
			}
		}
		if (n)
			return;
		if (ssl >= str->capacity)
			str->capacity = mallocresize(ssl + 1);
		char *temp = (char*)malloc(str->capacity + 1);
		do
		{
			if (c[i] == key)
			{
				memcpy(temp + n, token, tsl);
				n += tsl;
			}
			else
				temp[n++] = c[i];
		} while (++i < str->length);
		temp[ssl] = 0;
		free(str->text);
		str->text = temp;
		str->length = ssl;
	}
	void strreplace_eq(string *str, const char key, const char *token)
	{
		strreplace_eq(str, key, token, strlen(token));
	}
	void strreplace_eq(string *str, const char *key, const char *token, const int ksl, const int tsl)
	{
		int ssl = str->length;
		const int dif = tsl - ksl;
		int i = ssl - ksl + 1;
		int *y = (int*)malloc(ssl * sizeof(int));
		int *t = y;
		char *c = str->text;
		while (i--)
		{
			const char x = c[i];
			if (x == '\'' || x == '\"')
			{
				const int z = i--;
				while(c[i] ^ x && i >= 0)
					i--;
				if (i < 0)
					i = z;
			}
			if (!strbegin(c + i, key))
			{
				ssl += dif;
				*y++ = i;
			}
		}
		if (t == y--)
			return;
		if (ssl >= str->capacity)
			str->capacity = mallocresize(ssl + 1);
		char *temp = (char*)malloc(str->capacity + 1);
		for (int n = 0; i < str->length; )
		{
			if (i == *y)
			{
				memcpy(temp + n, token, tsl);
				i += ksl;
				n += tsl;
				--y;
			}
			else
				temp[n++] = str->text[i++];
		}
		temp[ssl] = 0;
		free(str->text);
		str->text = temp;
		str->length = ssl;
		free(t);
	}
	void strreplace_eq( string *str, const char *key, const char *token)
	{
		strreplace_eq(str, key, token, strlen(key), strlen(token));
	}
	
	int strbintonum(const string *str)
	{
		return strbintonum(str->text);
	}
	int strocttonum(const string *str)
	{
		return strocttonum(str->text);
	}
	int strdectonum(const string *str)
	{
		return strdectonum(str->text);
	}
	int strhextonum(const string *str)
	{
		return strhextonum(str->text);
	}

	byte strissquote(const string *str)
	{
		return *str->text == '\'' && str->text[str->length - 1] == '\'';
	}
	byte strisdquote(const string *str)
	{
		return *str->text == '\"' && str->text[str->length - 1] == '\"';
	}
	byte strisquote(const string *str)
	{
		return strissquote(str) || strisdquote(str);
	}
	int strisrep(const string *str, const char c)
	{
		return strisrep(str->text, c);
	}
}