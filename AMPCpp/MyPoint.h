#pragma once
#include <string>

using namespace std;

class MyPoint
{
public:
	MyPoint(string name, double x, double y, double z);
	MyPoint();
	~MyPoint();

	string Name;
	double X;
	double Y;
	double Z;
};
