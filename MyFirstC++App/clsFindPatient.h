#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsPatients.h"

class clsFindPatient : protected clsScreen ,protected clsPatients
{
private:

	static void _PrintCardPatient(stPatient Patient) {
		cout << "\n-----------------------------\n";
		cout << "\tCard Patient :\n";
		cout << "-----------------------------\n\n";
		cout << "Patient ID       : " << Patient.PatientID << "\n";
		cout << "Full Name        : " << Patient.FullName << "\n";
		cout << "Phone Number     : " << Patient.PhoneNumber << "\n";
		cout << "Birth Date       : " << Patient.BirthDate << "\n";
		cout << "Gender           : " << GenderText(Patient.Gender) << "\n";
		cout << "Address          : " << Patient.Address << "\n";
		cout << "First Visit Date : " << Patient.FirstVisitDate << "\n";
		cout << "Last Visit Date  : " << Patient.LastVisitDate << "\n";
		cout << "Chronic Diseases : " << ChronicDiseasesText(Patient.ChronicDiseases) << "\n";
		cout << "Drug Allergy     : " << DrugAllergyText(Patient.DrugAllergy) << "\n";
		cout << "Blood Type       : " << BloodTypeText(Patient.BloodType) << "\n";
		cout << "\n-----------------------------\n\n";

	}
	
	static short _ReadPatientID(vector <stPatient> vPatients ) {
		if (vPatients.empty()) {
			cout << "\nNo Patients Found in the System!\n";
			return 0;  // ÞíãÉ ÊÏá Úáì ÚÏã æÌæÏ ãÑÖì
		}

		short PatientID = 0;
		short LastPatientId = vPatients.size();

		cout << "\nPlease , Enter your Patient ID : [1 to " << LastPatientId << "] ? ";
		PatientID = clsInputValidate::ReadShortNumberBetween(1 , LastPatientId);

		return PatientID;
	}


public:
	static void ShowFindPatient() {
		_DrawScreenHeader("\t     Find Patient");

		vector <stPatient>vPatients = LoadPatientToFile();

		short PatientId = _ReadPatientID(vPatients);

		bool Found = false;
		for (stPatient& P : vPatients) {
			if (P.PatientID == PatientId) {
				_PrintCardPatient(P);
				Found = true;
				break;
			}
		}
		if (!Found) {
			cout << "\n\t Patient with ID (" << PatientId << ") Not Found!\n";
			cout << "\t Available IDs: ";
			for (stPatient& P : vPatients) {
				cout << P.PatientID << " ";
			}
			cout << endl;
		}
	}

	
};
