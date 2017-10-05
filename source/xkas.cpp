#include "xkas.h"

namespace xkas
{
	using ::strcpy;
	using ::stricmp;

	string *asmpath = new string(), *srcpath = new string(), *destpath = new string();
	string *asmdir = new string();
	int dirlen;
	byte romdata[MAXROMSIZE];
	int romsize;
	int headersize;

	strlist *linedata	= new strlist(),
			*blockdata	= new strlist(),
			*opdata		= new strlist(),
			*errors		= new strlist(),
			*warnings	= new strlist(),
			*print		= new strlist(),
			*exportdata	= new strlist();

	string *lnamespace	= new string(),
		   *macroline	= new string(),
		   *exportpath	= new string();
	
	state_data state;
	assume_data assume;
	vector<int> pcstack;

	define_list defines;
	label_list labels;
	macro_list macros;

	list<macro_data> old_macros;
	macro_item *cmacro;
	macro_data *omacro;

	list<file_item> files;

	int filenum,
		linenum,
		blocknum,
		opnum,
		opargs,
		errorcount,
		warncount,
		printcount;

	byte pass,
		 oparg_labels,
		 oparg_labels_unresolved,
		 exportopen,
		 printerrors,
		 printwarnings,
		 printdata,
		 printtime;

	long time;
	
	void initasmdata(const char *path)
	{
		xkas::dirlen = strrpos(path, '\\') + 1;
		strcpyseg(xkas::asmdir, path, xkas::dirlen);
		strcpy(xkas::asmpath, path + xkas::dirlen);
	}
	
	void initromdata(const char *path)
	{
		if (path)
		{
			strcpy(xkas::srcpath, path);

			FILE *rom = fopen(path, "rb");
			if (!rom)
				return warningna(0, "base rom file not found");

			fseek(rom, 0, SEEK_END);
			xkas::romsize = ftell(rom);
			xkas::headersize = xkas::romsize & 0x7FFF;
			xkas::romsize -= xkas::headersize;
			fseek(rom, xkas::headersize, SEEK_SET);
			fread(xkas::romdata, 1, xkas::romsize, rom);
			fclose(rom);
		}
		else
		{
			const int len = xkas::asmpath->length + (strrpos(xkas::asmpath, ".asm") == null ? 4 : 0);
			strcpy(xkas::srcpath, xkas::asmdir);
			strcat(xkas::srcpath, xkas::asmpath, len - 4);
			strcat(xkas::srcpath, ".smc");
			
			xkas::headersize = 0;
			xkas::romsize = 0;
			memset(xkas::romdata, 0, MAXROMSIZE);
		}
	}

	void initialize(const char *asmpath, const char *srcpath, const char *destpath)
	{
		initasmdata(asmpath);
		initromdata(srcpath);
		strcpy(xkas::destpath, destpath ? destpath : xkas::srcpath->text);
	}

	void assemble(const char *asmpath, const char *srcpath, const char *destpath, const byte write)
	{
		//if (xkas::printtime)
			xkas::time = clock();
		initialize(asmpath, srcpath, destpath);
		patch(0, 2);
		if (write)
			xkas::write(xkas::destpath->text);
		if (!xkas::errorcount)
		{
			xkas::time = clock() - xkas::time;
			printf("Assembled in %f seconds", ((float)xkas::time) / CLOCKS_PER_SEC);
		}
	}
	
	void patch(byte init, byte end)
	{
		xkas::labels.count = 0;
		xkas::defines.count = 0;
		xkas::macros.count = 0;
		xkas::filenum = 0;
		xkas::errorcount = 0;
		xkas::warncount = 0;
		xkas::printcount = 0;

		xkas::files.count = 0;
		xkas::linenum =
		xkas::blocknum = 0;
		loadasmfile(xkas::asmpath->text);

		for (int i = init; i < end; ++i)
		{
			xkas::pass = i;
			xkas::state.pc = 0xC00000;
			xkas::state.mode = MODE_HIROM;
			xkas::state.header = xkas::headersize ? 1 : 0;
			xkas::state.fillbyte = 0;
			xkas::state.padbyte = 0;
			xkas::state.base = 0;
			xkas::state.rep = 1;
			xkas::state.bytecount = 0;
			xkas::state.opcount = 0;
			xkas::state.inmacro = 0;
			xkas::state.retmacro = 0;
			xkas::state.macronum = 0;
			xkas::state.retfile = 0;
			xkas::assume.f_mx = 0;
			xkas::assume.f_db = 0;
			xkas::assume.f_d = 0;
			xkas::state.pbcount.count = 0;
			xkas::state.mbcount.count = 0;
			xkas::filenum = 0;

			xkas::state.infreespace =
			xkas::state.endfreespace = 0;

			static int l;
			for (l = 0; l < 0x100; l++)
				xkas::state.table[l] = l;

			for (l = 0; l < xkas::state.pbcount.count; ++l)
				xkas::state.pbcount.data[l] = 0;
			for (l = 0; l < xkas::state.mbcount.count; ++l)
				xkas::state.mbcount.data[l] = 0;
			
			strcpy(xkas::labels.lprefix, "__null_");
			
            setasmfile(xkas::files.data[0]->name);
line_loop:
			for (; xkas::linenum < xkas::linedata->count; ++xkas::linenum)
			{
				if (xkas::state.inmacro)
					xkas::state.retmacro = continuemacro();

				static string *line;
				line = xkas::linedata->data[xkas::linenum];

				static int x;
				x = strpos_eq(line, ';');
				if (x != null)
					strset(line, x);

				strreplace_eq(line, '\t', ' ');
				strreplace_eq(line, '{', ' ');
				strreplace_eq(line, '}', ' ');

				do
				{
					x = line->length;
					strreplace_eq(line, ", ", ',');
				}while(line->length != x);

				
				if (declaremacros())
					continue;
				if (xkas::state.inmacro)
				{
					strcpy(xkas::macroline, line);
					resolvemacroargs(line);
				}

				static byte blockadd = 0;
block_loop:
				if (blockadd)
				{
					resolvedefines(line);
					split_eq(xkas::blockdata, " : ", line);
					blockadd = 0;
				}
				else
				{
					split_eq(xkas::blockdata, " : ", line);
					if (xkas::state.retmacro || xkas::state.retfile)
						xkas::state.retmacro = xkas::state.retfile = 0;
					else
						xkas::blocknum = 0;
				}
				
				for (; xkas::blocknum < xkas::blockdata->count; ++xkas::blocknum)
				{
					resolvedefines(xkas::blockdata->data[xkas::blocknum]);
					if (strpos_eq(xkas::blockdata->data[xkas::blocknum], " : ") != null)
					{
						blockadd = 1;
						goto block_loop;
					}

					static int r;
					r = xkas::state.rep;
					xkas::state.rep = 1;
					for (l = 0; l < r; ++l)
					{
						xkas::opdata->count = 0;
						split_eq(xkas::opdata, ' ', xkas::blockdata->data[xkas::blocknum]);
						strlisttrim(xkas::opdata);
						xkas::opargs = xkas::opdata->count;

						static int im, cf;
						im = xkas::state.inmacro;
						cf = xkas::filenum;
						assemble_op();
						if (im != xkas::state.inmacro)
							goto line_loop;
						if (cf != xkas::filenum)
							goto line_loop;
					}
				}
				if (xkas::state.inmacro)
					strcpy(line, xkas::macroline);
				if (xkas::state.retmacro)
					--xkas::linenum;
			}
			if (xkas::filenum)
			{
				static file_item *fi;
				fi = xkas::files.data[xkas::filenum];
				setasmfile(xkas::files.data[fi->pfilenum]->name);
				xkas::linenum = fi->plinenum;
				xkas::blocknum = fi->pblocknum + 1;
				xkas::state.retfile = 1;
				goto line_loop;
			}
		}
	}

