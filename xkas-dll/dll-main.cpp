#include "..\source\xkas.h"

#define EXPORT extern "C" __declspec(dllexport)

using namespace xkas;

namespace xkas
{
	extern string *asmpath, *srcpath, *destpath, *asmdir;
	extern strlist *errors,
				   *warnings,
				   *print;

	extern define_list defines;
	extern label_list labels;
	extern macro_list macros;

	extern state_data state;

	extern byte romdata[MAXROMSIZE];
	extern int romsize,
			   errorcount,
			   warncount,
			   printcount;
}

EXPORT void xInitializeAsmData(char *path)
{
	initasmdata(path);
}

EXPORT void xInitializeRomData(char *path)
{
	initromdata(path);
}

EXPORT void xInitialize(char *asmpath, char *srcpath, char *destpath)
{
	initialize(asmpath, srcpath, destpath);
}

EXPORT void xAssemble(char *asmpath, char *srcpath, char *destpath, byte write)
{
	assemble(asmpath, srcpath, destpath, write);
}

EXPORT void xPatch(byte init, byte end)
{
	patch(init, end);
}

EXPORT void xWrite(char *path)
{
	write(path);
}

EXPORT byte *xGetData()
{
	return xkas::romdata;
}

EXPORT int xGetRomSize()
{
	return xkas::romsize;
}

EXPORT byte xGetHeader()
{
	return xkas::state.header;
}

EXPORT void xSetHeader(byte val)
{
	xkas::state.header = val;
}

EXPORT char *xGetAsmPath()
{
	return xkas::asmpath->text;
}

EXPORT char *xGetDirectory()
{
	return xkas::asmdir->text;
}

EXPORT char *xGetSrcPath()
{
	return xkas::srcpath->text;
}

EXPORT char *xGetDestPath()
{
	return xkas::destpath->text;
}

EXPORT int xGetNumDefines()
{
	return defines.count;
}

EXPORT char *xGetDefineName(int index)
{
	if (defines.count > index)
		return (*defines.data[index]).name->text;
	else
		return NULL;
}

EXPORT char *xGetDefineValue(int index)
{
	if (defines.count > index)
		return (*defines.data[index]).value->text;
	else
		return NULL;
}

EXPORT char *xFindDefineValue(char *name)
{
	define_item *define = defines.find(name);
	if (name)
		return define->value->text;
	return NULL;
}

EXPORT void xLockDefineValue(char *name, char *value)
{
	defines.add(name, value, 1);
}

EXPORT char *xResolveDefines(char *block)
{
	string *str = new string(block);
	resolvedefines(str);
	return str->text;
}

EXPORT int xGetNumLabels()
{
	return labels.count;
}

EXPORT char *xGetLabelName(int index)
{
	if (labels.count > index)
		return (*labels.data[index]).name;
	else
		return NULL;
}

EXPORT char *xGetLabelOffset(int index)
{
	if (labels.count > index)
		return (*labels.data[index]).name;
	else
		return NULL;
}

EXPORT int xFindLabelOffset(char *name)
{
	label_item *label = labels.find(new string(name));
	if (label)
		return label->offset;
	return null;
}

EXPORT char *xResolveLables(char *block)
{
	string *str = new string(block);
	resolvelabels(str);
	return str->text;
}

EXPORT int xGetNumber(char *str)
{
	return getnum(new string(str));
}

EXPORT int xStringMath(char *str)
{
	return strmath(str);
}

EXPORT void xSetPrintErrorsToConsole(byte value)
{
	printerrors = value;
}

EXPORT byte xGetPrintErrorsToConsole()
{
	return printerrors;
}

EXPORT int xGetErrorCount()
{
	return errorcount;
}

EXPORT char *xGetErrorString(int index)
{
	return errors->data[index]->text;
}

EXPORT void xSetPrintWarningsToConsole(byte value)
{
	printwarnings = value;
}

EXPORT byte xGetPrintWarningsToConsole()
{
	return printwarnings;
}

EXPORT int xGetWarningCount()
{
	return warncount;
}

EXPORT char *xGetWarningString(int index)
{
	return warnings->data[index]->text;
}

EXPORT void xSetPrintDataToConsole(byte value)
{
	printdata = value;
}

EXPORT byte xGetPrintDataToConsole()
{
	return printdata;
}

EXPORT int xGetPrintDataCount()
{
	return printcount;
}

EXPORT char *xGetPrintDataString(int index)
{
	return print->data[index]->text;
}