#include "BinVector_dyn.h"

BinVector::BinVector(int a)
{
	int ind = a, count = 0;
	while (ind != 0)
	{
		ind /= 2;
		count++;
	}
	len = count;
	char* ptr = (char*)(&a), * dop = nullptr;
	if (count % 8 == 0) ind = (count / 8);
	else ind = (count / 8) + 1;
	if (ind)
	{
		dop = new(std::nothrow) char[ind] {};
		if (dop == nullptr) throw std::bad_alloc();
	}
	bvect = dop;
	for (int j = 0; j < ind; j++)
		bvect[j] = ptr[j];
}

BinVector::BinVector(const char* str)
{
	len = 0;
	int size = 0;
	char* dop = nullptr;
	if (str == nullptr) throw std::invalid_argument("Any symbols were expected.");
	while (str[len])
		len++;
	for (int k = 0; k < len; k++)
		if ((str[k] < 48) || (str[k] > 49)) throw std::invalid_argument("Symbols 1 and 0 were expected.");
	if (len % 8 == 0) size = (len / 8);
	else size = (len / 8) + 1;
	if (size)
	{
		dop = new(std::nothrow) char[size] {};
		if (dop == nullptr) throw std::bad_alloc();
	}
	bvect = dop;
	for (int i = len - 1; i >= 0; i--)
		if (str[len - i - 1] == '0') bvect[i / 8] &= ~(1 << (i % 8));
		else bvect[i / 8] |= 1 << (i % 8);
	for (int i = len; i < size * 8; i++)
		bvect[i / 8] &= ~(1 << (i % 8));
}

BinVector::BinVector(const BinVector& a) : len(a.len), bvect(nullptr)
{
	int size = 0;
	char* dop = nullptr;
	if (len % 8 == 0) size = (len / 8);
	else size = (len / 8) + 1;
	if (size)
	{
		dop = new(std::nothrow) char[size] {};
		if (dop == nullptr) throw std::bad_alloc();
	}
	bvect = dop;
	for (int i = 0; i < size; i++)
		bvect[i] = a.bvect[i];
}

std::ostream& operator << (std::ostream& c, const BinVector& b)
{
	c << "{ ";
	if (b.len != 0)
		for (int i = b.len - 1; i >= 0; i--)
		{
			c << bool(b.bvect[i / 8] & (1 << (i % 8)));
			if (i != 0) c << ", ";
		}
	else
		c << 0;
	c << " }";
	return c;
}

std::istream& operator >> (std::istream& c, BinVector& b)
{
	std::string str;
	int flag = 0;
	std::getline(c, str);
	if (str.length() == 0) {
		c.setstate(std::ios::failbit);
		return c;
	}
	for (int i = 0; i < str.length(); i++)
		if ((str[i] < 48) || (str[i] > 49)) flag = 1;
	if (flag) c.setstate(std::ios::failbit);
	else
	{
		int count = 0;
		char* dop = nullptr;
		if (str.length() % 8 == 0) count = (str.length() / 8);
		else count = (str.length() / 8) + 1;
		if (count)
		{
			dop = new(std::nothrow) char[count] {};
			if (dop == nullptr) throw std::bad_alloc();
		}
		delete[] b.bvect;
		b.len = str.length();
		b.bvect = dop;
		for (int i = b.len - 1; i >= 0; i--)
			if (str[b.len - i - 1] == '0') b.bvect[i / 8] &= ~(1 << (i % 8));
			else b.bvect[i / 8] |= 1 << (i % 8);
		for (int i = b.len; i < count * 8; i++)
			b.bvect[i / 8] &= ~(1 << (i % 8));
	}
	return c;
}

void GetMax(const BinVector& a, const BinVector& b, char const*& maxvect, char const*& secvect, int& max, int& secind)
{
	if (a.len > b.len)
	{
		max = a.len;
		secind = b.len;
		maxvect = a.bvect;
		secvect = b.bvect;
	}
	else
	{
		max = b.len;
		secind = a.len;
		maxvect = b.bvect;
		secvect = a.bvect;
	}
}

BinVector operator | (const BinVector& a, const BinVector& b)
{
	int max = 0, secind = 0, index = 0, count = 0;
	char const* secvect = nullptr, * maxvect = nullptr;
	char* str = nullptr;
	GetMax(a, b, maxvect, secvect, max, secind);
	str = new (std::nothrow) char[max + 1]{};
	if (str == nullptr) throw std::bad_alloc();
	str[max] = '\0';
	for (index = 0; index < secind; index++) {
		if (bool(a.bvect[index / 8] & (1 << (index % 8))) || bool(b.bvect[index / 8] & (1 << (index % 8)))) str[count] = '1';
		else str[count] = '0';
		count++;
	}
	for (index = secind; index < max; index++)
	{
		if (bool(maxvect[index / 8] & (1 << (index % 8)))) str[count] = '1';
		else str[count] = '0';
		count++;
	}
	for (int i = 0, j = count - 1; i < j; i++, j--)
		std::swap(str[i], str[j]);
	BinVector res(str);
	delete[] str;
	return res;
}

