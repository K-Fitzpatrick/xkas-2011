#include "base.h"

namespace xkas
{
	/* Returns the first occurrance of key in str */
	int strpos(const char *str, const char key)
	{
		for (int i = 0; str[i]; ++i)
			if (str[i] == key)
				return i;
		return null;
	}
	int strpos(const char *str, const char *key, const int ssl, const int ksl)
	{
		if (ksl > ssl)
			return null;
		const int dif = ssl - ksl;
		for (int i = 0; i <= dif; ++i)
			if (!memcmp(str + i, key, ksl))
				return i;
		return null;
	}
	int strpos(const char *str, const char *key)
	{
		return strpos(str, key, strlen(str), strlen(key));
	}
	int stripos(const char *str, const char key)
	{
		const char y = upper[key];
		for (int i = 0; str[i]; ++i)
			if (upper[str[i]] == y)
				return i;
		return null;
	}
	int stripos(const char *str, const char *key, const int ssl, const int ksl)
	{
		if (ksl > ssl)
			return null;
		const int dif = ssl - ksl;
		for (int i = 0; i <= dif; ++i)
			if (!stribegin(str + i, key))
				return i;
		return null;
	}
	int stripos(const char *str, const char *key)
	{
		return stripos(str, key, strlen(str), strlen(key));
	}
	int strpos_eq(const char *str, const char key)
	{
		for (int i = 0, x = *str; x; x = str[++i])
		{
			if (x == '\'' || x == '\"')
			{
				const int z = i++;
				while(str[i] && str[i] ^ x)
					++i;
				if (!str[i])
					i = z;
			}
			if (x == key)
				return i;
		}
		return null;
	}
	int strpos_eq(const char *str, const char *key, const int ssl, const int ksl)
	{
		if (ksl > ssl)
			return null;
		const int dif = ssl - ksl;
		for (int i = 0, x = *str; i <= dif; x = str[++i])
		{
			if (x == '\'' || x == '\"')
			{
				const int z = i++;
				while (str[i] != x && i <= dif)
					++i;
				if (i > dif)
					i = z;
			}
			if (!memcmp (str + i, key, ksl))
				return i;
		}
		return null;
	}
	int strpos_eq(const char *str, const char *key)
	{
		return strpos_eq(str, key, strlen(str), strlen(key));
	}
	int stripos_eq(const char *str, const char key)
	{
		const char y = upper[key];
		for (int i = 0, x = *str; x; x = str[++i])
		{
			if (x == '\'' || x == '\"')
			{
				const int z = i++;
				while(str[i] ^ x && str[i])
					++i;
				if (!str[i])
					i = z;
			}
			if (upper[str[i]] == y)
				return i;
		}
		return null;
	}
	int stripos_eq(const char *str, const char *key, const int ssl, const int ksl)
	{
		if (ksl > ssl)
			return null;
		const int dif = ssl - ksl;
		for (int i = 0, x = *str; i <= dif; x = str[++i])
		{
			if (x == '\'' || x == '\"')
			{
				const int z = i++;
				while (str[i] != x && i <= dif)
					++i;
				if (i > dif)
					i = z;
			}
			if (!stribegin(str + i, key))
				return i;
		}
		return null;
	}
	int stripos_eq(const char *str, const char *key)
	{
		return stripos_eq(str, key, strlen(str), strlen(key));
	}

