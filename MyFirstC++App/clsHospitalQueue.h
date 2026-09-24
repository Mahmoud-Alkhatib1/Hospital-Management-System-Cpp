#pragma once

#include <iostream>
#include <queue>
#include <string>
#include "clsDate.h"

using namespace std;

class clsHospitalQueue
{
private:

	class clsPatient {

		string _Name = "";
		string _Type = "";
		string _Time = "";

	public:

		clsPatient(string name, string Type) {
			_Name = name;
			_Type = Type;
			_Time = clsDate::GetSystemDateTimeString();
		}

		string GetName() {
			return _Name;
		}
		
		string GetType() {
			return _Type;
		}
		
		string GetTime() {
			return _Time;
		}

		string Print() {

			return " Calling " + _Type + " patient: " + _Name + " [" + _Type + "] at " + _Time + "\n\n";
		}
	};

public:

	queue<clsPatient> emergencyQueue;
	queue<clsPatient> normalQueue;

	void AddPatient(string name, bool isEmergency) {

		if (isEmergency) {

			cout << name << " added to EMERGENCY queue\n";
			clsPatient Patient(name, "EMERGENCY");
			emergencyQueue.push(Patient);
		}
		else {

			cout << name << " added to NORMAL queue\n";
			clsPatient Patient(name, "NORMAL");
			normalQueue.push(Patient);
		}


	}

	void CallNext() {
		if (!emergencyQueue.empty()) {
			emergencyQueue.front().Print();
			emergencyQueue.pop();
		}
		else if (!normalQueue.empty()) {
			normalQueue.front().Print();
			normalQueue.pop();
		}
		else {
			cout << "No patients waiting!\n";
		}
	}

	short TotalWaiting() {
		return emergencyQueue.size() + normalQueue.size();
	}

	void ShowAll() {
		cout << "\n===================================\n\n";
		cout << "CURRENT PATIENTS QUEUE\n\n";
		cout << "===================================\n\n";


		cout << "EMERGENCY QUEUE(" << emergencyQueue.size() << "patients) : \n";

		queue <clsPatient>EmergencyTemp = emergencyQueue;

		if (EmergencyTemp.empty()) {
			cout << "(Empty)\n";
		}
		else {
			while (!EmergencyTemp.empty()) {
				clsPatient Patient = EmergencyTemp.front();
				cout << Patient.Print() << endl;
				EmergencyTemp.pop();
			}
		}
		
		cout << "NORMAL QUEUE(" << normalQueue.size() << "patients) : \n";

		queue <clsPatient>NormalTemp = normalQueue;

		if (NormalTemp.empty()) {
			cout << "(Empty)\n";
		}
		else{
			while (!NormalTemp.empty()) {
				clsPatient Patient = NormalTemp.front();
				cout << Patient.Print() << endl;
				NormalTemp.pop();
			}
		}
		

		cout << "\n===================================\n\n";
		cout << "Total waiting: " << TotalWaiting() << " patients.\n\n";
		cout << "===================================\n\n";

	}
};

