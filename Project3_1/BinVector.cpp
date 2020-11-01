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
	for (int i = 0, j = index - 1; i < j; i++, j--)
		std::swap(ar[i], ar[j]);
}

BinVector::BinVector(const std::string& str)
{
	if (str.length() >= SZ)
		throw std::length_error("Длина введённой строки больше, чем максимальный допустимый размер вектора.");
	index = str.length();
	for (int k = 0; k < index; k++)
		ar[k] = str[k];
}

void BinVector::setVec(int div)
{
	int k = 0, & dop = k, count = 0;
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
	index = count;
	for (int i = 0, j = index - 1; i < j; i++, j--)
		std::swap(ar[i], ar[j]);
}

void BinVector::OR(const BinVector& b, BinVector& res)
{
	int max = 0, secind = 0, ind, count = 0;
	char const * secvect = nullptr, * maxvect = nullptr;
	GetMax(secvect, maxvect, b, max, secind);
	char* str = new char[max];
	for (ind = 1; ind <= secind; ind++) {
		if ((maxvect[max - ind] == '0') && (secvect[secind - ind] == '0')) str[count] = '0';
		else str[count] = '1';
		count++;
	}
	for (ind = max - secind - 1; ind >= 0; ind--) {
		if (maxvect[ind] == '1') str[count] = '1';
		else str[count] = '0';
		count++;
	}
	for (int i = 0, j = count - 1; i < j; i++, j--)
		std::swap(str[i], str[j]);
	res(str, count);
	delete[] str;
}

void BinVector::AND(const BinVector& b, BinVector& res)
{
	int max = 0, secind = 0, ind, count = 0;
	char const* secvect = nullptr, * maxvect = nullptr;
	GetMax(secvect, maxvect, b, max, secind);
	char* str = new char[max];
	for (ind = 1; ind <= secind; ind++) {
		if ((maxvect[max - ind] == '1') && (secvect[secind - ind] == '1'))
			str[count] = '1';
		else
			str[count] = '0';
		count++;
	}
	for (ind = max - secind - 1; ind >= 0; ind--)
	{
		str[count] = '0';
		count++;
	}
	for (int i = 0, j = count - 1; i < j; i++, j--)
		std::swap(str[i], str[j]);
	res(str, count);
	delete[] str;
}

void BinVector::XOR(const BinVector& b, BinVector& res)
{
	int max = 0, secind = 0, ind, count = 0;
	char const* secvect = nullptr, * maxvect = nullptr;
	GetMax(secvect, maxvect, b, max, secind);
	char* str = new char[max];
	for (ind = 1; ind <= secind; ind++) {
		if (maxvect[max - ind] == secvect[secind - ind])
			str[count] = '0';
		else
			str[count] = '1';
		count++;
		}
	for (ind = max - secind - 1; ind >= 0; ind--) {
		if (maxvect[ind] == '1')
			str[count] = '1';
		else
			str[count] = '0';
		count++;
		}
	for (int i = 0, j = count - 1; i < j; i++, j--)
		std::swap(str[i], str[j]);
	res(str, count);
	delete[] str;
}

void BinVector::GetMax(char const*& secvect, char const *& maxvect, const BinVector& b, int& max, int& secind)
{
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
}

void BinVector::DOP(BinVector& res)
{
	char* str = new char [index];
	for (int i = 0; i < index; i++)
		if (ar[i] == '0') str[i] = '1';
		else str[i] = '0';
	res(str, index);
}

void BinVector::WN(BinVector& res)
{
	char* str = new char [index];
	int fir = 0, last = index - 1, dop = 0;
	while ((fir < last) && ((ar[fir] != '1') || (ar[last] != '1')))
	{
		if (ar[fir] != '1') fir++;
		if (ar[last] != '1') last--;
	}
	for (fir; fir <= last; fir++)
	{
		str[dop] = ar[fir];
		dop++;
	}
	res(str, dop);
	delete[] str;
}

void BinVector:: operator () (const char* str, int len)
{
	index = len;
	for (int i = 0; i < index; i++)
		ar[i] = str[i];
}

void GetOR(BinVector& my_vect)
{
	BinVector sec, res;
	GetSecVec(sec);
	my_vect.OR(sec, res);
	const char* buf = res.getVec();
	int ind = res.getSize();
	std::cout << "Итоговый вектор : { ";
	for (int i = 0; i < ind; i++)
	{
		std::cout << buf[i];
		if (i + 1 != ind) std::cout << ", ";
	}
	std::cout << " }" << std::endl;
}

void GetAND(BinVector& my_vect)
{
	BinVector sec, res;
	GetSecVec(sec);
	my_vect.AND(sec, res);
	const char* buf = res.getVec();
	int ind = res.getSize();
	std::cout << "Итоговый вектор : { ";
	for (int i = 0; i < ind; i++)
	{
		std::cout << buf[i];
		if (i + 1 != ind) std::cout << ", ";
	}
	std::cout << " }" << std::endl;
}

void GetXOR(BinVector& my_vect)
{
	BinVector sec, res;
	GetSecVec(sec);
	my_vect.XOR(sec, res);
	const char* buf = res.getVec();
	int ind = res.getSize();
	std::cout << "Итоговый вектор : { ";
	for (int i = 0; i < ind; i++)
	{
		std::cout << buf[i];
		if (i + 1 != ind) std::cout << ", ";
	}
	std::cout << " }" << std::endl;
}

void GetDOP(BinVector& my_vect)
{
	BinVector res;
	my_vect.DOP(res);
	const char* buf = res.getVec();
	int ind = res.getSize();
	std::cout << "Итоговый вектор : { ";
	for (int i = 0; i < ind; i++)
	{
		std::cout << buf[i];
		if (i + 1 != ind) std::cout << ", ";
	}
	std::cout << " }" << std::endl;
}

void GetWN(BinVector& my_vect)
{
	BinVector res;
	my_vect.WN(res);
	const char* buf = res.getVec();
	int ind = res.getSize();
	std::cout << "Итоговый вектор : { ";
	for (int i = 0; i < ind; i++)
	{
		std::cout << buf[i];
		if (i + 1 != ind) std::cout << ", ";
	}
	std::cout << " }" << std::endl;
}

void GetSecVec(BinVector& vect)
{
	int dop_ent = 0, dop_sw = 0, & link = dop_sw;
	std::cout << "Выберите способ инициализации нового вектора:" << std::endl
		<< "1. Двоичное число." << std::endl
		<< "2. Десятичное число" << std::endl;
	while (dop_ent == 0)
	{
		Get_num(link, 0);
		switch (dop_sw)
		{
		case 1:
			std::cout << "Введите число:" << std::endl;
			vect.setVec(10);
			dop_ent = 1;
			break;
		case 2:
			std::cout << "Введите число:" << std::endl;
			vect.setVec(2);
			dop_ent = 1;
			break;
		default:
			std::cout << "Способа с таким номером не существует. Попробуйте снова:" << std::endl;
			break;
		}
	}
}