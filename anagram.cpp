#include<bits/stdc++.h>
#include<iostream> 
#include<string.h>
#include <sstream> 
#include "receiver.h"
using namespace std;


   string CheckValues::CheckValuesForAlert(float value,string &ValueName,float HighValueForAlert,float HighValueForWarning,float LowValueForAlert,float LowValueForWarning)
  {
      string s="";
    if(value>HighValueForWarning)
      s=checkforhighvalues(value,ValueName,HighValueForAlert,HighValueForWarning);
    else
       s=checkforlowvalues(value,ValueName,LowValueForAlert,LowValueForWarning);
     return s;
  }
  string CheckValues::checkforlowvalues(float value,string &ValueName,float LowValueForAlert,float LowValueForWarning)
  {   string s="";
    if(value<LowValueForAlert)
	 {
	 	s="ALERT!!"+ValueName+" is "+"very low";
	 }
     else if(value<LowValueForWarning)
     {
     	s="Warning!!"+ValueName+" is "+"very low";
	 }
     return s;
  }
  string CheckValues::checkforhighvalues(float value,string &ValueName,float HighValueForAlert,float HighValueForWarning)
  {
     string s="";
     if(value>HighValueForAlert)
     {  
        s="ALERT!!"+ValueName+" is "+"very high";
	 }
	 else if(value>HighValueForWarning)
	 {
	 	s="Warning!!"+ValueName+" is "+"high";
	 }
     return s;
  }
  

   void PrintMessage::PrintMessageOnConsole(string &messageForTem,string &messageForHumi)
        {
           cout<<messageForTem<<endl;
           cout<<messageForHumi<<endl;
        }

void extractValuesFromStringAndSendValuesForChecking(string line) 
{ 
    stringstream ss(line); 
        while(ss.good())
        {
         	string tempreaturestring,humiditystring;
         	getline(ss,tempreaturestring,' ');
         	getline(ss,humiditystring,'\n');
         	CheckForWarningAndAlert obj(stof(tempreaturestring),stof(humiditystring));
        } 
}
       

 int main()
{    
    
          string line="";
    while(getline(cin,line))
    {   
        extractValuesFromStringAndSendValuesForChecking(line);
    }
    return 0;
}
