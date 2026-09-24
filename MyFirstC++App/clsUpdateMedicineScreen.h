#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMedicine.h"
#include <iomanip>

class clsUpdateMedicineScreen : protected clsScreen
{
private:
	static void _ReadMedicine(clsMedicine& NewMedicine) {
		cout << "\n\nMedicine Name : ";
		NewMedicine.Name = clsInputValidate::ReadString();

		cout << "\n\nCategory : ";
		NewMedicine.Category = clsInputValidate::ReadString();

		cout << "\n\nPrice : ";
		NewMedicine.Price = clsInputValidate::ReadDblNumber();

		cout << "\n\nQuantity : ";
		NewMedicine.Quantity = clsInputValidate::ReadIntNumber();

	}

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
	static void ShowUpdateMedicineScreen() {
		_DrawScreenHeader("\t  Update Medicine");

		cout << "\nPlease, Enter a MedicineID : ";

		vector<clsMedicine>vMedicines = clsMedicine::GetAllMedicine();
		short MedicineID;
		if (!vMedicines.empty()) {
			MedicineID = clsInputValidate::ReadShortNumber();
		}
		else {
			cout << "\nThere is no medication to modify it. \n\n";
			return;
		}

		while (!clsMedicine::IsMedicineExists(MedicineID)) {
			cout << "We couldn't find medicineID, please enter medicineID : ";
			MedicineID = clsInputValidate::ReadShortNumber();
		}

		clsMedicine UpdateMedicine = clsMedicine::FindMedicineID(MedicineID);

		_PrintMedicineCard(UpdateMedicine);


		_ReadMedicine(UpdateMedicine);


		_PrintMedicineCard(UpdateMedicine);

		char More = 'y';
		cout << "\n\nAre you sure you have saved the Update Medicine's data ? [Y/N] : ";
		cin >> More;
		clsMedicine::enSaveResults SaveResult;

		if (More == 'Y' || More == 'y') {
			SaveResult = UpdateMedicine.Save();
			switch (SaveResult) {
			case clsMedicine::enSaveResults::svSucceeded:
				cout << "\n\n  Medicine Updated Successfuly... \n";
				break;
			case clsMedicine::enSaveResults::svFaildEmptyObject:
				cout << "\nError Medicine was not saved because it's Empty";
				break;
			case clsMedicine::enSaveResults::svFaildIDExists:
				cout << "\nError Medicine was not saved because ID is used!\n";
				break;
			}
		}
	}

};

