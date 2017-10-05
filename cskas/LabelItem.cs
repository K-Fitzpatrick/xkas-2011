using System;
using System.Collections.Generic;
using System.Text;

namespace xkas
{
    public unsafe struct LabelItem
    {
        private string name;
        private int offset;

        public string Name
        {
            get { return this.name; }
        }
        public int Offset
        {
            get { return this.offset; }
        }

        internal LabelItem(sbyte* name, int offset)
        {
            this.name = new string(name);
            this.offset = offset;
        }

        public LabelItem(string name, int offset)
        {
            this.name = name;
            this.offset = offset;
        }
    }
}