	void write(char *path)
	{
		if (!xkas::errorcount)
		{
			FILE *rom = fopen(path, "wb");
            if (rom)
            {
			    fseek(rom, state.header ? HEADERSIZE : 0, SEEK_SET);
			    fwrite(xkas::romdata, 1, xkas::romsize, rom);
			    fclose(rom);
            }
            else
                errorna(1, "Could not write to %s.", path);
		}
	}
	
	void assemble_op()
	{
		static int i, v, l, n, z, fsize, fstart, fend;
		static char t[0x4000], *data;
		static string *op1, *op2, *op3, *tempstr1 = new string(), *tempstr2 = new string();
		static strlist *templist1 = new strlist(), *templist2 = new strlist();
		static FILE *wf;

		if (!xkas::opargs)
			return;

		do
		{
			op1 = xkas::opdata->data[0];
		    v = strisrep(op1, '+');
		    if (v ^ null)
		    {
			    sprintf(t, ".__br_pos%d_%d", v, state.pbcount.get(v - 1));
			    strcpy(op1, t);
			    ++xkas::state.pbcount.data[v - 1];
		    }
		    else
		    {
			    v = strisrep(op1, '-');
			    if (v ^ null)
			    {
				    sprintf(t, ".__br_neg%d_%d", v, state.mbcount.get(v - 1));
				    strcpy(op1, t);
				    ++xkas::state.mbcount.data[v - 1];
			    }
		    }
			if (!((strbegin(op1, '.') && !strend(op1, ':')) || (strbegin(op1, '%') && !strend(op1, "()")) || (!strbegin(op1, '.') && strend(op1, ':')) || (!strbegin(op1, '?') && !strend(op1, ':'))))
				break;

			labels.add(op1, basetopc(xkas::state.pc));
			tempstr1 = xkas::opdata->data[0];
			for (int i = 1; i < opargs; i++)
				xkas::opdata->data[i - 1] = xkas::opdata->data[i];
			xkas::opdata->data[--xkas::opargs] = tempstr1;
		} while(xkas::opargs);
		if (!xkas::opargs)
			return;

		op2 = xkas::opdata->data[1];
		v = strisrep(op2, '+');
		if (v ^ null)
		{
			sprintf(t, ".__br_pos%d_%d", v, state.pbcount.get(v - 1));
			strcpy(op2, t);
		}
		else
		{
			v = strisrep(op2, '-');
			if (v ^ null)
			{
				sprintf(t, ".__br_neg%d_%d", v, state.mbcount.get(v - 1) - 1);
				strcpy(op2, t);
			}
		}

        if (xkas::opargs >= 2 && xkas::opargs <= 4)
		{
			if (!stricmp(xkas::opdata->data[0], "incbin"))
			{
				if (xkas::opdata->data[1]->text[1] ^ ':' && xkas::dirlen)
				{
					static char realpath[257];
					memcpy(realpath, xkas::asmdir->text, xkas::dirlen);
					strcpy(realpath + xkas::dirlen, xkas::opdata->data[1]->text);
					wf = fopen(realpath, "rb");
				}
				else
					wf = fopen(xkas::opdata->data[1]->text, "rb");
				if (!wf)
					return errorwa(0, 0, "file not found [%s]", xkas::opdata->data[1]->text);

				if (xkas::opargs >= 3)
				{
					op1 = xkas::opdata->data[2];
					if (!stricmp(op1, "start(") && !strend(op1, ')'))
					{
						strltrim(op1, (int)strlen("start("));
						strrtrim(op1, 1);
						fstart = getnum(op1);
					}
					else
					{
						errorwa(0, 0, "invalid command [%s]", op1->text);
						fstart = 0;
					}
				}
				else
					fstart = 0;

				if (xkas::opargs == 4)
				{
					op1 = xkas::opdata->data[3];
					if (!stricmp(op1, "size(") && !strend(op1, ')'))
					{
						strltrim(op1, (int)strlen("size("));
						strrtrim(op1, 1);
						fsize = getnum(op1);
						fend = fstart + fsize;
					}
					else if (!stricmp(op1, "end(") && !strend(op1, ')'))
					{
						strltrim(op1, (int)strlen("end("));
						strrtrim(op1, 1);
						fend = getnum(op1);
						fsize = fend - fstart;
					}
					else
					{
						fseek(wf, 0, SEEK_END);
						fend = ftell(wf);
						fsize = fend - fstart;
						errorwa(0, 0, "invalid command [%s]", op1->text);
					}
				}
				else
				{
					fseek(wf, 0, SEEK_END);
					fend = ftell(wf);
					fsize = fend - fstart;
				}

				if (fsize < 0)
				{
					fclose(wf);
					return errorwa(0, 0, "file read length less than zero");
				}
				incpc(fsize);
				
				fseek(wf, 0, SEEK_END);
				if (fend <= ftell(wf))
				{
					if (pass)
					{
						fseek(wf, fstart, SEEK_SET);
						fread(xkas::romdata + xkas::state.fpc, 1, fsize, wf);
					}
				}
				else
					errorwa(0, 0, "attempt to read past file size [%x]", ftell(wf));

				setpcfp();
				fclose(wf);
				return;
			}
		}
		
		if (xkas::opargs == 1)
		{
			op1 = xkas::opdata->data[0];
			if (!strbegin(op1, '%'))
			{
				if (xkas::state.inmacro)
					strcpy(xkas::linedata->data[xkas::linenum], xkas::macroline);

				strltrim(op1, 1);
				v = strpos_eq(op1, '(');

				if (v == null || op1->text[op1->length - 1] != ')')
					return errorwa(0, 0, "macro declared improperly");

				static string *tempstr = new string();
				strcpy(tempstr, op1->text + v);
				strset(op1, v);
				strltrim(tempstr, 1);
				strrtrim(tempstr, 1);

				if (tempstr->length)
					z = split_eqc(tempstr, ',');
				else
					z = 0;

				static macro_item *macro;
				macro = xkas::macros.find(op1->text);
				if (!macro)
					return errorwa(0, 0, "macro not defined");

				return beginmacro(macro, tempstr->text, z);
			}
			else if ((strbegin(op1, '.') && !strend(op1, ':')) || !strend(op1, "()") || (!strbegin(op1, '.') && strend(op1, ':')) || (!strbegin(op1, '?') && !strend(op1, ':')))
			{
				labels.add(op1, basetopc(xkas::state.pc));
			}
			else if (!stricmp(op1, "header"))
			{
				xkas::state.header = 1;
				if (!xkas::headersize)
					xkas::headersize = 0x200;
			}
			else if (!stricmp(op1, "noheader"))
			{
				xkas::state.header = 0;
			}
			else if (!stricmp(op1, "lorom"))
			{
				xkas::state.mode = MODE_LOROM;
				xkas::state.pc = 0x008000;
				setpcfp();
			}
			else if (!stricmp(op1, "hirom"))
			{
				xkas::state.mode = MODE_HIROM;
				xkas::state.pc = 0xC00000;
				setpcfp();
			}
			else if (!stricmp(op1, "exlorom"))
			{
				xkas::state.mode = MODE_EXLOROM;
				xkas::state.pc = 0x008000;
				setpcfp();
			}
			else if (!stricmp(op1, "exhirom"))
			{
				xkas::state.mode = MODE_EXHIROM;
				xkas::state.pc = 0x400000;
				setpcfp();
			}
			else if (!stricmp(op1, "export.close"))
			{
				if (!pass)
					return;

				if (!exportopen)
					return errorwa(1, 1, "No export file is opened");

				if (xkas::exportpath->text[1] && xkas::dirlen)
				{
					static char path[257];
					memcpy(path, xkas::asmdir->text, xkas::dirlen);
					strcpy(path + xkas::dirlen, xkas::exportpath->text);
					wf = fopen(path, "wb");
				}
				else
					wf = fopen(xkas::exportpath->text, "wb");

				if (!wf)
					return errorwa(1, 1, "could not access %s", xkas::exportpath->text);

				for (i = 0; i < xkas::exportdata->count; ++i)
					fprintf(wf, xkas::exportdata->data[i]->text);

				fclose(wf);
			}
			else if (!stricmp(op1, "cleartable"))
			{
				for (i = 0; i < 0x100; i++)
					xkas::state.table[i] = i;
			}
			else if (!stricmp(op1, "pushpc"))
			{
				xkas::pcstack.push(xkas::state.pc);
			}
			else if (!stricmp(op1, "pullpc"))
			{
				if (!xkas::pcstack.count)
					return errorwa(1, 0, "pc stack is empty");

				xkas::state.pc = xkas::pcstack.pop();
				setpcfp();
			}
			else
				op1_immediate();
		}
		else if (xkas::opargs == 2)
		{
			op1 = xkas::opdata->data[0];
			op2 = xkas::opdata->data[1];
			
			if (!stricmp(op1, "db"))
				z = 1;
			else if (!stricmp(op1, "dw"))
				z = 2;
			else if (!stricmp(op1, "dl"))
				z = 3;
			else if (!stricmp(op1, "dd"))
				z = 4;
			else
				z = 0;

			if (z)
			{
				split_eq(templist1, ',', op2);
				for (i = 0; i < templist1->count; ++i)
				{
					tempstr1 = templist1->data[i];
					data = tempstr1->text;
					if (strisquote(tempstr1))
					{
						n = tempstr1->length - 1;
						for (l = 1; l < n; ++l)
						{
							v = xkas::state.table[data[l]];
							if (z == opsize_byte)
								putb(v);
							else if (z == opsize_ushort)
								putw(v);
							else if (z == opsize_long)
								putl(v);
							else if (z == opsize_dushort)
								putd(v);
						}
					}
					else
					{
						v = getnum(tempstr1);
						if (z == opsize_byte)
							putb(v);
						else if (z == opsize_ushort)
							putw(v);
						else if (z == opsize_long)
							putl(v);
						else if (z == opsize_dushort)
							putd(v);
					}
				}
			}
			else if (!stricmp(op1, "org"))
			{
				xkas::state.pc = getnum(op2);
				setpcfp();
			}
			else if (!stricmp(op1, "base"))
			{
				if (!stricmp(op2, "off"))
					xkas::state.base = 0;
				else
					xkas::state.base = getnum(op2);
				xkas::state.basepc = xkas::state.pc;
			}
			else if (!stricmp(op1, "assume"))
			{
				split_eq(templist1, ',', op2);
				for (i = 0; i < templist1->count; --i)
				{
					split_eq(templist2, ':', templist1->data[i]);
					if (templist2->count != 2)
						return errorwa(0, 0, "invalid assume argument");

					tempstr1 = templist2->data[0];
					tempstr2 = templist2->data[1];
					if (!stricmp(tempstr1, "mx"))
					{
						if (!stricmp(tempstr2, "off"))
							xkas::assume.f_mx = 0;
						else
						{
							xkas::assume.f_mx = 1;
							if (!strcmp(tempstr2, "%00"))
								xkas::assume.mx = 0;
							else if (!strcmp(tempstr2, "%01"))
								assume.mx = 1;
							else if (!strcmp(tempstr2, "%10")) 
								assume.mx = 2;
							else if (!strcmp(tempstr2, "%11"))
								assume.mx = 3;
							else if (!strcmp(tempstr2, "%0-"))
								assume.mx &= 1;
							else if (!strcmp(tempstr2, "%1-"))
								assume.mx |= 2;
							else if (!strcmp(tempstr2, "%-0"))
								assume.mx &= 2;
							else if (!strcmp(tempstr2, "%-1"))
								assume.mx |= 1;
							else if (stricmp(tempstr2, "on"))
								return errorwa(0, 0, "invalid assume argument");
						}
					}
					else if (!stricmp(tempstr1, "db"))
					{
						if (!stricmp(tempstr2, "off"))
							xkas::assume.f_db = 0;
						else
						{
							xkas::assume.f_db = 1;
							xkas::assume.db = getnum(tempstr2);
						}
					}
					else if (!stricmp(tempstr1, "d"))
					{
						//To do: add support for "d" command.
					}
					else
						return errorwa(0, 0, "invalid assume argument");
				}
			}
			else if (!stricmp(op1, "namespace"))
			{
				if (!stricmp(op2, "off"))
					strset(xkas::lnamespace);
				else
				{
					if (strisquote(op2))
					{
						strltrim(op2, 1);
						strrtrim(op2, 1);
					}
					else
						errorwa(0, 0, "invalid assume argument");
					strcpy(xkas::lnamespace, op2);
					strcat(xkas::lnamespace, "_");
				}
			}
			else if (!stricmp(op1, "export.open"))
			{
				if (!pass)
					return;

				static byte open;

				if (!strbegin(op2, ">>"))
				{
					strltrim(op2, 2);
					open = 1;
				}
				else if (!strbegin(op2, '>'))
				{
					strltrim(op2, 1);
					open = 0;
				}

				strcpy(xkas::exportpath, op2);
				if (open)
				{
					if (xkas::exportpath->text[1] && xkas::dirlen)
					{
						static char path[257];
						memcpy(path, xkas::asmdir->text, xkas::dirlen);
						strcpy(path + xkas::dirlen, xkas::exportpath->text);
						wf = fopen(path, t);
					}
					else
						wf = fopen(xkas::exportpath->text, t);

					if (!wf)
						return errorwa(0, 0, "failed to open export file [%s]", xkas::exportpath);
					
					fseek(wf, 0, SEEK_END);
					v = ftell(wf);
					data = (char*)malloc(v + 1);
					fread(data, 1, v, wf);
					data[v] = 0;
					strtrim(data, '\r');
					split(templist1, '\n', data);
					strlisttrim(templist1);
				}
				xkas::exportopen = 1;
			}
			else if (!stricmp(op1, "export.label"))
			{
				if (pass)
				{
					if (!xkas::exportopen)
						return errorwa(0, 1, "you must use export.open to select a file first");

					strcpy(tempstr1, op2->text);
					sprintf(t, "%s = $%.6x", tempstr1->text, getnum(op2));
					strcpy(xkas::exportdata, t, xkas::exportdata->count);
				}
			}
			else if (!stricmp(op1, "export.define"))
			{
				if (pass)
				{
					if (!xkas::exportopen)
						return errorwa(0, 1, "you must use export.open to select a file first");

					strinfuse(op2, "!");
					static define_item *define;
					define = defines.find(op2);
					if (!define)
					{
						errorwa(0, 1, "define not found");
						sprintf(t, "%s = {error}", op2->text);
					}
					else
						sprintf(t, "%s = %s", op2->text, define->value->text);

					strcpy(xkas::exportdata, t, xkas::exportdata->count);
				}
			}
			else if (!stricmp(op1, "fillbyte"))
			{
				xkas::state.fillbyte = getnum(op2);
			}
			else if (!stricmp(op1, "padbyte"))
			{
				xkas::state.padbyte = getnum(op2);
			}
			else if (!stricmp(op1, "fill"))
			{
				v = getnum(op2);
				incpc(v);
				if (pass)
				{
					memset(xkas::romdata + xkas::state.fpc, xkas::state.fillbyte, v);
					xkas::state.fpc += v;
				}
			}
			else if (!stricmp(op1, "pad"))
			{
				static int vpc, zpc;

				v = getnum(op2);
				z = xkas::state.pc;
				vpc = sfctopc(v);
				zpc = sfctopc(z);
				if (vpc >= zpc)
				{
					v = vpc - zpc;
					incpc(v);
					if (pass)
					{
						memset(xkas::romdata + xkas::state.fpc, xkas::state.fillbyte, v);
						xkas::state.fpc += v;
					}
				}
			}
			else if (!stricmp(op1, "reset"))
			{
				if (pass)
				{
					split_eq(templist1, ',', op2);
					for (i = 0; i < templist1->count; ++i)
					{
						if (!stricmp(templist1->data[i], "bytes"))
							xkas::state.bytecount = 0;
						else if (!stricmp(templist1->data[i], "opcodes"))
							xkas::state.opcount = 0;
					}
				}
			}
			else if (!stricmp(op1, "print"))
			{
				if (!pass)
					return;

				z = 1;
				split_eq(templist1, ',', op2);
				tempstr1->length = 0;
				v = xkas::printcount++;
				for (i = 0; i < templist1->count; i++)
				{
					tempstr2 = templist1->data[i];
					if (!stricmp(tempstr2, "pc"))
					{
						sprintf(t, "%.6x", xkas::state.pc);
						strcat(xkas::print, t, v);
					}
					else if (!stricmp(tempstr2, "bytes"))
					{
						sprintf(t, "%d", xkas::state.bytecount);
						strcat(xkas::print, t, v);
					}
					else if (!stricmp(tempstr2, "opcodes"))
					{
						sprintf(t, "%d", xkas::state.opcount);
						strcat(xkas::print, t, v);
					}
					else if (strisquote(tempstr2))
					{
						strltrim(tempstr2, 1);
						strrtrim(tempstr2, 1);

						strreplace(tempstr2, "\\n", '\n');
						strreplace(tempstr2, "\\r", '\r');
						strreplace(tempstr2, "\\\\", '\\');
						strcpy(t, tempstr2->text);
						strcat(xkas::print, t, v);
					}
					else
					{
						errorwa(1, 1, "invalid print command [%s]", tempstr2->text);
						z = 0;
					}
				}

				if (!z)
					printcount--;
				else if (xkas::printdata)
					printf("%s\n", xkas::print->data[v]->text);
			}
			else if (!stricmp(op1, "table"))
			{
				split_eq(templist1, ',', op2);
				wf = fopen(templist1->data[0]->text, "rb");
				if (!wf)
					return errorwa(0, 0, "file not found");

				memset(xkas::state.table, 0, 0x100);
				z = 0;
				if (templist1->count == 2)
				{
					tempstr1 = templist1->data[1];
					if (!stricmp(tempstr1, "ltr") || !stricmp(tempstr1, "l"))
						z = 0;
					else if (!stricmp(tempstr1, "rtl") || !stricmp(tempstr1, "r"))
						z = 1;
				}

				fseek(wf, 0, SEEK_END);
				fsize = ftell(wf);
				rewind(wf);
				data = (char*)malloc(fsize + 1);
				fread(data, 1, fsize, wf);
				fclose(wf);
				
				data[fsize] = 0;
				strtrim(data, '\r');
				strcpy(tempstr1, data);
				free(data);
				split(templist1, '\n', tempstr1);
				strlisttrim(templist1);

				for (i = 0; i < templist1->count; ++i)
				{
					split(templist2, '=', templist1->data[i]);
					if (templist2->count == 2)
					{
						v = strhextonum(templist2->data[1 - z]);
						xkas::state.table[templist2->data[z]->text[0]] = v;
					}
				}
			}
			else if (!stricmp(op1, "incsrc") || !stricmp(op1, "import")) 
			{
				if (!xkas::pass)
					loadasmfile(op2->text);
                if (op2->text[1] != ':' && dirlen)
			        memcpy(t, xkas::asmdir->text, xkas::dirlen);

                strcpy(t + xkas::dirlen, op2->text);
                setasmfile(t);
			}
			else if (!stricmp(op1, "loadpc"))
			{
				split_eq(templist1, ',', op2);
				wf = fopen(templist1->data[0]->text, "rb");
				if (!wf)
					return errorwa(0, 0, "file not found");

				if (templist1->count == 1)
					v = 0;
				else
					v = getnum(templist1->data[1]);

				fseek(wf, 0, SEEK_END);
				z = ftell(wf);

				if (v << 2 >= z)
					return errorwa(0, 0, "requested pc value past end of file");

				fseek(wf, v << 2, SEEK_SET);
				xkas::state.pc = fgetc(wf);
				xkas::state.pc |= fgetc(wf) << 8;
				xkas::state.pc |= fgetc(wf) << 0x10;
				xkas::state.pc |= fgetc(wf) << 0x18;
				setpcfp();
				fclose(wf);
			}
			else if (!stricmp(op1, "savepc"))
			{
				if (pass)
				{
					split_eq(templist1, ',', op2);
					wf = fopen(templist1->data[0]->text, "rb+");
					if (!wf)
						wf = fopen(templist1->data[0]->text, "wb");

						if (templist1->count == 1)
					v = 0;
				else
					v = getnum(templist1->data[1]);

				fseek(wf, v << 2, SEEK_SET);
				fputc(xkas::state.pc, wf);
				fputc(xkas::state.pc >> 8, wf);
				fputc(xkas::state.pc >> 0x10, wf);
				fputc(xkas::state.pc >> 0x18, wf);
				fclose(wf);
				}
			}
			else if (!stricmp(op1, "warnpc"))
			{
				if (pass)
				{
					v = getnum(op2);
					if (xkas::state.pc >= v)
						errorwa(0, 1, "warnpc() value >= pc [pc=%0.6]", xkas::state.pc);
				}
			}
			else if (!stricmp(op1, "skip"))
			{
				incpc(getnum(op2));
				setpcfp();
			}
			else if (!stricmp(op1, "rep") && strbegin(op2, '#'))
			{
				xkas::state.rep = getnum(op2);
				//if (xkas::state.rep < 0)
				//	warning(1, "consider using rep 0");
			}
			else if (!stricmp(op2, "a"))
				op1a();
			else if (!strbegin(op2, '#'))
				op2constant();
			else if (!strbegin(op2, '(') && !striend(op2, ",s),y"))
				op2stack_relative_indexed_indirect_y();
			else if (!strbegin(op2, '[') && !striend(op2, "],y"))
				op2indirect_long_indexed_y();
			else if (!strbegin(op2, '[') && !strend(op2, ']'))
				op2indirect_long();
			else if (!strbegin(op2, '(') && !striend(op2, ",x)"))
				op2indirect_indexed_x();
			else if (!strbegin(op2, '(') && !striend(op2, "),y"))
				op2indirect_indexed_y();
            else if (!strmathparenth(op2->text))
				op2indirect();
			else if (!striend(op2, ",s"))
				op2stack_relative();
			else if (!striend(op2, ",x"))
				op2indexed_x();
			else if (!striend(op2, ",y"))
				op2indexed_y();
			else
				op2absolute();
		}
		else if (xkas::opargs == 3)
		{
			op1 = xkas::opdata->data[0];
			op2 = xkas::opdata->data[1];
			op3 = xkas::opdata->data[2];

			if (!stricmp(op2, "equ") || !stricmp(op2, "="))
			{
				if (strisquote(op3))
				{
					strltrim(op3, 1);
					strrtrim(op3, 1);
				}

				if (!strbegin(op1, '!'))
				//	xkas::labels.add(op1, getnum(op3));
				//else
					xkas::defines.add(op1, op3);
				else
					errorwa(0, 0, "invalid define command");
			}
		}
		else
			invalid_op();
	}

#define M_AS1(s, x)					\
	if (!stricmp(op1, s))			\
	{								\
		state.opcount++;			\
		putb(x);					\
		return;						\
	}

#define M_AS1N(s, x)				\
	if (!stricmp(opdata, s))		\
	{								\
		as1n_fn(x, v);				\
		return;						\
	}

#define M_AS2B(s, x)				\
	if (!stricmp(op1, s))			\
	{								\
		state.opcount++;			\
		putb(x);					\
		putb(v);					\
		return;						\
	}

#define M_AS2BR(s, x)				\
	if (!stricmp(opdata, s))		\
	{								\
		state.opcount++;			\
		putb(x);					\
		putb(v);					\
		as2b_rs(v);					\
		return;						\
	}

#define M_AS2BS(s, x)				\
	if (!stricmp(opdata, s))		\
	{								\
		state.opcount++;			\
		putb(x);					\
		putb(v);					\
		as2b_ss(v);					\
		return;						\
	}

#define M_AS2W(s, x)				\
	if (!stricmp(opdata, s))		\
	{								\
		state.opcount++;			\
		putb(x);					\
		putw(v);					\
		return;						\
	}

#define M_AS2L(s, x)				\
	if (!stricmp(opdata, s))		\
	{								\
		as2l_fn(x, v, size);		\
		return;						\
	}

#define M_AS2LF(s, x)				\
	if (!stricmp(opdata, s))		\
	{								\
		state.opcount++;			\
		putb(x);					\
		putl(v);					\
		return;						\
	}

#define M_AS2C(s, x, t)				\
	if (!stricmp(opdata, s))		\
	{								\
		as2c_fn(x, t, v, size);		\
		return;						\
	}

#define M_AS2RB(s, x)					\
	if (!stricmp(opdata, s))			\
	{									\
		state.opcount++;				\
		putb(x);						\
		if (!oparg_labels)				\
			putb(v);					\
		else							\
			putb(relative(v, 1));		\
		return;							\
	}

#define M_AS2RW(s, x)					\
	if (!stricmp(opdata, s))			\
	{									\
		state.opcount++;				\
		putb(x);						\
		if (!oparg_labels)				\
			putw(v);					\
		else							\
			putw(relative(v, 2));		\
		return;							\
	}

