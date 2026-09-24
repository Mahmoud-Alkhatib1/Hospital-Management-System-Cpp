#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsInvoice.h"

class clsAddNewInvoiceScreen : protected clsScreen , clsPatients
{
private:

	static short _ReadPatientID(vector<stPatient> vPatients) {
		cout << "Select Patient : \n\n";

		for (stPatient& Pat : vPatients) {
			cout << "[" << Pat.PatientID << "] " << Pat.FullName << endl;
		}
		cout << "\n\nEnter Patient ID : ";
		short PatientID = clsInputValidate::ReadShortNumber();

		for (stPatient& Pa : vPatients) {
			if (PatientID == Pa.PatientID) {

				cout << "\nPatient Selected : " << Pa.FullName << "(ID : " << Pa.PatientID << ")\n";
				break;
			}
		}
		cout << "\n\n";

		return PatientID;
	}

	static short _ReadDoctorID(vector<clsDoctors> vDoctors) {
		cout << "Select Doctors : \n\n";

		for (clsDoctors& Do : vDoctors) {
			cout << "[" << Do.GetDoctorID() << "] " << Do.GetFullName() << " , Specialist in "
				<< Do.GetSpecializationText() << endl;
		}

		cout << "\n\nEnter Doctor ID : ";
		short DoctorID = clsInputValidate::ReadShortNumber();
		for (clsDoctors& Do : vDoctors) {
			if (DoctorID == Do.GetDoctorID()) {
				cout << "\nDoctor Selected : " << Do.GetFullName() << "(ID : " << Do.GetDoctorID() << ")\n";
				
				break;
			}
		}

		return DoctorID;
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
		cout << "| " << setw(20) << left << "Specialization";
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
			cout << "| " << setw(20) << left << Doctor.GetSpecializationText();
			cout << "|\n";
		}

		cout << setw(8) << left << "";
		cout << "_________________________________________________________________________________\n";
		cout << "\n\t\tTotal Appointments: " << vAppointments.size() << endl;
	}

	static short _ReadAppointmentID(vector<clsAppointment>vAppointments , short PatientID ,short DoctorID) {
		vAppointments = clsAppointment::FindByPatientIDAndDoctorID(PatientID, DoctorID);

		_PrintAppointmentsTable(vAppointments);

		cout << "Appointment ID : ";
		short Appointment = clsInputValidate::ReadShortNumber();

		return Appointment;
	}

	static void _ReadInvoice(clsInvoice &vInvoices) {
		
		//Patient Data**************************
		vector<stPatient>vPatients = clsPatients::GetAllPatient();

		vInvoices.PatientID = _ReadPatientID(vPatients);
		stPatient Patient = clsPatients::Find(vInvoices.PatientID);
		//**************************************

		//Doctor Data**************************
		vector<clsDoctors>vDoctors = clsDoctors::GetAllDoctors();
		vInvoices.DoctorID = _ReadDoctorID(vDoctors);
		clsDoctors Doctor = clsDoctors::FindDoctorID(vInvoices.DoctorID);
		//**************************************

		//Appointment Data**************************
		vector<clsAppointment>vAppointments = clsAppointment::GetAllAppointment();
		vInvoices.AppointmentID = _ReadAppointmentID(vAppointments, vInvoices.PatientID, vInvoices.DoctorID);
		//**************************************

		//ConsultationFee***********************
		vInvoices.ConsultationFee = clsDoctors::FindDoctorID(vInvoices.DoctorID).GetConsultationFee();
		//**************************************

		//MedicinesCost*************************
		cout << "\nEnter Medicines Cost: $";
		vInvoices.MedicinesCost = clsInputValidate::ReadDblNumber();
		//**************************************

		//Total*********************************
		vInvoices.Total = vInvoices.ConsultationFee + vInvoices.MedicinesCost;
		cout << "\n\n===========================================\n";
		cout << "Total Amount : $" << vInvoices.Total;
		cout << "\n===========================================\n\n";
		//**************************************

		//PaymentMethod*************************
		vInvoices.PaymentMethod = clsInvoice::ReadPaymentMethod();
		//**************************************


	}

public:
	static void ShowAddNewInvoiceScreen() {
		_DrawScreenHeader("\t  Add New Invoice");

		vector<clsInvoice> vInvoices = clsInvoice::GetAllInvoices();

		short InvoiceID = clsInvoice::GetNewInvoiceID(vInvoices);

		clsInvoice NewInvoice = clsInvoice::GetAddNewInvoiceObject(InvoiceID);

		_ReadInvoice(NewInvoice);

		clsInvoice::enSaveResults SaveResults;

		char Confirm = 'y';

		cout << "\n\nAre you sure you want to save this invoice? [Y/N]: ";
		cin >> Confirm;

		if (Confirm == 'Y' || Confirm == 'y') {
			SaveResults = NewInvoice.Save();
			switch (SaveResults) {
			case clsInvoice::enSaveResults::svSucceeded:
				cout << "\n\t Invoice saved successfully!\n";
				cout << "\t   Invoice ID: " << NewInvoice.GetInvoiceID() << endl;
				break;
			case clsInvoice::enSaveResults::svFaildEmptyObject:
				cout << "\n  Error: Invoice was not saved because it's Empty\n";
				break;
			case clsInvoice::enSaveResults::svFaildIDExists:
				cout << "\n  Error: Invoice was not saved because ID is used!\n";
				break;
			}
		}
	}
};

