using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AMP {
	class PointCloud {
		private List<My3DPoint> _cloud;
		private readonly Random _random;

		public PointCloud() {
			_cloud = new List<My3DPoint>();
			_random = new Random();
		}

		public void CreatePointCloud(int anz, float dx, float dy, float dz) {
			for (int i = 0; i < anz; i++) {
				var point = CreateRandomPoint(dx, dy, dz);
				_cloud.Add(point);
			}
		}

		public void PrintPointCloud() {
			foreach (var point in _cloud) {
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
						_cloud.Add(new My3DPoint(name, x, y, z));
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

		private Tuple<My3DPoint, My3DPoint, float> GetMinDist() {
			//TODO For more than one MinDist
			throw new NotImplementedException();
		}

		private Tuple<My3DPoint, My3DPoint, float> GetMaxDist() {
			//TODO For more than one MaxDist
			throw new NotImplementedException();
		}

		private My3DPoint CreateRandomPoint(float dx, float dy, float dz) {
			var name = new Guid().ToString();
			var x = GetRandomNumber(-dx, dx);
			var y = GetRandomNumber(-dy, dy);
			var z = GetRandomNumber(-dz, dz);
			return new My3DPoint(name, x, y, z);
		}

		private float GetRandomNumber(float minimum, float maximum) {
			return (float)_random.NextDouble() * (maximum - minimum) + minimum;
		}
	}
}
