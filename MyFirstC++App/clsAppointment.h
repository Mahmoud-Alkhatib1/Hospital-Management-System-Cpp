#pragma once
#include <vector>
#include "clsString.h"
#include <string>
#include <fstream>
#include "clsDate.h"
#include "clsInputValidate.h"
#include "clsPatients.h"

class clsAppointment : clsPatients
{
private:
	enum enMode {
		eAddNewAppointment = 1, eUpdateAppointment = 2, EmptyAppointment = 3
	};

	enMode _Mode;
	short _AppointmentID;
	short _PatientID;
	short _DoctorID;
	string _Date;
	string _Time;
	bool MarkedForDeleted = false;

	static clsAppointment _GetEmptyAppointmentObject()
	{
		return clsAppointment(enMode::EmptyAppointment, 0, 0, 0, "", "");
	}

	static bool MarkDoctorForDeleteByAppointmentID(short AppointmentID, vector <clsAppointment>& vAppointments)
	{

		for (clsAppointment& D : vAppointments)
		{

			if (D._AppointmentID == AppointmentID)
			{
				D.MarkedForDeleted = true;
				return true;
			}

		}

		return false;
	}

	static clsAppointment ConvertAppointmentLineToObject(string Line, string Seperator = "#//#") {
		vector<string> vAppointmentData = clsString::Split(Line, Seperator);

		return clsAppointment(enMode::eUpdateAppointment, stoi(vAppointmentData[0]), 
			stoi(vAppointmentData[1]),stoi(vAppointmentData[2]), vAppointmentData[3],
			vAppointmentData[4]);
	}

	static string _ConvertAppointmentObjectToLine(clsAppointment Appointment, string Seperator = "#//#"){
		string TextAppointment = "";

		TextAppointment += to_string(Appointment._AppointmentID) + Seperator;
		TextAppointment += to_string(Appointment._PatientID) + Seperator;
		TextAppointment += to_string(Appointment._DoctorID) + Seperator;
		TextAppointment += Appointment._Date + Seperator;
		TextAppointment += Appointment._Time;

		return TextAppointment;
	}

	static vector<clsAppointment> _LoadAppointmentFromFile() {
		fstream MyFile;
		vector<clsAppointment>vAppointments;

		MyFile.open("Appointment.txt" , ios::in);
		if (MyFile.is_open()) {
			string Line;
			while(getline(MyFile , Line)) {
				if (Line != "") {
					clsAppointment Appointment = ConvertAppointmentLineToObject(Line);
					vAppointments.push_back(Appointment);
				}
			}
			MyFile.close();
		}
		return vAppointments;
	}

	static void _SaveAppointmentsDataToFile(vector<clsAppointment>vAppointments) {
		fstream MyFile;
		MyFile.open("Appointment.txt", ios::out);
		if (MyFile.is_open()) {
			string Line;
			for (clsAppointment &Ap : vAppointments) {
				if (Ap.MarkedForDeleted == false)
				{
					Line = _ConvertAppointmentObjectToLine(Ap);
					MyFile << Line << endl;
				}
				else {
					Ap = _GetEmptyAppointmentObject();
				}
			}
			MyFile.close();
		}
	}

	void _Update() {
		vector<clsAppointment> vAppointments = _LoadAppointmentFromFile();

		for (clsAppointment& Ap : vAppointments) {
			if (Ap.AppointmentID() == _AppointmentID) { 
				Ap = *this;  // «” »œ«· «·»Ì«‰« 
				break;
			}
		}

		_SaveAppointmentsDataToFile(vAppointments);
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertAppointmentObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine) {
		fstream MyFile;
		MyFile.open("Appointment.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();

		}

	}

public:
	clsAppointment(enMode Mode , short AppointmentID , short PatientID , short DoctorID , 
		string Date , string Time) {
		_Mode = Mode;
		_AppointmentID = AppointmentID;
		_PatientID = PatientID;
		_DoctorID = DoctorID;
		_Date = Date;
		_Time = Time;
	}

