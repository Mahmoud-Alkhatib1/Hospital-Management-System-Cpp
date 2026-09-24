#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsPatients.h"

class clsAddNewPatient : protected clsScreen , protected clsPatients
{
private:
	static stPatient _ReadAddNewPatient(string FullName) {
		short Counter = 0;

		stPatient Patient = LastPatient();

		Counter = Patient.PatientID;

		Counter++;

		Patient = clsPatients::EmptyToFilePatient();

		cout << "\nPlease , Add a new Patient : \n\n";

		Patient.PatientID = Counter;

		Patient.FullName = FullName;

		cout << "\nPhone Number : ";
		Patient.PhoneNumber = clsInputValidate::ReadString();

		cout << "\n\nBirth Date : ";
		Patient.BirthDate = clsInputValidate::ReadString();

		cout << "\n\nGender [Male = 1 , FeMale = 2] : ";
		Patient.Gender = clsInputValidate::ReadShortNumberBetween(1 ,2);

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

	static void ShowAddNewPatientToFile() {

		char More = 'y';

		do {

			system("cls");

			_DrawScreenHeader("\t  Add New Patient");


			string FullName;
			cout << "Full Name : ";
			FullName = clsInputValidate::ReadString();

			while (IsPatientExists(FullName)) {
				cout << "Patient With [" << FullName<<"] already exeits, Enter another Full Name : ";
				FullName = clsInputValidate::ReadString();
			}
			stPatient Patient = _ReadAddNewPatient(FullName);

			cout << "\n\nAre you sure you have saved the new patient's data ? [Y/N] : ";
			cin >> More;

			if (More == 'Y' || More == 'y') {
				Save(ConvertPatientObjectToLine(Patient));
				cout << "\n\n  Patient Added Successfuly... \n";
			}

			cout << "\nWould you like to add a new patient ? [Y/N] : ";
			cin >> More;
		} while (More == 'Y' || More == 'y');

		
	}
};
