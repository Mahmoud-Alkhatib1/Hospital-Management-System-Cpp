#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsAddNewDoctor.h"
#include "clsFindDoctor.h"
#include "clsUpdateDoctor.h"
#include "clsDeleteDoctor.h"
#include "clsShowAllDoctors.h"
#include "clsShowDoctorsBySpecialization.h"

class clsManageDoctors : protected clsScreen
{
private:

    static short _ReadManageDoctorOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 7]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 7, "Enter Number between 1 to 7? ");
        return Choice;
    }

    enum enManageDoctorOptions {
        eAddNewDoctor = 1, eFindDoctor = 2, eUpdateDoctorInfo = 3, eDeleteDoctor = 4,
        eShowAllDoctors = 5, eShowDoctorsBySpecialization = 6, eBackToMainMenu = 7
    };

    static void _GoBackToManageDoctor() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Doctor Menu...\n";
        system("pause>0");
        ShowManageDoctors();
    }

    static void _ShowAddNewDoctorToFile() {
        clsAddNewDoctor::ShowAddNewDoctorToFile();

    }

    static void _ShowFindDoctorToFile() {
        clsFindDoctor::ShowFindDoctorScreen();
    }

    static void _ShowUpdateDoctorInfo() {
        clsUpdateDoctor::ShowUpdateDoctor();
    }

    static void _ShowDeleteDoctor() {
        clsDeleteDoctor::ShowDeleteDoctor();
    }

    static void _ShowAllDoctors() {
        clsShowAllDoctors::ShowAllDoctors();
    }

    static void _ShowDoctorsBySpecialization() {
        clsShowDoctorsBySpecialization::ShowDoctorsBySpecialization();
    }

    static void _PerfromManageDoctorOption(enManageDoctorOptions ManageDoctorOptions) {
        switch (ManageDoctorOptions) {
        case enManageDoctorOptions::eAddNewDoctor:
            system("cls");
            _ShowAddNewDoctorToFile();
            _GoBackToManageDoctor();
            break;
        case enManageDoctorOptions::eFindDoctor:
            system("cls");
            _ShowFindDoctorToFile();
            _GoBackToManageDoctor();
        case enManageDoctorOptions::eUpdateDoctorInfo:
            system("cls");
            _ShowUpdateDoctorInfo();
            _GoBackToManageDoctor();
            break;
        case enManageDoctorOptions::eDeleteDoctor:
            system("cls");
            _ShowDeleteDoctor();
            _GoBackToManageDoctor();
            break;
        case enManageDoctorOptions::eShowAllDoctors:
            system("cls");
            _ShowAllDoctors();
            _GoBackToManageDoctor();
            break;
        case enManageDoctorOptions::eShowDoctorsBySpecialization:
            system("cls");
            _ShowDoctorsBySpecialization();
            _GoBackToManageDoctor();
            break;
        case enManageDoctorOptions::eBackToMainMenu:
            system("cls");
            break;
        }
    }

public:

    static void ShowManageDoctors() {

        system("cls");
        _DrawScreenHeader("\t  Doctor Menu");

        cout << setw(37) << left << "" << "===========================================\n\n";

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Add New Doctor.\n";
        cout << setw(37) << left << "" << "\t[2] Find Doctor\n";
        cout << setw(37) << left << "" << "\t[3] Update Doctor Info.\n";
        cout << setw(37) << left << "" << "\t[4] Delete Doctort.\n";
        cout << setw(37) << left << "" << "\t[5] Show All Doctors.\n";
        cout << setw(37) << left << "" << "\t[6] Show Doctors By Specialization.\n";
        cout << setw(37) << left << "" << "\t[7] Back to Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromManageDoctorOption((enManageDoctorOptions)_ReadManageDoctorOption());

    }
};
