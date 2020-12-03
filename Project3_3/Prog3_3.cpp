#include "BinVector_dyn.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	BinVector a, b;
	try
	{
		BinVector c(547); // 1000100011
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << "Error: " << e.what() << '\n';
	}
	BinVector dop;
	try {
		std::cout << "¬ведите первый вектор:" << std::endl;
		GetVec(a);
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << "Error: " << e.what() << '\n';
	}
	try {
		std::cout << "¬ведите второй вектор:" << std::endl;
		GetVec(b);
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << "Error: " << e.what() << '\n';
	}
	try {
		dop = a | b;
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << "Error: " << e.what() << '\n';
	}
	std::cout << a << " | " << b << " = " << dop << std::endl;
	try {
		dop = a & b;
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << "Error: " << e.what() << '\n';
	}
	std::cout << a << " & " << b << " = " << dop << std::endl;
	try {
		dop = ~a;
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << "Error: " << e.what() << '\n';
	}
	std::cout << "~" << a << " = " << dop << std::endl;
	try {
		dop = a;
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << "Error: " << e.what() << '\n';
	}
	try {
		dop ^= b;
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << "Error: " << e.what() << '\n';
	}
	std::cout << a << "^=" << b << " = " << dop << std::endl;
	try {
		a.WN(dop);
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << "Error: " << e.what() << '\n';
	}
	std::cout << a << " -> " << dop << std::endl;
	try {
		b.WN(dop);
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << "Error: " << e.what() << '\n';
	}
	std::cout << b << " -> " << dop << std::endl;
	return 0;
}