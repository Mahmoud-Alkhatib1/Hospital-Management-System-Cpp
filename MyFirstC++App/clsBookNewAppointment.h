#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsAppointment.h"
#include "clsInputValidate.h"
#include "clsPatients.h"
#include "clsDoctors.h"
#include <iomanip>
#include "clsString.h";

class clsBookNewAppointment : protected clsScreen, clsPatients, clsDoctors
{
private:

	static short _ReadPatientID(string &LastVisitDate , vector<stPatient> PatientsName) {
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
	vector<clsAppointment>& vAppointments,clsAppointment& NewAppointment) {
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

	static void _PrintWorkDaysList(vector<string> vWorkDays) {

		// «” Œ—«Ã ﬁ«∆„… «·√Ì«„ „‰ √Ê· ⁄‰’—
		vector<string> vDays = clsString::Split(vWorkDays[0], ",");

		//  Œ“Ì‰ Êﬁ  «·»œ¡ ÊÊﬁ  «·«‰ Â«¡
		string StartTime = vWorkDays[1];
		string EndTime   = vWorkDays[2];

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

	static bool IsDayInWorkingDays(string Day , vector<string> vWorkDays) {
		vector<string> vDays = clsString::Split(vWorkDays[0], ",");

		for (string &D : vDays) {
			if (D == Day) {
				return true;
			}
		}
		return false;
	}

	static string _ReadDate(clsDate CurrentDate1, clsDate Date3 ,string LastVisitDate,vector<string> vWorkDays
		,short DoctorID , vector<clsAppointment> vAppointments) {
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

		while (!IsDayInWorkingDays(Day , vWorkDays))
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
		_PrintDailySchedule(DoctorID,Date, vWorkDays, vAppointments);
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

	static bool _IsTimeSlotAvailable(vector<clsAppointment>vAppointments, short DoctorID, string Date , clsDate::stTime sTime1) {
		clsDate Date1(Date);
		vector<string> vTime;
		clsDate::stTime sTime2;
		for (clsAppointment& App : vAppointments) {
			clsDate Date2(App.Date);
			if (App.DoctorID == DoctorID && clsDate::IsDate1EqualDate2(Date1 , Date2)) {
				vTime = clsString::Split(App.Time, ":");
				sTime2.Hours = stoi(vTime[0]);
				sTime2.Min = stoi(vTime[1]);
				if (sTime1.Hours == sTime2.Hours) {
					return false;
				}
			}
		}/*≈÷«›… œ«·… ·„Ê«⁄Ìœ «·œﬂ Ê— »‘ﬂ· ÃœÊ· ”«⁄«  «·„Ê«⁄Ìœ »√Ì „—Ì÷ „— »ÿ…*/
		return true;
	}

	static string _ReadTime(vector<string> vWorkDays , vector<clsAppointment>vAppointments ,short DoctorID ,string Date) {

		cout << "\nEnter Time (HH:MM): ";
		string TimeString = clsInputValidate::ReadString();
		vector<string> vTime = clsString::Split(TimeString, ":");
		clsDate::stTime sTime;
		sTime.Hours = stoi(vTime[0]);
		sTime.Min = stoi(vTime[1]);
		string Time;
		//Â· «·„Ê⁄œ «·„œŒ· ÷„‰ ”«⁄«  œÊ«„ «·ÿ»Ì»
		while (!IsTimeInWorkingHours(sTime , vWorkDays))
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
	static void ShowBookNewAppointment() {
		_DrawScreenHeader("\t  Book New Appointment");

		vector<clsAppointment>vAppointments = clsAppointment::GetAllAppointment();
		short AppointmentID = 1;
		if (!vAppointments.empty()) {
			AppointmentID = vAppointments.back().AppointmentID() + 1;
		}

		clsAppointment NewAppointment = clsAppointment::GetAddNewAppointmentObject(AppointmentID);

		//Patient ID **************
		vector<stPatient> PatientsName = LoadPatientToFile();
		string LastVisitDate;
		NewAppointment.PatientID = _ReadPatientID(LastVisitDate, PatientsName);
		//*************************
		
		//Doctor ID ***************
		vector<clsDoctors> DoctorsName = GetAllDoctors();
		NewAppointment.DoctorID = _ReadDoctorID(DoctorsName, vAppointments);
		vector<string> vWorkDays = GetWorkingDaysList(NewAppointment.DoctorID);
		_PrintWorkDaysList(vWorkDays);
		//*************************

		//Date ********************
		clsDate CurrentDate1 = clsDate::GetSystemDate();// «· «—ÌŒ «·Õ«·Ì
		clsDate Date3(LastVisitDate); // «Œ— „Ê⁄œ ﬁ«„ » ”ÃÌ·Â «·„—Ì÷ 
		vector<clsAppointment>vDateApointment;
		if (HasFutureAppointment(CurrentDate1, Date3, vAppointments, NewAppointment)) {
			cout << "\n\nThere is a date for the action.\n";
			cout << "\nLast Visit Date = " << LastVisitDate << "\n";

			NewAppointment = clsAppointment::GetEmptyAppointmentObject();
		}
		else {
			NewAppointment.Date = _ReadDate(CurrentDate1, Date3, LastVisitDate , vWorkDays, NewAppointment.DoctorID
			, vAppointments);
		}
		//*************************

		//Time ********************
			NewAppointment.Time = _ReadTime(vWorkDays , vAppointments , NewAppointment.DoctorID , NewAppointment.Date);
		//*************************


		cout << "\nDoctor is available at this time.\n";


		clsAppointment::enSaveResults SaveResult;

		char More = 'y';
		cout << "\n\nAre you sure you have saved the new Apointment's data ? [Y/N] : ";
		cin >> More;

		if (More == 'Y' || More == 'y') {
			SaveResult = NewAppointment.Save();
			switch (SaveResult) {
			case enSaveResults::svSucceeded:
				clsPatients::UpdateLastVisitDate(NewAppointment.PatientID, NewAppointment.Date);
				cout << "\n\n  Apointment Added Successfuly... \n";
				break;
			case enSaveResults::svFaildEmptyObject:
				cout << "\nError Apointment was not saved because it's Empty";
				break;
			case clsAppointment::enSaveResults::svFaildIDExists:
				cout << "\nError Apointment was not saved because ID is used!\n";
				break;
			}
		}
	}
};

