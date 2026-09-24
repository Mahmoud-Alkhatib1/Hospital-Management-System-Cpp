#pragma once
#include <iostream>
#include "clsScreen.h";
#include <iomanip>
#include "clsInputValidate.h"
#include "clsManagePatient.h"
#include "clsManageDoctors.h"
#include "clsManageAppointments.h"
#include "clsManageMedicinesScreen.h"
#include "clsManageInvoicesScreen.h"

class clsShowMainMenue2 : protected clsScreen
{
private:
    enum enMainMenueOptions {
        eManagePatients = 1, eManageDoctors = 2, eManageAppointments = 3,
        eManageMedicines = 4, eInvoicesAndPayments = 5, eExit = 6
    };

    static short _ReadMainMenueOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowMainMenue2();
    }

    static void _ShowManagePatients() {
        clsManagePatient::ShowManagePatients();
    }

    static void _ShowManageDoctors() {
        clsManageDoctors::ShowManageDoctors();
    }

    static void _ShowManageAppointment() {
        clsManageAppointments::ShowManageAppointment();
    }

    static void _ShowManageMedicines() {
        clsManageMedicinesScreen::ShowManageMedicinesMenu();
    }

    static void _ShowManageInvoices() {
        clsManageInvoicesScreen::ShowManageInvoicesMenu();
    }

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOptions) {
        switch (MainMenueOptions) {
        case enMainMenueOptions::eManagePatients:
            system("cls");
            _ShowManagePatients();
            _GoBackToMainMenue();
        case enMainMenueOptions::eManageDoctors:
            system("cls");
            _ShowManageDoctors();
            _GoBackToMainMenue();
        case enMainMenueOptions::eManageAppointments:
            system("cls");
            _ShowManageAppointment();
            _GoBackToMainMenue();
        case enMainMenueOptions::eManageMedicines:
            system("cls");
            _ShowManageMedicines();
            _GoBackToMainMenue();
        case enMainMenueOptions::eInvoicesAndPayments:
            system("cls");
            _ShowManageInvoices();
            _GoBackToMainMenue();
        }
    }

public:

    static void ShowMainMenue2()
    {

        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Manage Patients.\n";
        cout << setw(37) << left << "" << "\t[2] Manage Doctors.\n";
        cout << setw(37) << left << "" << "\t[3] Manage Appointments.\n";
        cout << setw(37) << left << "" << "\t[4] Manage Medicines (Inventory).\n";
        cout << setw(37) << left << "" << "\t[5] Invoices & Payments.\n";
        cout << setw(37) << left << "" << "\t[6] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
    }

};

