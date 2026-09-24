#pragma once
#include <vector>
#include "clsString.h"
#include <string>
#include <fstream>
#include "clsDate.h"
#include "clsInputValidate.h"
#include "clsPerson.h"

class clsDoctors : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

    enum enSpecialization {
        eGeneral = 1,      // ⁄«„
        eCardiology = 2,      // ﬁ·»
        eDermatology = 3,      // Ã·œÌ…
        ePediatrics = 4,      // √ÿ›«·
        eGynecology = 5,      // ‰”«∆Ì…
        eNeurology = 6,      // √⁄’«»
        eOrthopedics = 7,      // ⁄Ÿ«„
        eOphthalmology = 8,      // ⁄ÌÊ‰
        eENT = 9       // √‰› Ê√–‰ ÊÕ‰Ã—…
    };

    enum enDayOfWeek {
        eSaturday = 1,
        eSunday = 2,
        eMonday = 3,
        eTuesday = 4,
        eWednesday = 5,
        eThursday = 6
    };

    enum enClinicNumber {
        enFirstClinic = 1, enSecondClinic = 2, eClinic3 = 3, eClinic4 = 4
        , enClinic5 = 5, enClinic6 = 6, enClinic7 = 7, enClinic8 = 8, enClinic9 = 9
    };

    enMode _Mode;
    short _DoctorID = 0;
    short _Specialization;
    double _ConsultationFee = 0.0;
    vector<short> _WorkingDays;
    string _WorkingHoursStart;
    string _WorkingHoursEnd;
    short _ClinicNumber;
    bool _IsActive;

    bool MarkedForDeleted = false;

    static clsDoctors _GetEmptyDoctorObject()
    {
        vector<short> EmptyDays;
        return clsDoctors(enMode::EmptyMode, 0, "", "", "", "", 0, 0.0, EmptyDays, "", "", 0);
    }

    static short _SpecializationNumber(string Specialization) {
        if (Specialization == "General") return 1;
        if (Specialization == "Cardiology") return 2;
        if (Specialization == "Dermatology") return 3;
        if (Specialization == "Pediatrics") return 4;
        if (Specialization == "Gynecology") return 5;
        if (Specialization == "Neurology") return 6;
        if (Specialization == "Orthopedics") return 7;
        if (Specialization == "Ophthalmology") return 8;
        if (Specialization == "ENT") return 9;

        return 1;
    }

    static string _SpecializationText(short Specialization) {
        string SpecializationArray[9] = { "General","Cardiology","Dermatology","Pediatrics"
            ,"Gynecology","Neurology","Orthopedics","Ophthalmology","ENT" };
        return SpecializationArray[Specialization - 1];
    }

    static short _WorkingDaysNumber(string WorkingDays) {
        if (WorkingDays == "Sunday") return 0;
        if (WorkingDays == "Monday") return 1;
        if (WorkingDays == "Tuesday") return 2;
        if (WorkingDays == "Wednesday") return 3;
        if (WorkingDays == "Thursday") return 4;
        if (WorkingDays == "Saturday") return 5;
        if (WorkingDays == "Friday") return 6;
        return 0;
    }

    static string _WorkingDaysText(vector<short> WorkingDays) {
        string Result = "";
        string DaysArray[7] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };

        for (size_t i = 0; i < WorkingDays.size(); i++) {
            Result += DaysArray[WorkingDays[i]];
            if (i != WorkingDays.size() - 1) Result += ",";
        }
        return Result;
    }

    static short _ClinicNumberNumber(string ClinicNumber) {
        if (ClinicNumber == "FirstClinic") return 1;
        if (ClinicNumber == "SecondClinic") return 2;
        if (ClinicNumber == "Clinic3") return 3;
        if (ClinicNumber == "Clinic4") return 4;
        if (ClinicNumber == "Clinic5") return 5;
        if (ClinicNumber == "Clinic6") return 6;
        if (ClinicNumber == "Clinic7") return 7;
        if (ClinicNumber == "Clinic8") return 8;
        if (ClinicNumber == "Clinic9") return 9;
        return 1;
    }

    static string _ClinicNumberText(short ClinicNumber) {
        string ClinicNumberArray[9] = { "FirstClinic","SecondClinic","Clinic3","Clinic4"
            ,"Clinic5","Clinic6","Clinic7","Clinic8","Clinic9" };
        return ClinicNumberArray[ClinicNumber - 1];
    }

    static bool MarkDoctorForDeleteByDoctorID(short DoctorID, vector <clsDoctors>& vDoctors)
    {
        for (clsDoctors& D : vDoctors)
        {
            if (D._DoctorID == DoctorID)
            {
                D.MarkedForDeleted = true;
                return true;
            }
        }
        return false;
    }

    static bool MarkDoctorForDeleteByDoctorID(string FullName, vector <clsDoctors>& vDoctors)
    {
        for (clsDoctors& D : vDoctors)
        {
            if (IsSameName(D.FullName(), FullName))
            {
                D.MarkedForDeleted = true;
                return true;
            }
        }
        return false;
    }

    static clsDoctors ConvertDoctorLineToObject(string Line, string Seperator = "#//#") {
        vector<string> vDoctorData = clsString::Split(Line, Seperator);

        //  ÕÊÌ· √Ì«„ «·⁄„· „‰ ‰’ ≈·Ï vector<short>
        vector<short> vWorkingDays;
        if (vDoctorData.size() > 7) {
            string DaysString = vDoctorData[7]; // „À«·: "Monday,Wednesday,Friday"
            vector<string> vDays = clsString::Split(DaysString, ",");
            for (string& Day : vDays) {
                vWorkingDays.push_back(_WorkingDaysNumber(Day));
            }
        }

        return clsDoctors(enMode::UpdateMode, stoi(vDoctorData[0]), vDoctorData[1], vDoctorData[2], vDoctorData[3]
            , vDoctorData[4], _SpecializationNumber(vDoctorData[5]), stod(vDoctorData[6]),
            vWorkingDays, vDoctorData[8], vDoctorData[9], _ClinicNumberNumber(vDoctorData[10]));
    }

    static string ConvertDoctorObjectToLine(clsDoctors Doctor, string Seperator = "#//#") {
        string Line = "";
        Line += to_string(Doctor._DoctorID) + Seperator;
        Line += Doctor.GetFirstName() + Seperator;
        Line += Doctor.GetLastName() + Seperator;
        Line += Doctor.GetPhone() + Seperator;
        Line += Doctor.GetEmail() + Seperator;
        Line += _SpecializationText(Doctor._Specialization) + Seperator;
        Line += to_string(Doctor._ConsultationFee) + Seperator;
        Line += _WorkingDaysText(Doctor._WorkingDays) + Seperator;
        Line += Doctor._WorkingHoursStart + Seperator;
        Line += Doctor._WorkingHoursEnd + Seperator;
        Line += _ClinicNumberText(Doctor._ClinicNumber);
        return Line;
    }

    static void _SaveDoctorsDataToFile(vector <clsDoctors> vDoctors)
    {
        fstream MyFile;
        MyFile.open("Doctor.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {
            for (clsDoctors& D : vDoctors)
            {
                if (D.MarkedForDeleted == false)
                {
                    DataLine = ConvertDoctorObjectToLine(D);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }

    static vector<clsDoctors> _LoadDoctorFromFile() {
        fstream MyFile;
        vector<clsDoctors> vDoctors;

        MyFile.open("Doctor.txt", ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                if (Line != "") {
                    clsDoctors Doctor = ConvertDoctorLineToObject(Line);
                    vDoctors.push_back(Doctor);
                }
            }
            MyFile.close();
        }
        return vDoctors;
    }

    static bool IsSameName(string NameFromFile, string InputName) {
        string UpperNameFromFile = clsString::UpperAllString(NameFromFile);
        string UpperInputName = clsString::UpperAllString(InputName);

        return (UpperNameFromFile == UpperInputName);
    }

    void _Update()
    {
        vector <clsDoctors> vDoctors = GetAllDoctors();

        for (clsDoctors& P : vDoctors)
        {
            if (P.GetDoctorID() == _DoctorID)
            {
                P = *this;
                break;
            }
        }
        _SaveDoctorsDataToFile(vDoctors);
    }

    void _AddNew()
    {
        _AddDataLineToFile(ConvertDoctorObjectToLine(*this));
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("Doctor.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

public:
    
    clsDoctors(enMode Mode, short DoctorID, string FirstName, string LastName, string Phone, string Email,
        short Specialization, double ConsultationFee, vector<short> WorkingDays,
        string WorkingHoursStart, string WorkingHoursEnd, short ClinicNumber) :
        clsPerson(FirstName, LastName, Phone, Email) {
        _Mode = Mode;
        _DoctorID = DoctorID;
        _Specialization = Specialization;
        _ConsultationFee = ConsultationFee;
        _WorkingDays = WorkingDays;
        _WorkingHoursStart = WorkingHoursStart;
        _WorkingHoursEnd = WorkingHoursEnd;
        _ClinicNumber = ClinicNumber;
        _IsActive = true;
    }    

    bool IsEmpty() {
        return (_Mode == enMode::EmptyMode);
    }

    void SetDoctorID(short DoctorID) { _DoctorID = DoctorID; }
    short GetDoctorID() { return _DoctorID; }
    __declspec(property(get = GetDoctorID, put = GetDoctorID))short DoctorID;

    string GetFullName() { return FullName(); }

    void SetSpecialization(short Specialization) { _Specialization = Specialization; }
    short GetSpecialization() { return _Specialization; }
    __declspec(property(get = GetSpecialization, put = SetSpecialization))short Specialization;

    void SetConsultationFee(double Fee) { _ConsultationFee = Fee; }
    double GetConsultationFee() { return _ConsultationFee; }
    __declspec(property(get = GetConsultationFee, put = SetConsultationFee))double ConsultationFee;

    void SetWorkingDays(vector<short> Days) { _WorkingDays = Days; }
    vector<short> GetWorkingDays() { return _WorkingDays; }
    __declspec(property(get = GetWorkingDays, put = SetWorkingDays))vector<short> WorkingDays;

    void SetWorkingHoursStart(string Start) { _WorkingHoursStart = Start; }
    string GetWorkingHoursStart() { return _WorkingHoursStart; }
    __declspec(property(get = GetWorkingHoursStart, put = SetWorkingHoursStart))string WorkingHoursStart;

    void SetWorkingHoursEnd(string End) { _WorkingHoursEnd = End; }
    string GetWorkingHoursEnd() { return _WorkingHoursEnd; }
    __declspec(property(get = GetWorkingHoursEnd, put = SetWorkingHoursEnd))string WorkingHoursEnd;

    void SetClinicNumber(short ClinicNumber) { _ClinicNumber = ClinicNumber; }
    short GetClinicNumber() { return _ClinicNumber; }
    __declspec(property(get = GetClinicNumber, put = SetClinicNumber))short ClinicNumber;

    void SetIsActive(bool Active) { _IsActive = Active; }
    bool GetIsActive() { return _IsActive; }
    __declspec(property(get = GetIsActive, put = SetIsActive))bool IsActive;


    string GetSpecializationText() { return _SpecializationText(_Specialization); }
    string GetWorkingDaysText() { return _WorkingDaysText(_WorkingDays); }
    string GetClinicNumberText() { return _ClinicNumberText(_ClinicNumber); }

    static void SplitFullName(string FullName, string& FirstName, string& LastName) {
        vector<string> vName = clsString::Split(FullName, " ");
        if (vName.size() >= 2) {
            FirstName = vName[0];
            LastName = vName[1];
            for (size_t i = 2; i < vName.size(); i++) {
                LastName += " " + vName[i];
            }
        }
        else {
            FirstName = FullName;
            LastName = "";
        }
    }

    static vector<clsDoctors> GetAllDoctors() {
        return _LoadDoctorFromFile();
    }

    static clsDoctors FindDoctorID(short DoctorID) {
        fstream MyFile;
        MyFile.open("Doctor.txt", ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsDoctors Doctor = ConvertDoctorLineToObject(Line);
                if (Doctor.GetDoctorID() == DoctorID) {
                    MyFile.close();
                    return Doctor;
                }
            }
        }
        return _GetEmptyDoctorObject();
    }

    static clsDoctors FindFullName(string FullName) {
        fstream MyFile;
        MyFile.open("Doctor.txt", ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsDoctors Doctor = ConvertDoctorLineToObject(Line);
                if (IsSameName(Doctor.FullName(), FullName)) {
                    MyFile.close();
                    return Doctor;
                }
            }
        }
        return _GetEmptyDoctorObject();
    }

    static void FindBySpecialization(short Specialization, vector<clsDoctors>& vDoctors) {
        vector<clsDoctors> vSpecializationDoctors;

        for (clsDoctors& D : vDoctors) {
            if (D.GetSpecialization() == Specialization) {
                vSpecializationDoctors.push_back(D);
            }
        }
        vDoctors = vSpecializationDoctors;
    }

    static bool IsDoctorAvailable(short DoctorID, string Date, string Time) {
        // To be implemented later 
        // create class clsAppointment and Appointments.txt
        return true;
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildIDOrFullNameExists = 2 };

    enSaveResults Save() {
        switch (_Mode) {
        case enMode::EmptyMode:
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        case enMode::AddNewMode:
            if (clsDoctors::IsDoctorExists(_DoctorID)) {
                return enSaveResults::svFaildIDOrFullNameExists;
            }
            else
            {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
        }
        }
        return enSaveResults::svFaildEmptyObject;
    }

    static void Save(vector <clsDoctors> vDoctors) {
        fstream MyFile;
        MyFile.open("Doctor.txt", ios::out);

        string DataLine;

        if (MyFile.is_open())
        {
            for (clsDoctors& D : vDoctors)
            {
                if (D.MarkedForDeleted == false)
                {
                    DataLine = ConvertDoctorObjectToLine(D);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }

    static void Delete(vector <clsDoctors>& vDoctors, short DoctorID) {
        MarkDoctorForDeleteByDoctorID(DoctorID, vDoctors);
        Save(vDoctors);
        vDoctors = GetAllDoctors();
    }

    static void Delete(clsDoctors& Doctor) {
        vector <clsDoctors> vDoctors = GetAllDoctors();
        MarkDoctorForDeleteByDoctorID(Doctor.FullName(), vDoctors);
        Save(vDoctors);
        vDoctors = GetAllDoctors();
    }

    static vector<string> GetWorkingDaysList(short DoctorID) {
        vector<string> vWorkingDaysLists;
        vector<clsDoctors> vDoctors = GetAllDoctors();

        for (clsDoctors& Do : vDoctors) {
            if (DoctorID == Do.GetDoctorID()) {
                vWorkingDaysLists.push_back(Do.GetWorkingDaysText());
                vWorkingDaysLists.push_back(Do.GetWorkingHoursStart());
                vWorkingDaysLists.push_back(Do.GetWorkingHoursEnd());
                break;
            }
        }
        return vWorkingDaysLists;
    }

    static clsDoctors GetAddNewDoctorObject(string FullName)
    {
        string FirstName, LastName;
        SplitFullName(FullName, FirstName, LastName);
        vector<short> EmptyDays;
        return clsDoctors(enMode::AddNewMode, 0, FirstName, LastName, "", "", 0, 0.0, EmptyDays, "", "", 0);
    }

    static bool IsDoctorExists(short ID)
    {
        clsDoctors Doctor = clsDoctors::FindDoctorID(ID);
        return (!Doctor.IsEmpty());
    }

    static bool IsDoctorExists(string FullName)
    {
        clsDoctors Doctor = clsDoctors::FindFullName(FullName);
        return (!Doctor.IsEmpty());
    }
};
