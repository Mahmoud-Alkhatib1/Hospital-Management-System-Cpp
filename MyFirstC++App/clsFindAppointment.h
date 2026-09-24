#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsAppointment.h"
#include "clsInputValidate.h"
#include "clsPatients.h"
#include "clsDoctors.h"
#include <iomanip>

class clsFindAppointment : protected clsScreen , clsPatients , clsDoctors
{
private:
	static stPatient _ReadPatientName() {
		string FullName;
		cout << "Please ,Enter Your Patient Name : ";
		FullName = clsInputValidate::ReadString();
		stPatient Patient = clsPatients::FindByName(FullName);

        while (Patient.PatientID == 0) {  
            cout << "\nPatient Not Found, choose other Patient Name: ";
            FullName = clsInputValidate::ReadString();
            Patient = clsPatients::FindByName(FullName);  
        }
		
		return Patient;
	}

    static void _PrintAppointmentsTable(vector<clsAppointment> vAppointments) {

        if (vAppointments.empty()) {
            cout << "\n\t\tNo Appointments Found!\n";
            return;
        }

        cout << "\n" << setw(8) << left << "";
        cout << "_________________________________________________________________________________\n";
        cout << setw(8) << left << "";
        cout << "| " << setw(5) << left << "ID";
        cout << "| " << setw(12) << left << "Date";
        cout << "| " << setw(10) << left << "Time";
        cout << "| " << setw(25) << left << "Doctor Name";
        cout << "| " << setw(18) << left << "Specialization";
        cout << "|\n";
        cout << setw(8) << left << "";
        cout << "_________________________________________________________________________________\n";

        for (clsAppointment& A : vAppointments) {

            // ÌáÈ ÈíÇäÇÊ ÇáØÈíÈ ÈÇÓÊÎÏÇã DoctorID
            clsDoctors Doctor = clsDoctors::FindDoctorID(A.DoctorID);

            cout << setw(8) << left << "";
            cout << "| " << setw(5) << left << A.AppointmentID();
            cout << "| " << setw(12) << left << A.GetDate();
            cout << "| " << setw(10) << left << A.GetTime();
            cout << "| " << setw(25) << left << Doctor.GetFullName();
            cout << "| " << setw(18) << left << Doctor.GetSpecializationText();
            cout << "|\n";
        }

        cout << setw(8) << left << "";
        cout << "_________________________________________________________________________________\n";
        cout << "\n\t\tTotal Appointments: " << vAppointments.size() << endl;
    }

public:
	
	static void ShowFindAppointment() {
		_DrawScreenHeader("\t  Find Appointment");

		stPatient PatientName = _ReadPatientName();

		vector<clsAppointment> FindByPatient = clsAppointment::FindByPatientID(PatientName.PatientID);

        _PrintAppointmentsTable(FindByPatient);

	}

};

