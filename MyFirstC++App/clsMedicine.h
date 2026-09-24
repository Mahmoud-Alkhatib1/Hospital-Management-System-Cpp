#pragma once
#include <vector>
#include "clsString.h"
#include <string>
#include <fstream>
#include "clsDate.h"
#include "clsInputValidate.h"

class clsMedicine
{
private :
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	short _MedicineID;
	string _Name;
	string _Category;
	double _Price;
	int _Quantity;

	bool MarkedForDeleted = false;

	static clsMedicine _GetEmptyMedicineObject() {
		return clsMedicine(enMode::EmptyMode , 0 , "" , "" , 0.0 , 0);
	}

	static string _ConvertMedicineObjectToLine(clsMedicine Medicine, string Seperator = "#//#") {
		string Line = "";

		Line += to_string(Medicine._MedicineID) + Seperator;
		Line += Medicine._Name + Seperator;
		Line += Medicine._Category + Seperator;
		Line += to_string(Medicine._Price) + Seperator;
		Line += to_string(Medicine._Quantity);

		return Line;
	}

	static clsMedicine _ConvertLineToMedicineObject(string Line, string Seperator = "#//#") {
		vector<string >vMedicines = clsString::Split(Line ,Seperator);

		return clsMedicine(enMode::UpdateMode, stoi(vMedicines[0]), vMedicines[1], vMedicines[2],
			stod(vMedicines[3]), stoi(vMedicines[4]));
	}

	static vector<clsMedicine> _LoadFromFile() {
		fstream MyFile;
		vector<clsMedicine>vMedicines;
		MyFile.open("Medicine.txt" , ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				if (Line != "") {
					clsMedicine Medicine = _ConvertLineToMedicineObject(Line);
					vMedicines.push_back(Medicine);
				}
			}MyFile.close();
		}
		return vMedicines;
	}

	static void _SaveToFile(vector<clsMedicine>& vMedicines) {
		fstream MyFile;

		string Line;

		MyFile.open("Medicine.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsMedicine& M : vMedicines)
			{
				if (M.MarkedForDeleted == false)
				{
					Line = _ConvertMedicineObjectToLine(M);
					MyFile << Line << endl;
				}
			}

			MyFile.close();
		}
	}

	static bool MarkMedicineForDeleteByMedicineID(short MedicineID, vector <clsMedicine>& vMedicines)
	{
		for (clsMedicine& M : vMedicines)
		{
			if (M.MedicineID == MedicineID)
			{
				M.MarkedForDeleted = true;
				return true;
			}
		}
		return false;
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertMedicineObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine) {
		fstream MyFile;
		MyFile.open("Medicine.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	void _Update() {
		vector<clsMedicine>vMedicines = _LoadFromFile();

		for (clsMedicine &M : vMedicines) {
			if (M.GetMedicineID() == _MedicineID) {
				M = *this;
				break;
			}
		}
		_SaveToFile(vMedicines);
	}

public:
	clsMedicine(enMode Mode ,short MedicineID, string Name, string Category, double Price, int Quantity) {
		_Mode = Mode;
		_MedicineID = MedicineID;
		_Name = Name;
		_Category = Category;
		_Price = Price;
		_Quantity = Quantity;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	void SetMedicineID(short MedicineID) { _MedicineID = MedicineID; }
	short GetMedicineID() { return _MedicineID; }
	__declspec(property(get = GetMedicineID, put = SetMedicineID))short MedicineID;

	void SetName(string Name) { _Name = Name; }
	string GetName() { return _Name; }
	__declspec(property(get = GetName, put = SetName))string Name;

	void SetCategory(string Category) { _Category = Category; }
	string GetCategory() { return _Category; }
	__declspec(property(get = GetCategory, put = SetCategory))string Category;

	void SetPrice(double Price) { _Price = Price; }
	double GetPrice() { return _Price; }
	__declspec(property(get = GetPrice, put = SetPrice))double Price;

	void SetQuantity(int Quantity) { _Quantity = Quantity; }
	int GetQuantity() { return _Quantity; }
	__declspec(property(get = GetQuantity, put = SetQuantity))int Quantity;

	static vector<clsMedicine> GetAllMedicine() {
		return _LoadFromFile();
	}

	static clsMedicine FindMedicineID(short MedicineID) {
		fstream MyFile;
		MyFile.open("Medicine.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsMedicine Medicine = _ConvertLineToMedicineObject(Line);
				if (Medicine.GetMedicineID() == MedicineID) {
					MyFile.close();
					return Medicine;
				}
			}
		}
		return _GetEmptyMedicineObject();

	}

	static clsMedicine FindByName(string Name) {
		fstream MyFile;
		MyFile.open("Medicine.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsMedicine Medicine = _ConvertLineToMedicineObject(Line);
				if (Medicine.GetName() == Name) {
					MyFile.close();
					return Medicine;
				}
			}
		}
		return _GetEmptyMedicineObject();

	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildIDExists = 2 };

	enSaveResults Save() {

		switch (_Mode) {
		case enMode::EmptyMode :
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
		case enMode::AddNewMode:
			if (clsMedicine::IsMedicineExists(MedicineID)) {
				return enSaveResults::svFaildIDExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;

		}

	}

	void Delete() {
		vector<clsMedicine> vMedicines = GetAllMedicine();
		MarkMedicineForDeleteByMedicineID(this->MedicineID , vMedicines);
		_SaveToFile(vMedicines);
	}

	bool Delete2() {
		vector<clsMedicine> vMedicines = GetAllMedicine();
		if(MarkMedicineForDeleteByMedicineID(this->MedicineID, vMedicines)) {
			_SaveToFile(vMedicines);
			return true;
		}
		return false;
	}


	static clsMedicine GetAddNewMedicineObject(short MedicineID) {
		return clsMedicine(enMode::AddNewMode , MedicineID , "" , "" , 0.0 , 0);
	}

	static bool IsMedicineExists(short MedicineID)
	{
		clsMedicine Medicine = clsMedicine::FindMedicineID(MedicineID);
		return (!Medicine.IsEmpty());
	}

	static bool IsMedicineExists(string Name)
	{
		clsMedicine Medicine = clsMedicine::FindByName(Name);
		return (!Medicine.IsEmpty());
	}
};

