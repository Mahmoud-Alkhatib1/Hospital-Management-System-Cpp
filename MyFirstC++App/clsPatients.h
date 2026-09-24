#pragma once
#include <vector>
#include "clsString.h"
#include "clsDate.h"
#include "clsInputValidate.h"

class clsPatients : clsScreen
{
protected:
    enum enGender { eMale = 1, eFemale = 2 };
    enum eChronicDiseases {
        eNone = 0, eHypertension = 1, eDiabetes = 2, eHeartDisease = 3,
        eAsthma = 4, eKidneyDisease = 5, eThyroidDisorder = 6, eMoreThanOneDisease = 7, eOther = 8
    };
    enum enBloodType {
        eAPositive = 1, eANegative = 2, eBPositive = 3, eBNegative = 4,
        eOPositive = 5, eONegative = 6, eABPositive = 7, eABNegative = 8
    };
    enum enDrugAllergy {
        eNoAllergy = 0,
        ePenicillin = 1,
        eAspirin = 2,
        eIbuprofen = 3,
        eParacetamol = 4,
        ePenicillinAndOther = 5  
    };

    struct stPatient {
        short PatientID = 0;
        string FullName = "";
        string PhoneNumber = "";
        string BirthDate = "";
        short Gender = 0;
        string Address = "";
        string FirstVisitDate = "";
        string LastVisitDate = "";
        short ChronicDiseases = 0;
        short BloodType = 0;
        short DrugAllergy = 0;

        bool MarkedForDeleted = false;
    };

    static vector<string> Split(string S1, string Delim) {
        vector<string> vString;
        short pos = 0;
        string sWord;
        while ((pos = S1.find(Delim)) != std::string::npos) {
            sWord = S1.substr(0, pos);
            if (sWord != "") vString.push_back(sWord);
            S1.erase(0, pos + Delim.length());
        }
        if (S1 != "") vString.push_back(S1);
        return vString;
    }

    //*******************************************************************************
    struct stVisit {
        short VisitID;           // —ﬁ„ «·“Ì«—… )  ·ﬁ«∆Ì)
        short PatientID;         // —ﬁ„ «·„—Ì÷ ) ··—»ÿ)
        string VisitDate;        //  «—ÌŒ «·“Ì«—…
        string DoctorName;       // «”„ «·ÿ»Ì»
        string Diagnosis;        // «· ‘ŒÌ’
        string Notes;            // „·«ÕŸ«  ≈÷«›Ì…
    };

    static string ConvertVisitObjectToLine(stVisit Visit, string Seperator = "#//#") {
        string LinePatienType = "";
        LinePatienType += to_string(Visit.VisitID) + Seperator;
        LinePatienType += Visit.VisitDate + Seperator;
        LinePatienType += Visit.DoctorName + Seperator;
        LinePatienType += Visit.Diagnosis + Seperator;
        
        return LinePatienType;
    }

    static stVisit ConvertVisitLineToObject(string Line, string Seperator = "#//#") {
        vector<string> vVisitData;
        stVisit Visit;
        vVisitData = clsString::Split(Line, Seperator);

        Visit.VisitID = stoi(vVisitData[0]);
        Visit.VisitDate = vVisitData[1];
        Visit.DoctorName = vVisitData[2];
        Visit.Diagnosis = vVisitData[3];
       
        return Visit;

    }
    //*******************************************************************************

    struct stDate { int Year, Month, Day; };

    static stDate GetSystemDate() {
        stDate Date;
        time_t t = time(0);
        tm* now = localtime(&t);
        Date.Year = now->tm_year + 1900;
        Date.Month = now->tm_mon + 1;
        Date.Day = now->tm_mday;
        return Date;
    }

    static stDate StringToDate(string DateString) {
        stDate Date;
        vector<string> vDate = clsString::Split(DateString, "/");
        Date.Day = stoi(vDate[0]);
        Date.Month = stoi(vDate[1]);
        Date.Year = stoi(vDate[2]);
        return Date;
    }

