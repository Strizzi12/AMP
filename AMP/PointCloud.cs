using System;
using System.Collections.Generic;
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

		public void CreatePointCloudFromFile() {
			//Read line wise from file
			//Create point for each line in file
			//Add to list
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
