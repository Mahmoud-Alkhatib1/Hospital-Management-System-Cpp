#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsDoctors.h"

class clsShowDoctorsBySpecialization : clsScreen
{
private:

	static void _ReadSpecialization(short &Specialization , vector<clsDoctors>&vDoctors) {
		_DrawScreenHeader("  Show Doctors By Specialization");

		cout << "please ,Enter Your Specialization [eGeneral = 1, Cardiology = 2, Dermatology = 3, Pediatrics = 4 ,\n"
			"                      Gynecology = 5, Neurology = 6, Orthopedics = 7, Ophthalmology = 8, ENT = 9] : ";
		Specialization = clsInputValidate::ReadShortNumberBetween(1, 9);

		clsDoctors::FindBySpecialization(Specialization , vDoctors);

	}

	static void _PrintCardDoctor(clsDoctors Doctor) {
		cout << setw(8) << left << "";
		cout << "| " << setw(17) << left << Doctor.FullName();
		cout << "| " << setw(27) << left << Doctor.GetWorkingDaysText();
		cout << "| " << setw(9) << left << Doctor.GetWorkingHoursStart();
		cout << "| " << setw(9) << left << Doctor.GetWorkingHoursEnd();
		cout << "| " << setw(14) << left << Doctor.GetClinicNumberText();
		cout << "| " << setw(15) << left << Doctor.GetSpecializationText();
		cout << "|" << endl;
	}

public:
	static void ShowDoctorsBySpecialization() {

		vector<clsDoctors>vDoctors = clsDoctors::GetAllDoctors();
		short Specialization;

		_ReadSpecialization(Specialization , vDoctors);

		system("cls");
		string Title = "\tSpecialization List Screen" ;
		string SubTitle = "\t  (" + to_string(vDoctors.size()) + ") Specialization(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "\n\t_______________________________________________________";
		cout << "_________________________________________________\n" << endl;

		cout << setw(8) << left << "";
		cout << "| " << left << setw(17) << "Full Name";
		cout << "| " << left << setw(27) << "Working Days";
		cout << "| " << left << setw(9) << "W.H.Start";
		cout << "| " << left << setw(9) << "W.H.End";
		cout << "| " << left << setw(14) << "Clinic Number ";
		cout << "| " << left << setw(15) << "Specialization";
		cout << "|" << endl;

		cout << setw(8) << left << "\n\t_______________________________________________________";
		cout << "_________________________________________________\n" << endl;

		if (vDoctors.size() == 0) {
			cout << "\t\t\t\tNo Specialization Available In the System!";

		}
		else {
			for (clsDoctors& D : vDoctors) {
				_PrintCardDoctor(D);
			}
		}
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________________\n" << endl;

	}

};

