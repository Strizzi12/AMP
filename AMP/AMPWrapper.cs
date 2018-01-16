using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace AMP {
	static unsafe class AMPWrapper {
		[DllImport("AMPLib", CallingConvention = CallingConvention.StdCall)]
		static extern void square_array(float* array, int length);

		public static void SquareArray() {
			// Allocate an array
			float[] arr = new[] { 1.0f, 2.0f, 3.0f, 4.0f };

			// Square the array elements using C++ AMP
			fixed (float* arrPt = &arr[0]) {
				square_array(arrPt, arr.Length);
			}

		}

		[DllImport("AMPLib", CallingConvention = CallingConvention.StdCall)]
		static extern void AmpCalcDistMatrix(float* array, int length);

		public static void CalcDistMatrix(PointCloud cloud)
		{
			//CalcDistMatrix();
		}
	}
}