	void op1_immediate()
	{
		static int v = 0;
		static char *op1;
		op1 = xkas::opdata->data[0]->text;

		M_AS1("php", 0x08) 
		M_AS1("asl", 0x0a)
		M_AS1("phd", 0x0b)
		M_AS1("clc", 0x18)
		M_AS1("inc", 0x1a)
		M_AS1("tcs", 0x1b)
		M_AS1("plp", 0x28)
		M_AS1("rol", 0x2a)
		M_AS1("pld", 0x2b)
		M_AS1("sec", 0x38)
		M_AS1("dec", 0x3a)
		M_AS1("tsc", 0x3b)
		M_AS1("rti", 0x40)
		M_AS1("pha", 0x48)
		M_AS1("lsr", 0x4a)
		M_AS1("phk", 0x4b)
		M_AS1("cli", 0x58)
		M_AS1("phy", 0x5a)
		M_AS1("tcd", 0x5b)
		M_AS1("rts", 0x60)
		M_AS1("pla", 0x68)
		M_AS1("ror", 0x6a)
		M_AS1("rtl", 0x6b)
		M_AS1("sei", 0x78)
		M_AS1("ply", 0x7a)
		M_AS1("tdc", 0x7b)
		M_AS1("dey", 0x88)
		M_AS1("txa", 0x8a)
		M_AS1("phb", 0x8b)
		M_AS1("tya", 0x98)
		M_AS1("txs", 0x9a)
		M_AS1("txy", 0x9b)
		M_AS1("tay", 0xa8)
		M_AS1("tax", 0xaa)
		M_AS1("plb", 0xab)
		M_AS1("clv", 0xb8)
		M_AS1("tsx", 0xba)
		M_AS1("tyx", 0xbb)
		M_AS1("iny", 0xc8)
		M_AS1("dex", 0xca)
		M_AS1("wai", 0xcb)
		M_AS1("cld", 0xd8)
		M_AS1("phx", 0xda)
		M_AS1("stp", 0xdb)
		M_AS1("inx", 0xe8)
		M_AS1("nop", 0xea)
		M_AS1("xba", 0xeb)
		M_AS1("sed", 0xf8)
		M_AS1("plx", 0xfa)
		M_AS1("xce", 0xfb)
		M_AS1("dea", 0x3a)
		M_AS1("ina", 0x1a)
		M_AS1("tad", 0x5b)
		M_AS1("tda", 0x7b)
		M_AS1("tas", 0x1b)
		M_AS1("tsa", 0x3b)
		M_AS1("swa", 0xeb)
		M_AS2B("brk", 0x00)
		M_AS2B("cop", 0x02)
		invalid_op();
	}

