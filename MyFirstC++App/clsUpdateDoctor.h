#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsDoctors.h"

class clsUpdateDoctor : clsScreen
{
private:

	static void _ReadDoctorInfo(clsDoctors& Doctor,string FullName) {
	
		string FirstName, LastName;

		char More = 'y';

		cout << "\nPlease , Add a new Doctor : \n\n";

		cout << "Would you like to change the Full Name of the doctor ? [Y/N] : ";
		cin >> More;
		if (More == 'y' || More == 'Y') {
			cout << "\nPlease ,Enter New Full Name : ";
			FullName = clsInputValidate::ReadString();
			while (clsDoctors::IsDoctorExists(FullName)) {
				cout << "Doctor With [" << FullName << "] already exeits, Enter another Full Name : ";
				FullName = clsInputValidate::ReadString();
			}
			clsDoctors::SplitFullName(FullName, FirstName, LastName);
			Doctor.FirstName = FirstName;

			Doctor.LastName = LastName;
		}
		else {
			clsDoctors::SplitFullName(FullName, FirstName, LastName);

			Doctor.FirstName = FirstName;

			Doctor.LastName = LastName;
		}


		cout << "\nPhone Number : ";
		Doctor.Phone = clsInputValidate::ReadString();

		cout << "\n\nEmail : ";
		Doctor.Email = clsInputValidate::ReadString();

		cout << "\n\nSpecialization [eGeneral = 1 , eCardiology = 2 , eDermatology = 3 , ePediatrics = 4 , "
			"eGynecology = 5 , eNeurology = 6 , eOrthopedics = 7 , eOphthalmology = 8 , eENT = 9] : ";
		Doctor.SetSpecialization(clsInputValidate::ReadShortNumberBetween(1, 9));

		cout << "\n\nConsultation Fee : ";
		Doctor.SetConsultationFee(clsInputValidate::ReadShortNumber());

		cout << "\n\nWorking Days [Sunday = 0 ,Monday = 1 ,Tuesday = 2 \n";
		cout << " ,Wednesday = 3 ,Thursday = 4 ,Friday = 5 ,Saturday = 6] : ";
		char y = 'y';
		vector<short>vDayNumber;
		do{
			short Day = clsInputValidate::ReadShortNumberBetween(0, 6);
			vDayNumber.push_back(Day);
			cout << "\nNext Work Day : [Y/N] : ";
			cin >> y;
		} while (y == 'y' || y == 'Y');
		Doctor.SetWorkingDays(vDayNumber);

		cout << "\n\nWorking Hours Start : ";
		Doctor.SetWorkingHoursStart(clsInputValidate::ReadString());

		cout << "\n\nWorking Hours End : ";
		Doctor.SetWorkingHoursEnd(clsInputValidate::ReadString());

		// ÊÚííä ÑÞã ÇáÚíÇÏÉ ÊáÞÇÆíÇð ÍÓÈ ÇáÊÎÕÕ
		short ClinicNumber = 1;  // ÇÝÊÑÇÖí
		switch (Doctor.Specialization) {
		case 1:  // eGeneral
			ClinicNumber = 1;
			break;
		case 2:  // eCardiology
			ClinicNumber = 2;
			break;
		case 3:  // eDermatology
			ClinicNumber = 3;
			break;
		case 4:  // ePediatrics
			ClinicNumber = 4;
			break;
		case 5:  // eGynecology
			ClinicNumber = 8;
			break;
		case 6:  // eNeurology
			ClinicNumber = 9;
			break;
		case 7:  // eOrthopedics
			ClinicNumber = 5;
			break;
		case 8:  // eOphthalmology
			ClinicNumber = 6;
			break;
		case 9:  // eENT
			ClinicNumber = 7;
			break;
		default:
			ClinicNumber = 1;
			break;
		}

		Doctor.SetClinicNumber(ClinicNumber);
		cout << "\n\nClinic Number assigned automatically: " << Doctor.GetClinicNumberText() << endl;

		cout << "\n\nIs Active : ";
		Doctor.SetIsActive(clsInputValidate::ReadShortNumberBetween(0, 1));

	}

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

	static void ShowUpdateDoctor() {
		_DrawScreenHeader("\t   Update Doctor Screen");

		char More = 'y';

		string FullName;
		cout << "Full Name : ";
		FullName = clsInputValidate::ReadString();

		while (!clsDoctors::IsDoctorExists(FullName)) {
			cout << "There is no doctor by that name [" << FullName << "], Please enter an existing Full Name : ";
			FullName = clsInputValidate::ReadString();
		}
		clsDoctors Doctor = clsDoctors::FindFullName(FullName);

		_PrintDoctor(Doctor);

		_ReadDoctorInfo(Doctor, FullName);

		clsDoctors::enSaveResults SaveResult;

		cout << "\n\nAre you sure you have Updated the new Doctor's data ? [Y/N] : ";
		cin >> More;
		if(More == 'Y' || More == 'y') {
			SaveResult = Doctor.Save();
			switch (SaveResult) {
			case clsDoctors::enSaveResults::svSucceeded: {
				cout << "\n\n  Doctor Updated Successfuly... \n";
				_PrintDoctor(Doctor);
				break;
			}
			case clsDoctors::enSaveResults::svFaildEmptyObject:
				cout << "\nError ID Or FullName was Not Saved becouse it's Empty...";
				break;
			}
		}
	}
};

