#include<string.h>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include "publisher.h"
#include "subscriber.h"
using namespace std;
extern int patientcount();
extern void mainMenu();

int main()

{
    
	int check = SUBSCRIBEmain();
	if (check != 0)
	{
		cout << "subscription failed:" << endl;
		cout << check << endl;
	}
	PUBLISHmain();
	cout << "welcome!!! enter 1 if you want to enter your details else do nothing\n";
	int option;
	cin >> option;
	if (option == 1)
		mainMenu();
	return 0;

}