	/* Returns the last occurrance of key in str */
	int strrpos(const char *str, const char key, const int ssl)
	{
		for (int i = ssl; i; )
			if (str[--i] == key)
				return i;
		return null;
	}
	int strrpos(const char *str, const char key)
	{
		return strrpos(str, key, strlen(str));
	}
	int strrpos(const char *str, const char *key, const int ssl, const int ksl)
	{
		for (int i = ssl - ksl; i >= 0; --i)
			if (!memcmp(str + i, key, ksl))
				return i;
		return null;
	}
	int strrpos(const char *str, const char *key)
	{
		return strrpos(str, key, strlen(str), strlen(key));
	}
	int strirpos(const char *str, const char key, const int ssl)
	{
		const char y = upper[key];
		for (int i = ssl; i; )
			if (upper[str[--i]] == y)
				return i;
		return null;
	}
	int strirpos(const char *str, const char key)
	{
		return strirpos(str, key, strlen(str));
	}
	int strirpos(const char *str, const char *key, const int ssl, const int ksl)
	{
		for (int i = ssl - ksl; i >= 0; --i)
			if (!stribegin(str + i, key))
				return i;
		return null;
	}
	int strirpos(const char *str, const char *key)
	{
		return strirpos(str, key, strlen(str), strlen(key));
	}
	int strrpos_eq(const char *str, const char key, const int ssl)
	{
		for (int i = ssl; i;)
		{
			const char x = str[--i];
			if (x == '\'' || x == '\"')
			{
				const int z = i--;
				while(str[i] ^ x && i >= 0)
					--i;
				if (i < 0)
					i = z;
			}
			if (str[i] == key)
				return i;
		}
		return null;
	}
	int strrpos_eq(const char *str, const char key)
	{
		return strrpos_eq(str, key, strlen(str));
	}
	int strrpos_eq(const char *str, const char *key, const int ssl, const int ksl)
	{
		for (int i = ssl - ksl; i >= 0; --i)
		{
			const char x = str[i];
			if (x == '\'' || x == '\"')
			{
				const int z = i--;
				while(str[i] ^ x && i >= 0)
					--i;
				if (i < 0)
					i = z;
			}
			if (!memcmp(str + i, key, ksl))
				return i;
		}
		return null;
	}
	int strrpos_eq(const char *str, const char *key)
	{
		return strrpos_eq(str, key, strlen(str), strlen(key));
	}
	int strirpos_eq(const char *str, const char key, const int ssl)
	{
		const char y = upper[key];
		for (int i = ssl; i; )
		{
			const char x = str[--i];
			if (x == '\'' || x == '\"')
			{
				const int z = i--;
				while(str[i] ^ x && i >= 0)
					--i;
				if (i < 0)
					i = z;
			}
			if (!stribegin(str + i, key))
				return i;
		}
		return null;
	}
	int strirpos_eq(const char *str, const char key)
	{
		return strirpos_eq(str, key, strlen(str));
	}
	int strirpos_eq(const char *str, const char *key, const int ssl, const int ksl)
	{
		for (int i = ssl - ksl; i >= 0; --i)
		{
			const char x = str[i];
			if (x == '\'' || x == '\"')
			{
				const int z = i--;
				while(str[i] ^ x && i >= 0)
					--i;
				if (i < 0)
					i = z;
			}
			if (!stribegin(str + i, key))
				return i;
		}
		return null;
	}
	int strirpos_eq(const char *str, const char *key)
	{
		return strirpos_eq(str, key, strlen(str), strlen(key));
	}

	/* Checks if str begins with key */
	byte strbegin(const char *str, const char key)
	{
		return *str ^ key;
	}
	byte strbegin(const char *str, const char *key)
	{
		for (; *key; ++str, ++key)
			if (*str ^ *key)
				return 1;
		return 0;
	}
	byte stribegin(const char *str, const char key)
	{
		return upper[*str] ^ upper[key];
	}
	byte stribegin(const char *str, const char *key)
	{
		for(; *key; ++str, ++key)
			if (upper[*str] ^ upper[*key])
				return 1;
		return 0;
	}

	/* Checks if str ends with key */
	byte strend(const char *str, const char key, const int ssl)
	{
		return str[ssl - 1] ^ key;
	}
	byte strend(const char *str, const char key)
	{
		return strend(str, key, strlen(str));
	}
	byte strend(const char *str, const char *key, const int ssl, const int ksl)
	{
		return memcmp(str + ssl - ksl, key, ksl);
	}
	byte strend(const char *str, const char *key)
	{
		return strend(str, key, strlen(str), strlen(key));
	}
	byte striend(const char *str, const char key, const int ssl)
	{
		return upper[str[ssl - 1]] ^ upper[key];
	}
	byte striend(const char *str, const char key)
	{
		return striend(str, key, strlen(str));
	}
	byte striend(const char *str, const char *key, const int ssl, const int ksl)
	{
		return stribegin(str + ssl - ksl, key);
	}
	byte striend(const char *str, const char *key)
	{
		return striend(str, key, strlen(str), strlen(key));
	}

