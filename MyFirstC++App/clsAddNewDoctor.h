#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsDoctors.h"

class clsAddNewDoctor : protected clsScreen
{
private:
	static void _ReadDoctorInfo(clsDoctors &Doctor , string FullName) {
		short Counter = 0;

		vector<clsDoctors>vDoctors = clsDoctors::GetAllDoctors();

        short LastDoctor = 0;
        if (!vDoctors.empty()) {
            LastDoctor = vDoctors.back().GetDoctorID();
        }

		string FirstName, LastName;

		clsDoctors::SplitFullName(FullName , FirstName , LastName);

		Counter = LastDoctor + 1;

        Doctor.SetDoctorID(Counter); 

		cout << "\nPlease , Add a new Doctor : \n\n";

		Doctor.FirstName = FirstName;

		Doctor.LastName = LastName;

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
        do {
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
        cout << "\nFee           : " << Doctor.ConsultationFee;
        cout << "\nWorking Days  : " << Doctor.GetWorkingDaysText();
        cout << "\nWorkingHours  : " << Doctor.WorkingHoursStart << " To " << Doctor.WorkingHoursEnd;
        cout << "\nClinic Number : " << Doctor.GetClinicNumberText();
        cout << "\n___________________\n";

    }

    //ÚäÏ ÇáÇäÊåÇÁ ãä ßßá ÔíÁ Ýí ÇáãÔÑæÚ ÓÃÚæÏ Çáì åäÇ ãää ÇÌá ÅÖÇÝÉ ÇßËÑ ãä íæã 
    /*static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {


            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nShow Register Login ? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pShowLogInRegister;
        }

        return Permissions;

    }*/

public:

    static void ShowAddNewDoctorToFile() {
        char More = 'y';

        do {

            system("cls");

            _DrawScreenHeader("\t  Add New Doctor");


            string FullName;
            cout << "Full Name : ";
            FullName = clsInputValidate::ReadString();

            while (clsDoctors::IsDoctorExists(FullName)) {
                cout << "Doctor With [" << FullName << "] already exeits, Enter another Full Name : ";
                FullName = clsInputValidate::ReadString();
            }
            clsDoctors Doctor = clsDoctors::GetAddNewDoctorObject(FullName);

            _ReadDoctorInfo(Doctor, FullName);

            _PrintDoctor(Doctor);

            clsDoctors::enSaveResults SaveResult;

            cout << "\n\nAre you sure you have saved the new Doctor's data ? [Y/N] : ";
            cin >> More;
            SaveResult = Doctor.Save();

            switch (SaveResult) {
            case clsDoctors::enSaveResults::svSucceeded:
            {
                cout << "\n\n  Doctor Added Successfuly... \n";
                break;
            }
            case clsDoctors::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError Doctor was not saved because it's Empty";
                break;

            }
            case clsDoctors::enSaveResults::svFaildIDOrFullNameExists:
            {
                cout << "\nError Doctor was not saved because ID Or FullName is used!\n";
                break;
            }
            }
            cout << "\nWould you like to add a new Doctor ? [Y/N] : ";
            cin >> More;
        }while (More == 'Y' || More == 'y');
    }
};

