#pragma once
#ifndef _BINVECTOR_H_
#define _BINVECTOR_H_

#include <iostream>
#include <sstream>

class BinVector
{
private:
	static const int SZ = 100;
	int index;
	char ar[SZ];
public:
	BinVector() : index(1) { ar[0] = '0'; }
	BinVector(int a);
	BinVector(const std::string & str);
	friend std::istream & operator >> (std::istream &c, BinVector &b);
	friend std::ostream & operator << (std::ostream &c, const BinVector &b);
	const char* getVec() { return ar; }
	friend void GetMax(char const*& secvect, char const*& maxvect, const BinVector& a, const BinVector& b, int& max, int& secind);
	friend BinVector operator | (const BinVector& a, const BinVector& b);
	friend BinVector operator & (const BinVector& a, const BinVector& b);
	void operator ^= (const BinVector& b);
	BinVector operator ~ ();
	BinVector WN(BinVector& res);
	void operator () (const char* str, int len);
	int getSize() const { return index; }
	int getMaxSize() const { return SZ; }
};

void SetVec(BinVector& my_vect);
void GetOR(const BinVector& my_vect);
void GetAND(const BinVector& my_vect);
void GetXOR(BinVector my_vect);
void GetDOP(BinVector& my_vect);
void GetWN(BinVector& my_vect);


template <class number>
int Get_info(number& a, int flag_for_int)
{
	int flag = 0, dop_count = 0, buf = pow(2, sizeof(a) * 8 - 1);
	std::string dop;
	getline(std::cin, dop);
	if (dop.length() == 0) return 1;
	while (buf != 0)
	{
		buf /= 10;
		dop_count++;
	}
	if (dop.length() > dop_count) return 2;
	for (int i = 0; i < dop.length(); i++)
		if (flag_for_int > 0) // 1 - for vect; 0 - for int
		{
			if ((dop[i] < 48) || (dop[i] > 49)) flag = 1;
		}
		else if ((dop[i] < 48) || (dop[i] > 57)) flag = 1;
	if (flag) return 3;
	std::stringstream ss;
	ss << dop;
	ss >> a;
	return 0;
}

template <class number>
void Get_num(number& num, int flag_for_int)
{
	int flag = 0;
	while (!flag)
		switch (Get_info(num, flag_for_vect))
		{
		case 0:
			flag = 1;
			break;
		case 1:
			std::cout << "Неверный формат ввода. Введите снова:" << std::endl;
			break;
		case 2:
			std::cout << "Длина введённой строки больше возможного допустимого значения. Введите снова:" << std::endl;
			break;
		case 3:
			std::cout << "Присутствие недопустимых символов. Введите снова:" << std::endl;
			break;
		}
		if (Get_info(num, flag_for_int) > 0) flag = 1;
		else std::cout << "Неверный формат ввода. Введите снова:" << std::endl;
}

#endif