#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMedicine.h"
#include <iomanip>

class clsFindMedicineScreen : protected clsScreen
{
private:
    static void _PrintMedicineCard(clsMedicine Medicine) {
        cout << "\n===========================================\n";
        cout << "           Medicine Details\n";
        cout << "===========================================\n";
        cout << "Medicine ID      : " << Medicine.GetMedicineID() << endl;
        cout << "Name             : " << Medicine.GetName() << endl;
        cout << "Category         : " << Medicine.GetCategory() << endl;
        cout << "Price            : $" << Medicine.GetPrice() << endl;
        cout << "Quantity         : " << Medicine.GetQuantity() << endl;
        cout << "===========================================\n";
    }

public:
    static void ShowFindMedicineScreen() {
        _DrawScreenHeader("\t  Find Medicine");

        short MedicineID;
        cout << "Please , Enter your Medicine : ";
        MedicineID = clsInputValidate::ReadShortNumber();

        while (!clsMedicine::IsMedicineExists(MedicineID)) {
            cout << "We couldn't find the medicineID , please enter a medicineID : ";
            MedicineID = clsInputValidate::ReadShortNumber();

        }
        clsMedicine Medicine = clsMedicine::FindMedicineID(MedicineID);

        _PrintMedicineCard(Medicine);
    }
};