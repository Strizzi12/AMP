using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AMP {
	public class PointCloud {
		public List<MyPoint> Cloud;
		private readonly Random _random;

		public PointCloud() {
			Cloud = new List<MyPoint>();
			_random = new Random();
		}

		public void CreatePointCloud(int anz, float dx, float dy, float dz) {
			for (int i = 0; i < anz; i++) {
				var point = CreateRandomPoint(dx, dy, dz);
				Cloud.Add(point);
			}
		}

		public void PrintPointCloud() {
			foreach (var point in Cloud) {
				Console.WriteLine("\"" + point.Name + "\"," + point.X + "," + point.Y + "," + point.Z);
			}
		}

		public void ReadPointCloudFromFile(string fileName) {
			foreach (string line in File.ReadLines(fileName)) {
				try {
					//Split string at ,
					var input = line.Split(',');
					if (input.Length == 4) {
						var name = input[0].Replace("\"", "");
						var x = Helper.TransformInput<float>(input[1]);
						var y = Helper.TransformInput<float>(input[2]);
						var z = Helper.TransformInput<float>(input[3]);
						Cloud.Add(new MyPoint() {
							Name = name,
							X = x,
							Y = y,
							Z = z
						});
					} else {
						Console.WriteLine("Error! Unknown argument detected.");
						break;
					}
				} catch (Exception e) {
					Console.WriteLine(e.Message);
					break;
				}
			}
		}

		private MyPoint CreateRandomPoint(double dx, double dy, double dz) {
			var name = new Guid().ToString();
			var x = GetRandomNumber(-dx, dx);
			var y = GetRandomNumber(-dy, dy);
			var z = GetRandomNumber(-dz, dz);
			return new MyPoint() {
				Name = name,
				X = x,
				Y = y,
				Z = z
			};
		}

		private double GetRandomNumber(double minimum, double maximum) {
			return _random.NextDouble() * (maximum - minimum) + minimum;
		}
	}
}
