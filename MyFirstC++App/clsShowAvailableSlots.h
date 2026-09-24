#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsAppointment.h"
#include "clsInputValidate.h"
#include "clsPatients.h"
#include "clsDoctors.h"
#include <iomanip>
#include "clsString.h"

class clsShowAvailableSlots : protected clsScreen
{
private:

    static short _ReadDoctorID(vector<clsDoctors>& DoctorsName) {
        cout << "\nSelect Doctor:\n\n";

        for (clsDoctors& Do : DoctorsName) {
            cout << "[" << Do.GetDoctorID() << "] " << Do.GetFullName()
                << " - " << Do.GetSpecializationText() << endl;
        }

        cout << "\nEnter Doctor ID: ";
        short DoctorID = clsInputValidate::ReadShortNumber();

        for (clsDoctors& Do : DoctorsName) {
            if (DoctorID == Do.GetDoctorID()) {
                cout << "\n Doctor Selected: " << Do.GetFullName() << endl;
                break;
            }
        }
        return DoctorID;
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

    static void _PrintAvailableSlotsTable(short DoctorID, string Date, vector<string> vWorkDays,
        vector<clsAppointment>& vAllAppointments) {

        // «” Œ—«Ã Êﬁ  «·»œ¡ ÊÊﬁ  «·«‰ Â«¡
        string StartTime = vWorkDays[1];
        string EndTime = vWorkDays[2];

        int StartHour = stoi(clsString::Split(StartTime, ":")[0]);
        int EndHour = stoi(clsString::Split(EndTime, ":")[0]);

        //  Ã„Ì⁄ «·”«⁄«  «·„ÕÃÊ“… ›Ì Â–« «·ÌÊ„
        vector<string> vBookedTimes;
        for (clsAppointment& App : vAllAppointments) {
            if (App.GetDoctorID() == DoctorID && App.GetDate() == Date) {
                vBookedTimes.push_back(App.GetTime());
            }
        }

        // ÿ»«⁄… —√” «·ÃœÊ·
        cout << "\n===========================================================\n";
        cout << "   Available Slots for " << clsDoctors::FindDoctorID(DoctorID).GetFullName() << endl;
        cout << "   Date: " << Date << endl;
        cout << "===========================================================\n";
        cout << "| " << setw(10) << left << "Time";
        cout << "| " << setw(15) << left << "Status";
        cout << "|\n";
        cout << "===========================================================\n";

        vector<string> vFreeSlots;

        // ÿ»«⁄… ﬂ· ”«⁄… „‰ Êﬁ  «·»œ¡ ≈·Ï Êﬁ  «·«‰ Â«¡
        for (int Hour = StartHour; Hour < EndHour; Hour++) {
            string TimeStr = (Hour < 10 ? "0" + to_string(Hour) : to_string(Hour)) + ":00";

            bool IsBooked = false;
            for (string& BookedTime : vBookedTimes) {
                if (BookedTime == TimeStr) {
                    IsBooked = true;
                    break;
                }
            }

            string Status = IsBooked ? "Booked" : "Free";

            if (!IsBooked) {
                vFreeSlots.push_back(TimeStr);
            }

            cout << "| " << setw(10) << left << TimeStr;
            cout << "| " << setw(15) << left << Status;
            cout << "|\n";
        }

        cout << "===========================================================\n";

        // ⁄—÷ ﬁ«∆„… «·”«⁄«  «·›«—€…
        if (!vFreeSlots.empty()) {
            cout << "\n Free Slots: ";
            for (size_t i = 0; i < vFreeSlots.size(); i++) {
                cout << vFreeSlots[i];
                if (i != vFreeSlots.size() - 1) cout << ", ";
            }
            cout << endl;
        }
        else {
            cout << "\n No free slots available on this day!\n";
        }
    }

public:
    static void ShowAvailableSlots() {
        _DrawScreenHeader("\t  Show Available Slots");

        // 1. ⁄—÷ ﬁ«∆„… «·√ÿ»«¡ Ê«Œ Ì«— ÿ»Ì»
        vector<clsDoctors> vDoctors = clsDoctors::GetAllDoctors();

        if (vDoctors.empty()) {
            cout << "\n\t No Doctors Found!\n";
            return;
        }

        short DoctorID = _ReadDoctorID(vDoctors);

        // 2. «·Õ’Ê· ⁄·Ï √Ì«„ ⁄„· «·ÿ»Ì»
        vector<string> vWorkDays = clsDoctors::GetWorkingDaysList(DoctorID);

        if (vWorkDays.empty() || vWorkDays[0].empty()) {
            cout << "\n\t Doctor schedule not available!\n";
            return;
        }

        // 3. ≈œŒ«· «· «—ÌŒ
        cout << "\nEnter Date (DD/MM/YYYY): ";
        string Date = clsInputValidate::ReadString();

        // 4. «· Õﬁﬁ „‰ √‰ «· «—ÌŒ ÂÊ ÌÊ„ ⁄„· ··ÿ»Ì»
        clsDate AppointmentDate(Date);
        int DayNumber = clsDate::DayOfWeekOrder(AppointmentDate.GetDay(),
            AppointmentDate.GetMonth(),
            AppointmentDate.GetYear());
        string DayName = clsDate::DayShortName2(DayNumber);

        if (!IsDayInWorkingDays(DayName, vWorkDays)) {
            cout << "\n\t Doctor does not work on " << DayName << "!\n";
            cout << "\t   Working days: " << vWorkDays[0] << endl;
            return;
        }

        // 5. «· Õﬁﬁ „‰ √‰ «· «—ÌŒ ·Ì” ﬁ»· «·ÌÊ„ «·Õ«·Ì
        clsDate CurrentDate = clsDate::GetSystemDate();
        if (clsDate::IsDate1BeforeDate2(AppointmentDate, CurrentDate)) {
            cout << "\n\t Cannot check availability for past dates!\n";
            return;
        }

        // 6.  Õ„Ì· «·„Ê«⁄Ìœ Ê⁄—÷ «·ÃœÊ·
        vector<clsAppointment> vAllAppointments = clsAppointment::GetAllAppointment();

        _PrintAvailableSlotsTable(DoctorID, Date, vWorkDays, vAllAppointments);
    }
};

