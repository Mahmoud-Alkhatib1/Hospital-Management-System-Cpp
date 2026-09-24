#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsPatients.h"

class clsDeletePatient : protected clsScreen, protected clsPatients
{
private:

	static void _PrintCardPatient(stPatient Patient) {
		cout << "\n-----------------------------\n";
		cout << "\t   Card Patient :\n";
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
		cout << "Blood Type       : " << BloodTypeText(Patient.BloodType) << "\n";
		cout << "\n-----------------------------\n\n";

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
	
	static void ShowDeletePatient() {

		char Answer = 'Y';

		do{

			system("cls");

			_DrawScreenHeader("\t   Delete Patient");

			vector <stPatient> vPatients = LoadPatientToFile();


			short PatientID = _ReadPatientID(vPatients);

			cout << "\nAre you sure you deleted the patient's data ? [Y/N] : ";
			cin >> Answer;

			if (Answer == 'Y' || Answer == 'y') {
				Delete(vPatients, PatientID);

				if (!CheckFindPatient(vPatients, PatientID)) {
					cout << "\n\tPatient Deleted Successfuly...\n";
				}
				else {
					cout << "\tA deletion error occurred...\n";
				}
			}
			

			cout << "\nDo you want to delete another patient ? [Y/N] : ";
			cin >> Answer;
		} while (Answer == 'Y' || Answer == 'y');
	}
};
