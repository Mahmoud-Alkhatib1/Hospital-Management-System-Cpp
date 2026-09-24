#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsAppointment.h"
#include "clsInputValidate.h"
#include "clsPatients.h"
#include "clsDoctors.h"
#include <iomanip>
#include "clsString.h";

class clsUpdateAppointment : protected clsScreen, clsPatients, clsDoctors
{
	static short _ReadPatientID(string& LastVisitDate, vector<stPatient> PatientsName) {
		cout << "Select Patient : \n\n";

		for (stPatient& Pat : PatientsName) {
			cout << "[" << Pat.PatientID << "] " << Pat.FullName << endl;
		}
		cout << "\n\nEnter Patient ID : ";
		short PatientID = clsInputValidate::ReadShortNumber();

		for (stPatient& Pa : PatientsName) {
			if (PatientID == Pa.PatientID) {
				LastVisitDate = Pa.LastVisitDate;
				cout << "\nPatient Selected : " << Pa.FullName << "(ID : " << Pa.PatientID << ")\n";
				break;
			}
		}
		cout << "\n\n";

		return PatientID;
	}

	static short _ReadDoctorID(vector<clsDoctors> DoctorsName, vector<clsAppointment>vAppointments) {
		cout << "Select Doctors : \n\n";

		for (clsDoctors& Do : DoctorsName) {
			cout << "[" << Do.GetDoctorID() << "] " << Do.GetFullName() << " , Specialist in "
				<< Do.GetSpecializationText() << endl;
		}

		cout << "\n\nEnter Doctor ID : ";
		short DoctorID = clsInputValidate::ReadShortNumber();
		for (clsDoctors& Do : DoctorsName) {
			if (DoctorID == Do.GetDoctorID()) {
				cout << "\nDoctor Selected : " << Do.GetFullName() << "(ID : " << Do.GetDoctorID() << ")\n";
				cout << "\nAppointment Schedule : \n\n";
				for (clsAppointment& App : vAppointments) {
					if (App.DoctorID == DoctorID) {
						cout << App.Date << " : " << App.Time << endl;
					}
				}
				break;
			}
		}

		return DoctorID;
	}

	static bool HasFutureAppointment(clsDate CurrentDate, clsDate LastVisitDate,
		vector<clsAppointment>& vAppointments, clsAppointment& NewAppointment) {
		vector<clsAppointment> vPatientDoctorAppointments;

		// Â· ¬Œ— „Ê⁄œ ··„—Ì÷ »⁄œ «· «—ÌŒ «·Õ«·Ìø
		if (clsDate::IsDate1BeforeDate2(CurrentDate, LastVisitDate)) {

			// «»ÕÀ ⁄‰ „Ê«⁄Ìœ ·‰›” «·„—Ì÷ Ê‰›” «·ÿ»Ì»
			for (clsAppointment& App : vAppointments) {
				if (App.GetPatientID() == NewAppointment.GetPatientID() &&
					App.GetDoctorID() == NewAppointment.GetDoctorID()) {
					vPatientDoctorAppointments.push_back(App);
				}
			}

			// ≈–« ﬂ«‰ Â‰«ﬂ „Ê«⁄Ìœ°  Õﬁﬁ „‰ ¬Œ— „Ê⁄œ
			if (!vPatientDoctorAppointments.empty()) {
				string LastAppointmentDate = vPatientDoctorAppointments.back().GetDate();
				clsDate LastAppDate(LastAppointmentDate);

				// ≈–« ﬂ«‰ ¬Œ— „Ê⁄œ »⁄œ «· «—ÌŒ «·Õ«·Ì  ÌÊÃœ „Ê⁄œ „” ﬁ»·Ì
				if (clsDate::IsDate1BeforeDate2(CurrentDate, LastAppDate)) {
					return true;
				}
			}
		}
		return false;
	}

