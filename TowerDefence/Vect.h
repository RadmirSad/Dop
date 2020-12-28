#pragma once

#ifndef _VECT_H_
#define _VECT_H_

#include <iostream>
#include <utility>

enum TUsability
{
	BAD,
	GOOD,
	DEAD,
	ALIVE
};

template <class T>
class ConstIter
{
private:
	T* cur = nullptr;
public:
	ConstIter() {}
	ConstIter(T* it) : cur(it) {}

	int operator != (const ConstIter& Dop) const { return (cur != Dop.cur); }
	int operator == (const ConstIter& Dop) const { return (cur == Dop.cur); }
	ConstIter& operator ++ () { if (cur == nullptr) throw std::domain_error("Iterator was empty"); ++cur; return *this; }
	ConstIter& operator -- () { if (cur == nullptr) throw std::domain_error("Iterator was empty"); --cur; return *this; }
	ConstIter operator + (int n) { if (cur == nullptr) throw std::domain_error("Iterator was empty"); cur += n; return *this; }
	ConstIter operator - (int n) { if (cur == nullptr) throw std::domain_error("Iterator was empty"); cur -= n; return *this; }

	const T& operator* () const { if (cur == nullptr) throw std::domain_error("Iterator was empty"); return *cur; }
	const T* operator& () const { if (cur == nullptr) throw std::domain_error("Iterator was empty"); return cur; }
};

template <class T>
class Iter
{
private:
	T* cur = nullptr;
public:
	Iter() { ; }
	Iter(T* it) : cur(it) { ; }

	int operator != (const Iter& Dop) const { return (cur != Dop.cur); }
	int operator == (const Iter& Dop) const { return (cur == Dop.cur); }
	Iter& operator ++ () { if (cur == nullptr) throw std::domain_error("Iterator was empty"); ++cur; return *this; }
	Iter& operator -- () { if (cur == nullptr) throw std::domain_error("Iterator was empty"); --cur; return *this; }
	Iter operator + (int n) { if (cur == nullptr) throw std::domain_error("Iterator was empty"); cur += n; return *this; }
	Iter operator - (int n) { if (cur == nullptr) throw std::domain_error("Iterator was empty"); cur -= n; return *this; }

	T& operator* () const { if (cur == nullptr) throw std::domain_error("Iterator was empty"); return *cur; }
	T* operator& () const { if (cur == nullptr) throw std::domain_error("Iterator was empty"); return cur; }
};

template <class T>
class MyVector;

template <class T>
std::ostream& operator << (std::ostream& out, const MyVector<T>& Vect)
{
	out << "{";
	if (Vect.Size != 0)
		for (int i = 0; i < Vect.Size; i++)
		{
			out << " ";
			out << Vect.Elem[i];
		}
	else out << "Empty";
	out << " }";
	return out;
}

template <class T>
class MyVector
{
private:
	const int DopSize = 10;
	int Size = 0;
	T* Elem = nullptr;

	int Reallocate(int NewVal);
public:
	MyVector() { ; }
	MyVector(int NewSize, const T* Elements);
	MyVector(const MyVector&);
	MyVector(MyVector&& NewVect) : Size(NewVect.Size), Elem(NewVect.Elem) { NewVect.Elem = nullptr; }
	~MyVector() { delete[] Elem; }

	int GetSize() const { return Size; }
	int GetDopSize() const { return DopSize; }

	MyVector& operator = (const MyVector&);
	MyVector& operator = (MyVector&&);
	const T& operator [] (int) const;
	T& operator [] (int);
	friend std::ostream& operator <<<T> (std::ostream& out, const MyVector& Vect);

	int Insert(ConstIter<T> pos, const T& elem);
	int Erase(ConstIter<T> fir, ConstIter<T> sec);
	void Clear();

	friend class ConstIter<T>;
	friend class Iter<T>;

	ConstIter<T> cbegin() { ConstIter<T> a(&Elem[0]); return a; }
	ConstIter<T> cend() { ConstIter<T> a(Elem + Size); return a;}
	Iter<T> begin() { Iter<T> a(Elem); return a; }
	Iter<T> end() { Iter<T> a(Elem + Size); return a;}

	int find(T MyEl);
};

