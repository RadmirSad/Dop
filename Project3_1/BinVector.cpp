#include "BinVector.h"

BinVector::BinVector(int a)
{
	int count = 0;
	while (a > 0)
	{
		if (a % 2 == 1) {
			ar[count] = '1';
			a--;
		}
		else ar[count] = '0';
		a /= 2;
		count++;
	}
	index = count;
	ar[count] = '\0';
	for (int i = 0, j = index - 1; i < j; i++, j--)
		std::swap(ar[i], ar[j]);
}

BinVector::BinVector(std::string str)
{
	if (str.length() >= SZ)
		throw std::length_error("Длина введённой строки больше, чем максимальный допустимый размер вектора.");
	index = str.length();
	for (int k = 0; k < index; k++)
		ar[k] = str[k];
	ar[index] = '\0';
}

void BinVector::setVec(int div)
{
	int k = 0, &dop = k, count = 0;
	if (div == 2) Get_num(dop, 0);
	else Get_num(dop, 1);
	while (k != 0)
	{
		if (k % 2 == 1)
			ar[count] = '1';
		else ar[count] = '0';
		k /= div;
		count++;
	}
	ar[count] = '\0';
	index = count;
	for (int i = 0, j = index - 1; i < j; i++, j--)
		std::swap(ar[i], ar[j]);
}

BinVector BinVector::OR(BinVector b)
{
	int max = 0, secind = 0, ind;
	char* maxvect = nullptr, *secvect = nullptr;
	std::string str;
	if (index > b.getSize())
	{
		max = index;
		secind = b.getSize();
		maxvect = ar;
		secvect = b.getVec();
	}
	else
	{
		max = b.getSize();
		secind = index;
		maxvect = b.getVec();
		secvect = ar;
	}
	for (ind = 1; ind <= secind; ind++)
		if ((maxvect[max - ind] == '0') && (secvect[secind - ind] == '0')) str += '0';
		else str += '1';
	for (ind = max - secind - 1; ind >= 0; ind--)		
		if (maxvect[ind] == '1') str += '1';
		else str += '0';
	for (int i = 0, j = str.length() - 1; i < j; i++, j--)
		std::swap(str[i], str[j]);
	BinVector res(str);
	return res;
}

BinVector BinVector::AND(BinVector b)
{
	int max = 0, secind = 0, ind;
	char* maxvect = nullptr, * secvect = nullptr;
	std::string str;
	if (index > b.getSize())
	{
		max = index;
		secind = b.getSize();
		maxvect = ar;
		secvect = b.getVec();
	}
	else
	{
		max = b.getSize();
		secind = index;
		maxvect = b.getVec();
		secvect = ar;
	}
	for (ind = 1; ind <= secind; ind++)
		if ((maxvect[max - ind] == '1') && (secvect[secind - ind] == '1')) str += '1';
		else str += '0';
	for (ind = max - secind - 1; ind >= 0; ind--)
		str += '0';
	for (int i = 0, j = str.length() - 1; i < j; i++, j--)
		std::swap(str[i], str[j]);
	BinVector res(str);
	return res;
}

BinVector BinVector::XOR(BinVector b)
{
		int max = 0, secind = 0, ind;
	char* maxvect = nullptr, *secvect = nullptr;
	std::string str;
	if (index > b.getSize())
	{
		max = index;
		secind = b.getSize();
		maxvect = ar;
		secvect = b.getVec();
	}
	else
	{
		max = b.getSize();
		secind = index;
		maxvect = b.getVec();
		secvect = ar;
	}
	for (ind = 1; ind <= secind; ind++)
		if (maxvect[max - ind] == secvect[secind - ind]) str += '0';
		else str += '1';
	for (ind = max - secind - 1; ind >= 0; ind--)		
		if (maxvect[max - ind] == '1') str += '1';
		else str += '0';
	for (int i = 0, j = str.length() - 1; i < j; i++, j--)
		std::swap(str[i], str[j]);
	BinVector res(str);
	return res;
}

BinVector BinVector::DOP()
{
	std::string str;
	for (int i = 0; i < index; i++)
		if (ar[i] == '0') str += '0';
		else str += '1';
	BinVector res(str);
	return res;
}

BinVector BinVector::WN()
{
	std::string str;
	int fir = 0, last = index - 1;
	while ((fir < last) && ((ar[fir] != '1') || (ar[last] != '1')))
	{
		if (ar[fir] != '1') fir++;
		if (ar[last] != '1') last--;
	}
	for (fir; fir <= last; fir++)
		str += ar[fir];
	BinVector res(str);
	return res;
}