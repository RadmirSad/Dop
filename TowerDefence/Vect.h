#pragma once

#ifndef _VECT_H_
#define _VECT_H_

#include <iostream>

template <class T>
class MyVector
{
private:
	const int DopSize = 10;
	int Size = 0;
	T* Elem = nullptr;
public:
	MyVector() { ; }
	MyVector(int NewSize);
	MyVector(const MyVector&);
	MyVector(MyVector&& NewVect) : Size(NewVect.Size), Elem(NewVect.Elem) { NewVect.Elem = nullptr; }
	~MyVector() { delete[] Elem; }
	class ConstIter;
	class Iter;

	int GetSize() const { return Size; }
	int GetDopSize() const { return DopSize; }

	MyVector& operator = (const MyVector&);
	MyVector& operator = (MyVector&&);
	T& operator [] (const MyVector&);
	T operator [] (MyVector);

	int Insert(const Iter& pos, const T& elem);
	int Erase(const Iter& fir, const Iter& sec);
	int Clear();

	ConstIter cbegin() { return Elem; }
	ConstIter cend() { return Elem + Size; }
	Iter begin() { return Elem; }
	Iter end() { return Elem + Size; }

	class ConstIter
	{
	private:
		T* cur = nullptr;
	public:
		ConstIter() {}
		ConstIter(T* it) : cur(it) {}

		int operator != (const ConstIter& Dop) const { return cur != Dop.cur; }
		int operator == (const ConstIter& Dop) const { return cur == Dop.cur; }
		ConstIter& operator ++ () { ++cur; return *this; }
		ConstIter& operator -- () { --cur; return *this; }
		ConstIter operator + (int n);
		ConstIter operator - (int n) { cur -= n; return *this; }

		const T& operator* () const { return *cur; }
		const T* operator& () const { return cur; }
	};

	class Iter
	{
	private:
		T* cur = nullptr;
	public:
		Iter() { ; }
		Iter(T* it) : cur(it) { ; }

		int operator != (const Iter& Dop) const { return cur != Dop.cur; }
		int operator == (const Iter& Dop) const { return cur == Dop.cur; }
		Iter& operator ++ () { ++cur; return *this; }
		Iter& operator -- () { --cur; return *this; }
		Iter operator + (int n);
		Iter operator - (int n) { cur -= n; return *this; }

		T& operator* () const { return *cur; }
		T* operator& () const { return cur; }
	};
};

template <class T>
MyVector<T>::MyVector(int NewSize)
{
	if (NewSize < 0) throw std::out_of_range("Expected value greater than 0");
	Size = NewSize;
	int count = 0;
	if (Size % DopSize == 0) count = Size;
	else count = (Size % DopSize) * DopSize + DopSize;
	Elem = new T[count];
}

template <class T>
MyVector<T>::MyVector(const MyVector& Sec)
{
	Size = Sec.Size;
	int count = 0;
	if (Size % DopSize == 0) count = Size;
	else count = (Size % DopSize) * DopSize + DopSize;
	Elem = new T[count];
	
}

#endif