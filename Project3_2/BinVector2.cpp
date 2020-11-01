#include "BinVector2.h"

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

BinVector::BinVector(const std::string & str)
{
	if (str.length() > SZ)
		throw std::length_error("Длина введённой строки больше, чем максимальный допустимый размер вектора.");
	index = str.length();
	for (int k = 0; k < index; k++)
		ar[k] = str[k];
}

void BinVector:: operator () (const char* str, int len)
{
	index = len;
	for (int i = 0; i < index; i++)
		ar[i] = str[i];
}

std::ostream& operator << (std::ostream& c, const BinVector& b)
{
	int i, ind = b.getSize();
	const char * buf = b.ar;
	c << "{ ";
	for (i = 0; i < ind; i++)
	{
		c << buf[i];
		if (i + 1 != ind) c << ", ";
	}
	c << " }" << std::endl;
	return c;
}

std::istream& operator >> (std::istream& c, BinVector& b)
{
	std::string str;
	int flag = 0;
	std::getline(c, str);
	if (str.length() == 0) {
		b.ar[0] = '0';
		b.index = 1;
	}
	else {
		if (str.length() > b.getMaxSize()) {
			c.setstate(std::ios::failbit);
			return c;
		}
		for (int i = 0; i < str.length(); i++)
			if ((str[i] < 48) || (str[i] > 49)) flag = 1;
		if (flag) c.setstate(std::ios::failbit);
		else
		{
			for (int i = 0; i < str.length(); i++)
				b.ar[i] = str[i];
			b.index = str.length();
		}
	}
	return c;
}

void SetVec(BinVector& my_vect)
{
	int count, flag = 0;
	char k;
	std::cout << "Введите вектор:" << std::endl;
	while (!flag)
	{
		count = 0;
		std::cin >> my_vect;
		if (std::cin.good()) std::cout << "Неверный формат ввода. Введите снова:" << std::endl;
		else flag = 1;
	}
	std::cout << "Введённый вектор : " << my_vect << std::endl;
}

void GetMax(char const*& secvect, char const*& maxvect, const BinVector& a, const BinVector& b, int& max, int& secind)
{
	if (a.getSize() > b.getSize())
	{
		max = a.getSize();
		secind = b.getSize();
		maxvect = a.ar;
		secvect = b.ar;
	}
	else
	{
		max = b.getSize();
		secind = a.getSize();
		maxvect = b.ar;
		secvect = a.ar;
	}
}

BinVector operator | (const BinVector& a, const BinVector& b)
{
	BinVector res;
	int max = 0, secind = 0, ind, count = 0;
	char const* secvect, * maxvect = nullptr;
	GetMax(secvect, maxvect, a, b, max, secind);
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
	return res;
}

BinVector operator & (const BinVector& a, const BinVector& b)
{
	BinVector res;
	int max = 0, secind = 0, ind, count = 0;
	char const* secvect, * maxvect = nullptr;
	GetMax(secvect, maxvect, a, b, max, secind);
	char* str = new char[max];
	for (ind = 1; ind <= secind; ind++) {
		if ((maxvect[max - ind] == '1') && (secvect[secind - ind] == '1')) str[count] = '1';
		else str[count] = '0';
		count++;
	}
	for (ind = max - secind - 1; ind >= 0; ind--) {
		str[count] = '0';
		count++;
	}
	for (int i = 0, j = count - 1; i < j; i++, j--)
		std::swap(str[i], str[j]);
	res(str, count);
	delete[] str;
	return res;
}

void BinVector::operator ^= (const BinVector& b)
{
	int max = 0, secind = 0, ind, count = 0;
	char const* secvect, * maxvect = nullptr;
	GetMax(secvect, maxvect, *this, b, max, secind);
	char* str = new char[max];
	for (ind = 1; ind <= secind; ind++) {
		if (maxvect[max - ind] == secvect[secind - ind]) str[count] = '0';
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
	(*this)(str, count);
}

BinVector BinVector::operator ~ ()
{
	std::string str;
	for (int i = 0; i < index; i++)
		if (ar[i] == '0') str += '1';
		else str += '0';
	BinVector res(str);
	return res;
}

BinVector BinVector::WN(BinVector& res)
{
	char* str = new char[index];
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

void GetOR(const BinVector& my_vect)
{
	BinVector sec;
	SetVec(sec);
	sec = my_vect | sec;
	const char* buf = sec.getVec();
	int ind = sec.getSize();
	std::cout << "Итоговый вектор : " << sec << std::endl;
}

void GetAND(const BinVector& my_vect)
{
	BinVector sec;
	sec.getVec();
	sec = my_vect & sec;
	const char* buf = sec.getVec();
	int ind = sec.getSize();
	std::cout << "Итоговый вектор : " << sec << std::endl;
}

void GetXOR(BinVector my_vect)
{
	BinVector sec;
	sec.getVec();
	my_vect ^= sec;
	const char* buf = sec.getVec();
	int ind = sec.getSize();
	std::cout << "Итоговый вектор : " << sec << std::endl;
}

void GetDOP(BinVector& my_vect)
{
	BinVector sec;
	sec = ~ my_vect;
	const char* buf = sec.getVec();
	int ind = sec.getSize();
	std::cout << "Итоговый вектор : " << sec << std::endl;
}

void GetWN(BinVector& my_vect)
{
	BinVector sec;
	my_vect.WN(sec);
	const char* buf = sec.getVec();
	int ind = sec.getSize();
	std::cout << "Итоговый вектор : " << sec << std::endl;
}