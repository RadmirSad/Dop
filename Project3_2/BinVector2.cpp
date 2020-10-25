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

std::ostream& operator << (std::ostream& c, BinVector& b)
{
	c << "{ ";
	int i, ind = b.getSize();
	char* buf = b.getVec();
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
	c >> b.ar;
	return c;
}

void BinVector::setVector()
{
	int count, flag = 0;
	char k;
	std::cout << "Введите вектор:" << std::endl;
	while (!flag)
	{
		count = 0;
		std::cin >> *this;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		k = ar[0];
		flag = 1;
		while (k != '\0')
		{
			if ((k != '1') && (k != '0'))
				flag = 0;
			k = ar[count + 1];
			count++;
		}
		if (flag == 0) std::cout << "Неверный формат ввода. Введите снова:" << std::endl;
	}
	index = count;
	std::cout << "Введённый вектор : " << *this << std::endl;
}

BinVector BinVector:: operator | (BinVector b)
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

BinVector BinVector::operator & (BinVector b)
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

BinVector BinVector::operator ^= (BinVector b)
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
		if (maxvect[max - ind] == secvect[secind - ind]) str += '0';
		else str += '1';
	for (ind = max - secind - 1; ind >= 0; ind--)
		if (maxvect[ind] == '1') str += '1';
		else str += '0';
	for (int i = 0, j = str.length() - 1; i < j; i++, j--)
		std::swap(str[i], str[j]);
	BinVector res(str);
	return res;
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

void GetOR(BinVector my_vect)
{
	BinVector sec;
	sec.setVector();
	sec = my_vect | sec;
	char* buf = sec.getVec();
	int ind = sec.getSize();
	std::cout << "Итоговый вектор : " << sec << std::endl;
}

void GetAND(BinVector my_vect)
{
	BinVector sec;
	sec.getVec();
	sec = my_vect & sec;
	char* buf = sec.getVec();
	int ind = sec.getSize();
	std::cout << "Итоговый вектор : " << sec << std::endl;
}

void GetXOR(BinVector my_vect)
{
	BinVector sec;
	sec.getVec();
	sec = my_vect ^= sec;
	char* buf = sec.getVec();
	int ind = sec.getSize();
	std::cout << "Итоговый вектор : " << sec << std::endl;
}

void GetDOP(BinVector my_vect)
{
	BinVector sec = ~ my_vect;
	char* buf = sec.getVec();
	int ind = sec.getSize();
	std::cout << "Итоговый вектор : " << sec << std::endl;
}

void GetWN(BinVector my_vect)
{
	BinVector sec = my_vect.WN();
	char* buf = sec.getVec();
	int ind = sec.getSize();
	std::cout << "Итоговый вектор : " << sec << std::endl;
}