BinVector operator & (const BinVector& a, const BinVector& b)
{
	int max = 0, secind = 0, index = 0, count = 0;
	char const* secvect = nullptr, * maxvect = nullptr;
	GetMax(a, b, maxvect, secvect, max, secind);
	char* str = nullptr;
	str = new (std::nothrow) char[max + 1]{};
	if (str == nullptr) throw std::bad_alloc();
	str[max] = '\0';
	for (index = 0; index < secind; index++) {
		if (bool(a.bvect[index / 8] & (1 << (index % 8))) && bool(b.bvect[index / 8] & (1 << (index % 8)))) str[count] = '1';
		else str[count] = '0';
		count++;
	}
	for (index = secind; index < max; index++)
	{
		str[count] = '0';
		count++;
	}
	for (int i = 0, j = count - 1; i < j; i++, j--)
		std::swap(str[i], str[j]);
	BinVector res(str);
	delete[] str;
	return res;
}

BinVector& BinVector::operator ^= (const BinVector& b)
{
	int max = 0, secind = 0, index = 0;
	char const* secvect = nullptr, * maxvect = nullptr; 
	char *buf = nullptr;
	GetMax(*this, b, maxvect, secvect, max, secind);
	if ((max % 8 == 0) && (max != 0)) index = (max / 8);
	else index = (max / 8) + 1;
	buf = new (std::nothrow) char[max + 1]{};
	if (buf == nullptr) throw std::bad_alloc();
	for (index = 0; index < secind; index++)
		if (bool(bvect[index / 8] & (1 << (index % 8))) == bool(b.bvect[index / 8] & (1 << (index % 8)))) buf[index / 8] &= ~(1 << (index % 8));
		else buf[index / 8] |= 1 << (index % 8);
	for (index = secind; index < max; index++)
		if (bool(maxvect[index / 8] & (1 << (index % 8)))) buf[index / 8] |= 1 << (index % 8);
		else buf[index / 8] &= ~(1 << (index % 8));
	delete[] bvect;
	bvect = buf;
	len = max;
	return (*this);
}

BinVector& BinVector::operator = (const BinVector& b)
{
	if (this == &b)
		return *this;
	int size = 0;
	char* dop = nullptr;
	if (b.len % 8 == 0) size = (b.len / 8);
	else size = (b.len / 8) + 1;
	dop = new (std::nothrow) char[size]{};
	if (dop == nullptr) throw std::bad_alloc();
	if (len) delete[] bvect;
	bvect = dop;
	len = b.len;
	for (int i = 0; i < size; i++)
		bvect[i] = b.bvect[i];
	return *this;
}

BinVector& BinVector::operator = (BinVector&& b)
{
	if (this == &b)
		return *this;
	if (len) delete[] bvect;
	bvect = b.bvect;
	len = b.len;
	b.bvect = nullptr;
	return *this;
}

BinVector BinVector::operator~ () const
{
	char* str = nullptr;
	if (len != 0)
	{
		str = new (std::nothrow) char[len + 1]{};
		if (str == nullptr) throw std::bad_alloc();
		str[len] = '\0';
		for (int k = 0; k < len; k++)
			if (!(bool(bvect[k / 8] & (1 << (k % 8))))) str[k] = '1';
			else str[k] = '0';
		for (int i = 0, j = len - 1; i < j; i++, j--)
			std::swap(str[i], str[j]);
	}
	else
	{
		str = new (std::nothrow) char[2];
		if (str == nullptr) throw std::bad_alloc();
		str[1] = '\0';
		str[0] = '1';
	}
	BinVector res(str);
	delete[] str;
	return res;
}

void BinVector::WN(BinVector& res)
{
	int fir = 0, last = len - 1, dop = 0;
	while ((fir < last) && !((bool(bvect[fir / 8] & (1 << (fir % 8)))) && (bool(bvect[last / 8] & (1 << (last % 8))))))
	{
		if (!(bvect[fir / 8] & (1 << (fir % 8)))) fir++;
		if (!(bvect[last / 8] & (1 << (last % 8)))) last--;
	}
	char* str = nullptr;
	str = new (std::nothrow) char[last - fir + 1 + 1]{};
	if (str == nullptr) throw std::bad_alloc();
	str[last - fir + 1] = '\0';
	for (fir; fir <= last; fir++)
	{
		if (bool(bvect[fir / 8] & (1 << (fir % 8)))) str[dop] = '1';
		else str[dop] = '0';
		dop++;
	}
	for (int i = 0, j = dop - 1; i < j; i++, j--)
		std::swap(str[i], str[j]);
	BinVector buf(str);
	res = buf;
	delete[] str;
}

void GetVec(BinVector& a)
{
	int flag = 0;
	while (!flag)
	{
		std::cin.clear();
		std::cin >> a;
		if (!std::cin.good())
		{
			std::cout << "Введён неверный символ, могут использоваться только символы '1' и '0'. Попробуйте снова:" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else flag = 1;
	}
}

void BinVector::GetVect(std::string& str)
{
	str = "";
	if (len != 0)
		for (int i = len - 1; i >= 0; i--)
		{
			if (bool(bvect[i / 8] & (1 << (i % 8)))) str += "1";
			else str += "0";
		}
	else
		str = "0";
}