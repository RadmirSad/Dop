#pragma once

#ifndef _BINVECTOR_H_
#define _BINVECTOR_H_

#include <iostream>
#include <sstream>

class BinVector
{
private:
	int len;
	char* bvect;
public:
	BinVector();
	BinVector(int a);
	BinVector(const char* str);
	BinVector(const BinVector& a);
	~BinVector() { delete[] bvect; }
	friend std::ostream& operator << (std::ostream& c, const BinVector& b);
	friend std::istream& operator >> (std::istream& c, BinVector& b);
	friend void GetMax(const BinVector& a, const BinVector& b, char const*& maxvect, char const*& secvect, int& max, int& secind);
	friend BinVector operator | (const BinVector& a, const BinVector& b);
	friend BinVector operator & (const BinVector& a, const BinVector& b);
	BinVector& operator ^= (const BinVector& b);
	BinVector operator ~ ();
	void WN(BinVector& res);
	BinVector& operator = (const BinVector& b);
	BinVector& operator = (BinVector&& b);
	int GetSize() const { return len; }
};

void GetVec(BinVector& a);

#endif