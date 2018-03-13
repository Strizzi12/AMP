#include <list>
#include "amp.h"
#include "amp_math.h"
#include "MyPoint.h"
#include "MyCalculator.h"
#include <iomanip>
#include <iostream>

using namespace concurrency;
using namespace precise_math;
using namespace std;

MyCalculator::MyCalculator()
{
}


MyCalculator::~MyCalculator()
{
}

void MyCalculator::AmpCalcMinMaxDistances(vector<MyPoint> array)
{
	try
	{
		double size = array.size();
		vector<double> pointArray;

		for (const auto& point : array) {
			pointArray.push_back(point.X);
			pointArray.push_back(point.Y);
			pointArray.push_back(point.Z);
		}

		// Create a view over the data on the CPU
		array_view<double, 2> inputMatrix(size, 3, pointArray);

		vector<double> vecDistMatrix(4 * size);
		array_view<double, 2> result(size, 4, vecDistMatrix);

		// Run code on the GPU
		parallel_for_each(result.extent, [=](index<2> idx) restrict(amp)
		{
			int row = idx[0];
			double max = 0;
			double min = HUGE_VAL;
			double minIndex = -1;
			double maxIndex = -1;
			for (long i = 0; i < size; i++) {
				if (i == row) {
					continue;
				}
				auto distToOtherPoint = pow(pow(inputMatrix(row, 0) - inputMatrix(i, 0), 2)
				                            + pow(inputMatrix(row, 1) - inputMatrix(i, 1), 2)
				                            + pow(inputMatrix(row, 2) - inputMatrix(i, 2), 2), 0.5);

				//Find min and max distances
				if (distToOtherPoint < min) {
					min = distToOtherPoint;
					minIndex = i;
				}
				if (distToOtherPoint > max) {
					max = distToOtherPoint;
					maxIndex = i;
				}

				result(row, 0) = min;
				result(row, 1) = minIndex;
				result(row, 2) = max;
				result(row, 3) = maxIndex;
			}
		});

		// Need to synchronize, because we have to wait for all other results.
		result.synchronize();

		// Now find min/max distances for all rows
		vector<pair<double, double>> minDist;
		vector<pair<double, double>> maxDist;
		double curMinValue = 0;
		double curMaxValue = 0;
		for (long row = 0; row < size; row++) {
			auto min = result(row, 0);
			auto max = result(row, 2);
			auto minIndex = result(row, 1);
			auto maxIndex = result(row, 3);
			if (row == 0) {
				curMinValue = min;
				curMaxValue = max;
				minDist.push_back(make_pair(row, minIndex));
				maxDist.push_back(make_pair(row, maxIndex));
			}
			else {
				if (curMinValue > min)
				{
					minDist.clear();
					curMinValue = min;
					minDist.push_back(make_pair(row, minIndex));
				}
				if (curMaxValue < max)
				{
					maxDist.clear();
					curMaxValue = max;
					maxDist.push_back(make_pair(row, maxIndex));
				}
			}
		}

		for (int i = 0; i < minDist.size(); i++)
		{
			pair<double, double> element = minDist.at(i);
			auto indexA = element.first;
			MyPoint a = array[indexA];
			auto indexB = element.second;
			MyPoint b = array[indexB];
			auto distToOtherPoint = pow(pow(a.X - b.X, 2) + pow(a.Y - b.Y, 2) + pow(a.Z - b.Z, 2), 0.5);
			cout << "Minimum distance of " << distToOtherPoint << " between point: " << a.Name << " and point: " << b.Name << "!" << endl;
		}
		cout << endl;
		for (int i = 0; i < maxDist.size(); i++)
		{
			pair<double, double> element = maxDist.at(i);
			auto indexA = element.first;
			MyPoint a = array[indexA];
			auto indexB = element.second;
			MyPoint b = array[indexB];
			auto distToOtherPoint = pow(pow(a.X - b.X, 2) + pow(a.Y - b.Y, 2) + pow(a.Z - b.Z, 2), 0.5);
			cout << "Maximum distance of " << distToOtherPoint << " between point: " << a.Name << " and point: " << b.Name << "!" << endl;
		}
	}
	catch (exception ex)
	{
		cout << ex.what();
	}
}