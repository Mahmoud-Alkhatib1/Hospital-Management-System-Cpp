#pragma once
#include<iostream>

using namespace std;

namespace MyLipC5 {
    bool IsPerfectNumber(int Number) {
        int sum = 0;

        for (int i = 1; i < Number; i++) {
            if (Number % i == 0) {
                sum += i;
            }
        }
        return Number == sum;
    }
    
    int ReverseNumber(int Number) {

        int Remainder = 0, Number2 = 0;

        while (Number > 0) {

            Remainder = Number % 10;
            Number = Number / 10;
            Number2 = Number2 * 10 + Remainder;
        }
        return Number2;
    } 
    
    int SumOfDigits(int Number) {

        int Remainder = 0;
        int sum = 0;
        while (Number > 0) {
            Remainder = Number % 10;
            sum += Remainder;
            Number = Number / 10;
        }
        return sum;
    } 
    
    int CountDigitFrequency(short DigitToCheck, int Number)
    {
        int FreqCount = 0;
        int Remainder = 0;

        while (Number > 0)
        {
            Remainder = Number % 10;
            Number = Number / 10;

            if (DigitToCheck == Remainder)
            {
                FreqCount++;
            }
        }
        return FreqCount;
    } 
    bool GuessPassword(string OriginalPassword) {

        int counter = 0;
        string word = "";

        for (int i = 65; i <= 90; i++) {

            for (int j = 65; j <= 90; j++) {

                for (int k = 65; k <= 90; k++) {

                    counter++;

                    word = word + char(i);
                    word = word + char(j);
                    word = word + char(k);

                    cout << "Trial [" << counter << "] : " << word << endl;

                    if (OriginalPassword == word) {

                        cout << "\nPassword in = " << word << endl;
                        cout << "\Found After " << counter << "Trial(s)\n";
                        return true;
                    }
                    word = "";
                }
            }
        }
        return false;
    }  
    
    int TimesRepeated(int Number, int Array[100], int arrLength) {
        int Counter = 0;
        for (int i = 0; i <= arrLength - 1; i++) {
            if (Number == Array[i]) {
                Counter++;
            }
        }
        return Counter;
    } 
    
    void FillArrayWithRandomNumbers(int Array[100], int& arrLength) {

        cout << "\nEnter Number Of Elements : ";
        cin >> arrLength;

        for (int i = 0; i < arrLength; i++)
            Array[i] = RandomNumber(1, 100);

    } 
    
    int MaxNumberInArray(int Array[100], int arrLength) {

        int max = 0;
        for (int i = 0; i < arrLength; i++) {
            if (max < Array[i]) {
                max = Array[i];
            }
        }
        return max;
    } 
    
    int MinNumberInArray(int Array[100], int arrLength) {

        int min = Array[0];
        for (int i = 0; i < arrLength; i++) {
            if (min > Array[i]) {
                min = Array[i];
            }
        }
        return min;
    } 
    
    int SumArray(int Array[100], int arrLength) {

        int sum = 0;
        for (int i = 0; i < arrLength; i++) {
            sum += Array[i];
        }
        return sum;
    } 
    
    float AverageArray(int Array[100], int arrLength) {

        float Avg = SumArray(Array, arrLength) / arrLength;

        return Avg;
    } 
    
    int RandomNumber(int From, int To) {

        int randNum = rand() % (To - From + 1) + From;
        return randNum;
    } 
    
    void CopyArray(int Array[100], int Array2[100], int arrLength) {

        for (int i = 0; i < arrLength; i++)
            Array2[i] = Array[i];
    } 
    
    void SumTwoArray(int Array[100], int Array2[100], int sumArray[100], int arrLength) {

        for (int i = 0; i < arrLength; i++)
            sumArray[i] = Array[i] + Array2[i];
    } 
    
    void Swap(int& A, int& B)
    {
        int Temp;
        Temp = A;
        A = B;
        B = Temp;
    } 
    
    void ShuffleArray(int arr[100], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            int index1 = RandomNumber(1, arrLength) - 1;
            int index2 = RandomNumber(1, arrLength) - 1;
            Swap(arr[index1], arr[index2]);
        }
    } 
    
    void CopyArrayInReverseOrder(int arrSource[100], int arrDestination[100], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
            arrDestination[i] = arrSource[arrLength - 1 - i];
    } 
    
    short FindNumberPositionInArray(int Number, int arr[100], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            if (arr[i] == Number)
                return i;
        }

        return -1;
    } 
    
    bool IsNumberInArray(int Number, int arr[100], int arrLength) {
        return FindNumberPositionInArray(Number, arr, arrLength) != -1;
    } 

    void AddArrayElement(int Number, int arr[100], int& arrLength)
    {
        arrLength++;
        arr[arrLength - 1] = Number;
    } 

    void CopyOddNumber(int arrSource[100], int arrDestination[100], int arrLength, int& arrDestinationLength) {
        for (int i = 0; i < arrLength; i++) {
            if (arrSource[i] % 2 != 0) {
                AddArrayElement(arrSource[i], arrDestination, arrDestinationLength);

            }
        }
    } 

    bool IsPalindromeArray(int arr[100], int arrLength){
        for (int i = 0; i < arrLength; i++) {
            if (arr[i] != arr[arrLength - i - 1]) {
                return false;
            }
        }

        return true;
    } 

    int OddCount(int arr[100], int arrLength) {
        int Counter = 0;

        for (int i = 0; i < arrLength; i++) {

            if (arr[i] % 2 != 0) {
                Counter++;
            }
        }
        return Counter;
    } 

    int EvenCount(int arr[100], int arrLength) {
        int Counter = 0;

        for (int i = 0; i < arrLength; i++) {

            if (arr[i] % 2 == 0) {
                Counter++;
            }
        }
        return Counter;
    } 

    int PositiveCount(int arr[100], int arrLength) {
        int Counter = 0;

        for (int i = 0; i < arrLength; i++) {

            if (arr[i] >= 0)
                Counter++;
        }
        return Counter;
    } 

    int NegativeCount(int arr[100], int arrLength) {
        int Counter = 0;

        for (int i = 0; i < arrLength; i++) {

            if (arr[i] < 0)
                Counter++;
        }
        return Counter;
    }
}