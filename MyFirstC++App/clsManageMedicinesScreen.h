#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsAddNewMedicineScreen.h"
#include "clsFindMedicineScreen.h"
#include "clsUpdateMedicineScreen.h"
#include "clsDeleteMedicineScreen.h"
#include "clsAllMedicinesScreen.h"

class clsManageMedicinesScreen : protected clsScreen
{
private:
    enum enManageMedicinesOptions {
        eAddNewMedicine = 1,
        eFindMedicine = 2,
        eUpdateMedicine = 3,
        eDeleteMedicine = 4,
        eShowAllMedicines = 5,
        eBackToMainMenu = 6
    };

    static short _ReadManageMedicinesOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6);
        return Choice;
    }

    static void _GoBackToManageMedicinesMenu() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Medicines Menu...\n";
        system("pause>0");
        ShowManageMedicinesMenu();
    }

    static void _ShowAddNewMedicineScreen() {
        clsAddNewMedicineScreen::ShowAddNewMedicineScreen();
    }

    static void _ShowFindMedicineScreen() {
        clsFindMedicineScreen::ShowFindMedicineScreen();
    }

    static void _ShowUpdateMedicineScreen() {
        clsUpdateMedicineScreen::ShowUpdateMedicineScreen();
    }

    static void _ShowDeleteMedicineScreen() {
        clsDeleteMedicineScreen::ShowDeleteMedicineScreen();
    }

    static void _ShowAllMedicinesScreen() {
        clsAllMedicinesScreen::ShowAllMedicines();
    }

    static void _PerformManageMedicinesOption(enManageMedicinesOptions Option) {
        switch (Option) {
        case enManageMedicinesOptions::eAddNewMedicine:
            system("cls");
            _ShowAddNewMedicineScreen();
            _GoBackToManageMedicinesMenu();
            break;
        case enManageMedicinesOptions::eFindMedicine:
            system("cls");
            _ShowFindMedicineScreen();
            _GoBackToManageMedicinesMenu();
            break;
        case enManageMedicinesOptions::eUpdateMedicine:
            system("cls");
            _ShowUpdateMedicineScreen();
            _GoBackToManageMedicinesMenu();
            break;
        case enManageMedicinesOptions::eDeleteMedicine:
            system("cls");
            _ShowDeleteMedicineScreen();
            _GoBackToManageMedicinesMenu();
            break;
        case enManageMedicinesOptions::eShowAllMedicines:
            system("cls");
            _ShowAllMedicinesScreen();
            _GoBackToManageMedicinesMenu();
            break;
        case enManageMedicinesOptions::eBackToMainMenu:
            system("cls");
            break;
        }
    }

public:
    static void ShowManageMedicinesMenu() {
        system("cls");
        _DrawScreenHeader("\t\tManage Medicines");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Medicines Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Add New Medicine.\n";
        cout << setw(37) << left << "" << "\t[2] Find Medicine.\n";
        cout << setw(37) << left << "" << "\t[3] Update Medicine Info.\n";
        cout << setw(37) << left << "" << "\t[4] Delete Medicine.\n";
        cout << setw(37) << left << "" << "\t[5] Show All Medicines.\n";
        cout << setw(37) << left << "" << "\t[6] Back to Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformManageMedicinesOption((enManageMedicinesOptions)_ReadManageMedicinesOption());
    }
};

