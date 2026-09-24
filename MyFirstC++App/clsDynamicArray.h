#pragma once
#include <iostream>


using namespace std;

template <class T> class clsDynamicArray
{
protected:
	int _Size = 0;
	T* _TempArray;

public:
	T* OriginalArray;

	clsDynamicArray(int Size = 0) {
		if (Size < 0) {
			Size = 0;
		}
		_Size = Size;
		OriginalArray = new T[_Size];
	}

	~clsDynamicArray() {
		delete[] OriginalArray;
	}

	bool setItem(int index, T value) {

		if (_Size <= index || _Size < 0) {
			return false;
		}
		else {

			OriginalArray[index] = value;
			return true;
		}
	}

	int Size() {
		return _Size;
	}

	bool IsEmpty() {
		return (_Size == 0 ? true : false);
	}

	void PrintList() {
		for (int i = 0; i < _Size; i++) {
			cout << OriginalArray[i] << " ";
		}
		cout << endl;
	}

	void Resize(int NewSize) {

		if (NewSize < 0) {
			NewSize = 0;
		}

		_TempArray = new T[NewSize];

		if (NewSize < _Size) {
			_Size = NewSize;
		}

		for (int i = 0; i < _Size; i++) {
			_TempArray[i] = OriginalArray[i];

		}

		_Size = NewSize;

		delete[] OriginalArray;
		OriginalArray = _TempArray;

	}

	T GetItem(int index) {
		return OriginalArray[index];
	}

	void Reverse() {

		int Counter = 0;
		_TempArray = new T[_Size];

		for (int i = _Size - 1; i >= 0; i--) {
			_TempArray[Counter] = OriginalArray[i];
			Counter++;
		}
		delete[]OriginalArray;
		OriginalArray = _TempArray;
	}

	void Clear() {
		_Size = 0;
		_TempArray = new T[0];
		delete[]OriginalArray;
		OriginalArray = _TempArray;
	}

	bool DeleteItemAt(int index) {


		if (index >= _Size || index < 0) {
			return false;
		}

		_Size--;

		_TempArray = new T[_Size];

		for (int i = 0; i < index; i++) {

			_TempArray[i] = OriginalArray[i];
		}

		for (int i = index + 1; i < _Size + 1; i++) {

			_TempArray[i - 1] = OriginalArray[i];
		}

		delete[] OriginalArray;
		OriginalArray = _TempArray;
		return true;
	}

	void DeleteFirstItem() {
		DeleteItemAt(0);
	}

	void DeleteLastItem() {
		DeleteItemAt(_Size - 1);
	}

	int Find(T value) {

		for (int i = 0; i < _Size; i++)
		{
			if (OriginalArray[i] == value)
			{
				return i;
			}
		}
		return -1;
	}

	bool DeleteItem(T Value) {

		int index = Find(Value);

		if (index == -1) {
			return false;
		}

		DeleteItemAt(index);
		return true;
	}

	bool InsertAt(int index, T Value) {

		if (index > _Size || index < 0) {
			return false;
		}

		_Size++;

		_TempArray = new T[_Size];

		for (int i = 0; i < index; i++) {

			_TempArray[i] = OriginalArray[i];

		}

		_TempArray[index] = Value;

		for (int i = index; i < _Size - 1; i++) {
			_TempArray[i + 1] = OriginalArray[i];
		}

		delete[]OriginalArray;
		OriginalArray = _TempArray;
		return true;
	}

	bool InsertAtBeginning(T Value) {
		return InsertAt(0, Value);
	}

	bool InsertBefore(int index, T Value) {
		if (index < 1) {
			return InsertAt(0, Value);
		}
		else {
			return InsertAt(index - 1, Value);
		}
	}

	bool InsertAfter(int index, T Value)
	{
		if (index >= _Size)
			return InsertAt(_Size - 1, Value);
		else
			return InsertAt(index + 1, Value);
	}

	bool InsertAtEnd(T Value) {
		return InsertAt(_Size, Value);
	}

};


