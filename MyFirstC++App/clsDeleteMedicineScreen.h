#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMedicine.h"
#include <iomanip>

class clsDeleteMedicineScreen : protected clsScreen
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
	static void ShowDeleteMedicineScreen() {
		_DrawScreenHeader("\t  Delete Medicine");

		cout << "\nPlease, Enter a MedicineID : ";


		vector<clsMedicine>vMedicines = clsMedicine::GetAllMedicine();

		if (vMedicines.empty()) {
			cout << "\n\t No medicines found in the system!\n";
			return;
		}

		cout << "\nPlease, Enter Medicine ID: ";
		short MedicineID = clsInputValidate::ReadShortNumber();

		while (!clsMedicine::IsMedicineExists(MedicineID)) {
			cout << "We couldn't find medicineID, please enter medicineID : ";
			MedicineID = clsInputValidate::ReadShortNumber();
		}

		clsMedicine DeleteMedicine = clsMedicine::FindMedicineID(MedicineID);


		_PrintMedicineCard(DeleteMedicine);

		char More = 'y';
		cout << "\n\nAre you sure you want to delete this medicine? [Y/N]: ";
		cin >> More;

		if (More == 'Y' || More == 'y') {
			if (DeleteMedicine.Delete2()) {
				cout << "\n\t Medicine Deleted Successfully!\n";
			}
			else {
				cout << "\n\t Error: Failed to delete medicine!\n";
			}
		
		}
	}
};