	void op1a()
	{
		static char *op1;
		op1 = xkas::opdata->data[0]->text;

		M_AS1("asl", 0x0a)
		M_AS1("lsr", 0x4a)
		M_AS1("rol", 0x2a)
		M_AS1("ror", 0x6a)
		M_AS1("inc", 0x1a)
		M_AS1("dec", 0x3a)
		invalid_op();
	}

	void op2constant()
	{
		static int v = 0;
		static string *op1, *op2;
		static byte size;
		op1 = xkas::opdata->data[0];
		op2 = xkas::opdata->data[1];
		strltrim(op2, 1);
		size = setsize(v);

		if (size == opsize_byte || size == opsize_ushort || size == opsize_none)
		{
			M_AS2C("ora", 0x09, 2)
			M_AS2C("and", 0x29, 2) 
			M_AS2C("eor", 0x49, 2)
			M_AS2C("adc", 0x69, 2)
			M_AS2C("bit", 0x89, 2)
			M_AS2C("lda", 0xa9, 2)
			M_AS2C("cmp", 0xc9, 2)
			M_AS2C("sbc", 0xe9, 2)
			M_AS2C("cpx", 0xe0, 1)
			M_AS2C("cpy", 0xc0, 1)
			M_AS2C("ldx", 0xa2, 1)
			M_AS2C("ldy", 0xa0, 1)
			M_AS1N("asl", 0x0a)
			M_AS1N("lsr", 0x4a)
			M_AS1N("rol", 0x2a)
			M_AS1N("ror", 0x6a)
			M_AS1N("inc", 0x1a)
			M_AS1N("dec", 0x3a)
			M_AS1N("inx", 0xe8)
			M_AS1N("dex", 0xca)
			M_AS1N("iny", 0xc8)
			M_AS1N("dey", 0x88)
			M_AS1N("nop", 0xea)
		}

		if (size == opsize_byte || size == opsize_none)
		{
			M_AS2BR("rep", 0xc2)
			M_AS2BS("sep", 0xe2)
			M_AS2B("brk", 0x00)
			M_AS2B("cop", 0x02)
		}
		invalid_op();
	}

