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
	BinVector() : index(1) { ar[0] = '0'; ar[1] = '\0'; }
	BinVector(int a);
	BinVector(std::string str);
	void setVec(int div);
	char* getVec() { return ar; }
	BinVector OR(BinVector b);
	BinVector AND(BinVector b);
	BinVector XOR(BinVector b);
	BinVector DOP();
	BinVector WN();
	int getSize() const { return index; }
	int getMaxSize() const { return SZ; }
};

void GetOR(BinVector my_vect);
void GetAND(BinVector my_vect);
void GetXOR(BinVector my_vect);
void GetDOP(BinVector my_vect);
void GetWN(BinVector my_vect);
void SetVect(BinVector& link);

BinVector GetSecVec();

template <class number>
int Get_info(number& a, int flag_for_vect)
{
	int flag = 0;
	std::string dop;
	getline(std::cin, dop);
	if (dop.length() == 0) return 0;
	for (int i = 0; i < dop.length(); i++)
		if (flag_for_vect > 0) // 1 - for vect; 0 - for int
		{
			if ((dop[i] < 48) || (dop[i] > 49)) flag = 1;
		}
		else if ((dop[i] < 48) || (dop[i] > 57)) flag = 1;
	if (flag) return 0;
	std::stringstream ss;
	ss << dop;
	ss >> a;
	return 1;
}

template <class number>
void Get_num(number& num, int flag_for_vect)
{
	int flag = 0;
	while (!flag)
		if (Get_info(num, flag_for_vect) > 0) flag = 1;
		else std::cout << "Неверный формат ввода. Введите снова:" << std::endl;
}

#endif