	static void _PrintAppointmentDetails(clsAppointment UpdateAppointment) {

		stPatient Patient1 = clsPatients::Find(UpdateAppointment.PatientID);
		clsDoctors Doctor1 = clsDoctors::FindDoctorID(UpdateAppointment.DoctorID);

		cout << "\n\n===========================================\n";
		cout << "        Appointment\n";
		cout << "===========================================\n";
		cout << "| " << setw(12) << left << "Appointment ID : " << UpdateAppointment.AppointmentID()<<"\n";
		cout << "| " << setw(12) << left << "Patient Name   : " << Patient1.FullName << "\n";
		cout << "| " << setw(12) << left << "Doctor Name    : " << Doctor1.FullName() << "\n";
		cout << "| " << setw(12) << left << "Date           : " << UpdateAppointment.Date << "\n";
		cout << "| " << setw(12) << left << "Time           : " << UpdateAppointment.Time << "\n";
		cout << "|\n";
		cout << "===========================================\n\n";
	}

	static void _PrintWorkDaysList(vector<string> vWorkDays) {

		// «” Œ—«Ã ﬁ«∆„… «·√Ì«„ „‰ √Ê· ⁄‰’—
		vector<string> vDays = clsString::Split(vWorkDays[0], ",");

		//  Œ“Ì‰ Êﬁ  «·»œ¡ ÊÊﬁ  «·«‰ Â«¡
		string StartTime = vWorkDays[1];
		string EndTime = vWorkDays[2];

		// ÿ»«⁄… —√” «·ÃœÊ·
		cout << "\n===========================================\n";
		cout << "        Doctor Working Hours\n";
		cout << "===========================================\n";
		cout << "| " << setw(12) << left << "Day";
		cout << "| " << setw(12) << left << "Start Time";
		cout << "| " << setw(12) << left << "End Time";
		cout << "|\n";
		cout << "===========================================\n";

		// ÿ»«⁄… ﬂ· ÌÊ„ „⁄ √Êﬁ«  «·œÊ«„
		for (string& Day : vDays) {
			cout << "| " << setw(12) << left << Day;
			cout << "| " << setw(12) << left << StartTime;
			cout << "| " << setw(12) << left << EndTime;
			cout << "|\n";
		}

		cout << "===========================================\n";
	}

	static void _PrintDailySchedule(short DoctorID, string Date, vector<string> vWorkDays,
		vector<clsAppointment>& vAllAppointments) {

		// 1. «” Œ—«Ã Êﬁ  «·»œ¡ ÊÊﬁ  «·«‰ Â«¡
		string StartTime = vWorkDays[1];  // "09:00"
		string EndTime = vWorkDays[2];    // "17:00"

		int StartHour = stoi(clsString::Split(StartTime, ":")[0]);
		int EndHour = stoi(clsString::Split(EndTime, ":")[0]);

		// 2. ÿ»«⁄… —√” «·ÃœÊ·
		clsDate AppointmentDate(Date);
		int DayNumber = clsDate::DayOfWeekOrder(AppointmentDate.GetDay(),
			AppointmentDate.GetMonth(),
			AppointmentDate.GetYear());
		string DayName = clsDate::DayShortName2(DayNumber);

		cout << "\n===========================================================\n";
		cout << "           " << DayName << ", " << Date << endl;
		cout << "===========================================================\n";
		cout << "| " << setw(10) << left << "Time";
		cout << "| " << setw(15) << left << "Status";
		cout << "|\n";
		cout << "===========================================================\n";

		// 3. ÿ»«⁄… ﬂ· ”«⁄… „‰ Êﬁ  «·»œ¡ ≈·Ï Êﬁ  «·«‰ Â«¡
		for (int Hour = StartHour; Hour < EndHour; Hour++) {
			string TimeStr = (Hour < 10 ? "0" + to_string(Hour) : to_string(Hour)) + ":00";

			// 4. «·»ÕÀ ›Ì vAllAppointments ≈–« ﬂ«‰ «·Êﬁ  „ÕÃÊ“«
			bool IsBooked = false;
			for (clsAppointment& App : vAllAppointments) {
				if (App.GetDoctorID() == DoctorID &&
					App.GetDate() == Date &&
					App.GetTime() == TimeStr) {
					IsBooked = true;
					break;
				}
			}

			string Status = IsBooked ? "Booked" : "Free";

			cout << "| " << setw(10) << left << TimeStr;
			cout << "| " << setw(15) << left << Status;
			cout << "|\n";
		}

		cout << "===========================================================\n";
	}

