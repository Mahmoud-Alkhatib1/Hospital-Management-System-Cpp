#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsInvoice.h"

class clsDeleteInvoiceScreen : protected clsScreen, clsPatients
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



public:
    static void ShowDeleteInvoiceScreen() {
        _DrawScreenHeader("\t  Delete Invoice");

        vector<clsInvoice> vInvoices = clsInvoice::GetAllInvoices();
        if (vInvoices.empty()) {
            cout << "\n\t No Invoices Found!\n";
            return;
        }

        cout << "\nEnter Invoice ID: ";

        short InvoiceID = clsInputValidate::ReadShortNumber();

        clsInvoice DeleteInvoice = clsInvoice::Find(InvoiceID);

        while (DeleteInvoice.IsEmpty()) {
            cout << "\n\t\t Invoice with ID (" << InvoiceID << ") Not Found! , Please Enter InvoiceID : ";
            InvoiceID = clsInputValidate::ReadShortNumber();
            DeleteInvoice = clsInvoice::Find(InvoiceID);
        }

        _PrintInvoiceCard(DeleteInvoice);

        char Choice = 'y';
        cout << "\nDo you want to delete the invoice ? [Y/N] : ";
        cin >> Choice;
        if (Choice == 'Y' || Choice == 'y') {
            if (DeleteInvoice.Delete()) {
                cout << "\n\t  Invoice Deleted successfully!\n"; 
            }
            else{
                cout << "\n\t Error: Failed to delete invoice!\n";
            }
        }
    }
};

