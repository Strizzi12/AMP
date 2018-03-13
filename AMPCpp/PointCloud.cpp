#include "PointCloud.h"
#include <algorithm>
#include <vector>
#include <ostream> 
#include <sstream>
#include <fstream>
#include <iostream>

PointCloud::PointCloud()
{
	Cloud = vector<MyPoint>();
}


PointCloud::~PointCloud()
{
}

void PointCloud::PrintCloud(vector<MyPoint> cloud) {
	for (int i = 0; i < cloud.size(); i++)
	{
		cout << Cloud[i].Name << "," << Cloud[i].X << "," << Cloud[i].Y << "," << Cloud[i].Z << endl;
	}
}

void PointCloud::ReadPointCloudFromFile(string filename) {
	string line;	
	ifstream file(filename);

	if (file.is_open())
	{
		// getting a single line
		while (getline(file, line))
		{
			MyPoint point;

			point.Name = "";
			point.X = 0.0;
			point.Y = 0.0;
			point.Z = 0.0;
			string delimiter = ",";
			size_t last = 0;
			size_t next = 0;
			int index = 0;
			string token;

			while (index < 4) {
				next = line.find(delimiter, last);
				token = line.substr(last, next - last);
				last = next + 1;
				switch (index) {
					case 0: 
						point.Name = token;
						break;
					case 1: 
						point.X = stod(token);
						break;
					case 2: 
						point.Y = stod(token);
						break;
					case 3: 
						point.Z = stod(token);
						break;
				}
				index++;
			}
			Cloud.push_back(point);
		}
		file.close();
	}
}

void PointCloud::CreatePointCloud(int anz, double dx, double dy, double dz)
{
	for (int i = 0; i < anz; i++) {
		auto point = CreateRandomPoint(dx, dy, dz);
		Cloud.push_back(point);
	}
}

double PointCloud::FRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return (fMin + f * (fMax - fMin));
}

string PointCloud::randomString(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	string str(length, 0);
	generate_n(str.begin(), length, randchar);
	return str;
}

MyPoint PointCloud::CreateRandomPoint(double dx, double dy, double dz) {
	auto name = randomString(20);
	auto x = FRand(-dx, dx);
	auto y = FRand(-dy, dy);
	auto z = FRand(-dz, dz);
	return MyPoint(name, x, y, z);
}