	void op2stack_relative_indexed_indirect_y()
	{
		static int v = 0;
		static string *op1, *op2;
		static byte size;
		op1 = xkas::opdata->data[0];
		op2 = xkas::opdata->data[1];
		strltrim(op2, 1);
		strrtrim(op2, 5);
		size = setsize(v);

		if (size == opsize_byte || size == opsize_none)
		{
			M_AS2B("ora", 0x13)
			M_AS2B("and", 0x33) 
			M_AS2B("eor", 0x53)
			M_AS2B("adc", 0x73)
			M_AS2B("sta", 0x93)
			M_AS2B("lda", 0xb3)
			M_AS2B("cmp", 0xd3) 
			M_AS2B("sbc", 0xf3)
		}
		invalid_op();
	}

	void op2indirect_long_indexed_y()
	{
		static int v = 0;
		static string *op1, *op2;
		static byte size;
		op1 = xkas::opdata->data[0];
		op2 = xkas::opdata->data[1];
		strltrim(op2, 1);
		strrtrim(op2, 3);
		size = setsize(v);

		if (size == opsize_byte || size == opsize_none) 
		{
			M_AS2B("ora", 0x17)
			M_AS2B("and", 0x37)
			M_AS2B("eor", 0x57)
			M_AS2B("adc", 0x77)
			M_AS2B("sta", 0x97)
			M_AS2B("lda", 0xb7)
			M_AS2B("cmp", 0xd7)
			M_AS2B("sbc", 0xf7)
		}
		invalid_op();
	}

