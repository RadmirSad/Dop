#include "BinVector_dyn.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	BinVector a, b, c(547), dop; // 1000100011
	std::cout << "������� ������ ������:" << std::endl;
	GetVec(a);
	std::cout << "������� ������ ������:" << std::endl;
	GetVec(b);
	dop = a | b;
	std::cout << a << " | " << b << " = " << dop << std::endl;
	dop = a & b;
	std::cout << a << " & " << b << " = " << dop << std::endl;
	dop = ~ a;
	std::cout << "~" << a << " = " << dop << std::endl;
	dop = a;
	dop ^= b;
	std::cout << a << "^=" << b << " = " << dop << std::endl;
	a.WN(dop);
	std::cout << a << " -> " << dop << std::endl;
	b.WN(dop);
	std::cout << b << " -> " << dop << std::endl;
	return 0;
}