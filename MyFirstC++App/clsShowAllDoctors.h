#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsDoctors.h"

class clsShowAllDoctors : clsScreen
{
private:
	static void _PrintCardDoctor(clsDoctors Doctor) {
		cout << setw(8) << left << "";
		cout << "| " << setw(5) << left << Doctor.GetDoctorID();
		cout << "| " << setw(20) << left << Doctor.FullName();
		cout << "| " << setw(12) << left << Doctor.Phone;
		cout << "| " << setw(20) << left << Doctor.Email;
		cout << "| " << setw(20) << left << Doctor.GetSpecializationText();
		cout << "|" << endl;
	}

	static void _InformetionDoctor(clsDoctors Doctor) {
		cout << setw(8) << left << "";
		cout << "| " << setw(5) << left << Doctor.GetDoctorID();
		cout << "| " << setw(6) << left << Doctor.GetConsultationFee();
		cout << "| " << setw(27) << left << Doctor.GetWorkingDaysText();
		cout << "| " << setw(10) << left << Doctor.GetWorkingHoursStart();
		cout << "| " << setw(10) << left << Doctor.GetWorkingHoursEnd();
		cout << "| " << setw(15) << left << Doctor.GetClinicNumberText();
		cout << "|" << endl;
	}

public:

	static void ShowAllDoctors() {

		vector<clsDoctors>vDoctors = clsDoctors::GetAllDoctors();

		string Title = "\t  Doctor List Screen";
		string SubTitle = "\t    (" + to_string(vDoctors.size()) + ") Doctor(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "";
		cout << "| " << left << setw(5) << "ID";
		cout << "| " << left << setw(20) << "Full Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(20) << "Specialization";
		cout << "|" << endl;

		cout << setw(8) << left << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vDoctors.size() == 0) {
			cout << "\t\t\t\tNo Doctor Available In the System!";

		}
		else {
			for (clsDoctors& D : vDoctors) {
				_PrintCardDoctor(D);
			}
		}
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;



		cout << "\t\t\t\t\t\tDoctor information : \n";

		cout << setw(8) << left << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "";
		cout << "| " << left << setw(5) << "ID";
		cout << "| " << left << setw(6) << "Fee";
		cout << "| " << left << setw(27) << "Working Days";
		cout << "| " << left << setw(10) << "W.H.Start";
		cout << "| " << left << setw(10) << "W.H.End";
		cout << "| " << left << setw(15) << "Clinic Number ";
		cout << "|" << endl;

		cout << setw(8) << left << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		for (clsDoctors& D : vDoctors) {

			_InformetionDoctor(D);
		}
		cout << setw(8) << left << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}

};

