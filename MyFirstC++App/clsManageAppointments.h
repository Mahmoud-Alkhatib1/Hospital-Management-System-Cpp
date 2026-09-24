#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsBookNewAppointment.h"
#include "clsUpdateAppointment.h"
#include "clsDeleteAppointment.h"
#include "clsFindAppointment.h"
#include "clsShowTodaysAppointments.h"
#include "clsShowDoctorAppointments.h"
#include "clsShowAvailableSlots.h"

class clsManageAppointments : protected clsScreen
{
private:

    static short _ReadManageAppointmentsOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 8]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 8, "Enter Number between 1 to 8? ");
        return Choice;
    }

    enum enManageAppointmentsOptions {
        eBookNewAppointment = 1, eUpdateAppointment = 2, eCancelAppointment = 3,
        eFindAppointment = 4,eTodaysAppointments = 5, eDoctorsAppointments = 6,
        eAvailableSlots = 7 ,eBackToMainMenu = 8
    };

    static void _GoBackToManageAppointment() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Appointment Menu...\n";
        system("pause>0");
        ShowManageAppointment();
    }

    static void _ShowBookNewAppointment() {
        clsBookNewAppointment::ShowBookNewAppointment();

    }

    static void _ShowUpdateAppointment() {
        clsUpdateAppointment::ShowUpdateAppointment();
    }

    static void _ShowDeleteAppointment() {
        clsDeleteAppointment::ShowDeleteAppointment();
    }

    static void _ShowFindAppointment() {
        clsFindAppointment::ShowFindAppointment();
    }

    static void _ShowTodaysAppointments() {
       clsShowTodaysAppointments::ShowTodaysAppointments();
    }

    static void _ShowDoctorsAppointments() {
        clsShowDoctorAppointments::ShowDoctorAppointment();
    }

    static void _ShowAvailableSlots() {
        clsShowAvailableSlots::ShowAvailableSlots();
    }

    static void _PerfromManageAppointmentOption(enManageAppointmentsOptions ManageAppointmentsOptions) {
        switch (ManageAppointmentsOptions) {
        case enManageAppointmentsOptions::eBookNewAppointment:
            system("cls");
            _ShowBookNewAppointment();
            _GoBackToManageAppointment();
            break;
        case enManageAppointmentsOptions::eUpdateAppointment:
            system("cls");
            _ShowUpdateAppointment();
            _GoBackToManageAppointment();
            break;
        case enManageAppointmentsOptions::eCancelAppointment:
            system("cls");
            _ShowDeleteAppointment();
            _GoBackToManageAppointment();
            break;
        case enManageAppointmentsOptions::eFindAppointment:
            system("cls");
            _ShowFindAppointment();
            _GoBackToManageAppointment();
            break;
        case enManageAppointmentsOptions::eTodaysAppointments:
            system("cls");
            _ShowTodaysAppointments();
            _GoBackToManageAppointment();
            break;
        case enManageAppointmentsOptions::eDoctorsAppointments:
            system("cls");
            _ShowDoctorsAppointments();
            _GoBackToManageAppointment();
            break;
        case enManageAppointmentsOptions::eAvailableSlots:
            system("cls");
            _ShowAvailableSlots();
            _GoBackToManageAppointment();
            break;
        case enManageAppointmentsOptions::eBackToMainMenu:
            system("cls");
            break;
        }

    }

public:

    static void ShowManageAppointment() {

        system("cls");
        _DrawScreenHeader("\t  Doctor Menu");

        cout << setw(37) << left << "" << "===========================================\n\n";

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Book New Appointment.\n";
        cout << setw(37) << left << "" << "\t[2] Update Appointment.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Appointment.\n";
        cout << setw(37) << left << "" << "\t[4] Find Appointment.\n";
        cout << setw(37) << left << "" << "\t[5] Show Today's Appointments.\n";
        cout << setw(37) << left << "" << "\t[6] Show Doctor's Appointments.\n";
        cout << setw(37) << left << "" << "\t[7] Show Available Slots.\n";
        cout << setw(37) << left << "" << "\t[8] Back to Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromManageAppointmentOption((enManageAppointmentsOptions)_ReadManageAppointmentsOption());

    }
};


