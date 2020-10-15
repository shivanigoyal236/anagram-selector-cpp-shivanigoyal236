#pragma once
#pragma once

#include <iostream>
#include<string>

using namespace std;

class patientInfo {
private:
    string name;
    string gender;
    int age;
    string procedureName;
    string Rmsg;

public:
    patientInfo() {}
    patientInfo(string Name, string Gender, int Age, string ProcedureName,string RMSG) : name(Name), gender(Gender), age(Age), procedureName(ProcedureName),Rmsg(RMSG) {}

    string getName() {
        return name;
    }

    string getGender() {
        return gender;
    }

    int getAge() {
        return age;
    }

    string getProcedureName() {
        return procedureName;
    }
    string getReceivedString()
    {
        return Rmsg;
    }

    void setName(string newName) {
        name = newName;
    }

    void setGender(string newGender) {
        gender = newGender;
    }

    void setAge(int newAge) {
        age = newAge;
    }
    void setProcedureName(string newProcedure) {
        procedureName = newProcedure;
    }
    void setReceivedString(string msg)
    {
        Rmsg = msg;
    }
    string toString() {
        string result = name + ";" + to_string(age) + ";" + gender + ";" + procedureName;
        return result;
    }
};
