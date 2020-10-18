#include "pch.h"
#include "D:\Program\Lab\Proj2.3.1\Project3_1\BinVector.cpp"

TEST(BinConstr, InitDef)
{
	BinVector k;
	ASSERT_EQ(1, k.getSize());
	char* l = k.getVec();
	ASSERT_EQ('0', l[0]);
	ASSERT_EQ('\0', l[1]);
}

TEST(BinConstr, InitInt)
{
	BinVector a(5);
	ASSERT_EQ(3, a.getSize());
	char* l = a.getVec(), k [] = "101";
	for (int i = 0; i < a.getSize(); i++)
		ASSERT_EQ(k[i], l[i]);
	BinVector b(10);
	ASSERT_EQ(4, b.getSize());
	l = b.getVec();
	char str[] = "1010";
	for (int i = 0; i < b.getSize(); i++)
		ASSERT_EQ(str[i], l[i]);
}

TEST(BinConstr, InitStr)
{
	std::string k = "001000101";
	BinVector a(k);
	ASSERT_EQ(9, a.getSize());
	char* dop = a.getVec();
	for (int i = 0; i < k.length(); i++)
		ASSERT_EQ(k[i], dop[i]);
	k = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
	ASSERT_THROW(BinVector b(k), std::length_error);
	k = "11001101";
	BinVector c(k);
	ASSERT_EQ(8, c.getSize());
	dop = c.getVec();
	for (int i = 0; i < c.getSize(); i++)
		ASSERT_EQ(k[i], dop[i]);
}

/*TEST(BinMeth, Setter)
{
	BinVector a;
	std::cout << "Enter 10" << std::endl;
	a.setVec(2); // ввод числа 10 в 10-ой системе
	ASSERT_EQ(4, a.getSize());
	std::string str = "1010";
	char* buf = a.getVec();
	for (int i = 0; i < a.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	std::cout << "Enter 10" << std::endl;
	a.setVec(10); // ввод числа 10 в 2-ой системе
	ASSERT_EQ(2, a.getSize());
	str = "10";
	buf = a.getVec();
	for (int i = 0; i < a.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	std::cout << "Enter 101" << std::endl;
	a.setVec(2); // ввод числа 101 в 10-ой системе
	ASSERT_EQ(7, a.getSize());
	str = "1100101";
	buf = a.getVec();
	for (int i = 0; i < a.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	std::cout << "Enter 0010111010" << std::endl;
	a.setVec(10); // ввод числа 1011101 в 2-ой системе
	ASSERT_EQ(8, a.getSize());
	str = "10111010";
	buf = a.getVec();
	for (int i = 0; i < a.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
}*/

TEST(BinMeth, GetOR)
{
	BinVector a, b(10), c("00110101"), d(15); // 1111
	char* buf = a.OR(b).getVec();
	std::string str = "1010";
	for (int i = 0; i < b.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = b.OR(a).getVec();
	for (int i = 0; i < b.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = a.OR(c).getVec();
	str = "00110101";
	for (int i = 0; i < c.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = a.OR(d).getVec();
	str = "1111";
	for (int i = 0; i < d.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = b.OR(c).getVec();
	str = "00111111";
	for (int i = 0; i < c.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = b.OR(d).getVec();
	str = "1111";
	for (int i = 0; i < d.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = c.OR(d).getVec();
	str = "00111111";
	for (int i = 0; i < c.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
}

TEST(BinMeth, GetAND)
{
	BinVector a, b(10), c("00110101"), d(15); // 1111
	char* buf = a.AND(b).getVec();
	std::string str = "0000";
	for (int i = 0; i < b.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = b.AND(a).getVec();
	for (int i = 0; i < b.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = a.AND(c).getVec();
	str = "00000000";
	for (int i = 0; i < c.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = a.AND(d).getVec();
	str = "0000";
	for (int i = 0; i < d.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = b.AND(c).getVec();
	str = "00000000";
	for (int i = 0; i < c.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = b.AND(d).getVec();
	str = "1010";
	for (int i = 0; i < b.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = c.AND(d).getVec();
	str = "00000101";
	for (int i = 0; i < c.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
}

TEST(BinMeth, GetXOR)
{
	BinVector a, b(10), c("00110101"), d(15); // 1111
	char* buf = a.XOR(b).getVec();
	std::string str = "1010";
	for (int i = 0; i < b.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = b.XOR(a).getVec();
	for (int i = 0; i < b.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = a.XOR(c).getVec();
	str = "00110101";
	for (int i = 0; i < c.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = a.XOR(d).getVec();
	str = "1111";
	for (int i = 0; i < d.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = b.XOR(c).getVec();
	str = "00111111";
	for (int i = 0; i < c.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = b.XOR(d).getVec();
	str = "0101";
	for (int i = 0; i < b.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = c.XOR(d).getVec();
	str = "00111010";
	for (int i = 0; i < c.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
}

TEST(BinMeth, GetDOP)
{
	BinVector a, b(10), c("00110101"), d(15);
	char* buf = a.DOP().getVec();
	std::string str = "1";
	ASSERT_EQ(str[0], buf[0]);
	buf = b.DOP().getVec();
	str = "0101";
	for (int i = 0; i < b.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = c.DOP().getVec();
	str = "11001010";
	for (int i = 0; i < c.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = d.DOP().getVec();
	str = "0000";
	for (int i = 0; i < d.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
}

TEST(BinMeth, GetWN)
{
	BinVector a, b(10), c("00110101"), d(15);
	char* buf = a.WN().getVec();
	std::string str = "0";
	ASSERT_EQ(str[0], buf[0]);
	buf = b.WN().getVec();
	str = "101";
	for (int i = 0; i < b.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = c.WN().getVec();
	str = "110101";
	for (int i = 0; i < c.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
	buf = d.WN().getVec();
	str = "1111";
	for (int i = 0; i < d.getSize(); i++)
		ASSERT_EQ(str[i], buf[i]);
}

TEST(BinMeth, WNMeth)
{
	BinVector a("000101100");
	char* b = a.WN().getVec();
	ASSERT_EQ('1', b[0]);
	ASSERT_EQ('0', b[1]);
	ASSERT_EQ('1', b[2]);
	ASSERT_EQ('1', b[3]);
}