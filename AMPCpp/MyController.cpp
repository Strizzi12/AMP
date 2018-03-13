#include "MyController.h"
#include <Windows.h>
#include <iostream>
#include "string"
#include <sstream> 
#include <algorithm>
#include "MyCalculator.h"
#include <chrono>
#include <list>

using namespace std;
using namespace chrono;

MyController::MyController()
{
	Error = false;
	WaitForTermination = false;
	PrintProcessTime = false;
	MoreInfo = false;
	UseInfile = false;
}


MyController::~MyController()
{
}

void MyController::ParseInputArguments(int argc, char* argv[])
{
	for (int i = 1; i <= (argc - 1); i++)
	{
		if (strcmp(argv[i], "-w") == 0)
		{
			WaitForTermination = true;
			continue;
		}
		if (strcmp(argv[i], "-i" ) == 0 && argv[i + 1] != NULL)
		{
			auto infile = string(argv[i + 1]);
			PointCloud.ReadPointCloudFromFile(infile);
			i++;
			UseInfile = true;
			continue;
		}
		if (strcmp(argv[i], "-p") == 0)
		{
			PrintProcessTime = true;
			continue;
		}
		if (strcmp(argv[i], "-g") == 0 && argv[i + 1] != NULL)
		{
			int anz = 0;
			double dx = 0.0f;
			double dy = 0.0f;
			double dz = 0.0f;
			list<string> input;

			auto completeString = string(argv[i + 1]);
			stringstream test(completeString);
			string segment;
			while (getline(test, segment, ','))
			{
				input.push_back(segment);
			}
			anz = atoi(input.front().c_str());
			input.pop_front();
			dx = stod(input.front().c_str());
			input.pop_front();
			dy = stod(input.front().c_str());
			input.pop_front();
			dz = stod(input.front().c_str());
			input.pop_front();

			PointCloud.CreatePointCloud(anz, dx, dy, dz);
			PointCloud.PrintCloud(PointCloud.Cloud);
			i++;
			continue;
		}
		if (strcmp(argv[i], "-h") == 0)
		{
			PrintHelp();
			continue;
		}
		if (strcmp(argv[i], "-v") == 0)
		{
			MoreInfo = true;
		}
		else
		{
			cerr << "Error! Unknown argument detected." << endl;
			Error = true;
			break;
		}
	}
}

void MyController::PrintHelp()
{
	cout << "Die Applikation kann wie folgt aufzurufen:" << endl << endl;
	cout << "mmDistPt [-i infile] [-h] [-p] [-v] [-w] [-g n,dx,dy,dz]" << endl << endl;
	cout << "-i infile     Input filename" << endl;
	cout << "-g n,dx,dy,dz Erzeugt eine zufällige Punktwolke aus n Punkten mi einer 3D-räumlichen Ausdehnung von +/- dx,dy,dz und gibt diese zeilenweise auf stdout aus;" << endl;
	cout << "              wird diese Option nicht angegeben, so werden alle Dateien gelesen;" << endl;
	cout << "-h            Anzeige der Hilfe & Copyright Info; wird automatisch angezeigt, wenn beim Programmstart keinen Option angegeben wird." << endl;
	cout << "-p            Ausgabe der Prozesserungszeit auf stdout in Sekunden.Millisekunden" << endl;
	cout << "-v            Erweiterte Ausgabe etwaiger Prozessierungsinformationen auf stdout" << endl;
	cout << "-w            Warten auf eine Taste unmittelbar bevor die applikation terminiert." << endl << endl;
	cout << "Copyright© by Mike Thomas and Andreas Reschenhofer" << endl;
}

void MyController::Wait()
{
	if (WaitForTermination == true)
	{
		cout << endl << "Finished, waiting for key press.";
		cin.ignore();
	}
}

void MyController::MyPrint(string str)
{
	if (MoreInfo == true)
	{
		cout << str << endl;
	}
}

void MyController::PrintTime()
{
	if (PrintProcessTime == true)
	{
		printf("Time taken: %.6fs\n", double(StopTime - StartTime) / CLOCKS_PER_SEC);

		duration<double> time_span = duration_cast<duration<double>>(StopTimeHighResolution - StartTimeHighResolution);
		//printf("Time taken (high resolution time): %.6fs\n", time_span.count());
		cout << "Time taken (high resolution time): " << time_span.count() << endl;
	}
}

clock_t MyController::GetTime()
{
	return clock();
}

high_resolution_clock::time_point MyController::GetHighResolutionTime()
{
	return high_resolution_clock::now();
}	

void MyController::SetStartTime()
{
	if (PrintProcessTime == true)
	{
		StartTime = GetTime();
		StartTimeHighResolution = GetHighResolutionTime();
	}
}

void MyController::SetStopTime()
{
	if (PrintProcessTime == true)
	{
		StopTime = GetTime();
		StopTimeHighResolution = GetHighResolutionTime();
	}
}

//private functions
bool MyController::IsAllDigits(string& str)
{
	return all_of(str.begin(), str.end(), isdigit); // C++11
}