#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;

int patientcount()
{
	int rows = 0;
	ifstream file("patientDetailsReport.csv");
	string line;
	while (getline(file, line))
		rows++;
	return rows-1;
}