	static bool IsDayInWorkingDays(string Day, vector<string> vWorkDays) {
		vector<string> vDays = clsString::Split(vWorkDays[0], ",");

		for (string& D : vDays) {
			if (D == Day) {
				return true;
			}
		}
		return false;
	}

	static string _ReadDate(clsDate CurrentDate1, clsDate Date3, string LastVisitDate, vector<string> vWorkDays
		, short DoctorID, vector<clsAppointment> vAppointments) {
		cout << "\nEnter Date (DD/MM/YYYY): ";
		string Datestring = clsInputValidate::ReadString();

		clsDate Date2(Datestring);

		short DayNumber = clsDate::DayOfWeekOrder(Date2.Day, Date2.Month, Date2.Year);//ÌÊ„ «· «—ÌŒ «·Õ«·Ì »«·—ﬁ„
		string Day = clsDate::DayShortName2(DayNumber);

		string CurrentDate = clsDate::DateToString(CurrentDate1);
		//Â· «· «—ÌŒ «·„œŒ· ﬁœÌ„ , ﬁ»· «· «·—ÌŒ «·Õ«·Ì 
		while (IsDate1BeforeDate2(Date2, CurrentDate1))
		{
			cout << "\n\t the Date Entered is Old, please enter from the " << CurrentDate << " and onwards (DD/MM/YYYY): ";

			Datestring = clsInputValidate::ReadString();
			Date2 = clsDate(Datestring);
			DayNumber = clsDate::DayOfWeekOrder(Date2.Day, Date2.Month, Date2.Year);//ÌÊ„ «· «—ÌŒ «·Õ«·Ì »«·—ﬁ„
			Day = clsDate::DayShortName2(DayNumber);

		}

		while (!IsDayInWorkingDays(Day, vWorkDays))
		{
			cout << "\n\t The date entered is : " << Day << " , a holiday in the doctor's program.\n";
			cout << "\t Please enter a new date (DD/MM/YYYY): ";

			Datestring = clsInputValidate::ReadString();
			Date2 = clsDate(Datestring);
			DayNumber = clsDate::DayOfWeekOrder(Date2.Day, Date2.Month, Date2.Year);//ÌÊ„ «· «—ÌŒ «·Õ«·Ì »«·—ﬁ„
			Day = clsDate::DayShortName2(DayNumber);

		}
		cout << "\nThe date entered is : " << Day << "\n\n";
		string Date = clsDate::DateToString(Date2);
		_PrintDailySchedule(DoctorID, Date, vWorkDays, vAppointments);
		return Date;
	}

	static bool IsTimeInWorkingHours(clsDate::stTime sTime, vector<string> vWorkDays) {
		vector<string> StartTime = clsString::Split(vWorkDays[1], ":");
		vector<string> EndTime = clsString::Split(vWorkDays[2], ":");
		if (stoi(StartTime[0]) <= sTime.Hours && stoi(EndTime[0]) > sTime.Hours) {
			return true;
		}
		return false;
	}

	static bool _IsTimeSlotAvailable(vector<clsAppointment>vAppointments, short DoctorID, string Date, clsDate::stTime sTime1) {
		clsDate Date1(Date);
		vector<string> vTime;
		clsDate::stTime sTime2;
		for (clsAppointment& App : vAppointments) {
			clsDate Date2(App.Date);
			if (App.DoctorID == DoctorID && clsDate::IsDate1EqualDate2(Date1, Date2)) {
				vTime = clsString::Split(App.Time, ":");
				sTime2.Hours = stoi(vTime[0]);
				sTime2.Min = stoi(vTime[1]);
				if (sTime1.Hours == sTime2.Hours) {
					return false;
				}
			}
		}
		return true;
	}

