#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsDoctors.h"
#include "clsInputValidate.h"

class clsFindDoctor : clsScreen
{
private:
    static void _PrintDoctor(clsDoctors Doctor)
    {
        cout << "\nDoctor Card:";
        cout << "\n___________________";
        cout << "\nFull Name     : " << Doctor.FullName();
        cout << "\nEmail         : " << Doctor.Email;
        cout << "\nPhone         : " << Doctor.Phone;
        cout << "\nSpecialization: " << Doctor.GetSpecializationText();
        cout << "\nFee           : " << Doctor.ConsultationFee;
        cout << "\nWorking Days  : " << Doctor.GetWorkingDaysText();
        cout << "\nWorkingHours  : " << Doctor.WorkingHoursStart << " To " << Doctor.WorkingHoursEnd;
        cout << "\nClinic Number : " << Doctor.GetClinicNumberText();
        cout << "\n___________________\n";

    }

public:
    static void ShowFindDoctorScreen()
    {

        _DrawScreenHeader("\tFind Doctor Screen");

        string FullName;
        cout << "\nPlease Enter Full Name: ";
        FullName = clsInputValidate::ReadString();
        while (!clsDoctors::IsDoctorExists(FullName))
        {
            cout << "\nFull Name is not found, choose another one: ";
            FullName = clsInputValidate::ReadString();
        }

        clsDoctors Doctor = clsDoctors::FindFullName(FullName);

        if (!Doctor.IsEmpty())
        {
            cout << "\nDoctor Found :-)\n";
        }
        else
        {
            cout << "\nDoctor Was not Found :-(\n";
        }

        _PrintDoctor(Doctor);

    }
};

