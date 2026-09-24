#pragma once

#include<iostream>
using namespace std;

namespace MyLib {
	void Text() {
		cout << "Hi , This is my First Library! " << endl;
	}

	int Sum2Numbers(int a, int b){
		return a + b;
	}
}