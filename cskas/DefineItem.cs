using System;
using System.Collections.Generic;
using System.Text;

namespace xkas
{
    public unsafe struct DefineItem
    {
        private string name;
        private string value;

        public string Name
        {
            get { return this.name; }
        }

        public string Value
        {
            get { return this.value; }
        }

        internal DefineItem(sbyte* name, sbyte* value)
        {
            this.name = new string(name);
            this.value = new string(value);
        }

        public DefineItem(string name, string value)
        {
            this.name = name;
            this.value = value;
        }
    }
}