using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AMP {
	class My3DPoint {
		public float X { get; }
		public float Y { get; }
		public float Z { get; }
		public string Name { get; }

		public My3DPoint(string name, float x, float y, float z) {
			Z = z;
			Y = y;
			X = x;
			Name = name;
		}
	}
}