	short AppointmentID() {
		return _AppointmentID;
	}

	void SetPatientID(short PatientID) { _PatientID = PatientID; }
	short GetPatientID() { return _PatientID; }
	__declspec(property(get = GetPatientID, put = SetPatientID))short PatientID;

	void SetDoctorID(short DoctorID) { _DoctorID = DoctorID; }
	short GetDoctorID() { return _DoctorID; }
	__declspec(property(get = GetDoctorID, put = SetDoctorID))short DoctorID;

	void SetDate(string Date) {
		_Date = Date;
	}
	string GetDate() {
		return _Date;
	}
	__declspec(property(get = GetDate, put = SetDate))string Date;

	void SetTime(string Time) {
		_Time = Time;
	}

	string GetTime() {
		return _Time;
	}

	__declspec(property(get = GetTime, put = SetTime))string Time;

	bool IsEmpty() {
		return (_Mode == enMode::EmptyAppointment);
	}

	static clsAppointment GetEmptyAppointmentObject() {
		return _GetEmptyAppointmentObject();
	}

	static vector<clsAppointment> GetAllAppointment() {
		return _LoadAppointmentFromFile();
	}

	static clsAppointment FindAppointmentID(short AppointmentID) {
		fstream MyFile;
		vector<clsAppointment>vAppointments;
		MyFile.open("Appointment.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsAppointment Appointment = ConvertAppointmentLineToObject(Line);

				if (Appointment._AppointmentID == AppointmentID) {
					MyFile.close();
					return Appointment;
				}
				vAppointments.push_back(Appointment);
			}

		}
		return _GetEmptyAppointmentObject();
	}

	static vector<clsAppointment> FindByPatientID(short PatientID) {
		fstream MyFile;
		vector<clsAppointment>vAppointments;

		MyFile.open("Appointment.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				if (Line != "") {
					clsAppointment Appointment = ConvertAppointmentLineToObject(Line);
					if (Appointment.GetPatientID() == PatientID) {
						vAppointments.push_back(Appointment);
					}
				}
			}
			MyFile.close();
		}
		return vAppointments;
		
	}

	static vector<clsAppointment> FindByPatientIDAndDoctorID(short PatientID , short DoctorID) {
		fstream MyFile;
		vector<clsAppointment>vAppointments;

		MyFile.open("Appointment.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				if (Line != "") {
					clsAppointment Appointment = ConvertAppointmentLineToObject(Line);
					if (Appointment.GetPatientID() == PatientID && Appointment.DoctorID == DoctorID) {
						vAppointments.push_back(Appointment);
					}
				}
			}
			MyFile.close();
		}
		return vAppointments;

	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildIDExists = 2 };

	enSaveResults Save() {
		switch (_Mode) {
		case enMode::EmptyAppointment:
			if (IsEmpty())
			{

				return enSaveResults::svFaildEmptyObject;

			}
		case enMode::eAddNewAppointment:
			if (clsAppointment::IsAppointmentExists(_AppointmentID)) {
				return enSaveResults::svFaildIDExists;
			}
			else
			{
				_AddNew();
				//We need to set the mode to update after add new
				_Mode = enMode::eUpdateAppointment;
				return enSaveResults::svSucceeded;
			}
		case enMode::eUpdateAppointment:
			_Update();
			return enSaveResults::svSucceeded;

		}
	}

	static void Delete(vector <clsAppointment>& vAppointments, short AppointmentID) {

		MarkDoctorForDeleteByAppointmentID(AppointmentID, vAppointments);
		_SaveAppointmentsDataToFile(vAppointments);

		vAppointments = GetAllAppointment();

	}

	static clsAppointment GetAddNewAppointmentObject(short ID)
	{
		return clsAppointment(enMode::eAddNewAppointment, ID, 0, 0, "", "");
	}

	static bool IsAppointmentExists(short ID)
	{
		clsAppointment Appointment = clsAppointment::FindAppointmentID(ID);
		return (!Appointment.IsEmpty());
	}


};

