#include "../source/xkas.h"

using namespace xkas;

#define MAX_PATH 260

int main(int argc, char *argv[])
{
	printerrors = 1;
	printwarnings = 1;
	printdata = 1;

	int count = argc;
	byte write = 1;
	while (--count)
	{
		if (!stricmp(argv[count], "+e"))
			xkas::printerrors = 1;
		else if (!stricmp(argv[count], "-e"))
			xkas::printerrors = 0;
		else if (!stricmp(argv[count], "+w"))
			xkas::printwarnings = 1;
		else if (!stricmp(argv[count], "-w"))
			xkas::printwarnings = 0;
		else if (!stricmp(argv[count], "+p"))
			xkas::printdata = 1;
		else if (!stricmp(argv[count], "-p"))
			xkas::printdata = 0;
		else if (!stricmp(argv[count], "-r"))
			write = 0;
		else if (!stricmp(argv[count], "+r"))
			write = 1;
		else if (!stricmp(argv[count], "+t"))
			printtime = 1;
		else if (!stricmp(argv[count], "-t"))
			printtime = 0;
		else
			break;
	}

	switch (count)
	{
	case 1:
		assemble(argv[1], NULL, NULL, write);
		break;
	case 2:
		assemble(argv[1], NULL, argv[2], write);
		break;
	case 3:
		assemble(argv[1], argv[2], argv[3], write);
		break;
	default:
		printf("xkas v0.06 ~byuu\n");
		printf("this is an unofficial build by spel werdz rite\n");
		/*
		printf("usage: xkas <patch.asm> <rom.smc> <dest.smc> <+e/-e> <+w/-w> <+p/-p>\n");
		printf("e: output errors to console\n");
		printf("w: output warnings to console\n");
		printf("p: output print commands to console\n");
		*/
		
		char afn[MAX_PATH], sfn[MAX_PATH], dfn[MAX_PATH];
		printf("\nenter asm file name (no spaces):\n");
		fgets(afn, MAX_PATH - 1, stdin);
		printf("\nenter source rom file name (no spaces):\n");
		fgets(sfn, MAX_PATH - 1, stdin);
		printf("\nenter destination rom file name (no spaces):\n");
		fgets(dfn, MAX_PATH - 1, stdin);
		assemble(afn, sfn, dfn, 1);
		system("pause");
		break;
	}

	return 0;
}