	/* Removes all characters between start and end of str */
	int strtrim(char *str, const int start, const int end)
	{
		int i1 = start, i2 = end;
		while (str[i2])
			str[i1++] = str[i2++];
		str[i1] = 0;
		return i1;
	}
	int strltrim(char *str, const int start)
	{
		int i = 0;
		for (char* c = str + start; c[i]; ++i)
			str[i] = c[i];
		str[i] = 0;
		return i;
	}
	int strrtrim(char *str, const int end, const int ssl)
	{
		str[ssl - end] = 0;
		return ssl - end;
	}
	int strrtrim(char *str, const int end)
	{
		return strrtrim(str, end, strlen(str));
	}

	/* Removes all instanced of key from str and
		returns the new length */
	int strtrim(char *str, const char key)
	{
		int n = 0;
		for (int i = 0; str[i]; ++i)
			if (str[i] ^ key)
				str[n++] = str[i];
		str[n] = 0;
		return n;
	}
	int strtrim(char *str, const char *key, const int ksl)
	{
		int n = 0;
		for (int i = 0; str[i]; )
			if (memcmp(str + i, key, ksl))
				str[n++] = str[i++];
			else
				i += ksl;
		str[n] = 0;
		return n;
	}
	int strtrim(char *str, const char *key)
	{
		return strtrim(str, key, strlen(key));
	}
	int stritrim(char *str, const char key)
	{
		const char y = upper[key];
		int n = 0;
		for (int i = 0; str[i]; ++i)
			if (upper[str[i]] ^ y)
				str[n++] = str[i];
		str[n] = 0;
		return n;
	}
	int stritrim(char *str, const char *key, const int ksl)
	{
		int n = 0;
		for (int i = 0; str[i]; )
			if (stribegin(str + i, key))
				str[n++] = str[i++];
			else
				i += ksl;
		str[n] = 0;
		return n;
	}
	int stritrim(char *str, const char *key)
	{
		return stritrim(str, key, strlen(key));
	}

	/* Removes key from beginning of str (if it exists)
		and returns the modified length of str */
	int strltrim(char *str, const char key, const int ssl)
	{
		if (*str ^ key)
			return ssl;
		const int len = ssl - 1;
		memcpy(str, str + 1, len);
		str[len] = 0;
		return len;
	}
	int strltrim(char *str, const char key)
	{
		return strltrim(str, key, strlen(str));
	}
	int strltrim(char *str, const char *key, const int ssl, const int ksl)
	{
		if (!memcmp(str, key, ksl))
			return ssl;
		const int len = ssl - ksl;
		memcpy(str, str + ksl, len);
		str[len] = 0;
		return len;
	}
	int strltrim(char *str, const char *key)
	{
		return strltrim(str, key, strlen(str), strlen(key));
	}
	int striltrim(char *str, const char key, const int ssl)
	{
		if (upper[*str] ^ upper[key])
			return ssl;
		const int len = ssl - 1;
		memcpy(str, str + 1, len);
		str[len] = 0;
		return len;
	}
	int striltrim(char *str, const char key)
	{
		return striltrim(str, key, strlen(str));
	}
	int striltrim(char *str, const char *key, const int ssl, const int ksl)
	{
		if (stribegin(str, key))
			return ssl;
		const int len = ssl - ksl;
		memcpy(str, str + ksl, len);
		str[len] = 0;
		return len;
	}
	int striltrim(char *str, const char *key)
	{
		return striltrim(str, key, strlen(str), strlen(key));
	}

