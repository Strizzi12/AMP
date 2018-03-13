using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace AMP {
	class Program {

		static void Main(string[] args) {
			var controller = new Controller();

			controller.ParseInputArguments(args);

			var watch = Stopwatch.StartNew();

			var result = AMPWrapper.CalcMinMaxDistances(controller.PointCloud);
			var minList = result.Item1;
			var maxList = result.Item2;

			foreach (var minTuple in minList) {
				Console.WriteLine($"Minimum Distance from Point: {controller.PointCloud.Cloud[(int)minTuple.Item1]} to Point: {controller.PointCloud.Cloud[(int)minTuple.Item2]}");
			}

			foreach (var maxTuple in maxList) {
				Console.WriteLine($"Maximum Distance from Point: {controller.PointCloud.Cloud[(int)maxTuple.Item1]} to Point: {controller.PointCloud.Cloud[(int)maxTuple.Item2]}");
			}

			watch.Stop();

			var elapsedMs = watch.ElapsedMilliseconds;
			if (controller.PrintProcessTime) {
				Console.WriteLine("Execution time = " + elapsedMs + " ms");
			}
			controller.Terminate();
		}
	}
}
