#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsInvoice.h"
#include "clsPatients.h"
#include "clsDoctors.h"
#include <iomanip>

class clsFindInvoiceScreen : protected clsScreen , clsPatients
{
private:
    
    static void _PrintInvoiceCard(clsInvoice Invoice) {
        // Ã·» »Ì«‰«  «·„—Ì÷ Ê«·ÿ»Ì»
        stPatient Patient = clsPatients::Find(Invoice.GetPatientID());
        clsDoctors Doctor = clsDoctors::FindDoctorID(Invoice.GetDoctorID());

        cout << "\n===========================================\n";
        cout << "           Invoice Details\n";
        cout << "===========================================\n";
        cout << "Invoice ID      : " << Invoice.GetInvoiceID() << endl;
        cout << "Date            : " << Invoice.GetDate() << endl;
        cout << "\nPatient Name    : " << Patient.FullName << " (ID: " << Patient.PatientID << ")" << endl;
        cout << "Doctor Name     : " << Doctor.GetFullName() << " (ID: " << Doctor.GetDoctorID() << ")" << endl;
        cout << "Appointment ID  : " << Invoice.GetAppointmentID() << endl;
        cout << "\n===========================================\n";
        cout << "Consultation Fee: $" << Invoice.GetConsultationFee() << endl;
        cout << "Medicines Cost  : $" << Invoice.GetMedicinesCost() << endl;
        cout << "-------------------------------------------\n";
        cout << "Total           : $" << Invoice.GetTotal() << endl;
        cout << "-------------------------------------------\n";
        cout << "Payment Method  : " << Invoice.GetPaymentMethodText() << endl;
        cout << "===========================================\n";
    }

    static void _PrintInvoicesList(vector<clsInvoice>& vInvoices) {
        if (vInvoices.empty()) {
            cout << "\n\t\t No Invoices Found!\n";
            return;
        }

        cout << "\n===========================================\n";
        cout << "           Invoices List\n";
        cout << "===========================================\n";

        for (clsInvoice& Inv : vInvoices) {
            stPatient Patient = clsPatients::Find(Inv.GetPatientID());
            cout << "| Invoice ID: " << setw(5) << left << Inv.GetInvoiceID();
            cout << " | Date: " << setw(10) << left << Inv.GetDate();
            cout << " | Total: $" << setw(6) << left << Inv.GetTotal();
            cout << " | Patient: " << Patient.FullName << endl;
        }

        cout << "===========================================\n";
        cout << "\n\t\tTotal Invoices: " << vInvoices.size() << endl;
    }

    static short _ReadChoice() {
        cout << "\nFind by: [1] Invoice ID, [2] Patient ID\n";
        cout << "Enter your choice (1 or 2): ";
        return clsInputValidate::ReadShortNumberBetween(1, 2);
    }

    static short _ReadInvoiceID() {
        cout << "\nEnter Invoice ID: ";
        return clsInputValidate::ReadShortNumber();
    }

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

public:
    static void ShowFindInvoiceScreen() {
        _DrawScreenHeader("\t  Find Invoice");

        short Choice = _ReadChoice();

        if (Choice == 1) {
            // «·»ÕÀ »—ﬁ„ «·›« Ê—…
            short InvoiceID = _ReadInvoiceID();
            clsInvoice Invoice = clsInvoice::Find(InvoiceID);

            if (Invoice.IsEmpty()) {
                cout << "\n\t\t Invoice with ID (" << InvoiceID << ") Not Found!\n";
            }
            else {
                _PrintInvoiceCard(Invoice);
            }
        }
        else {
            vector<stPatient> vPatients = clsPatients::GetAllPatient();
            // «·»ÕÀ »—ﬁ„ «·„—Ì÷ (ﬁœ Ì⁄Ìœ ⁄œ… ›Ê« Ì—)
            short PatientID = _ReadPatientID(vPatients);
            
            vector<clsInvoice> vInvoices = clsInvoice::FindByPatientID(PatientID);
            _PrintInvoicesList(vInvoices);
            
        }

    }
};

