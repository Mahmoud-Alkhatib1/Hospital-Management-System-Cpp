#pragma once
#include "clsScreen.h"
#include "clsMedicine.h"
#include <iomanip>

class clsAllMedicinesScreen : protected clsScreen
{
private:
    static void _PrintMedicineTableHeader() {
        cout << setw(8) << left << "";
        cout << "========================================================================\n";
        cout << setw(8) << left << "";
        cout << "| " << setw(5) << left << "ID";
        cout << "| " << setw(20) << left << "Name";
        cout << "| " << setw(15) << left << "Category";
        cout << "| " << setw(11) << left << "Price";
        cout << "| " << setw(10) << left << "Quantity";
        cout << "|\n";
        cout << setw(8) << left << "";
        cout << "========================================================================\n";
    }

    static void _PrintMedicineRecord(clsMedicine Medicine) {
        cout << setw(8) << left << "";
        cout << "| " << setw(5) << left << Medicine.GetMedicineID();
        cout << "| " << setw(20) << left << Medicine.GetName();
        cout << "| " << setw(15) << left << Medicine.GetCategory();
        cout << "| " << setw(11) << left << "$" + to_string(Medicine.GetPrice());
        cout << "| " << setw(10) << left << Medicine.GetQuantity();
        cout << "|\n";
    }

public:
    static void ShowAllMedicines() {

        vector<clsMedicine> vMedicines = clsMedicine::GetAllMedicine();

        string SubTitle = "\t    (" + to_string(vMedicines.size()) + ") Medicine(s).";

        _DrawScreenHeader("\t  All Medicines List" , SubTitle);


        _PrintMedicineTableHeader();

        if (vMedicines.size() != 0) {
            for (clsMedicine& M : vMedicines) {
                _PrintMedicineRecord(M); 
            }
        }
        else {
            cout << "Not Found Medicine... \n\n";
        }
        cout << setw(8) << left << "";
        cout << "========================================================================\n";

        cout << "\n\t\t\t\tTotal Medicines : " << vMedicines.size() << endl;

    }
};
