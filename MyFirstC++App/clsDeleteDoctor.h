#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsDoctors.h"

class clsDeleteDoctor : clsScreen
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
        cout << "\nFee           : " << Doctor.GetConsultationFee();
        cout << "\nWorking Days  : " << Doctor.GetWorkingDaysText();
        cout << "\nWorkingHours  : " << Doctor.GetWorkingHoursStart() << " To " << Doctor.GetWorkingHoursEnd();
        cout << "\nClinic Number : " << Doctor.GetClinicNumberText();
        cout << "\n___________________\n";

    }

public:
    static void ShowDeleteDoctor() {
		char More = 'y';

		do {

			system("cls");

			_DrawScreenHeader("\t  Add New Doctor");


			string FullName;
			cout << "Full Name : ";
			FullName = clsInputValidate::ReadString();

			while (!clsDoctors::IsDoctorExists(FullName)) {
				cout << "There is no doctor by that name [" << FullName << "], Please enter an existing Full Name : ";
				FullName = clsInputValidate::ReadString();
			}
			clsDoctors Doctor = clsDoctors::FindFullName(FullName);

			_PrintDoctor(Doctor);

			cout << "\n\nAre you sure you have Deleted the new Doctor's data ? [Y/N] : ";
			cin >> More;

			if (More == 'Y' || More == 'y') {
				clsDoctors::Delete(Doctor);
				cout << "\n\n  Doctor Deleted Successfuly... \n";
			}

			cout << "\nWould you like to Deleted a new Doctor ? [Y/N] : ";
			cin >> More;
		} while (More == 'Y' || More == 'y');

	}
};

