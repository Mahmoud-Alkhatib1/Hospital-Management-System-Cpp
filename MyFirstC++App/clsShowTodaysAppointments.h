#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsAppointment.h"
#include "clsInputValidate.h"
#include "clsPatients.h"
#include "clsDoctors.h"
#include <iomanip>
#include "clsString.h";

class clsShowTodaysAppointments : protected clsScreen, clsPatients, clsDoctors
{
private:
    static void _PrintTodayAppointmentsTable(vector<clsAppointment>& vTodayAppointments) {

        if (vTodayAppointments.empty()) {
            cout << "\n\t\tNo Appointments Today!\n";
            return;
        }

        cout << "\n" << setw(8) << left << "";
        cout << "==================================================================================\n";
        cout << setw(8) << left << "";
        cout << "| " << setw(10) << left << "Time";
        cout << "| " << setw(25) << left << "Patient Name";
        cout << "| " << setw(35) << left << "Doctor Name";
        cout << "|\n";
        cout << setw(8) << left << "";
        cout << "==================================================================================\n";

        for (clsAppointment& App : vTodayAppointments) {

            // ÌáÈ ÈíÇäÇÊ ÇáãÑíÖ
            stPatient Patient = clsPatients::Find(App.GetPatientID());

            // ÌáÈ ÈíÇäÇÊ ÇáØÈíÈ
            clsDoctors Doctor = clsDoctors::FindDoctorID(App.GetDoctorID());

            cout << setw(8) << left << "";
            cout << "| " << setw(10) << left << App.GetTime();
            cout << "| " << setw(25) << left << Patient.FullName;
            cout << "| " << setw(35) << left << Doctor.GetFullName() + " (" + Doctor.GetSpecializationText() + ")";
            cout << "|\n";
        }

        cout << setw(8) << left << "";
        cout << "==================================================================================\n";
        cout << "\n\t\tTotal Appointments Today: " << vTodayAppointments.size() << endl;
    }


public:
	static void ShowTodaysAppointments() {
		_DrawScreenHeader("\t  ShowTodaysAppointments");
		clsDate CurrentDate1 = clsDate::GetSystemDate();// ÇáÊÇÑíÎ ÇáÍÇáí

		vector<clsAppointment>vAppointments = clsAppointment::GetAllAppointment();

		vector <clsAppointment> vTodayAppointments;
        string TodayStr = clsDate::DateToString(CurrentDate1);
        for (clsAppointment& App : vAppointments) {
            if (App.GetDate() == TodayStr) {
                vTodayAppointments.push_back(App);
            }
        }
		
        _PrintTodayAppointmentsTable(vTodayAppointments);

	}
};

