#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsInvoice.h"
#include "clsPatients.h"
#include "clsDoctors.h"

class clsUpdateInvoiceScreen : protected clsScreen , clsPatients
{
private:
    static void _PrintInvoiceCard(clsInvoice Invoice) {
        clsPatients::stPatient Patient = clsPatients::Find(Invoice.GetPatientID());
        clsDoctors Doctor = clsDoctors::FindDoctorID(Invoice.GetDoctorID());

        cout << "\n===========================================\n";
        cout << "         Current Invoice Details\n";
        cout << "===========================================\n";
        cout << "Invoice ID      : " << Invoice.GetInvoiceID() << endl;
        cout << "Date            : " << Invoice.GetDate() << endl;
        cout << "Patient Name    : " << Patient.FullName << " (ID: " << Patient.PatientID << ")" << endl;
        cout << "Doctor Name     : " << Doctor.GetFullName() << " (ID: " << Doctor.GetDoctorID() << ")" << endl;
        cout << "Appointment ID  : " << Invoice.GetAppointmentID() << endl;
        cout << "Consultation Fee: $" << Invoice.GetConsultationFee() << endl;
        cout << "Medicines Cost  : $" << Invoice.GetMedicinesCost() << endl;
        cout << "Total           : $" << Invoice.GetTotal() << endl;
        cout << "Payment Method  : " << Invoice.GetPaymentMethodText() << endl;
        cout << "===========================================\n";
    }

    static void _PrintUpdatedTotals(clsInvoice Invoice) {
        cout << "\n===========================================\n";
        cout << "         Updated Invoice Details\n";
        cout << "===========================================\n";
        cout << "Medicines Cost  : $" << Invoice.GetMedicinesCost() << endl;
        cout << "Total           : $" << Invoice.GetTotal() << endl;
        cout << "Payment Method  : " << Invoice.GetPaymentMethodText() << endl;
        cout << "===========================================\n";
    }

public:
    static void ShowUpdateInvoiceScreen() {
        _DrawScreenHeader("\t  Update Invoice");

        vector<clsInvoice> vInvoices = clsInvoice::GetAllInvoices();
        if (vInvoices.empty()) {
            cout << "\n\t No Invoices Found!\n";
            cout << "\n\tPress any key to go back...\n";
            system("pause>0");
            return;
        }

        short InvoiceID;
        cout << "\nPlease, Enter Invoice ID: ";
        InvoiceID = clsInputValidate::ReadShortNumber();

        while (!clsInvoice::IsInvoiceExists(InvoiceID)) {
            cout << "\n\t Invoice not found! Please enter another ID: ";
            InvoiceID = clsInputValidate::ReadShortNumber();
        }

        clsInvoice UpdateInvoice = clsInvoice::Find(InvoiceID);
        _PrintInvoiceCard(UpdateInvoice);

        short Choice;
        cout << "\nWhat would you like to update?\n";
        cout << "[1] Medicines Cost\n";
        cout << "[2] Payment Method\n";
        cout << "[3] Cancel\n";
        cout << "\nEnter your choice (1-3): ";
        Choice = clsInputValidate::ReadShortNumberBetween(1, 3);

        if (Choice == 3) {
            cout << "\n\tOperation cancelled.\n";
            return;
        }

        switch (Choice) {
        case 1: {
            double NewMedicinesCost;
            cout << "\nEnter new Medicines Cost: $";
            NewMedicinesCost = clsInputValidate::ReadDblNumber();
            UpdateInvoice.SetMedicinesCost(NewMedicinesCost);
            break;
        }
        case 2: {
            UpdateInvoice.PaymentMethod = clsInvoice::ReadPaymentMethod();
            break;
        }
        }

        _PrintUpdatedTotals(UpdateInvoice);

        char Confirm;
        cout << "\nAre you sure you want to save the changes? [Y/N]: ";
        cin >> Confirm;

        if (Confirm == 'Y' || Confirm == 'y') {
            clsInvoice::enSaveResults SaveResult = UpdateInvoice.Save();
            switch (SaveResult) {
            case clsInvoice::enSaveResults::svSucceeded:
                cout << "\n\t Invoice Updated Successfully!\n";
                break;
            case clsInvoice::enSaveResults::svFaildEmptyObject:
                cout << "\n\t Error: Invoice was not saved because it's empty!\n";
                break;
            case clsInvoice::enSaveResults::svFaildIDExists:
                cout << "\n\t Error: Invoice ID already exists!\n";
                break;
            }
        }
        else {
            cout << "\n\tOperation cancelled.\n";
        }

    }
};