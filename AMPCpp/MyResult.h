#pragma once
#include <list>

using namespace std;

class MyResult {
public:
	MyResult(list<tuple<double, double>>, list<tuple<double, double>>);
	~MyResult();

	list<tuple<double, double>> Min;
	list<tuple<double, double>> Max;
};