	void op2indirect_long()
	{
		static int v = 0;
		static string *op1, *op2;
		static byte size;
		op1 = xkas::opdata->data[0];
		op2 = xkas::opdata->data[1];
		strltrim(op2, 1);
		strrtrim(op2, 1);
		size = setsize(v);

		if (size == opsize_byte || size == opsize_none)
		{
			M_AS2B("ora", 0x07)
			M_AS2B("and", 0x27)
			M_AS2B("eor", 0x47)
			M_AS2B("adc", 0x67)
			M_AS2B("sta", 0x87)
			M_AS2B("lda", 0xa7)
			M_AS2B("cmp", 0xc7)
			M_AS2B("sbc", 0xe7)
		}

		if (size == opsize_ushort || size == opsize_none)
		{
			M_AS2W("jmp", 0xdc)
			M_AS2W("jml", 0xdc)
		}
		invalid_op();
	}

	void op2indirect_indexed_x()
	{
		static int v = 0;
		static string *op1, *op2;
		static byte size;
		op1 = xkas::opdata->data[0];
		op2 = xkas::opdata->data[1];
		strltrim(op2, 1);
		strrtrim(op2, 3);
		size = setsize(v);

		if (size == opsize_byte || size == opsize_none)
		{
			M_AS2B("ora", 0x01)
			M_AS2B("and", 0x21)
			M_AS2B("eor", 0x41)
			M_AS2B("adc", 0x61)
			M_AS2B("sta", 0x81)
			M_AS2B("lda", 0xa1)
			M_AS2B("cmp", 0xc1)
			M_AS2B("sbc", 0xe1)
		}

		if (size == opsize_ushort || size == opsize_none)
		{
			M_AS2W("jmp", 0x7c)
			M_AS2W("jsr", 0xfc)
		}
		invalid_op();
	}

	void op2indirect_indexed_y()
	{
		static int v = 0;
		static string *op1, *op2;
		static byte size;
		op1 = xkas::opdata->data[0];
		op2 = xkas::opdata->data[1];
		strltrim(op2, 1);
		strrtrim(op2, 3);
		size = setsize(v);

		if (size == opsize_byte || size == opsize_none)
		{
			M_AS2B("ora", 0x11)
			M_AS2B("and", 0x31)
			M_AS2B("eor", 0x51)
			M_AS2B("adc", 0x71)
			M_AS2B("sta", 0x91)
			M_AS2B("lda", 0xb1)
			M_AS2B("cmp", 0xd1)
			M_AS2B("sbc", 0xf1)
		}
		invalid_op();
	}