    static bool IsDate1BeforeDate2(stDate Date1, stDate Date2) {
        return (Date1.Year < Date2.Year) ? true :
            ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true :
                (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
    }

    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {
        return (Date1.Year < Date2.Year) ? true :
            ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true :
                (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
    }

    static void SwapDates(stDate& Date1, stDate& Date2) {
        stDate TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }

    static bool IsLastDayInMonth(stDate Date) {
        return (Date.Day == clsDate::NumberOfDaysInAMonth(Date.Month, Date.Year));
    }

    static stDate AddOneDay(stDate Date) {
        if (IsLastDayInMonth(Date)) {
            if (clsDate::IsLastMonthInYear(Date.Month)) {
                Date.Month = 1; Date.Day = 1; Date.Year++;
            }
            else {
                Date.Day = 1; Date.Month++;
            }
        }
        else {
            Date.Day++;
        }
        return Date;
    }

    static int GetDifferenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay = false) {
        int Days = 0;
        short SawpFlagValue = 1;
        if (!IsDate1BeforeDate2(Date1, Date2)) {
            SwapDates(Date1, Date2);
            SawpFlagValue = -1;
        }
        while (IsDate1BeforeDate2(Date1, Date2)) {
            Days++;
            Date1 = AddOneDay(Date1);
        }
        return IncludeEndDay ? ++Days * SawpFlagValue : Days * SawpFlagValue;
    }

    static int AgeNumber(stPatient Patient) {
        stDate Date1 = StringToDate(Patient.BirthDate);
        stDate Date2 = GetSystemDate();
        return GetDifferenceInDays(Date1, Date2) / 365;  //  ﬁ—Ì»«
    }

    static string GenderText(short Gender) {
        string ArrayGender[2] = { "Male", "FeMale" };
        return ArrayGender[Gender - 1];
    }

    static short GenderToNumber(string GenderText) {
        if (GenderText == "Male") return 1;
        if (GenderText == "FeMale") return 2;
        return 1;
    }

    static string ChronicDiseasesText(short ChronicDiseases) {
        string ArrayChronic[9] = { "None", "Hypertension", "Diabetes", "HeartDisease",
                                   "Asthma", "KidneyDisease", "ThyroidDisorder","MoreThanOneDisease" ,"Other" };
        return ArrayChronic[ChronicDiseases];
    }

    static short ChronicDiseasesToNumber(string DiseaseText) {
        if (DiseaseText == "None") return 0;
        if (DiseaseText == "Hypertension") return 1;
        if (DiseaseText == "Diabetes") return 2;
        if (DiseaseText == "HeartDisease") return 3;
        if (DiseaseText == "Asthma") return 4;
        if (DiseaseText == "KidneyDisease") return 5;
        if (DiseaseText == "ThyroidDisorder") return 6;
        if (DiseaseText == "MoreThanOneDisease") return 7;
        if (DiseaseText == "Other") return 8;
        return 0;
    }

    static string BloodTypeText(short BloodType) {
        string ArrayBlood[8] = { "A+", "A-", "B+", "B-", "O+", "O-", "AB+", "AB-" };
        return ArrayBlood[BloodType - 1];
    }

    static short BloodTypeToNumber(string BloodText) {
        if (BloodText == "A+") return 1;
        if (BloodText == "A-") return 2;
        if (BloodText == "B+") return 3;
        if (BloodText == "B-") return 4;
        if (BloodText == "O+") return 5;
        if (BloodText == "O-") return 6;
        if (BloodText == "AB+") return 7;
        if (BloodText == "AB-") return 8;
        return 1;
    }

    static string DrugAllergyText(short Allergy) {
        string ArrayAllergy[6] = {
            "NoAllergies",
            "Penicillin",
            "Aspirin",
            "Ibuprofen",
            "Paracetamol",
            "Penicillin&Others"
        };
        return ArrayAllergy[Allergy];
    }

    static short DrugAllergyNumber(string AllergyText) {
        if (AllergyText == "NoAllergies") return 0;
        if (AllergyText == "Penicillin") return 1;
        if (AllergyText == "Aspirin") return 2;
        if (AllergyText == "Ibuprofen") return 3;
        if (AllergyText == "Paracetamol") return 4;
        if (AllergyText == "Penicillin&Others") return 5;
        return 0;
    }

    static string ConvertPatientObjectToLine(stPatient Patient, string Seperator = "#//#") {
        string LinePatienType = "";
        LinePatienType += to_string(Patient.PatientID) + Seperator;
        LinePatienType += Patient.FullName + Seperator;
        LinePatienType += Patient.PhoneNumber + Seperator;
        LinePatienType += Patient.BirthDate + Seperator;
        LinePatienType += GenderText(Patient.Gender) + Seperator;          
        LinePatienType += Patient.Address + Seperator;
        LinePatienType += Patient.FirstVisitDate + Seperator;
        LinePatienType += Patient.LastVisitDate + Seperator;
        LinePatienType += ChronicDiseasesText(Patient.ChronicDiseases) + Seperator;
        LinePatienType += DrugAllergyText(Patient.DrugAllergy) + Seperator;
        LinePatienType += BloodTypeText(Patient.BloodType);                          
        return LinePatienType;
    }

	static stPatient ConvertPatientLineToObject(string Line ,string Seperator = "#//#") {
		vector<string> vPatientData;
		stPatient Patient;
		vPatientData = clsString::Split(Line, Seperator);


		Patient.PatientID = stoi(vPatientData[0]);
		Patient.FullName = vPatientData[1];
		Patient.PhoneNumber = vPatientData[2];
		Patient.BirthDate = vPatientData[3];
		Patient.Gender = GenderToNumber(vPatientData[4]);
		Patient.Address = vPatientData[5];
		Patient.FirstVisitDate = vPatientData[6];
		Patient.LastVisitDate = vPatientData[7];
		Patient.ChronicDiseases = ChronicDiseasesToNumber(vPatientData[8]);
        Patient.DrugAllergy = DrugAllergyNumber(vPatientData[9]);
		Patient.BloodType = BloodTypeToNumber(vPatientData[10]);

		return Patient;

	}

    static vector<stPatient> LoadPatientToFile(string TextFile = "Patient.txt") {
        fstream MyFile;
        vector<stPatient> vPatient;

        MyFile.open(TextFile, ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                if (Line != "") {
                    stPatient Patient = ConvertPatientLineToObject(Line);
                    vPatient.push_back(Patient);
                }
            }
            MyFile.close();
        }
        return vPatient;
    }

