#pragma once

#pragma warning(disable: 4530)
#pragma warning(disable: 4996)

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef linux
#define stricmp strcasecmp
#endif

#define null 0xFFFFFFFF
#define M_GETMAX(a, b) a > b ? a : b
#define M_GETMIN(a, b) a < b ? a : b

#define next4(n) n, n+1, n+2, n+3
#define next16(n) next4(n), next4(n+4), next4(n+8), next4(n+12)
#define next64(n) next16(n), next16(n+16), next16(n+32), next16(n+48)
#define upr next16('A'), next4('Q'), next4('U'), 'Y', 'Z'
#define lwr next16('a'), next4('q'), next4('u'), 'y', 'z'

const char upper[] = { next64(0), 0x40, upr, 0x5B, next4(0x5C), 0x60, upr, 0x7B, next4(0x7C) };
const char lower[] = { next64(0), 0x40, lwr, 0x5B, next4(0x5C), 0x60, lwr, 0x7B, next4(0x7C) };

typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;

inline int mallocresize(const int val)
{
	register int i = val - 1;
	i |= i >> 1;
	i |= i >> 2;
	i |= i >> 4;
	i |= i >> 8;
	i |= i >> 16;
	return ++i;
}

namespace xkas
{
	int strpos(const char *str, const char key);
	int strpos(const char *str, const char *key, const int ssl, const int ksl);
	int strpos(const char *str, const char *key);
	int stripos(const char *str, const char key);
	int stripos(const char *str, const char *key, const int ssl, const int ksl);
	int stripos(const char *str, const char *key);
	int strpos_eq(const char *str, const char key);
	int strpos_eq(const char *str, const char *key, const int ssl, const int ksl);
	int strpos_eq(const char *str, const char *key);
	int stripos_eq(const char *str, const char key);
	int stripos_eq(const char *str, const char *key, const int ssl, const int ksl);
	int stripos_eq(const char *str, const char *key);

	int strrpos(const char *str, const char key, const int ssl);
	int strrpos(const char *str, const char key);
	int strrpos(const char *str, const char *key, const int ssl, const int ksl);
	int strrpos(const char *str, const char *key);
	int strirpos(const char *str, const char key, const int ssl);
	int strirpos(const char *str, const char key);
	int strirpos(const char *str, const char *key, const int ssl, const int ksl);
	int strirpos(const char *str, const char *key);
	int strrpos_eq(const char *str, const char key, const int ssl);
	int strrpos_eq(const char *str, const char key);
	int strrpos_eq(const char *str, const char *key, const int ssl, const int ksl);
	int strrpos_eq(const char *str, const char *key);
	int strirpos_eq(const char *str, const char key, const int ssl);
	int strirpos_eq(const char *str, const char key);
	int strirpos_eq(const char *str, const char *key, const int ssl, const int ksl);
	int strirpos_eq(const char *str, const char *key);

	byte strbegin(const char *str, const char key);
	byte strbegin(const char *str, const char *key);
	byte stribegin(const char *str, const char key);
	byte stribegin(const char *str, const char *key);

	byte strend(const char *str, const char key, const int ssl);
	byte strend(const char *str, const char key);
	byte strend(const char *str, const char *key, const int ssl, const int ksl);
	byte strend(const char *str, const char *key);
	byte striend(const char *str, const char key, const int ssl);
	byte striend(const char *str, const char key);
	byte striend(const char *str, const char *key, const int ssl, const int ksl);
	byte striend(const char *str, const char *key);

	int strtrim(char *str, const int start, const int end);
	int strltrim(char *str, const int start);
	int strrtrim(char *str, const int end, const int ssl);
	int strrtrim(char *str, const int end);

	int strtrim(char *str, const char key);
	int strtrim(char *str, const char *key, const int ksl);
	int strtrim(char *str, const char *key);
	int stritrim(char *str, const char key);
	int stritrim(char *str, const char *key, const int ksl);
	int stritrim(char *str, const char *key);

	int strltrim(char *str, const char key, const int ssl);
	int strltrim(char *str, const char key);
	int strltrim(char *str, const char *key, const int ssl, const int ksl);
	int strltrim(char *str, const char *key);
	int striltrim(char *str, const char key, const int ssl);
	int striltrim(char *str, const char key);
	int striltrim(char *str, const char *key, const int ssl, const int ksl);
	int striltrim(char *str, const char *key);

	int strrtrim(char *str, const char key, const int ssl);
	int strrtrim(char *str, const char key);
	int strrtrim(char *str, const char *key, const int ssl, const int ksl);
	int strrtrim(char *str, const char *key);
	int strirtrim(char *str, const char key, const int ssl);
	int strirtrim(char *str, const char key);
	int strirtrim(char *str, const char *key, const int ssl, const int ksl);
	int strirtrim(char *str, const char *key);

	int strbintonum(const char *str);
	int strocttonum(const char *str);
	int strdectonum(const char *str);
	int strhextonum(const char *str);

	byte strisalpha(const char c);
	byte strislwr(const char c);
	byte strisupr(const char c);
	byte strisnum(const char c);
	byte strisbin(const char c);
	byte strishex(const char c);
	byte strisdeftxt(const char c);
	byte strislbltxt(const char c);

	byte strissquote(const char *str);
	byte strisdquote(const char *str);
	byte strisquote(const char *str);
	int strisrep(const char *str, const char c);
}