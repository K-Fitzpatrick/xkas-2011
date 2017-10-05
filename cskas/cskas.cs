using System.IO;
using System.Windows.Forms;

namespace xkas
{
    public static unsafe partial class cskas
    {
        public static byte* Data
        {
            get
            {
                return xGetData();
            }
        }

        public static int ROMSize
        {
            get
            {
                return xGetRomSize();
            }
        }

        public static bool Header
        {
            get
            {
                return xGetHeader() != 0;
            }
            set
            {
                xSetHeader((byte)(value ? 1 : 0));
            }
        }

        public static string ASMPath
        {
            get
            {
                return new string(xGetAsmPath());
            }
        }

        public static string ASMDirectory
        {
            get
            {
                return new string(xGetDirectory());
            }
        }

        public static string SrcROMPath
        {
            get
            {
                return new string(xGetSrcPath());
            }
        }

        public static string DestROMPath
        {
            get
            {
                return new string(xGetDestPath());
            }
        }

        public static bool PrintErrorsToConsole
        {
            get
            {
                return xGetPrintErrorsToConsole() == 1;
            }
            set
            {
                xSetPrintErrorsToConsole((byte)(value ? 1 : 0));
            }
        }

        public static int ErrorCount
        {
            get
            {
                return xGetErrorCount();
            }
        }

        public static bool PrintWarningsToConsole
        {
            get
            {
                return xGetPrintWarningsToConsole() == 1;
            }
            set
            {
                xSetPrintWarningsToConsole((byte)(value ? 1 : 0));
            }
        }

        public static int WarningCount
        {
            get
            {
                return xGetWarningCount();
            }
        }

        public static bool PrintDataToConsole
        {
            get
            {
                return xGetPrintDataToConsole() == 1;
            }
            set
            {
                xSetPrintDataToConsole((byte)(value ? 1 : 0));
            }
        }

        public static int PrintDataCount
        {
            get
            {
                return xGetPrintDataCount();
            }
        }

        public static void InitializeASMData(string path)
        {
            xInitializeAsmData(path);
        }

        public static void InitializeROMData(string path)
        {
            xInitializeRomData(path);
        }

        public static void InitializeData(string asmPath)
        {
            xInitialize(asmPath, null, null);
        }

        public static void InitializeData(string asmPath, string romPath)
        {
            xInitialize(asmPath, romPath, null);
        }

        public static void InitializeData(string asmPath, string srcPath, string destPath)
        {
            xInitialize(asmPath, srcPath, destPath);
        }

        public static void Assemble()
        {
            xPatch(0, 2);
        }

        public static void Assemble(string asmPath)
        {
            xAssemble(asmPath, null, null, 1);
        }

        public static void Assemble(string asmPath, string romPath)
        {
            xAssemble(asmPath, romPath, null, 1);
        }

        public static void Assemble(string asmPath, string srcPath, string destPath)
        {
            xAssemble(asmPath, srcPath, destPath, 1);
        }

        public static void Assemble(string asmPath, bool write)
        {
            xAssemble(asmPath, null, null, (byte)(write ? 1 : 0));
        }

        public static void Assemble(string asmPath, string romPath, bool write)
        {
            xAssemble(asmPath, romPath, null, (byte)(write ? 1 : 0));
        }

        public static void Assemble(string asmPath, string srcPath, string destPath, bool write)
        {
            xAssemble(asmPath, srcPath, destPath, (byte)(write ? 1 : 0));
        }

        public static void WriteData(string path)
        {
            xWrite(path);
        }

        public static byte* GetROMData()
        {
            return xGetData();
        }

        public static void SetupAssemblyInfo()
        {
            xPatch(0, 1);
        }

        public static void PatchNoPass()
        {
            xPatch(1, 2);
        }

        public static DefineItem[] GetAllDefines()
        {
            DefineItem[] defines = new DefineItem[xGetNumDefines()];
            for (int i = defines.Length; --i >= 0; )
                defines[i] = new DefineItem(xGetDefineName(i), xGetDefineValue(i));
            return defines;
        }

        public static string FindDefineValue(string name)
        {
            return new string(xFindDefineValue(name));
        }

        public static string ResolveDefines(string line)
        {
            return new string(xResolveDefines(line));
        }

        public static LabelItem[] GetAllLabels()
        {
            LabelItem[] labels = new LabelItem[xGetNumLabels()];
            for (int i = labels.Length; --i >= 0; )
                labels[i] = new LabelItem(xGetLabelName(i), xGetLabelValue(i));
            return labels;
        }

        public static int FindLabelOffset(string name)
        {
            return xFindLabelOffset(name);
        }

        public static int GetNumber(string str)
        {
            return xGetNumber(str);
        }

        public static int StringMath(string str)
        {
            return xStringMath(str);
        }

        public static string GetErrorString(int index)
        {
            return new string(xGetErrorString(index));
        }

        public static string[] GetErrors()
        {
            string[] errors = new string[xGetErrorCount()];
            for (int i = errors.Length; --i >= 0; )
                errors[i] = new string(xGetErrorString(i));
            return errors;
        }

        public static string GetWarningString(int index)
        {
            return new string(xGetWarningString(index));
        }

        public static string[] GetWarnings()
        {
            string[] warnings = new string[xGetWarningCount()];
            for (int i = warnings.Length; --i >= 0; )
                warnings[i] = new string(xGetWarningString(i));
            return warnings;
        }

        public static string GetPrintDataString(int index)
        {
            return new string(xGetPrintDataString(index));
        }

        public static string[] GetPrintData()
        {
            string[] data = new string[xGetPrintDataCount()];
            for (int i = data.Length; --i >= 0; )
                data[i] = new string(xGetPrintDataString(i));
            return data;
        }
    }
}