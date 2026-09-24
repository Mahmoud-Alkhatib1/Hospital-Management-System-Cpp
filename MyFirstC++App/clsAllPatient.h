#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsPatients.h"

class clsAllPatient : protected clsScreen , clsPatients
{
private:
	static void _PrintCardPatient(stPatient Patient) {
		cout << setw(8) << left << "";
		cout << "| " << setw(7) << left << Patient.PatientID;
		cout << "| " << setw(27) << left << Patient.FullName;
		cout << "| " << setw(12) << left << Patient.PhoneNumber;
		cout << "| " << setw(12) << left << Patient.BirthDate;
		cout << "| " << setw(7) << left << GenderText(Patient.Gender);
		cout << "| " << setw(12) << left << Patient.Address;
		cout << "|" << endl;
	}

	static void _InformetionPatient(stPatient Patient) {
		cout << setw(8) << left << "";
		cout << "| " << setw(7) << left << Patient.PatientID;
		cout << "| " << setw(12) << left << Patient.FirstVisitDate;
		cout << "| " << setw(12) << left << Patient.LastVisitDate;
		cout << "| " << setw(20) << left << ChronicDiseasesText(Patient.ChronicDiseases);
		cout << "| " << setw(15) << left << DrugAllergyText(Patient.DrugAllergy);
		cout << "| " << setw(10) << left << BloodTypeText(Patient.BloodType);
		cout << "|" << endl;
	}

public:

	static void ShowAllPatients() {

		vector<stPatient>vPatients = LoadPatientToFile();

		string Title = "\t  Patient List Screen";
		string SubTitle = "\t    (" + to_string(vPatients.size()) + ") Patient(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "";
		cout << "| " << left << setw(7) << "ID";
		cout << "| " << left << setw(27) << "Full Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(12) << "Birth Date";
		cout << "| " << left << setw(7) << "Gender";
		cout << "| " << left << setw(12) << "Address";
		cout << "|" << endl;

		cout << setw(8) << left << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vPatients.size() == 0) {
			cout << "\t\t\t\tNo Patient Available In the System!";

		}
		else {
			for (stPatient& P : vPatients) {
				_PrintCardPatient(P);
			}
		}
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;



		cout << "\t\t\t\t\t\tPatient information : \n";

		cout << setw(8) << left << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "";
		cout << "| " << left << setw(7) << "ID";
		cout << "| " << left << setw(12) << "First Visit";
		cout << "| " << left << setw(12) << "Last Visit";
		cout << "| " << left << setw(20) << "Chronic Disease";
		cout << "| " << left << setw(15) << "Drug Allergy ";
		cout << "| " << left << setw(10) << "Blood Type";
		cout << "|" << endl;

		cout << setw(8) << left << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		for (stPatient& P : vPatients) {

			_InformetionPatient(P);
		}
		cout << setw(8) << left << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}
};

