#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsAppointment.h"
#include "clsInputValidate.h"
#include "clsPatients.h"
#include "clsDoctors.h"
#include <iomanip>
#include "clsString.h";

class clsShowDoctorAppointments : protected clsScreen, clsPatients, clsDoctors
{
private:
	
	static void _PrintDoctorDateOrAllAppointment(short DoctorID ,vector<clsAppointment>vAppointments) {
		cout << "\n[1] Date (DD/MM/YYYY)\n";
		cout << "[2] for all appointments\n";

		cout << "\nEnter Date (DD/MM/YYYY) or 0 for all appointments: [1]/[2]";
		short More = clsInputValidate::ReadShortNumberBetween(1, 2);
		clsDoctors Doctor = clsDoctors::FindDoctorID(DoctorID);


		short Counter = 0;

		if (More == 1) {
			cout << "Please , enter your Date (DD/MM/YYYY) : ";
			string Date = clsInputValidate::ReadString();

			cout << "\n===========================================================\n";
			cout << "     Appointments for " << Doctor.GetFullName() << " on " << Date << endl;

			// ØÈÇÚÉ ÑÃÓ ÇáÌÏæá
			cout << "===========================================================\n";
			cout << "| " << setw(12) << left << "Time";
			cout << "| " << setw(30) << left << "Patient Name";
			cout << "| " << setw(10) << left << "Patient ID";
			cout << "|\n";
			cout << "===========================================================\n";


			for (clsAppointment& App : vAppointments) {
				if (App.DoctorID == DoctorID) {
					if (App.Date == Date) {
						Counter++;
							clsPatients::stPatient Patient = clsPatients::Find(App.GetPatientID());
							cout << "| " << setw(12) << left << App.GetTime();
							cout << "| " << setw(30) << left << Patient.FullName;
							cout << "| " << setw(10) << left << Patient.PatientID;
							cout << "|\n";
					}
				}
			}
			cout << "===========================================================\n";
			cout << "\n\t\tTotal Appointments: " << Counter << endl;
		}
		else {
			cout << "\n===========================================================\n";
			cout << "     All Appointments for " << Doctor.GetFullName() << endl;

			// ØÈÇÚÉ ÑÃÓ ÇáÌÏæá
			cout << "===========================================================\n";
			cout << "| " << setw(12) << left << "Time";
			cout << "| " << setw(30) << left << "Patient Name";
			cout << "| " << setw(10) << left << "Patient ID";
			cout << "|\n";
			cout << "===========================================================\n";


			for (clsAppointment& App : vAppointments) {
				if (App.DoctorID == DoctorID) {
					clsPatients::stPatient Patient = clsPatients::Find(App.GetPatientID());
					Counter++;
					cout << "| " << setw(12) << left << App.GetTime();
					cout << "| " << setw(30) << left << Patient.FullName;
					cout << "| " << setw(10) << left << Patient.PatientID;
					cout << "|\n";
				}
			}
			cout << "===========================================================\n";
			cout << "\n\t\tTotal Appointments: " << Counter << endl;
		}
		
	}

	static short _ReadDoctorID(vector<clsDoctors> DoctorsName) {
		cout << "Select Doctors : \n\n";

		for (clsDoctors& Do : DoctorsName) {
			cout << "[" << Do.GetDoctorID() << "] " << Do.GetFullName() << " , Specialist in "
				<< Do.GetSpecializationText() << endl;
		}

		cout << "\n\nEnter Doctor ID : ";
		short DoctorID = clsInputValidate::ReadShortNumber();
		for (clsDoctors& Do : DoctorsName) {
			if (DoctorID == Do.GetDoctorID()) {
				cout << "\nDoctor Selected : " << Do.GetFullName() << "(ID : " << Do.GetDoctorID() << ")\n";
			}
		}

		return DoctorID;
	}


public:
	static void ShowDoctorAppointment() {

		_DrawScreenHeader("\t  Show Doctor Appointment");
		vector<clsAppointment>vAppointments = clsAppointment::GetAllAppointment();

		vector<clsDoctors> DoctorsName = clsDoctors::GetAllDoctors();

		short DoctorID = _ReadDoctorID(DoctorsName);

		_PrintDoctorDateOrAllAppointment(DoctorID, vAppointments);
	}
	
};

