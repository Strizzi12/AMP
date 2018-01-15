using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AMP {
	class My3DPoint {
		private float _x;
		private float _y;
		private float _z;
		private string _name;

		public My3DPoint(string name, float x, float y, float z) {
			_z = z;
			_y = y;
			_x = x;
			_name = name;
		}
	}
}
