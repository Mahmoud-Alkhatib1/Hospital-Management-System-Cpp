#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsAddNewInvoiceScreen.h"
#include "clsFindInvoiceScreen.h"
#include "clsUpdateInvoiceScreen.h"
#include "clsDeleteInvoiceScreen.h"
#include "clsAllInvoicesScreen.h"

class clsManageInvoicesScreen : protected clsScreen
{
private:
    enum enManageInvoicesOptions {
        eAddNewInvoice = 1,
        eFindInvoice = 2,
        eUpdateInvoice = 3,
        eDeleteInvoice = 4,
        eShowAllInvoices = 5,
        eBackToMainMenu = 6
    };

    static short _ReadManageInvoicesOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6);
        return Choice;
    }

    static void _GoBackToManageInvoicesMenu() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Invoices Menu...\n";
        system("pause>0");
        ShowManageInvoicesMenu();
    }

    static void _ShowAddNewInvoiceScreen() {
        clsAddNewInvoiceScreen::ShowAddNewInvoiceScreen();
    }

    static void _ShowFindInvoiceScreen() {
        clsFindInvoiceScreen::ShowFindInvoiceScreen();
    }

    static void _ShowUpdateInvoiceScreen() {
        clsUpdateInvoiceScreen::ShowUpdateInvoiceScreen();
    }

    static void _ShowDeleteInvoiceScreen() {
        clsDeleteInvoiceScreen::ShowDeleteInvoiceScreen();
    }

    static void _ShowAllInvoicesScreen() {
        clsAllInvoicesScreen::ShowAllInvoices();
    }

    static void _PerformManageInvoicesOption(enManageInvoicesOptions Option) {
        switch (Option) {
        case enManageInvoicesOptions::eAddNewInvoice:
            system("cls");
            _ShowAddNewInvoiceScreen();
            _GoBackToManageInvoicesMenu();
            break;
        case enManageInvoicesOptions::eFindInvoice:
            system("cls");
            _ShowFindInvoiceScreen();
            _GoBackToManageInvoicesMenu();
            break;
        case enManageInvoicesOptions::eUpdateInvoice:
            system("cls");
            _ShowUpdateInvoiceScreen();
            _GoBackToManageInvoicesMenu();
            break;
        case enManageInvoicesOptions::eDeleteInvoice:
            system("cls");
            _ShowDeleteInvoiceScreen();
            _GoBackToManageInvoicesMenu();
            break;
        case enManageInvoicesOptions::eShowAllInvoices:
            system("cls");
            _ShowAllInvoicesScreen();
            _GoBackToManageInvoicesMenu();
            break;
        case enManageInvoicesOptions::eBackToMainMenu:
            system("cls");
            break;
        }
    }

public:
    static void ShowManageInvoicesMenu() {
        system("cls");
        _DrawScreenHeader("\t\tManage Invoices");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Invoice Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Add New Invoice.\n";
        cout << setw(37) << left << "" << "\t[2] Find Invoice.\n";
        cout << setw(37) << left << "" << "\t[3] Update Invoice Info.\n";
        cout << setw(37) << left << "" << "\t[4] Delete Invoice.\n";
        cout << setw(37) << left << "" << "\t[5] Show All Invoices.\n";
        cout << setw(37) << left << "" << "\t[6] Back to Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformManageInvoicesOption((enManageInvoicesOptions)_ReadManageInvoicesOption());
    }
};


