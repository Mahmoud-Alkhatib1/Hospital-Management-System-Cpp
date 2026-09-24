#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsPatients.h"

class clsPatientMedicalHistory : protected clsScreen, protected clsPatients
{
private:
	static void _PrintCardPatient(stPatient Patient) {
		cout << "\n------------------------------------------\n\n";
		cout << "\t  [1-] Patient Basic Information :\n";
		cout << "\n------------------------------------------\n\n";
		cout << "Patient ID       : " << Patient.PatientID << "\n";
		cout << "Full Name        : " << Patient.FullName << "\n";
		cout << "Phone Number     : " << Patient.PhoneNumber << "\n";
		cout << "Birth Date       : " << AgeNumber(Patient) << " Years\n";
		cout << "Gender           : " << GenderText(Patient.Gender) << "\n";
		cout << "Blood Type       : " << BloodTypeText(Patient.BloodType) << "\n";
		cout << "\n------------------------------------------\n\n";
		cout << "\t  [2-] Chronic Diseases\n";
		cout << "\n------------------------------------------\n\n";
		cout << "Chronic Diseases : " << ChronicDiseasesText(Patient.ChronicDiseases) << "\n";
		cout << "\n------------------------------------------\n\n";
		cout << "\t  [3-] Drug Allergies\n";
		cout << "\n------------------------------------------\n\n";
		if(Patient.DrugAllergy == 0){
			cout << " No known drug allergies... \n\n";
		}
		else {
			cout << " Drug Allergies : " << DrugAllergyText(Patient.DrugAllergy) << "\n";
		}
		cout << "\n------------------------------------------\n\n";
		cout << "\t  [4-] Visit History (Last 5 Visits)\n";
		cout << "\n------------------------------------------\n\n";

		//cout << "Address          : " << Patient.Address << "\n";
		//cout << "First Visit Date : " << Patient.FirstVisitDate << "\n";
		//cout << "Last Visit Date  : " << Patient.LastVisitDate << "\n";
		//cout << "Chronic Diseases : " << ChronicDiseasesText(Patient.ChronicDiseases) << "\n";
	}

	static bool CheckFindPatient(vector <stPatient> vPatients, short PatientID) {
		for (stPatient& P : vPatients) {
			if (P.PatientID == PatientID) {
				_PrintCardPatient(P);

				return true;
			}
		}
		return false;
	}

	static short _ReadPatientID(vector <stPatient> vPatients) {
		cout << "\nPlease , Enter your Patient ID : [1 to " << vPatients.back().PatientID << "] ? ";
		short PatientID = clsInputValidate::ReadShortNumberBetween(1, vPatients.back().PatientID);

		while (!CheckFindPatient(vPatients, PatientID)) {
			cout << "\n\t Patient with ID (" << PatientID << ") Not Found!\n";
			cout << "\t Available IDs: ";
			for (stPatient& P : vPatients) {
				cout << P.PatientID << " ";
			}
			cout << endl;
			cout << "\nPlease , Enter your Patient ID : [1 to " << vPatients.back().PatientID << "] ? ";
			short PatientID = clsInputValidate::ReadShortNumberBetween(1, vPatients.back().PatientID);

		}
		return PatientID;
	}

public:
	static void ShowPatientMedicalHistory() {

		_DrawScreenHeader("\t   Patient Medical History");

		vector <stPatient> vPatients = LoadPatientToFile();

		short PatientID = _ReadPatientID(vPatients);


	}
};

