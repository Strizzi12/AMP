#pragma once
#include "MyPoint.h"
#include <vector>

using namespace std;

class MyCalculator
{
public:
	MyCalculator();
	~MyCalculator();

	void AmpCalcMinMaxDistances(vector<MyPoint> array);
};