#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMedicine.h"
#include <iomanip>

class clsAddNewMedicineScreen : protected clsScreen
{
private:
	static void _ReadMedicine(clsMedicine & NewMedicine) {
		cout << "\n\nMedicine Name : ";
		NewMedicine.Name = clsInputValidate::ReadString();

		while (clsMedicine::IsMedicineExists(NewMedicine.Name)) {
			cout << "This medicine already exists , Medicine Name : ";
			NewMedicine.Name = clsInputValidate::ReadString();
		}

		cout << "\n\nCategory : ";
		NewMedicine.Category = clsInputValidate::ReadString();

		cout << "\n\nPrice : ";
		NewMedicine.Price = clsInputValidate::ReadDblNumber();
		
		cout << "\n\nQuantity : ";
		NewMedicine.Quantity = clsInputValidate::ReadIntNumber();

	}


public:
	static void ShowAddNewMedicineScreen() {
		_DrawScreenHeader("\t  Add New Medicine");

		cout << "\nPlease, Add a new Medicine : \n\n";

		vector<clsMedicine>vMedicines = clsMedicine::GetAllMedicine();
		short MedicineID;
		if (!vMedicines.empty()) {
			MedicineID = vMedicines.back().MedicineID + 1;
		}
		else {
			MedicineID = 1;
		}

		clsMedicine NewMedicine = clsMedicine::GetAddNewMedicineObject(MedicineID);

		cout << "Medicine ID : " << MedicineID;

		_ReadMedicine(NewMedicine);

		char More = 'y';
		cout << "\n\nAre you sure you have saved the new Medicine's data ? [Y/N] : ";
		cin >> More;
		clsMedicine::enSaveResults SaveResult;

		if (More == 'Y' || More == 'y') {
			SaveResult = NewMedicine.Save();
			switch (SaveResult) {
			case clsMedicine::enSaveResults::svSucceeded:
				cout << "\n\n  Medicine Added Successfuly... \n";
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