template <class T>
MyVector<T>::MyVector(int NewSize, const T* Elements)
{
	if (NewSize <= 0) throw std::out_of_range("Expected value greater than 0");
	if (Elements == nullptr) throw std::invalid_argument("A pointer to a memory location was expected");
	Size = NewSize;
	int count = 0;
	if (Size % DopSize == 0) count = Size;
	else count = (Size % DopSize) * DopSize + DopSize;
	Elem = new T[count];
	for (int i = 0; i < count; i++)
		Elem[i] = Elements[i];
}

template <class T>
MyVector<T>::MyVector(const MyVector& Sec)
{
	Size = Sec.Size;
	int count = 0;
	if (Size % DopSize == 0) count = Size;
	else count = (Size % DopSize) * DopSize + DopSize;
	if (count != 0)
		Elem = new T[count];
	else Elem = nullptr;
	for (int i = 0; i < Size; i++)
		Elem[i] = Sec.Elem[i];
}

template <class T>
MyVector<T>& MyVector<T>::operator = (const MyVector& Sec)
{
	if (this == &Sec)
		return *this;
	int count = Sec.Size;
	if (count % DopSize == 0) count = Size;
	else count = (count % DopSize) * DopSize + DopSize;
	T* buf = new T[count];
	Size = count;
	delete[] Elem;
	Elem = buf;
	for (int i = 0; i < Size; i++)
		Elem[i] = Sec.Elem[i];
	return *this;
}

template <class T>
MyVector<T>& MyVector<T>::operator = (MyVector&& Sec)
{
	if (this == &Sec)
		return *this;
	Size = Sec.Size;
	delete[] Elem;
	Elem = Sec.Elem;
	Sec.Elem = nullptr;
	return *this;
}

template <class T>
const T& MyVector<T>::operator [] (int index) const
{
	if ((index < 0) || (index >= Size)) throw std::out_of_range("The element on this index does not exist");
	return Elem[index];
}

template <class T>
T& MyVector<T>::operator [] (int index)
{
	if ((index < 0) || (index >= Size)) throw std::out_of_range("The element on this index does not exist");
	return Elem[index];
}

template <class T>
int MyVector<T>::Reallocate(int NewVal)
{
	if (NewVal <= 0) return BAD;
	T* buf = new T[NewVal];
	int count = 0;
	if (NewVal > Size)
		count = Size;
	else count = NewVal;
	for (int i = 0; i < count; i++)
		buf[i] = std::move(Elem[i]);
	delete[] Elem;
	Elem = buf;
	return GOOD;
}

template <class T>
int MyVector<T>::Insert(ConstIter<T> pos, const T& myel)
{
	int index = 0;
	for (; (index < Size) && (&Elem[index] != &pos); index++)	;
	if ((index == Size) && (pos != cend()))
	{
#ifdef DEBUG
		std::cout << "Incorrect iterator" << std::endl;
#endif
		return BAD;
	}
	if (Size % DopSize == 0) Reallocate(Size + DopSize);
	T fir = myel;
	for (int i = index + 1; i < Size; i++)
	{
		T sec = Elem[i];
		Elem[i] = fir;
		fir = sec;
	}
	Elem[Size] = fir;
	Size++;
	return GOOD;
}

template <class T>
int MyVector<T>::Erase(ConstIter<T> fir, ConstIter<T> sec)
{
	int First = 0, Second = 0, flag = 0, diff = 0;
	for (; (First < Size) && (&(Elem[First]) != &fir); ++First)	;
	if (First == Size)
	{
#ifdef DEBUG
		std::cout << "There are no elements in this range" << std::endl;
#endif
		return GOOD;
	}
	for (; (Second < Size) && (&(Elem[Second]) != &sec); Second++);
	if (Second <= First)
	{
#ifdef DEBUG
		std::cout << "Incorrect range" << std::endl;
#endif
		return BAD;
	}
	diff = Second - First;
	for (flag = First; flag < Size - diff; flag++)
		Elem[flag] = Elem[flag + diff];
	if ((Size - diff) / DopSize != Size / DopSize) Reallocate(Size - diff);
	Size -= diff;
	return GOOD;
}

template <class T>
void MyVector<T>::Clear()
{
	delete[] Elem;
	Elem = nullptr;
	Size = 0;
}

template <class T>
int MyVector<T>::find(T MyEl)
{
	int num = 0;
	for (; (num < Size) && (Elem[num] != MyEl); num++);
	if (num == Size) return -1;
	else return num;
}
#endif