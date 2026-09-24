#pragma once

#include <iostream>
#include <queue>
#include <string>

using namespace std;

class clsPrintJob
{
private:
	short _TotalJobs = 0;     
	short _NextNumber = 1;      


	class clsJob {
	private:
		string _Username;
		short _Pages;
		short _Number;

	public:
		clsJob(string user, short pages, short number) {
			_Username = user;
			_Pages = pages;
			_Number = number;
		}

		string GetUser() { return _Username; }
		
		short GetPages() { return _Pages; }
		
		short GetNumber() { return _Number; }

		short ServerTime() {
			return _Pages * 2;
		}

		void Print() {
			cout << "Position " << _Number << " -> " << _Username
				<< " | " << _Pages << " pages | " << ServerTime() << " sec\n";
		}
	};

public:
	queue<clsJob> PrintQueue;

	void AddJob(string user, short pages) {

		clsJob newJob(user, pages, _NextNumber++);

		PrintQueue.push(newJob);

		_TotalJobs++;

		cout << " Added : " << user << " (" << pages << " pages)\n";
	}

	short WaitingJobs() {
		return PrintQueue.size();
	}

	void PrintNext() {
		if (PrintQueue.empty()) {
			cout << " No jobs to print!\n";
			return;
		}

		cout << " Printing: ";
		PrintQueue.front().Print();
		PrintQueue.pop();
	}

	void ShowQueue() {
		if (PrintQueue.empty()) {
			cout << "\n================================\n";
			cout << "      PRINT QUEUE STATUS\n";
			cout << "================================\n";
			cout << "Queue is empty!\n";
			cout << "================================\n";
			return;
		}

		cout << "\n================================\n";
		cout << "      PRINT QUEUE STATUS\n";
		cout << "================================\n";

		queue<clsJob> temp = PrintQueue;
		while (!temp.empty()) {
			temp.front().Print();
			temp.pop();
		}

		cout << "--------------------------------\n";
		cout << "Total pages waiting: " << TotalPages() << " pages\n";
		cout << "Total jobs waiting: " << WaitingJobs() << "\n";
		cout << "================================\n";
	}

	short TotalPages() {
		queue<clsJob> temp = PrintQueue;
		short total = 0;
		while (!temp.empty()) {
			total += temp.front().GetPages();
			temp.pop();
		}
		return total;
	}

};

