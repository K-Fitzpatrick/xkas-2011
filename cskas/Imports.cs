using System;
using System.Runtime.InteropServices;

namespace xkas
{
    public static unsafe partial class cskas
    {
        public const string DLLPath = @"Libraries\xkas.dll";

        [DllImport(cskas.DLLPath)]
        private static extern void xInitializeAsmData(string path);
        [DllImport(cskas.DLLPath)]
        private static extern void xInitializeRomData(string path);
        [DllImport(cskas.DLLPath)]
        private static extern void xInitialize(string asmpath, string srcpath, string destpath);
        [DllImport(cskas.DLLPath)]
        private static extern void xAssemble(string asmpath, string srcpath, string destpath, byte write);
        [DllImport(cskas.DLLPath)]
        private static extern void xPatch(byte init, byte end);
        [DllImport(cskas.DLLPath)]
        private static extern void xWrite(string path);
        [DllImport(cskas.DLLPath)]
        private static extern byte* xGetData();
        [DllImport(cskas.DLLPath)]
        private static extern int xGetRomSize();
        [DllImport(cskas.DLLPath)]
        private static extern byte xGetHeader();
        [DllImport(cskas.DLLPath)]
        private static extern byte xSetHeader(int val);
        [DllImport(cskas.DLLPath)]
        private static extern sbyte* xGetAsmPath();
        [DllImport(cskas.DLLPath)]
        private static extern sbyte* xGetDirectory();
        [DllImport(cskas.DLLPath)]
        private static extern sbyte* xGetSrcPath();
        [DllImport(cskas.DLLPath)]
        private static extern sbyte* xGetDestPath();
        [DllImport(cskas.DLLPath)]
        private static extern int xGetNumDefines();
        [DllImport(cskas.DLLPath)]
        private static extern sbyte* xGetDefineName(int index);
        [DllImport(cskas.DLLPath)]
        private static extern sbyte* xGetDefineValue(int index);
        [DllImport(cskas.DLLPath)]
        private static extern sbyte* xFindDefineValue(string name);
        [DllImport(cskas.DLLPath)]
        private static extern sbyte* xResolveDefines(string block);
        [DllImport(cskas.DLLPath)]
        private static extern int xGetNumLabels();
        [DllImport(cskas.DLLPath)]
        private static extern sbyte* xGetLabelName(int index);
        [DllImport(cskas.DLLPath)]
        private static extern int xGetLabelValue(int index);
        [DllImport(cskas.DLLPath)]
        private static extern int xFindLabelOffset(string name);
        [DllImport(cskas.DLLPath)]
        private static extern sbyte* xResolveLables(string block);
        [DllImport(cskas.DLLPath)]
        private static extern int xGetNumber(string str);
        [DllImport(cskas.DLLPath)]
        private static extern int xStringMath(string str);
        [DllImport(cskas.DLLPath)]
        private static extern byte xGetPrintErrorsToConsole();
        [DllImport(cskas.DLLPath)]
        private static extern void xSetPrintErrorsToConsole(byte value);
        [DllImport(cskas.DLLPath)]
        private static extern int xGetErrorCount();
        [DllImport(cskas.DLLPath)]
        private static extern sbyte* xGetErrorString(int index);
        [DllImport(cskas.DLLPath)]
        private static extern byte xGetPrintWarningsToConsole();
        [DllImport(cskas.DLLPath)]
        private static extern void xSetPrintWarningsToConsole(byte value);
        [DllImport(cskas.DLLPath)]
        private static extern int xGetWarningCount();
        [DllImport(cskas.DLLPath)]
        private static extern sbyte* xGetWarningString(int index);
        [DllImport(cskas.DLLPath)]
        private static extern byte xGetPrintDataToConsole();
        [DllImport(cskas.DLLPath)]
        private static extern void xSetPrintDataToConsole(byte value);
        [DllImport(cskas.DLLPath)]
        private static extern int xGetPrintDataCount();
        [DllImport(cskas.DLLPath)]
        private static extern sbyte* xGetPrintDataString(int index);
    }
}