    static bool MarkPatientForDeleteByPatientID(short PatientID, vector <stPatient>& vPatients)
    {

        for (stPatient& P : vPatients)
        {

            if (P.PatientID == PatientID)
            {
                P.MarkedForDeleted = true;
                return true;
            }

        }

        return false;
    }

	static stPatient EmptyToFilePatient() {
		stPatient Patient;
		Patient.PatientID = 0;
		Patient.FullName = "";
		Patient.PhoneNumber = "";
		Patient.BirthDate = "";
		Patient.Gender = 0;
		Patient.Address = "";
		Patient.FirstVisitDate = "";
		Patient.LastVisitDate = "";
		Patient.ChronicDiseases = 0;
		Patient.BloodType = 0;

		return Patient;
	}

    static void _SavePatientsToFile(string Patient) {

        fstream MyFile;

        MyFile.open("Patient.txt", ios::out | ios::app);
        if (MyFile.is_open()) {

            MyFile << Patient << endl;
            MyFile.close();
        }
    }

    static bool IsSameName(string NameFromFile, string InputName) {
        string UpperNameFromFile = clsString::UpperAllString(NameFromFile);
        string UpperInputName = clsString::UpperAllString(InputName);

        return (UpperNameFromFile == UpperInputName);
    }

public:

    bool MarkedForDeleted() {
        stPatient Patient;
        return Patient.MarkedForDeleted;
    }

