#ifndef __ARRAY_H
#define __ARRAY_H

#include <iostream>

// T should have:
// 1- operator= --> for using assiment and 'add'
// 2- operator<< --> for printing with cout
// 3- default c'tor --> for creating the array

template<class T>
class Array
{
private:
	int physicalSize, logicalSize;
	char delimiter;
	T* arr;

public:
	Array(int size = 0, char delimiter = '\n');
	Array(const Array& other);
	~Array();

	void push_back(const T& newVal) { operator+=(newVal); }
	bool empty() const { return logicalSize == 0; }
	int size() const { return logicalSize; }
	int capacity() const { return physicalSize; }
	void reserve(int n);
	const T* begin() const { return arr + 0; } 
	const T* end() const { return arr + logicalSize; }

	const Array& operator=(const Array& other);
	const Array& operator+=(const T& newVal);
	T& operator[](int i) { return arr[i]; }
	const T& operator[](int i) const { return arr[i]; }

	friend std::ostream& operator<<(std::ostream& os, const Array& arr)
	{
		for (int i = 0; i < arr.logicalSize; i++)
			os << arr.arr[i] << arr.delimiter;
		return os;
	}
};

template<class T>
Array<T>::Array(int maxSize, char delimiter) : physicalSize(maxSize), logicalSize(0), delimiter(delimiter)
{
	arr = new T[physicalSize];
}

template<class T>
Array<T>::Array(const Array& other) : arr(nullptr)
{
	*this = other;
}

template<class T>
Array<T>::~Array()
{
	delete[] arr;
}

template<class T>
const Array<T>& Array<T>::operator=(const Array<T>& other)
{
	if (this != &other)
	{
		delete[]arr;
		physicalSize = other.physicalSize;
		logicalSize = other.logicalSize;
		delimiter = other.delimiter;
		arr = new T[physicalSize];
		for (int i = 0; i < logicalSize; i++)
			arr[i] = other.arr[i];
	}
	return *this;
}

template<class T>
const Array<T>& Array<T>::operator+=(const T& newVal)
{
	if (logicalSize == physicalSize)
		reserve(physicalSize * 2);
	arr[logicalSize++] = newVal;
	return *this;
}

template<class T>
void Array<T>::reserve(int n)
{
	if (physicalSize < n)
	{
		physicalSize = n;
		T* temp = new T[physicalSize];
		for (int i = 0; i < logicalSize; i++)
			temp[i] = arr[i];
		delete[] arr;
		arr = temp;
	}
}

#endif // __ARRAY_H