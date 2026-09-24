#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsPatients.h"

class clsUpdatePatient : protected clsScreen, protected clsPatients
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

	static short _ReadPatientID(vector <stPatient> vPatients) {
		if (vPatients.empty()) {
			cout << "\nNo Patients Found in the System!\n";
			return 0;  // ÞíãÉ ÊÏá Úáì ÚÏã æÌæÏ ãÑÖì
		}

		short PatientID = 0;
		short LastPatientId = vPatients.size();

		cout << "\nPlease , Enter your Patient ID : [1 to " << LastPatientId << "] ? ";
		PatientID = clsInputValidate::ReadShortNumberBetween(1, LastPatientId);

		return PatientID;
	}

	static stPatient _ReadUpdateInfoPatient(stPatient Patient , short PatientID) {
		
		cout << "\nPlease , Update a new Patient : \n\n";

		Patient.PatientID = PatientID;

		cout << "Full Name : ";
		Patient.FullName = clsInputValidate::ReadString();

		cout << "\n\nPhone Number : ";
		Patient.PhoneNumber = clsInputValidate::ReadString();

		cout << "\n\nBirth Date : ";
		Patient.BirthDate = clsInputValidate::ReadString();

		cout << "\n\nGender [Male = 1 , FeMale = 2] : ";
		Patient.Gender = clsInputValidate::ReadShortNumberBetween(1, 2);

		cout << "\n\nAddress : ";
		Patient.Address = clsInputValidate::ReadString();

		cout << "\n\nFirst Visit Date : ";
		Patient.FirstVisitDate = clsInputValidate::ReadString();

		cout << "\n\nLast Visit Date : ";
		Patient.LastVisitDate = clsInputValidate::ReadString();

		cout << "\n\nChronic Diseases [None = 0 ,Hypertension = 1 ,Diabetes = 2 ,HeartDisease = 3 \n";
		cout << " ,Asthma = 4 ,KidneyDisease = 5 ,ThyroidDisorder = 6 MoreThanOneDisease = 7,Other = 8] : ";
		Patient.ChronicDiseases = clsInputValidate::ReadShortNumberBetween(0, 8);

		cout << "\n\nDrug Allergie [No Allergies = 0 ,Penicillin = 1 ,Aspirin = 2\n";
		cout << " ,Ibuprofen = 3 ,Paracetamol = 4 ,Penicillin & Others = 5] : ";
		Patient.DrugAllergy = clsInputValidate::ReadShortNumberBetween(0, 5);

		cout << "\n\nBlood Type [APositive = 1, ANegative = 2, BPositive = 3, BNegative = 4\n, OPositive = 5,";
		cout << " ONegative = 6, ABPositive = 7, ABNegative = 8] :";
		Patient.BloodType = clsInputValidate::ReadShortNumberBetween(1, 8);
		return Patient;
	}

public:

	static void ShowUpdatePatientInfo() {
		_DrawScreenHeader("\t    Update Patient Info");

		cout << "Please enter the ID of the patient whose information you want to edit.\n\n";

		vector <stPatient>vPatients = LoadPatientToFile();
		short PatientId;
		stPatient Patient;

		bool Found = false;
		do {
			PatientId = _ReadPatientID(vPatients);
			Patient = Find(PatientId);

			if (Patient.PatientID != 0) {
				for (stPatient& P : vPatients) {
					if (Patient.PatientID == P.PatientID) {
						_PrintCardPatient(Patient);
						Found = true;
					}
				}
			}
			else if (!Found) {
				cout << "\n\t Patient with ID (" << PatientId << ") Not Found!\n";
				cout << "\t Available IDs: ";
				for (stPatient& P : vPatients) {
					cout << P.PatientID << " ";
				}
				cout << endl;
				cout << "Choose a ID from the list above.\n";

			}
		} while (!Found);

		stPatient UpdatePatient = _ReadUpdateInfoPatient(Patient, PatientId);

		char More = 'y';


		cout << "\n\nAre you sure you have saved the new patient's data ? [Y/N] : ";
		cin >> More;

		if (More == 'Y' || More == 'y') {
			vPatients = Update(UpdatePatient);
			cout << "\n\tPatient Updated Successfuly...\n";
		}
	}
};

