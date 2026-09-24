#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "clsString.h"
#include "clsDate.h"
#include "clsInputValidate.h"

class clsInvoice
{
private:
    enum enMode { EmptyMode = 0, AddNewMode = 1, UpdateMode = 2 };
    enum enPaymentMethod { eCash = 1, eCard = 2 };

    enMode _Mode;
    short _InvoiceID;
    short _PatientID;
    short _DoctorID;
    short _AppointmentID;
    double _ConsultationFee;
    double _MedicinesCost;
    double _Total;
    enPaymentMethod _PaymentMethod;
    string _Date;
    bool MarkedForDeleted = false;

    // ========== œÊ«· „”«⁄œ… Œ«’… ==========

    static clsInvoice _GetEmptyInvoiceObject() {
        return clsInvoice(enMode::EmptyMode, 0, 0, 0, 0, 0.0, 0.0, eCash, "");
    }

    static string _ConvertInvoiceObjectToLine(clsInvoice Invoice, string Seperator = "#//#") {
        string Line = "";
        Line += to_string(Invoice.GetInvoiceID()) + Seperator;
        Line += to_string(Invoice.GetPatientID()) + Seperator;
        Line += to_string(Invoice.GetDoctorID()) + Seperator;
        Line += to_string(Invoice.GetAppointmentID()) + Seperator;
        Line += to_string(Invoice.GetConsultationFee()) + Seperator;
        Line += to_string(Invoice.GetMedicinesCost()) + Seperator;
        Line += to_string(Invoice.GetTotal()) + Seperator;      // Total
        Line += to_string(Invoice.GetPaymentMethod()) + Seperator;  // PaymentMethod
        Line += Invoice.GetDate();                              // Date
        return Line;
    }

    static clsInvoice _ConvertLineToInvoiceObject(string Line, string Seperator = "#//#") {
        vector<string> vInvoiceData = clsString::Split(Line, Seperator);

        if (vInvoiceData.size() < 9) {
            return _GetEmptyInvoiceObject();
        }

        return clsInvoice(
            enMode::UpdateMode,
            stoi(vInvoiceData[0]),   // InvoiceID
            stoi(vInvoiceData[1]),   // PatientID
            stoi(vInvoiceData[2]),   // DoctorID
            stoi(vInvoiceData[3]),   // AppointmentID
            stod(vInvoiceData[4]),   // ConsultationFee
            stod(vInvoiceData[5]),   // MedicinesCost
            (enPaymentMethod)stoi(vInvoiceData[7]), // PaymentMethod («·›Â—” 7)
            vInvoiceData[8]          // Date («·›Â—” 8)
        );
    }

    static vector<clsInvoice> _LoadFromFile() {
        fstream MyFile;
        vector<clsInvoice> vInvoices;

        MyFile.open("Invoices.txt", ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                if (Line != "") {
                    clsInvoice Invoice = _ConvertLineToInvoiceObject(Line);
                    vInvoices.push_back(Invoice);
                }
            }
            MyFile.close();
        }
        return vInvoices;
    }

    static void _SaveToFile(vector<clsInvoice>& vInvoices) {
        fstream MyFile;
        MyFile.open("Invoices.txt", ios::out);

        if (MyFile.is_open()) {
            for (clsInvoice& Inv : vInvoices) {
                if (Inv.MarkedForDeleted == false) {
                    MyFile << _ConvertInvoiceObjectToLine(Inv) << endl;
                }
            }
            MyFile.close();
        }
    }

    void _AddNew() {
        vector<clsInvoice> vInvoices = _LoadFromFile();
        vInvoices.push_back(*this);
        _SaveToFile(vInvoices);
    }

    void _Update() {
        vector<clsInvoice> vInvoices = _LoadFromFile();
        for (clsInvoice& Inv : vInvoices) {
            if (Inv.GetInvoiceID() == _InvoiceID) {
                Inv = *this;
                break;
            }
        }
        _SaveToFile(vInvoices);
    }

    double _CalculateTotal() {
        return _ConsultationFee + _MedicinesCost;
    }

