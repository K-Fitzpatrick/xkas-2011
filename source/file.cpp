#include "file.h"

namespace xkas
{
	using ::strcpy;
	using ::stricmp;
	using ::strlen;

	extern string *asmdir;
	extern int dirlen;
	extern byte romdata[MAXROMSIZE], pass;
	extern int romsize;

	extern strlist *linedata;

	extern state_data state;

	extern int filenum,
			   linenum,
			   blocknum;

	extern list<file_item> files;

	void loadasmfile(char *path)
	{
		static FILE *src;
		static char realpath[257];
		if (path[1] != ':' && dirlen)
			memcpy(realpath, xkas::asmdir->text, xkas::dirlen);
		
		strcpy(realpath + xkas::dirlen, path);
		src = fopen(realpath, "rb");

		if (!src)
		{
			if (xkas::filenum)
				errorwa(0, 0, "%s not found", realpath);
			else
				errorna(0, "%s not found", realpath);
			return;
		}

		static int i, size, len;
		static file_item *fi;

		fseek(src, 0, SEEK_END);
		size = ftell(src);
		rewind(src);

		len = strlen(realpath);
		fi = xkas::files.get(xkas::files.count);

		fi->name = (char*)malloc(len + 1);

		strcpy(fi->name, realpath);

		fi->data = (char*)malloc(size + 1);
		fread(fi->data, 1, size, src);
		fi->data[size] = 0;

		fi->pfilenum = xkas::filenum;
		fi->plinenum = xkas::linenum;
		fi->pblocknum = xkas::blocknum;

		fclose(src);
	}

	void setasmfile(char *path)
	{
		int i;
		for (i = 0; i < xkas::files.count; i++)
			if (!stricmp(path, xkas::files.data[i]->name))
				break;

		if (i >= FILE_RLIMIT)
			return errorwa(0, 0, "file limit reached");
		if (i >= xkas::files.count)
			return;
		xkas::filenum = i;

		if (xkas::files.data[i]->data)
		{
			strcpy(xkas::linedata, xkas::files.data[i]->data);
			strtrim(xkas::linedata, '\r');
			split(xkas::linedata, '\n');
			xkas::linenum = xkas::blocknum = 0;
		}
	}
	
	void putb(byte x)
	{
		incpc(1);
		if (!xkas::pass)
			return;
		xkas::romdata[xkas::state.fpc++] = x;
	}

	void putw(ushort x)
	{
		incpc(2);
		if (!xkas::pass)
			return;
		xkas::romdata[xkas::state.fpc++] = (byte)x;
		xkas::romdata[xkas::state.fpc++] = (byte)(x >> 8);
	}
	
	void putl(int x)
	{
		incpc(3);
		if (!xkas::pass)
			return;
		xkas::romdata[xkas::state.fpc++] = (byte)x;
		xkas::romdata[xkas::state.fpc++] = (byte)(x >> 8);
		xkas::romdata[xkas::state.fpc++] = (byte)(x >> 0x10);
	}
	
	void putd(int x)
	{
		incpc(4);
		if (!xkas::pass)
			return;
		xkas::romdata[xkas::state.fpc++] = (byte)x;
		xkas::romdata[xkas::state.fpc++] = (byte)(x >> 8);
		xkas::romdata[xkas::state.fpc++] = (byte)(x >> 0x10);
		xkas::romdata[xkas::state.fpc++] = (byte)(x >> 0x18);
	}
}