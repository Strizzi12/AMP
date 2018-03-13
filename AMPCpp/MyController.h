#pragma once
#include <string>
#include <vector>
#include <time.h>
#include <chrono>
#include "PointCloud.h"

using namespace std;
using namespace chrono;

class MyController
{
public:
	MyController();
	~MyController();

	//Variables
	bool WaitForTermination;
	bool PrintProcessTime;
	bool Error;
	bool MoreInfo;
	bool UseInfile;
	clock_t StartTime;
	clock_t StopTime;
	high_resolution_clock::time_point StartTimeHighResolution;
	high_resolution_clock::time_point StopTimeHighResolution;

	PointCloud PointCloud;

	//Functions
	void ParseInputArguments(int argc, char* argv[]);
	void PrintHelp();
	void Wait();
	void MyPrint(string str);
	void PrintTime();
	static clock_t GetTime();
	static high_resolution_clock::time_point GetHighResolutionTime();
	void SetStartTime();
	void SetStopTime();

private:
	bool IsAllDigits(string &str);

};