    clsPatients() {

    }

    clsPatients(
        short PatientID ,string FullName ,string PhoneNumber ,string BirthDate ,short Gender ,string Address
        ,string FirstVisitDate ,string LastVisitDate ,short ChronicDiseases ,short BloodType
    ) {
        stPatient Patient;
        Patient.PatientID = PatientID;
        Patient.FullName = FullName;
        Patient.PhoneNumber = PhoneNumber;
        Patient.BirthDate = BirthDate;
        Patient.Gender = Gender;
        Patient.Address = Address;
        Patient.FirstVisitDate = FirstVisitDate;
        Patient.LastVisitDate = LastVisitDate;
        Patient.ChronicDiseases = ChronicDiseases;
        Patient.BloodType = BloodType;

    }



    static bool IsPatientExists(string FullName) {
        vector<stPatient> vPatients = LoadPatientToFile();

        for (stPatient& P : vPatients) {
            if (IsSameName(P.FullName, FullName)) {
                return true;  // «·«”„ „ÊÃÊœ
            }
        }
        return false;  // «·«”„ €Ì— „ÊÃÊœ (·«ÕŸ √‰ return false ÌÃ» √‰  ﬂÊ‰ »⁄œ «‰ Â«¡ «·Õ·ﬁ…)
    }

    static stPatient LastPatient() {
        vector <stPatient> vPatient = LoadPatientToFile();

        if (vPatient.empty()) {
            return EmptyToFilePatient();
        }
        return vPatient.back();
    }

    static void Save(string Patient) {
        _SavePatientsToFile(Patient);
    }

    static void Save(vector <stPatient> vPatients) {
            fstream MyFile;
            MyFile.open("Patient.txt", ios::out);//overwrite

            string DataLine;

            if (MyFile.is_open())
            {

                for (stPatient &P : vPatients)
                {
                    if (P.MarkedForDeleted == false)
                    {
                        //we only write records that are not marked for delete.  
                        DataLine = ConvertPatientObjectToLine(P);
                        MyFile << DataLine << endl;

                    }
                    else {
                        P = EmptyToFilePatient();
                    }

                }

                MyFile.close();

            }
    }

    static stPatient Find(short PatientID)
    {

        fstream MyFile;
        MyFile.open("Patient.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                stPatient Patient = ConvertPatientLineToObject(Line);
                if (Patient.PatientID == PatientID)
                {
                    MyFile.close();
                    return Patient;
                }

            }

            MyFile.close();

        }
        return EmptyToFilePatient();
    }

    static stPatient FindByName(string FullName) {
        fstream MyFile;
        MyFile.open("Patient.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                stPatient Patient = ConvertPatientLineToObject(Line);
                if (IsSameName(Patient.FullName , FullName))
                {
                    MyFile.close();
                    return Patient;
                }

            }

            MyFile.close();

        }
        return EmptyToFilePatient();
    }

    static vector <stPatient> Update(stPatient Patient)
    {
        vector <stPatient> vPatients;
        vPatients = LoadPatientToFile();

        for (stPatient& P : vPatients)
        {
            if (P.PatientID == Patient.PatientID)
            {
                P = Patient;
                break;
            }
        }
        Save(vPatients);
        return vPatients;
    }
    
    static void Delete(vector <stPatient>& vPatients ,short PatientID) {
        MarkPatientForDeleteByPatientID(PatientID, vPatients);
        Save(vPatients);

        vPatients = LoadPatientToFile();
    }

    static void UpdateLastVisitDate(short PatientID, string NewLastVisitDate) {
        vector<stPatient>vPatiants = LoadPatientToFile();

        for (stPatient & Pa : vPatiants) {
            if (Pa.PatientID == PatientID) {
                Pa.LastVisitDate = NewLastVisitDate;
                break;
            }
        }
        Save(vPatiants);
    }

    static vector<stPatient> GetAllPatient() {
        return LoadPatientToFile();
    }
};