	static string _ReadTime(vector<string> vWorkDays, vector<clsAppointment>vAppointments, short DoctorID, string Date) {

		cout << "\nEnter Time (HH:MM): ";
		string TimeString = clsInputValidate::ReadString();
		vector<string> vTime = clsString::Split(TimeString, ":");
		clsDate::stTime sTime;
		sTime.Hours = stoi(vTime[0]);
		sTime.Min = stoi(vTime[1]);
		string Time;
		//Â· «·„Ê⁄œ «·„œŒ· ÷„‰ ”«⁄«  œÊ«„ «·ÿ»Ì»
		while (!IsTimeInWorkingHours(sTime, vWorkDays))
		{
			Time = clsDate::TimeToString(sTime);

			cout << "\n\t The Time entered is : " << Time << " , a holiday in the doctor's program.\n";
			cout << "\t Please enter a new Time (HH:MM): ";

			TimeString = clsInputValidate::ReadString();
			vTime = clsString::Split(TimeString, ":");
			sTime.Hours = stoi(vTime[0]);
			sTime.Min = stoi(vTime[1]);

		}
		//Â· «·„Ê⁄œ „ÊÃÊœ ”«»ﬁ« ø
		while (!_IsTimeSlotAvailable(vAppointments, DoctorID, Date, sTime)) {
			Time = clsDate::TimeToString(sTime);

			cout << "\n\t This appointment is already booked, choose another time (HH:MM): ";

			TimeString = clsInputValidate::ReadString();
			vTime = clsString::Split(TimeString, ":");
			sTime.Hours = stoi(vTime[0]);
			sTime.Min = stoi(vTime[1]);
		}

		Time = clsDate::TimeToString(sTime);
		cout << "\nThe Time entered is : " << Time << "\n\n";

		return Time;
	}

public:
	static void ShowUpdateAppointment() {
		_DrawScreenHeader("\t  Update Appointment");

		vector<clsAppointment>vAppointments = clsAppointment::GetAllAppointment();
		short AppointmentID;
		cout << "Please , Enter Your Appointment : ";
		if (vAppointments.empty()) {
			cout << "\n\t? No appointments found!\n";
			return;
		}
		AppointmentID = clsInputValidate::ReadShortNumberBetween(1 , vAppointments.back().AppointmentID());
		clsAppointment UpdateAppointment = clsAppointment::FindAppointmentID(AppointmentID);

		_PrintAppointmentDetails(UpdateAppointment);

		short Number = 0;
		cout << "What would you like to update? \n\n";
		cout << "[1] Patient\n";
		cout << "[2] Doctor\n";
		cout << "[3] Date\n";
		cout << "[4] Time\n";
		cout << "[5] All\n\n";
		Number = clsInputValidate::ReadShortNumberBetween(1 , 5);

		vector<stPatient> PatientsName;
		string LastVisitDate;
		vector<string> vWorkDays;
		vector<clsDoctors> DoctorsName;
		vector<clsAppointment>vDateApointment;

		switch (Number) {
		case 1:
		{
			//Patient ID **************
			PatientsName = LoadPatientToFile();
			clsDate Date3(LastVisitDate);
			UpdateAppointment.PatientID = _ReadPatientID(LastVisitDate, PatientsName);
			break;
			//*************************
		}
		case 2: 
		{
			//Doctor ID ***************
			DoctorsName = GetAllDoctors();
			UpdateAppointment.DoctorID = _ReadDoctorID(DoctorsName, vAppointments);
			vWorkDays = GetWorkingDaysList(UpdateAppointment.DoctorID);
			_PrintWorkDaysList(vWorkDays);
			break;
			//*************************
		}
		case 3:
		{
			//Date ********************
			stPatient CurrentPatient = clsPatients::Find(UpdateAppointment.GetPatientID());
			LastVisitDate = CurrentPatient.LastVisitDate;

			clsDate CurrentDate1 = clsDate::GetSystemDate();// «· «—ÌŒ «·Õ«·Ì
			clsDate Date3(LastVisitDate); // «Œ— „Ê⁄œ ﬁ«„ » ”ÃÌ·Â «·„—Ì÷ 
			if (HasFutureAppointment(CurrentDate1, Date3, vAppointments, UpdateAppointment)) {
				cout << "\n\nThere is a date for the action.\n";
				cout << "\nLast Visit Date = " << LastVisitDate << "\n";

				UpdateAppointment = clsAppointment::GetEmptyAppointmentObject();
			}
			else {
				vWorkDays = GetWorkingDaysList(UpdateAppointment.DoctorID);

				UpdateAppointment.Date = _ReadDate(CurrentDate1, Date3, LastVisitDate, vWorkDays, UpdateAppointment.DoctorID
					, vAppointments);
			}
			break;
			//*************************
		}
		case 4:
		{
			//Time ********************
			if (vWorkDays.empty()) {
				DoctorsName = GetAllDoctors();
				vWorkDays = GetWorkingDaysList(UpdateAppointment.GetDoctorID());
			}
			UpdateAppointment.Time = _ReadTime(vWorkDays, vAppointments, UpdateAppointment.DoctorID, UpdateAppointment.Date);
			break;
			//*************************
		}
		case 5:
		{
			//Patient ID **************
			PatientsName = LoadPatientToFile();
			UpdateAppointment.PatientID = _ReadPatientID(LastVisitDate, PatientsName);
			//*************************

			//Doctor ID ***************
			DoctorsName = GetAllDoctors();
			UpdateAppointment.DoctorID = _ReadDoctorID(DoctorsName, vAppointments);
			vWorkDays = GetWorkingDaysList(UpdateAppointment.DoctorID);
			_PrintWorkDaysList(vWorkDays);
			//*************************

			//Date ********************
			clsDate CurrentDate1 = clsDate::GetSystemDate();// «· «—ÌŒ «·Õ«·Ì
			clsDate Date3(LastVisitDate); // «Œ— „Ê⁄œ ﬁ«„ » ”ÃÌ·Â «·„—Ì÷ 
			if (HasFutureAppointment(CurrentDate1, Date3, vAppointments, UpdateAppointment)) {
				cout << "\n\nThere is a date for the action.\n";
				cout << "\nLast Visit Date = " << LastVisitDate << "\n";

				UpdateAppointment = clsAppointment::GetEmptyAppointmentObject();
			}
			else {
				UpdateAppointment.Date = _ReadDate(CurrentDate1, Date3, LastVisitDate, vWorkDays, UpdateAppointment.DoctorID
					, vAppointments);
			}
			//*************************

			//Time ********************
			UpdateAppointment.Time = _ReadTime(vWorkDays, vAppointments, UpdateAppointment.DoctorID, UpdateAppointment.Date);
			//*************************
			break;
		}
		}

		cout << "\nDoctor is available at this time.\n";

		clsAppointment::enSaveResults SaveResult;

		char More = 'y';
		cout << "\n\nAre you sure you have Update the Apointment's data ? [Y/N] : ";
		cin >> More;

		if (More == 'Y' || More == 'y') {
			SaveResult = UpdateAppointment.Save();
			switch (SaveResult) {
			case clsAppointment::enSaveResults::svSucceeded:
				clsPatients::UpdateLastVisitDate(UpdateAppointment.PatientID, UpdateAppointment.Date);
				cout << "\n\n  Apointment Updated Successfuly... \n";
				break;
			case clsAppointment::enSaveResults::svFaildEmptyObject:
				cout << "\nError Apointment was not Updated because it's Empty";
				break;
			case clsAppointment::enSaveResults::svFaildIDExists:
				cout << "\nError Apointment was not Updated because ID is used!\n";
				break;
			}
		}
	}


};