	void op2indirect()
	{
		static int v = 0;
		static string *op1, *op2;
		static byte size;
		op1 = xkas::opdata->data[0];
		op2 = xkas::opdata->data[1];
		strltrim(op2, 1);
		strrtrim(op2, 1);
		size = setsize(v);

		if (size == opsize_byte || size == opsize_none)
		{
			M_AS2B("ora", 0x12)
			M_AS2B("and", 0x32)
			M_AS2B("eor", 0x52)
			M_AS2B("adc", 0x72)
			M_AS2B("sta", 0x92)
			M_AS2B("lda", 0xb2)
			M_AS2B("cmp", 0xd2)
			M_AS2B("sbc", 0xf2)
			M_AS2B("pei", 0xd4)
		}

		if (size == opsize_ushort || size == opsize_none)
		{
			M_AS2W("jmp", 0x6c)
		}
		invalid_op();
	}

	void op2stack_relative()
	{
		static int v = 0;
		static string *op1, *op2;
		static byte size;
		op1 = xkas::opdata->data[0];
		op2 = xkas::opdata->data[1];
		strrtrim(op2, 2);
		size = setsize(v);

		if (size == opsize_byte || size == opsize_none)
		{
			M_AS2B("ora", 0x03) 
			M_AS2B("and", 0x23)
			M_AS2B("eor", 0x43)
			M_AS2B("adc", 0x63)
			M_AS2B("sta", 0x83)
			M_AS2B("lda", 0xa3)
			M_AS2B("cmp", 0xc3)
			M_AS2B("sbc", 0xe3)
		}
		invalid_op();
	}

	void op2indexed_x()
	{
		static int v = 0;
		static string *op1, *op2;
		static byte size;
		op1 = xkas::opdata->data[0];
		op2 = xkas::opdata->data[1];
		strrtrim(op2, 2);
		size = setsize(v);

		if (size == opsize_byte) 
		{
			M_AS2B("ora", 0x15)
			M_AS2B("and", 0x35)
			M_AS2B("eor", 0x55)
			M_AS2B("adc", 0x75)
			M_AS2B("sta", 0x95)
			M_AS2B("lda", 0xb5)
			M_AS2B("cmp", 0xd5)
			M_AS2B("sbc", 0xf5)
			M_AS2B("asl", 0x16)
			M_AS2B("bit", 0x34)
			M_AS2B("rol", 0x36)
			M_AS2B("lsr", 0x56)
			M_AS2B("stz", 0x74)
			M_AS2B("ror", 0x76)
			M_AS2B("ldy", 0xb4)
			M_AS2B("dec", 0xd6)
			M_AS2B("inc", 0xf6)
		}

		if (size == opsize_byte || size == opsize_none)
		{
			M_AS2B("sty", 0x94)
		}

		if (size == opsize_ushort)
		{ 
			M_AS2W("ora", 0x1d)
			M_AS2W("and", 0x3d)
			M_AS2W("eor", 0x5d)
			M_AS2W("adc", 0x7d)
			M_AS2W("sta", 0x9d)
			M_AS2W("lda", 0xbd)
			M_AS2W("cmp", 0xdd)
			M_AS2W("sbc", 0xfd)
			M_AS2W("asl", 0x1e)
			M_AS2W("bit", 0x3c)
			M_AS2W("rol", 0x3e)
			M_AS2W("lsr", 0x5e)
			M_AS2W("ror", 0x7e)
			M_AS2W("stz", 0x9e)
			M_AS2W("ldy", 0xbc)
			M_AS2W("dec", 0xde)
			M_AS2W("inc", 0xfe)
		}

		if (size == opsize_long || size == opsize_none)
		{
			M_AS2L("ora", 0x1f)
			M_AS2L("and", 0x3f)
			M_AS2L("eor", 0x5f)
			M_AS2L("adc", 0x7f)
			M_AS2L("sta", 0x9f)
			M_AS2L("lda", 0xbf)
			M_AS2L("cmp", 0xdf)
			M_AS2L("sbc", 0xff)
		}
		invalid_op();
	}

	void op2indexed_y()
	{
		static int v = 0;
		static string *op1, *op2;
		static byte size;
		op1 = xkas::opdata->data[0];
		op2 = xkas::opdata->data[1];
		strrtrim(op2, 2);
		size = setsize(v);

		if (size == opsize_byte)
		{
			M_AS2B("ldx", 0xb6)
		}

		if (size == opsize_byte || size == opsize_none)
		{
			M_AS2B("stx", 0x96)
		}

		if (size == opsize_ushort || size == opsize_none)
		{
			M_AS2W("ora", 0x19)
			M_AS2W("and", 0x39)
			M_AS2W("eor", 0x59)
			M_AS2W("adc", 0x79)
			M_AS2W("sta", 0x99)
			M_AS2W("lda", 0xb9)
			M_AS2W("cmp", 0xd9)
			M_AS2W("sbc", 0xf9)
			M_AS2W("ldx", 0xbe)
		}
		invalid_op();
	}