	/* Removes key from the end of str (if it exists)
		and returns the modified length of str */
	int strrtrim(char *str, const char key, const int ssl)
	{
		const int len = ssl - 1;
		if (str[len] ^ key)
			return ssl;
		str[len] = 0;
		return len;
	}
	int strrtrim(char *str, const char key)
	{
		return strrtrim(str, key, strlen(str));
	}
	int strrtrim(char *str, const char *key, const int ssl, const int ksl)
	{
		const int len = ssl - ksl;
		if (memcmp(str + len, key, ksl))
			return ssl;
		str[len] = 0;
		return len;
	}
	int strrtrim(char *str, const char *key)
	{
		return strrtrim(str, key, strlen(str), strlen(key));
	}
	int strirtrim(char *str, const char key, const int ssl)
	{
		const int len = ssl - 1;
		if (upper[str[len]] ^ upper[key])
			return ssl;
		str[len] = 0;
		return len;
	}
	int strirtrim(char *str, const char key)
	{
		return strirtrim(str, key, strlen(str));
	}
	int strirtrim(char *str, const char *key, const int ssl, const int ksl)
	{
		const int len = ssl - ksl;
		if (stribegin(str + len, key))
			return ssl;
		str[len] = 0;
		return len;
	}
	int strirtrim(char *str, const char *key)
	{
		return strirtrim(str, key, strlen(str), strlen(key));
	}

	/* Parses str to an integer number */
	int strbintonum(const char *str)
	{
		int r = 0;
		for (int x = *str; x; x = *++str)
		{
			r <<= 1;
			if (x == '1')
				r |= 1;
			else if (x != '0')
				return r >> 1;
		}
		return r;
	}
	int strocttonum(const char *str)
	{
		int r = 0;
		for (int x = *str; x; x = *++str)
		{
			r <<= 3;
			if (x >= '0' && x <= '7')
				r += x - '0';
			else
				return r >> 3;
		}
		return r;
	}
	int strdectonum(const char *str)
	{
		int n = 0, r = 0;
		for (int x = *str; x; x = *++str)
		{
			n *= 10;
			if (x >= '0' && x <= '9')
				n += x - '0';
			else
				return r;
			r = n;
		}
		return r;
	}
	int strhextonum(const char *str)
	{
		int r = 0;
		for (int x = *str; x; x = *++str)
		{
			r <<= 4;
			if (x >= '0' && x <= '9')
				r |= x - '0';
			else if (x >= 'A' && x <= 'F')
				r |= x - 'A' + 0x0a;
			else if (x >= 'a' && x <= 'f')
				r |= x - 'a' + 0x0a;
			else
				return r >> 4;
		}
		return r;
	}

	/* Checks if c is a certain type of character */
	byte strislwr(const char c)
	{
		return c >= 'a' && c <= 'z';
	}
	byte strisupr(const char c)
	{
		return c >= 'A' && c <= 'Z';
	}
	byte strisalpha(const char c)
	{
		return strislwr(c) || strisupr(c);
	}
	byte strisnum(const char c)
	{
		return c >= '0' && c <= '9';
	}
	byte strisbin(const char c)
	{
		return c == '0' || c == '1';
	}
	byte strishex(const char c)
	{
		return (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || strisnum(c);
	}
	byte strisdeftxt(const char c)
	{
		return strisalpha(c) || strisnum(c) || c == '_';
	}
	byte strislbltxt(const char c)
	{
		return strisalpha(c) || c == '_' || c == '.' || c == '?';
	}

	/* Common string search functions xkas uses */
	byte strissquote(const char *str)
	{
		return (*str == '\'') && (str[strlen(str) - 1] == '\'');
	}
	byte strisdquote(const char *str)
	{
		return (*str == '\"') && (str[strlen(str) - 1] == '\"');
	}
	byte strisquote(const char *str)
	{
		return strissquote(str) || strisdquote(str);
	}
	int strisrep(const char *str, const char c)
	{
		if (*str == c)
		{
			int i = 0;
			for (; str[i]; ++i)
				if (str[i] != c)
					return null;
			return i;
		}
		return null;
	}
}