public:
    // ========== Constructor ==========
    clsInvoice(enMode Mode, short InvoiceID, short PatientID, short DoctorID,
        short AppointmentID, double ConsultationFee, double MedicinesCost,
        enPaymentMethod PaymentMethod, string Date) {
        _Mode = Mode;
        _InvoiceID = InvoiceID;
        _PatientID = PatientID;
        _DoctorID = DoctorID;
        _AppointmentID = AppointmentID;
        _ConsultationFee = ConsultationFee;
        _MedicinesCost = MedicinesCost;
        _Total = _CalculateTotal();
        _PaymentMethod = PaymentMethod;
        _Date = Date;
    }

    // ========== Getter & Setter ==========
    
    void SetInvoiceID(short InvoiceID) { _InvoiceID = InvoiceID; }
    short GetInvoiceID() { return _InvoiceID; }
    __declspec(property(get = GetInvoiceID, put = SetInvoiceID)) short InvoiceID;

    void SetPatientID(short PatientID) { _PatientID = PatientID; }
    short GetPatientID() { return _PatientID; }
    __declspec(property(get = GetPatientID, put = SetPatientID)) short PatientID;

    void SetDoctorID(short DoctorID) { _DoctorID = DoctorID; }
    short GetDoctorID() { return _DoctorID; }
    __declspec(property(get = GetDoctorID, put = SetDoctorID)) short DoctorID;

    void SetAppointmentID(short AppointmentID) { _AppointmentID = AppointmentID; }
    short GetAppointmentID() { return _AppointmentID; }
    __declspec(property(get = GetAppointmentID, put = SetAppointmentID)) short AppointmentID;

    void SetConsultationFee(double Fee) { _ConsultationFee = Fee; _Total = _CalculateTotal(); }
    double GetConsultationFee() { return _ConsultationFee; }
    __declspec(property(get = GetConsultationFee, put = SetConsultationFee)) double ConsultationFee;

    void SetMedicinesCost(double Cost) { _MedicinesCost = Cost; _Total = _CalculateTotal(); }
    double GetMedicinesCost() { return _MedicinesCost; }
    __declspec(property(get = GetMedicinesCost, put = SetMedicinesCost)) double MedicinesCost;

    void SetTotal(double Total) { _Total = Total; }
    double GetTotal() { return _Total; }
    __declspec(property(get = GetTotal , put = SetTotal)) double Total;

    void SetPaymentMethod(enPaymentMethod Method) { _PaymentMethod = Method; }
    enPaymentMethod GetPaymentMethod() { return _PaymentMethod; }
    __declspec(property(get = GetPaymentMethod, put = SetPaymentMethod)) enPaymentMethod PaymentMethod;

    void SetDate(string Date) { _Date = Date; }
    string GetDate() { return _Date; }
    __declspec(property(get = GetDate, put = SetDate)) string Date;

    bool IsEmpty() { return (_Mode == enMode::EmptyMode); }

    static clsInvoice GetEmptyInvoiceObject() {
        return _GetEmptyInvoiceObject();
    }


    // ========== œÊ«· ⁄«„… ==========

    static vector<clsInvoice> GetAllInvoices() {
        return _LoadFromFile();
    }

    static clsInvoice Find(short InvoiceID) {
        vector<clsInvoice> vInvoices = _LoadFromFile();
        for (clsInvoice& Inv : vInvoices) {
            if (Inv.GetInvoiceID() == InvoiceID) {
                return Inv;
            }
        }
        return _GetEmptyInvoiceObject();
    }

    static vector<clsInvoice> FindByPatientID(short PatientID) {
        vector<clsInvoice> vResult;
        vector<clsInvoice> vAll = _LoadFromFile();
        for (clsInvoice& Inv : vAll) {
            if (Inv.GetPatientID() == PatientID) {
                vResult.push_back(Inv);
            }
        }
        return vResult;
    }

    static short GetNewInvoiceID(vector<clsInvoice> vInvoices) {
        if (vInvoices.empty()) return 1;
        return vInvoices.back().GetInvoiceID() + 1;
    }

    static clsInvoice GetAddNewInvoiceObject(short InvoiceID ) {
        string Date = clsDate::DateToString(clsDate::GetSystemDate());
        return clsInvoice(enMode::AddNewMode, InvoiceID, 0, 0, 0,
            0.0, 0.0, enPaymentMethod::eCash, Date);
    }

    // ========== Save & Delete ==========

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildIDExists = 2 };

    enSaveResults Save() {
        switch (_Mode) {
        case enMode::EmptyMode:
            if (IsEmpty()) {
                return enSaveResults::svFaildEmptyObject;
            }
        case enMode::AddNewMode:
            if (clsInvoice::Find(_InvoiceID).IsEmpty() == false) {
                return enSaveResults::svFaildIDExists;
            }
            else {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
        case enMode::UpdateMode:
            _Update();
            return enSaveResults::svSucceeded;
        }
        return enSaveResults::svFaildEmptyObject;
    }

    bool Delete() {
        if (_Mode != enMode::UpdateMode) return false;

        vector<clsInvoice> vInvoices = _LoadFromFile();
        for (clsInvoice& Inv : vInvoices) {
            if (Inv.GetInvoiceID() == _InvoiceID) {
                Inv.MarkedForDeleted = true;
                _SaveToFile(vInvoices);
                return true;
            }
        }
        return false;
    }

    static bool IsInvoiceExists(short InvoiceID) {
        clsInvoice Invoice = clsInvoice::Find(InvoiceID);
        return (!Invoice.IsEmpty());
    }

    // ========== œÊ«· „”«⁄œ… ··⁄—÷ ==========

    static enPaymentMethod ReadPaymentMethod() {
        cout << "\nPayment Method:\n";
        cout << "[1] Cash\n";
        cout << "[2] Card\n";
        cout << "Enter your choice (1 or 2): ";

        short Choice = clsInputValidate::ReadShortNumberBetween(1, 2);

        return (Choice == 1) ? enPaymentMethod::eCash : enPaymentMethod::eCard;
    }

    static string GetPaymentMethodText(enPaymentMethod Method) {
        switch (Method) {
        case eCash: return "Cash";
        case eCard: return "Card";
        default: return "Unknown";
        }
    }

    string GetPaymentMethodText() {
        return GetPaymentMethodText(_PaymentMethod);
    }
};
