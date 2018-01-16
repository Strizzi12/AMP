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
			
			//TODO

			watch.Stop();
			
			//Console.WriteLine($"Number of checked files: {files.Count}");
			var elapsedMs = watch.ElapsedMilliseconds;
			if (controller.PrintProcessTime) {
				Console.WriteLine("Execution time = " + elapsedMs + " ms");
			}
			controller.Terminate();
		}
	}
}
