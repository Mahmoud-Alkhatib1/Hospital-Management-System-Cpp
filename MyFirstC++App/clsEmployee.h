#pragma once
#include<iostream>
#include"clsPerson.h";

using namespace std;

class clsEmployee : public clsPerson {
private:

    string _Title;
    float _Salary;
    string _Department;

public:

    clsEmployee(int ID, string FirstName, string LastName, string Email, string phone, string Title, string Department, float Salary)
        : clsPerson(ID, FirstName, LastName, Email, phone)
    {

        _Title = Title;
        _Department = Department;
        _Salary = Salary;
    }

    void SetTitle(string Title) {

        _Title = Title;
    }

    string GetTitle() {
        return _Title;
    }

    void SetSalary(float Salary) {

        _Salary = Salary;
    }

    float GetSalary() {
        return _Salary;
    }

    void SetDepartment(string Department) {

        _Department = Department;
    }

    string GetDepartment() {
        return _Department;
    }

    void Print() {
        //OverRiding
        cout << "\nInfo : \n";
        cout << "\n====================================";
        cout << "\nID          : " << ID() << endl;
        cout << "FirstName   : " << GetFirstName() << endl;
        cout << "LastName    : " << GetLastName() << endl;
        cout << "FullName    : " << FullName() << endl;
        cout << "Email       : " << GetEmail() << endl;
        cout << "Phone       : " << Getphone() << endl;
        cout << "Title       : " << _Title << endl;
        cout << "Department  : " << _Department << endl;
        cout << "Salary      : " << _Salary << endl;
        cout << "====================================\n\n";
    }
};


