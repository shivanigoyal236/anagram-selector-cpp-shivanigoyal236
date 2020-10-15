#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;


void saveDataToCSV(string msg)
{
	fstream fout;
	fout.open("patientdetailsReport.csv", ios::out | ios::app);
	string param;
	vector<string> patientParam;
	stringstream ss(msg);
	while (getline(ss, param,';' ))
	{
		
		patientParam.push_back(param);
		
	}
	for (int i = 0;i < patientParam.size();i++)
	{
		fout << patientParam[i] << ",";
	}
	fout <<"\n";
	
}
