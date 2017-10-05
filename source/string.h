#pragma once

#include "base.h"

#define STRSTARTLEN 0x20

namespace xkas
{
	class string
	{
	public:
		char *text;
		int length, capacity;

		string();
		string(const int size);
		string(const char *str);
		string(const char *str, const int start, const int end);
		string(const string *str);
		~string();

		void strmalloc(const int size);
		void strrealloc(const int size);
	};

	void strset(string *str, const int pos = 0, const char c = 0);

	void strcpy(string *str, const char *key);
	void strcpy(string *str, const string *key);
	void strcpyseg(string *str, const char *key, const int length);
	void strcpyseg(string *str, const string *key, const int length);

	void strcat(string *str, const char *key);
	void strcat(string *str, const string *key);
	void strcat(string *str, const char *key, const int length);
	void strcat(string *str, const string *key, const int length);

	byte strcmp(const string *str, const char *key);
	byte strcmp(const string *str, const string *key);
	byte stricmp(const string *str, const char *key);
	byte stricmp(const string *str, const string *key);

	int strpos(const string *str, const char key);
	int strpos(const string *str, const char *key);
	int strpos(const string *str, const string *key);
	int stripos(const string *str, const char key);
	int stripos(const string *str, const char *key);
	int stripos(const string *str, const string *key);
	int strpos_eq(const string *str, const char key);
	int strpos_eq(const string *str, const char *key);
	int strpos_eq(const string *str, const string *key);
	int stripos_eq(const string *str, const char key);
	int stripos_eq(const string *str, const char *key);
	int stripos_eq(const string *str, const string *key);

	int strrpos(const string *str, const char key);
	int strrpos(const string *str, const char *key);
	int strrpos(const string *str, const string *key);
	int strirpos(const string *str, const char key);
	int strirpos(const string *str, const char *key);
	int strirpos(const string *str, const string *key);
	int strrpos_eq(const string *str, const char key);
	int strrpos_eq(const string *str, const char *key);
	int strrpos_eq(const string *str, const string *key);
	int strirpos_eq(const string *str, const char key);
	int strirpos_eq(const string *str, const char *key);
	int strirpos_eq(const string *str, const string *key);

	byte strbegin(const string *str, const char key);
	byte strbegin(const string *str, const char *key);
	byte strbegin(const string *str, const string *key);
	byte stribegin(const string *str, const char key);
	byte stribegin(const string *str, const char *key);
	byte stribegin(const string *str, const string *key);

	byte strend(const string *str, const char key);
	byte strend(const string *str, const char *key);
	byte strend(const string *str, const string *key);
	byte striend(const string *str, const char key);
	byte striend(const string *str, const char *key);
	byte striend(const string *str, const string *key);

	void strinfuse(string *str, const char *key, const int ksl);
	void strinfuse(string *str, const char *key);
	void strinfuse(string *str, const string *key);

	void strinsert(string *str, const char *key, const int index, const int ksl);
	void strinsert(string *str, const char *key, const int index);
	void strinsert(string *str, const string *key, const int index);

	void strtrim(string *str, const int start, const int end);
	void strltrim(string *str, int start);
	void strrtrim(string *str, const int end);

	void strtrim(string *str, const char key);
	void strtrim(string *str, const char *key);
	void strtrim(string *str, const string *key);
	void stritrim(string *str, const char key);
	void stritrim(string *str, const char *key);
	void stritrim(string *str, const string *key);

	void strltrim(string *str, const char key);
	void strltrim(string *str, const char *key);
	void strltrim(string *str, const string *key);
	void striltrim(string *str, const char key);
	void striltrim(string *str, const char *key);
	void striltrim(string *str, const string *key);

	void strrtrim(string *str, const char key);
	void strrtrim(string *str, const char *key);
	void strrtrim(string *str, const string *key);
	void strirtrim(string *str, const char key);
	void strirtrim(string *str, const char *key);
	void strirtrim(string *str, const string *key);

	void strreplace(string *str, const char key, const char token);
	void strreplace(string *str, const char *key, const char token, const int ksl);
	void strreplace(string *str, const char *key, const char token);
	void strreplace(string *str, const char key, const char *token, const int tsl);
	void strreplace(string *str, const char key, const char *token);
	void strreplace(string *str, const char *key, const char *token, const int ksl, const int tsl);
	void strreplace(string *str, const char *key, const char *token);
	void strreplace_eq(string *str, const char key, const char token);
	void strreplace_eq(string *str, const char *key, const char token, const int ksl);
	void strreplace_eq(string *str, const char *key, const char token);
	void strreplace_eq(string *str, const char key, const char *token, const int tsl);
	void strreplace_eq(string *str, const char key, const char *token);
	void strreplace_eq(string *str, const char *key, const char *token, const int ksl, const int tsl);
	void strreplace_eq(string *str, const char *key, const char *token);

	int strbintonum(const string *str);
	int strocttonum(const string *str);
	int strdectonum(const string *str);
	int strhextonum(const string *str);

	byte strissquote(const string *str);
	byte strisdquote(const string *str);
	byte strisquote(const string *str);
	int strisrep(const string *str, const char c);
}