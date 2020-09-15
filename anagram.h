#include<bits/stdc++.h>
#include<iostream> 
#include<string.h>
#include <sstream>
using namespace std;

class CheckValues
{
     public:
   CheckValues(){}
    string CheckValuesForAlert(float value,string &ValueName,float HighValueForAlert,float HighValueForWarning,float LowValueForAlert,float LowValueForWarning);
    string checkforlowvalues(float value,string &ValueName,float LowValueForAlert,float LowValueForWarning);
    string checkforhighvalues(float value,string &ValueName,float HighValueForAlert,float HighValueForWarning);
};
class PrintMessage
{   
    public:
    void PrintMessageOnConsole(string &messageForTem,string &messageForHumi);
};

class CheckForWarningAndAlert
{     
 private:
    CheckValues check;
    PrintMessage *print;
    float ErrorHighValueForTem=40;
    float ErrorLowValueForTem=0;
    float WarningHighValueForTem=37;
    float WarningLowValueFortem=4;
    float ErrorHighValueForHumi=90;
    float WarningHighValueForHumi=70;
    public:
    CheckForWarningAndAlert(){}
     CheckForWarningAndAlert(float tempreature,float humidity)
     {
         string humidityname="humidity",tempreaturename="tempreature";
     string messageForTem=check.CheckValuesForAlert(tempreature,tempreaturename,ErrorHighValueForTem
     ,WarningHighValueForTem,ErrorLowValueForTem,WarningLowValueFortem);
     string messageForHumi=check.CheckValuesForAlert(humidity,humidityname,ErrorHighValueForHumi
     ,WarningHighValueForHumi,0,0);
     print->PrintMessageOnConsole(messageForTem,messageForHumi);
     }
    
};
