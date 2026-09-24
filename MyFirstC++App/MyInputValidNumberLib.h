#pragma once
#include<iostream>

using namespace std;

namespace MyIV {
	int ReadNumber() {
		int Number = 0;
		cout << "Please enter a Number ? : ";
		cin >> Number;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid Number , Enter a Valid one " << endl;
			cin >> Number;
		}
		return Number;
	}
	float ReadPositiveNumber() {
		float Number = 0;
		do {
			cout << "Please enter a Number ? : ";
			cin >> Number;
		} while (Number <= 0);

		return Number;
	}

}

