#pragma once
#include "clsScreen.h"
#include "clsInvoice.h"
#include "clsPatients.h"
#include "clsDoctors.h"
#include <iomanip>

class clsAllInvoicesScreen : protected clsScreen , clsPatients
{
private:
    static void _PrintInvoicesTableHeader() {
        cout << setw(8) << left << "";
        cout << "=======================================================================================================\n";
        cout << setw(8) << left << "";
        cout << "| " << setw(4) << left << "ID";
        cout << "| " << setw(12) << left << "Date";
        cout << "| " << setw(29) << left << "Patient Name";
        cout << "| " << setw(25) << left << "Doctor Name";
        cout << "| " << setw(12) << left << "Total";
        cout << "| " << setw(8) << left << "Payment";
        cout << "|\n";
        cout << setw(8) << left << "";
        cout << "=======================================================================================================\n";
    }

    static void _PrintInvoiceRecord(clsInvoice Invoice) {
        // ÌáÈ ÈíÇäÇÊ ÇáãÑíÖ æÇáØÈíÈ
        stPatient Patient = clsPatients::Find(Invoice.GetPatientID());
        clsDoctors Doctor = clsDoctors::FindDoctorID(Invoice.GetDoctorID());

        cout << setw(8) << left << "";
        cout << "| " << setw(4) << left << Invoice.GetInvoiceID();
        cout << "| " << setw(12) << left << Invoice.GetDate();
        cout << "| " << setw(29) << left << (Patient.FullName.length() > 22 ? Patient.FullName.substr(0, 19) + "..." : Patient.FullName);
        cout << "| " << setw(25) << left << (Doctor.GetFullName().length() > 22 ? Doctor.GetFullName().substr(0, 19) + "..." : Doctor.GetFullName());
        cout << "| " << setw(12) << left << ("$" + to_string(Invoice.GetTotal()));
        cout << "| " << setw(8) << left << Invoice.GetPaymentMethodText();
        cout << "|\n";
    }

    static void _PrintInvoicesTableFooter(int Count) {
        cout << setw(8) << left << "";
        cout << "=======================================================================================================\n";
        cout << "\n\t\tTotal Invoices: " << Count << endl;
    }

public:
    static void ShowAllInvoices() {
        _DrawScreenHeader("\t  All Invoices List");

        vector<clsInvoice> vInvoices = clsInvoice::GetAllInvoices();

        if (vInvoices.empty()) {
            cout << "\n\t\t No Invoices Found!\n";
            cout << "\n\tPress any key to go back...\n";
            system("pause>0");
            return;
        }

        _PrintInvoicesTableHeader();

        for (clsInvoice& Inv : vInvoices) {
            if (!Inv.IsEmpty()) {
                _PrintInvoiceRecord(Inv);
            }
        }

        _PrintInvoicesTableFooter(vInvoices.size());

    }
};
