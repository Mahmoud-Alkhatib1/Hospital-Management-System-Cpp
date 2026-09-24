#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsAddNewPatient.h"
#include "clsFindPatient.h"
#include "clsUpdatePatient.h"
#include "clsDeletePatient.h"
#include "clsAllPatient.h"
#include "clsPatientMedicalHistory.h"

class clsManagePatient : protected clsScreen
{
private:

    static short _ReadManagePatientOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 7]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 7, "Enter Number between 1 to 7? ");
        return Choice;
    }

    enum enManagePatientOptions {
        eAddNewPatient = 1, eFindPatient = 2, eUpdatePatientInfo = 3, eDeletePatient = 4,
        eShowAllPatients = 5, eShowPatientMedicalHistory = 6, eBackToMainMenu = 7
    };

    static void _GoBackToManagePatient() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Manage Patient...\n";
        system("pause>0");
        ShowManagePatients();
    }

    static void _ShowAddNewPatientToFile() {
        clsAddNewPatient::ShowAddNewPatientToFile();
    }

    static void _ShowFindPatientToFile() {
        clsFindPatient::ShowFindPatient();
    }

    static void _ShowUpdatePatientInfo() {
        clsUpdatePatient::ShowUpdatePatientInfo();
    }

    static void _ShowDeletePatient() {
        clsDeletePatient::ShowDeletePatient();
    }

    static void _ShowAllPatients() {
        clsAllPatient::ShowAllPatients();
    }

    static void _ShowPatientMedicalHistory() {
        clsPatientMedicalHistory::ShowPatientMedicalHistory();
    }

    static void _PerfromManagePatientOption(enManagePatientOptions ManagePatientOptions) {
        switch (ManagePatientOptions) {
        case enManagePatientOptions::eAddNewPatient:
            system("cls");
            _ShowAddNewPatientToFile();
            _GoBackToManagePatient();
            break;
        case enManagePatientOptions::eFindPatient:
            system("cls");
            _ShowFindPatientToFile();
            _GoBackToManagePatient();
            break;
        case enManagePatientOptions::eUpdatePatientInfo:
            system("cls");
            _ShowUpdatePatientInfo();
            _GoBackToManagePatient();
        case enManagePatientOptions::eDeletePatient:
            system("cls");
            _ShowDeletePatient();
            _GoBackToManagePatient();
            break;
        case enManagePatientOptions::eShowAllPatients:
            system("cls");
            _ShowAllPatients();
            _GoBackToManagePatient();
            break;
        case enManagePatientOptions::eShowPatientMedicalHistory:
            system("cls");
            _ShowPatientMedicalHistory();
            _GoBackToManagePatient();
        case enManagePatientOptions::eBackToMainMenu:
            system("cls");
            break;
        }
    }

public:

    static void ShowManagePatients() {
        //if  Õﬁﬁ ≈–« ﬂ«‰ Â‰«ﬂ „—÷Ï «Ê ·« 
        system("cls");
        _DrawScreenHeader("\t  Manage Patient");

        cout << setw(37) << left << "" << "===========================================\n\n";

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Add New Patient.\n";
        cout << setw(37) << left << "" << "\t[2] Find Patient.\n";
        cout << setw(37) << left << "" << "\t[3] Update Patient Info.\n";
        cout << setw(37) << left << "" << "\t[4] Delete Patient.\n";
        cout << setw(37) << left << "" << "\t[5] Show List All Patients.\n";
        cout << setw(37) << left << "" << "\t[6] Show Patient Medical History.\n";
        cout << setw(37) << left << "" << "\t[7] Back to Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromManagePatientOption((enManagePatientOptions)_ReadManagePatientOption());

    }
};
