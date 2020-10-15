#include <iostream>
#include<sstream>
#include "patientInfo.h"
#include <string>
#include<vector>

extern int publish(string);
patientInfo publisherpatientInfo;
using namespace std;

void mainMenu()
{
	
	string stringInput;
	int integerInput;

l1:	cout << "enter patient name:";
	cin >> stringInput;
	publisherpatientInfo.setName(stringInput);
	cout << "enter patient age in numbers:";
	cin >> integerInput;
	publisherpatientInfo.setAge(integerInput);
	cout << "enter your gender\nTYPE F for female\nTYPE M for male:";
	cin >> stringInput;
	publisherpatientInfo.setGender(stringInput);
	cout << "enter name of procedure:";
	cin >> stringInput;
	publisherpatientInfo.setProcedureName(stringInput);

	string verifyingDetails;
	cout << publisherpatientInfo.getName() << " " << publisherpatientInfo.getAge() << " " << publisherpatientInfo.getGender() << " " << publisherpatientInfo.getProcedureName() << endl;
	cout << "Check if the details entered are correct: (yes/no)" << endl;
	cin >> verifyingDetails;
	
    if (verifyingDetails == "yes")
	{
		string finalDetails = publisherpatientInfo.toString();
		
		publish(finalDetails);

	}
	else
	{
		goto l1;

	}

}
