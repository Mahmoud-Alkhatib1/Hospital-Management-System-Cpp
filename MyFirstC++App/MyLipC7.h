#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>

using namespace std;

namespace MyLipC7 {
	int RandomNumber(int From, int To)
	{
		return rand() % (To - From + 1) + From;
	}

	void FillMatrixWithRandomNumbers(int arr[3][3], short Rows, short cols) {
		for (int i = 0; i < Rows; i++) {

			for (int j = 0; j < cols; j++) {

				arr[i][j] = RandomNumber(1, 100);
			}
		}
	}

	void SumRowMatrix(int arr[3][3], short Rows, short cols) {
		int Sum = 0;
		for (int i = 0; i < Rows; i++) {

			for (int j = 0; j < cols; j++) {

				Sum += arr[i][j];
			}
			cout << " Row " << i + 1 << " Sum = " << setw(3) << Sum;
			cout << endl;
		}
	}

	bool AreTypicalMatrices(int Matrix[3][3], int Matrix2[3][3], short Rows, short cols) {
		for (int i = 0; i < Rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (Matrix[i][j] != Matrix2[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	bool IsIdentityMatrices(int Matrix[3][3], short Rows, short cols) {

		for (int i = 0; i < Rows; i++) {

			for (int j = 0; j < cols; j++) {

				if (i == j && Matrix[i][j] != 1) {
					return false;
				}
				else if (i != j && Matrix[i][j] != 0) {
					return false;
				}
			}
		}
		return true;
	}

	short MinmumNumberInMatrix(int Matrix[3][3], short Rows, short cols) {

		short Min = Matrix[0][0];
		for (int i = 0; i < Rows; i++) {

			for (int j = 0; j < cols; j++) {
				if (Matrix[i][j] < Min) {
					Min = Matrix[i][j];
				}
			}
		}
		return Min;
	}

	short MaxmumNumberInMatrix(int Matrix[3][3], short Rows, short cols) {

		short Max = Matrix[0][0];
		for (int i = 0; i < Rows; i++) {

			for (int j = 0; j < cols; j++) {
				if (Matrix[i][j] > Max) {
					Max = Matrix[i][j];
				}
			}
		}
		return Max;
	}

	int IsPalindromeMatrix(int Matrix[3][3], short Rows, short cols) {
		for (int i = 0; i < Rows; i++) {

			for (int j = 0; j < cols / 2; j++) {
				if (Matrix[i][j] != Matrix[i][cols - 1 - j]) {
					return false;
				}
			}
		}
		return true;
	}

	void PrintFirstLetter(string string1) {

		bool isFirstLetter = true;

		cout << "First Letters of This string: \n";
		for (short i = 0; i < string1.length(); i++) {
			if (string1[i] != ' ' && isFirstLetter) {
				cout << string1[i] << endl;
			}
			isFirstLetter = (string1[i] == ' ' ? true : false);
		}
	}

	string UpperFirstLetterOfEachWord(string string1) {

		bool isFirstLetter = true;

		cout << "First Letters of This string: \n";
		for (short i = 0; i < string1.length(); i++) {
			if (string1[i] != ' ' && isFirstLetter) {
				string1[i] = toupper(string1[i]);
			}
			isFirstLetter = (string1[i] == ' ' ? true : false);
		}
		return string1;
	}

	string LowerFirstLetterOfEachWord(string string1) {

		bool isFirstLetter = true;

		cout << "First Letters of This string: \n";
		for (short i = 0; i < string1.length(); i++) {
			if (string1[i] != ' ' && isFirstLetter) {
				string1[i] = tolower(string1[i]);
			}
			isFirstLetter = (string1[i] == ' ' ? true : false);
		}
		return string1;
	}

	string UpperAllString(string string1) {

		for (short i = 0; i < string1.length(); i++) {
			string1[i] = toupper(string1[i]);
		}
		return string1;
	}

	string LowerAllString(string string1) {

		for (short i = 0; i < string1.length(); i++) {
			string1[i] = tolower(string1[i]);
		}
		return string1;
	}


	char InvertLetterCase(char Ch1) {
		return isupper(Ch1) ? tolower(Ch1) : toupper(Ch1);
	}


	string InvertAllStringLetterCase(string string1) {
		for (int i = 0; i < string1.length(); i++) {
			string1[i] = InvertLetterCase(string1[i]);
		}
		return string1;
	}

	short CountCapitalLetters(string string1) {
		short Counter = 0;

		for (int i = 0; i < string1.length(); i++) {
			if (isupper(string1[i]))
				Counter++;
		}
		return Counter;
	}

	short CountSmallLetters(string string1) {
		short Counter = 0;

		for (int i = 0; i < string1.length(); i++) {
			if (islower(string1[i]))
				Counter++;
		}
		return Counter;
	}

	short CountLetters(string string1, char ch1) {
		short counter = 0;

		for (int i = 0; i < string1.length(); i++) {
			if (string1[i] == ch1) {
				counter++;
			}
		}
		return counter;
	}

	short CountLetters(string string1, char Letter, bool MatchCase = true) {
		short counter = 0;

		for (int i = 0; i < string1.length(); i++) {
			if (MatchCase) {
				if (string1[i] == Letter) {
					counter++;
				}
			}
			else {
				if (tolower(string1[i]) == tolower(Letter))
					counter++;
			}
		}
		return counter;
	}

	bool IsVowel(char Letter) {
		Letter = tolower(Letter);

		return ((Letter == 'a') || (Letter == 'e') || (Letter == 'i') || (Letter == 'o') || (Letter == 'u'));

	}

	short CountVowels(string string1) {
		short counter = 0;

		for (int i = 0; i < string1.length(); i++) {
			if (IsVowel(string1[i]))
				counter++;
		}
		return counter;
	}

	short CountWords(string string1) {
		string delim = " ";

		short pos = 0;
		string sWord;
		short counter = 0;

		while ((pos = string1.find(delim)) != std::string::npos) {
			sWord = string1.substr(0, pos);
			if (sWord != " ") {
				counter++;
			}
			string1.erase(0, pos + delim.length());
		}
		if (string1 != " ") {
			counter++;
		}
		return counter;
	}

	vector<string> SplitString(string S1, string Delim)
	{

		vector<string> vString;

		short pos = 0;
		string sWord;   

		while ((pos = S1.find(Delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);    
			if (sWord != "")
			{
				vString.push_back(sWord);
			}

			S1.erase(0, pos + Delim.length()); 
		}

		if (S1 != "")
		{
			vString.push_back(S1); 
		}

		return vString;

	}


	string TrimLeft(string string1) {
		for (short i = 0; i < string1.length(); i++) {
			if (string1[i] != ' ') {
				return string1.substr(i, string1.length() - i);
			}
		}
		return "";
	}

	string TrimRight(string string1) {
		for (short i = string1.length() - 1; i >= 0; i--) {
			if (string1[i] != ' ') {
				return string1.substr(0, i + 1);
			}
		}
		return "";
	}

	string Trim(string string1) {
		return (TrimLeft(TrimRight(string1)));
	}

	string JoinString(vector <string> vString, string Delim) {

		string S1 = "";
		for (string& s : vString) {
			S1 = S1 + s + Delim;
		}
		return S1.substr(0, S1.length() - Delim.length());
	}


	string JoinString(string Arr[], short Length, string Delim) {

		string S1 = "";
		for (short i = 0; i < Length; i++) {
			S1 = S1 + Arr[i] + Delim;
		}
		return S1.substr(0, S1.length() - Delim.length());
	}


	string ReverseWordInString(string string1) {

		vector <string> vString;
		string S2 = "";

		vString = SplitString(string1, " ");

		vector <string>::iterator iter = vString.end();

		while (iter != vString.begin()) {

			--iter;

			S2 += *iter + " ";
		}
		S2 = S2.substr(0, S2.length() - 1);

		return S2;
	}

	string ReplaceWordInStringUsingBuiltInFunction(string string1, string StringToReplace,
		string ReplaceTo) {

		short pos = string1.find(StringToReplace);

		while (pos != std::string::npos) {
			string1 = string1.replace(pos, StringToReplace.length(), ReplaceTo);
			pos = string1.find(StringToReplace);
		}

		return string1;
	}


	string ReplaceWordInStringUsingSplit(string string1, string StringToReplace,
		string ReplaceTo, bool matchCase = true) {

		vector<string>vString = SplitString(string1, " ");

		for (string& s : vString) {
			if (matchCase) {
				if (s == StringToReplace) {
					s = ReplaceTo;
				}
			}
			else {
				if (LowerAllString(s) == LowerAllString(StringToReplace)) {
					s = ReplaceTo;
				}
			}
		}
		return JoinString(vString, " ");
	}

	string RemovePunctuationsFromString(string string1) {
		string s = "";

		for (short i = 0; i < string1.length(); i++) {
			if (!ispunct(string1[i])) {

				s += string1[i];
			}
		}
		return s;
	}

}
