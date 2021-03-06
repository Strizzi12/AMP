// CountBytes.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "MyConstants.h"
#include "MyCalculator.h"
#include "MyController.h"
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;


int main(int argc, char* argv[])
{
	//Initialization
	MyController myController;
	MyCalculator myCalculator;

	//Input Parsing
	if (argc < 2)
	{
		myController.PrintHelp();
		return 0;
	}
	myController.ParseInputArguments(argc, argv);
	

	high_resolution_clock::time_point start = high_resolution_clock::now();

	//Calculation area
	if (myController.UseInfile)
	{
		auto cloud = myController.PointCloud.Cloud;
		myCalculator.AmpCalcMinMaxDistances(cloud);
	}

	high_resolution_clock::time_point stop = high_resolution_clock::now();


	//Workaround for printing high resolution time	
	if (myController.PrintProcessTime == true)
	{
		duration<double> time_span = duration_cast<duration<double>>(stop - start);
		cout << "Time taken (high resolution time): " << setprecision(3) << time_span.count() << "s" << endl;
	}
	myController.Wait();
	return 0;
}