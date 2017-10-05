#include "file.h"

namespace xkas
{
	struct freeorg_item
	{
		int fnum;
		int lnum;
	};

	class freeorg_list : list<freeorg_item>
	{

	};
}