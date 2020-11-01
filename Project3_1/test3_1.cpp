#include "pch.h"
#include "D:\Program\Lab\Proj2.3.1\Project3_1\BinVector.cpp"

TEST(BinConstr, InitDef)
{
	BinVector k;
	EXPECT_EQ(1, k.getSize());
	const char* l = k.getVec();
	EXPECT_EQ('0', l[0]);
}

TEST(BinConstr, InitInt)
{
	BinVector a(5);
	EXPECT_EQ(3, a.getSize());
	const char* l = a.getVec(), k [] = "101";
	for (int i = 0; i < a.getSize(); i++)
		EXPECT_EQ(k[i], l[i]);
	BinVector b(10);
	EXPECT_EQ(4, b.getSize());
	l = b.getVec();
	char str[] = "1010";
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], l[i]);
}

TEST(BinConstr, InitStr)
{
	std::string k = "001000101";
	BinVector a(k);
	EXPECT_EQ(9, a.getSize());
	const char* dop = a.getVec();
	for (int i = 0; i < k.length(); i++)
		ASSERT_EQ(k[i], dop[i]);
	k = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
	ASSERT_THROW(BinVector b(k), std::length_error);
	k = "11001101";
	BinVector c(k);
	EXPECT_EQ(8, c.getSize());
	dop = c.getVec();
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(k[i], dop[i]);
}

TEST(BinMeth, Setter)
{
	BinVector a;
	std::cout << "Enter 10" << std::endl;
	a.setVec(2); // ввод числа 10 в 10-ой системе
	EXPECT_EQ(4, a.getSize());
	std::string str = "1010";
	const char* buf = a.getVec();
	for (int i = 0; i < a.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	std::cout << "Enter 10" << std::endl;
	a.setVec(10); // ввод числа 10 в 2-ой системе
	EXPECT_EQ(2, a.getSize());
	str = "10";
	buf = a.getVec();
	for (int i = 0; i < a.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	std::cout << "Enter 101" << std::endl;
	a.setVec(2); // ввод числа 101 в 10-ой системе
	EXPECT_EQ(7, a.getSize());
	str = "1100101";
	buf = a.getVec();
	for (int i = 0; i < a.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	std::cout << "Enter 0010111010" << std::endl;
	a.setVec(10); // ввод числа 1011101 в 2-ой системе
	EXPECT_EQ(8, a.getSize());
	str = "10111010";
	buf = a.getVec();
	for (int i = 0; i < a.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
}

TEST(BinMeth, GetOR)
{
	BinVector a, b(10), c("00110101"), d(15), dop, &res = dop; // 1111
	a.OR(b, res);
	const char* buf = res.getVec();
	std::string str = "1010";
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	b.OR(a, res);
	buf = res.getVec();
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	a.OR(c, res);
	buf = res.getVec();
	str = "00110101";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	a.OR(d, res);
	buf = res.getVec();
	str = "1111";
	for (int i = 0; i < d.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	b.OR(c, res);
	buf = res.getVec();
	str = "00111111";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	b.OR(d, res);
	buf = res.getVec();
	str = "1111";
	for (int i = 0; i < d.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	c.OR(d, res);
	buf = res.getVec();
	str = "00111111";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
}
 
TEST(BinMeth, GetAND)
{
	BinVector a, b(10), c("00110101"), d(15), dop, &res = dop; // 1111
	a.AND(b, res);
	const char* buf = res.getVec();
	std::string str = "0000";
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	b.AND(a, res);
	buf =res.getVec();
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	a.AND(c, res);
	buf = res.getVec();
	str = "00000000";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	a.AND(d, res);
	buf = res.getVec();
	str = "0000";
	for (int i = 0; i < d.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	b.AND(c, res);
	buf = res.getVec();
	str = "00000000";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	b.AND(d, res);
	buf = res.getVec();
	str = "1010";
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	c.AND(d, res);
	buf = res.getVec();
	str = "00000101";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
}

TEST(BinMeth, GetXOR)
{
	BinVector a, b(10), c("00110101"), d(15), dop, & res = dop; // 1111
	a.XOR(b, res);
	const char* buf = res.getVec();
	std::string str = "1010";
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	b.XOR(a, res);
	buf = res.getVec();
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	a.XOR(c, res);
	buf = res.getVec();
	str = "00110101";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	a.XOR(d, res);
	buf = res.getVec();
	str = "1111";
	for (int i = 0; i < d.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	b.XOR(c, res);
	buf = res.getVec();
	str = "00111111";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	b.XOR(d, res);
	buf = res.getVec();
	str = "0101";
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	c.XOR(d, res);
	buf = res.getVec();
	str = "00111010";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
}

TEST(BinMeth, GetDOP)
{
	BinVector a, b(10), c("00110101"), d(15), res;
	a.DOP(res);
	const char* buf = res.getVec();
	std::string str = "1";
	EXPECT_EQ(str[0], buf[0]);
	b.DOP(res);
	buf = res.getVec();
	str = "0101";
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	c.DOP(res);
	buf = res.getVec();
	str = "11001010";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	d.DOP(res);
	buf = res.getVec();
	str = "0000";
	for (int i = 0; i < d.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
}

TEST(BinMeth, GetWN)
{
	BinVector a, b(10), c("00110101"), d(15), res;
	a.WN(res);
	const char* buf = res.getVec();
	std::string str = "0";
	EXPECT_EQ(str[0], buf[0]);
	b.WN(res);
	buf = res.getVec();
	str = "101";
	for (int i = 0; i < str.length(); i++)
		EXPECT_EQ(str[i], buf[i]);
	c.WN(res);
	buf = res.getVec();
	str = "110101";
	for (int i = 0; i < str.length(); i++)
		EXPECT_EQ(str[i], buf[i]);
	d.WN(res);
	buf = res.getVec();
	str = "1111";
	for (int i = 0; i < str.length(); i++)
		EXPECT_EQ(str[i], buf[i]);
}