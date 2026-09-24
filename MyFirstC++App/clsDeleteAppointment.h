#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsAppointment.h"
#include "clsInputValidate.h"
#include "clsPatients.h"
#include "clsDoctors.h"
#include <iomanip>
#include "clsString.h";

class clsDeleteAppointment : protected clsScreen, clsPatients, clsDoctors
{
private:
	static void _PrintAppointmentDetails(clsAppointment DeleteAppointment) {

		stPatient Patient1 = clsPatients::Find(DeleteAppointment.PatientID);
		clsDoctors Doctor1 = clsDoctors::FindDoctorID(DeleteAppointment.DoctorID);

		cout << "\n\n===========================================\n";
		cout << "        Appointment\n";
		cout << "===========================================\n";
		cout << "| " << setw(12) << left << "Appointment ID : " << DeleteAppointment.AppointmentID() << "\n";
		cout << "| " << setw(12) << left << "Patient Name   : " << Patient1.FullName << "\n";
		cout << "| " << setw(12) << left << "Doctor Name    : " << Doctor1.FullName() << "\n";
		cout << "| " << setw(12) << left << "Date           : " << DeleteAppointment.Date << "\n";
		cout << "| " << setw(12) << left << "Time           : " << DeleteAppointment.Time << "\n";
		cout << "|\n";
		cout << "===========================================\n\n";
	}

public:
	static void ShowDeleteAppointment() {
		_DrawScreenHeader("\t  Delete Appointment");

		vector<clsAppointment>vAppointments = clsAppointment::GetAllAppointment();
		short AppointmentID;
		cout << "Please , Enter Your Appointment : ";
		if (vAppointments.empty()) {
			cout << "\n\t? No appointments found!\n";
			return;
		}
		AppointmentID = clsInputValidate::ReadShortNumberBetween(1, vAppointments.back().AppointmentID());
		clsAppointment DeleteAppointment = clsAppointment::FindAppointmentID(AppointmentID);

		_PrintAppointmentDetails(DeleteAppointment);

		char More = 'y';
		cout << "\n\nAre you sure you want to delete this appointment? [Y/N] : ";
		cin >> More;

		if (More == 'Y' || More == 'y') {
			clsAppointment::Delete(vAppointments, AppointmentID);
			cout << "\n\n  Apointment Deleted Successfuly... \n";
		}
	}
};

