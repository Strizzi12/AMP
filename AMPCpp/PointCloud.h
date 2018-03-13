#pragma once
#include "MyPoint.h"
#include <vector>

using namespace std;

class PointCloud {
public:
	PointCloud();
	~PointCloud();

	vector<MyPoint> Cloud;

	void CreatePointCloud(int anz, double dx, double dy, double dz);
	MyPoint CreateRandomPoint(double dx, double dy, double dz);
	void ReadPointCloudFromFile(string filename);
	void PrintCloud(vector<MyPoint> cloud);
	double FRand(double fMin, double fMax);
	string randomString(size_t length);
};
