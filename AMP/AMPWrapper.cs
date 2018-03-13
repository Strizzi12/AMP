using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace AMP {
	static unsafe class AMPWrapper {
		[DllImport("AMPLib", CallingConvention = CallingConvention.StdCall)]
		static extern void AmpCalcMinMaxDistances(List<MyPoint> array);

		public static void CalcMinMaxDistances(PointCloud cloud) {
			AmpCalcMinMaxDistances(cloud.Cloud);
		}
	}
}