	void op2absolute()
	{
		static int v = 0;
		static string *op1, *op2;
		static byte size;
		op1 = xkas::opdata->data[0];
		op2 = xkas::opdata->data[1];
		size = setsize(v);

		int a = xkas::state.pc;

		if (size == opsize_byte || size == opsize_none)
		{
			M_AS2RB("bra", 0x80)
			M_AS2RB("bcc", 0x90)
			M_AS2RB("bcs", 0xb0)
			M_AS2RB("beq", 0xf0)
			M_AS2RB("bne", 0xd0)
			M_AS2RB("bmi", 0x30)
			M_AS2RB("bpl", 0x10)
			M_AS2RB("bvc", 0x50)
			M_AS2RB("bvs", 0x70)
		}

		if (size == opsize_ushort || size == opsize_none)
		{
			M_AS2RW("brl", 0x82)
			M_AS2RW("per", 0x62)
		}

		if (size == opsize_byte)
		{
			M_AS2B("ora", 0x05)
			M_AS2B("and", 0x25)
			M_AS2B("eor", 0x45)
			M_AS2B("adc", 0x65)
			M_AS2B("sta", 0x85)
			M_AS2B("lda", 0xa5)
			M_AS2B("cmp", 0xc5)
			M_AS2B("sbc", 0xe5)
			M_AS2B("tsb", 0x04)
			M_AS2B("asl", 0x06)
			M_AS2B("trb", 0x14)
			M_AS2B("bit", 0x24)
			M_AS2B("rol", 0x26)
			M_AS2B("lsr", 0x46)
			M_AS2B("stz", 0x64)
			M_AS2B("ror", 0x66)
			M_AS2B("sty", 0x84)
			M_AS2B("stx", 0x86)
			M_AS2B("ldy", 0xa4)
			M_AS2B("ldx", 0xa6)
			M_AS2B("cpy", 0xc4)
			M_AS2B("dec", 0xc6)
			M_AS2B("cpx", 0xe4)
			M_AS2B("inc", 0xe6)
		}

		if(size==opsize_ushort)
		{ 
			M_AS2W("ora", 0x0d)
			M_AS2W("and", 0x2d)
			M_AS2W("eor", 0x4d)
			M_AS2W("adc", 0x6d)
			M_AS2W("sta", 0x8d)
			M_AS2W("lda", 0xad)
			M_AS2W("cmp", 0xcd)
			M_AS2W("sbc", 0xed)
			M_AS2W("mvp", 0x44)
			M_AS2W("mvn", 0x54)
		}

		if (size == opsize_ushort || size == opsize_long || size == opsize_none)
		{
			M_AS2W("tsb", 0x0c)
			M_AS2W("asl", 0x0e)
			M_AS2W("trb", 0x1c)
			M_AS2W("bit", 0x2c)
			M_AS2W("rol", 0x2e)
			M_AS2W("lsr", 0x4e)
			M_AS2W("ror", 0x6e)
			M_AS2W("sty", 0x8c)
			M_AS2W("stx", 0x8e)
			M_AS2W("stz", 0x9c)
			M_AS2W("ldy", 0xac)
			M_AS2W("ldx", 0xae)
			M_AS2W("cpy", 0xcc)
			M_AS2W("dec", 0xce)
			M_AS2W("cpx", 0xec)
			M_AS2W("inc", 0xee)
			M_AS2W("pea", 0xf4)
		}

		if (size == opsize_long || size == opsize_none)
		{
			M_AS2L("ora", 0x0f)
			M_AS2L("and", 0x2f)
			M_AS2L("eor", 0x4f)
			M_AS2L("adc", 0x6f)
			M_AS2L("sta", 0x8f)
			M_AS2L("lda", 0xaf)
			M_AS2L("cmp", 0xcf)
			M_AS2L("sbc", 0xef)
		}

		if(size==opsize_ushort || size==opsize_none)
		{
			M_AS2W("jmp", 0x4c)
			M_AS2W("jsr", 0x20)
		}

		if(size==opsize_long || size==opsize_none)
		{
			M_AS2LF("jmp", 0x5c)
			M_AS2LF("jsr", 0x22)
			M_AS2LF("jml", 0x5c)
			M_AS2LF("jsl", 0x22)
		}
		invalid_op();
	}

	void as1n_fn(byte x, int v)
	{
		static int i;
		for (i = 0; i < v; i++)
		{
			state.opcount++;
			putb(x);
		}
	}

	void as2c_fn(byte x, byte t, int v, int size)
	{
		state.opcount++;
		putb(x);
		if (assume.f_mx)
		{
			if (assume.mx&t)
				putb(v);
			else
				putw(v);
		}
		else 
		{
			if (size == opsize_byte)
				putb(v);
			else
				putw(v);
		}
	}

	void as2l_fn(byte x, int v, int size)
	{
		state.opcount++;
		if (assume.f_db && !oparg_labels_unresolved)
		{
			if (assume.db == ((v >> 16) & 0xFF))
			{
				putb(x - 2); //this is only possible because of the way the snes cpu was designed
				putw(v);	  //example: af - 2 = ad [af = lda.l label; ad = lda.w label]
				return;
			}
		}
		putb(x);
		putl(v);
	}

	void as2b_rs(byte v)
	{
		if (assume.f_mx)
		{
			if (v & 0x20)
				assume.mx &= ~2;
			if (v & 0x10)
				assume.mx &= ~1;
		}
	}

	void as2b_ss(byte v)
	{
		if (assume.f_mx)
		{
			if (v & 0x20)
				assume.mx |= 2;	
			if (v & 0x10)
				assume.mx |= 1;
		}
	}

	void invalid_op()
	{
		errorwa(0, 0, "invalid opcode or command");
	}

	void errorwa(byte t, byte pass, const char* s, ...)
	{
		if (pass ^ xkas::pass)
			return;

		static va_list args;
		static char str[0x4000];
		static string *error;
		error = xkas::errors->get(xkas::errorcount++);

		sprintf(str, "%s (%d) : error: ", xkas::files.data[xkas::filenum]->name, xkas::linenum + 1);
		strcpy(error, str);

		va_start(args, s);
		vsprintf(str, s, args);
		va_end(args);
		strcat(error, str);

		if (!t)
		{
			static strlist *tempstr = new strlist();
			static int i;

			strcat(error, " [");
			strcpy(tempstr, xkas::blockdata, 0, xkas::blocknum);
			split_eq(tempstr, ' ');
			strlisttrim(tempstr);
			for (i = 0; i < tempstr->count; ++i)
			{
				strcat(error, tempstr->data[i]);
				if (i != tempstr->count - 1)
					strcat(error, " ");
			}
			strcat(error, "]");
		}

		if (xkas::printerrors)
			printf("%s\n", error->text);
	}

	void errorna(byte pass, const char *s, ...)
	{
		if (pass ^ xkas::pass)
			return;

		static va_list args;
		static char str[0x4000];
		static string *error;
		error = xkas::errors->get(xkas::errorcount++);

		strcpy(error, "error: ");

		va_start(args, s);
		vsprintf(str, s, args);
		va_end(args);
		strcat(error, str);

		if (xkas::printerrors)
			printf("%s\n", error->text);
	}

	void warningwa(byte t, const char* s, ...)
	{
		if (pass ^ xkas::pass)
			return;

		static va_list args;
		static char str[0x4000];
		static string *warning;
		warning = xkas::warnings->get(xkas::warncount++);

		sprintf(str, "%s (%d): warning: ", xkas::files.data[xkas::filenum]->name, xkas::linenum + 1);
		strcpy(warning, str);

		va_start(args, s);
		vsprintf(str, s, args);
		va_end(args);
		strcat(warning, str);

		if (!t)
		{
			static strlist *tempstr = new strlist();
			static int i;

			strcat(warning, " [");
			strcpy(tempstr, xkas::blockdata, 0, xkas::blocknum);
			split_eq(tempstr, ' ');
			strlisttrim(tempstr);
			for (i = 0; i < tempstr->count; ++i)
			{
				strcat(warning, tempstr->data[i]);
				if (i != tempstr->count - 1)
					strcat(warning, " ");
			}
			strcat(warning, "]");
		}

		if (xkas::printwarnings)
			printf("%s\n", warning->text);
	}

	void warningna(byte pass, const char *s, ...)
	{
		if (pass ^ xkas::pass)
			return;

		static va_list args;
		static char str[0x4000];
		static string *warning;
		warning = xkas::warnings->get(xkas::warncount++);

		strcpy(warning, "warning: ");

		va_start(args, s);
		vsprintf(str, s, args);
		va_end(args);
		strcat(warning, str);

		if (xkas::printwarnings)
			printf("%s\n", warning->text);
	}
}