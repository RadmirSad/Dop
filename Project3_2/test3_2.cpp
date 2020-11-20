#include "pch.h"
#include "D:\Program\Lab\Proj2.3.1\Project3_2\BinVector2.cpp"

TEST(VectOper, or)
{
	BinVector a, b(10), c("00110101"), d(15); // 1111
	const char* buf = (a | b).getVec();
	std::string str = "1010";
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	buf = (b | a).getVec();
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	buf = (a | c).getVec();
	str = "00110101";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	buf = (a | d).getVec();
	str = "1111";
	for (int i = 0; i < d.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	buf = (b | c).getVec();
	str = "00111111";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	buf = (b | d).getVec();
	str = "1111";
	for (int i = 0; i < d.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	buf = (c | d).getVec();
	str = "00111111";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
}

TEST(VectOper, and)
{
	BinVector a, b(10), c("00110101"), d(15); // 1111
	const char* buf = (a & b).getVec();
	std::string str = "0000";
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	buf = (b & a).getVec();
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	buf = (a & c).getVec();
	str = "00000000";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	buf = (a & d).getVec();
	str = "0000";
	for (int i = 0; i < d.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	buf = (b & c).getVec();
	str = "00000000";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	buf = (b & d).getVec();
	str = "1010";
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	buf = (c & d).getVec();
	str = "00000101";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
}

TEST(VectOper, xor)
{
	BinVector a, b(10), c("00110101"), d(15), dop; // 1111
	dop = a;
	a ^= b;
	const char* buf = a.getVec();
	std::string str = "1010";
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	a = dop;
	dop = b;
	b ^= a;
	buf = b.getVec();
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	b = dop;
	dop = a;
	a ^= c;
	buf = a.getVec();
	str = "00110101";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	a = dop;
	a ^= d;
	buf = a.getVec();
	str = "1111";
	for (int i = 0; i < d.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	a = dop;
	dop = b;
	b ^= c;
	buf = b.getVec();
	str = "00111111";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	b = dop;
	b ^= d;
	buf = b.getVec();
	str = "0101";
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	b = dop;
	dop = c;
	c ^= d;
	buf = c.getVec();
	str = "00111010";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	c = dop;
}

TEST(VectOper, dop)
{
	BinVector a, b(10), c("00110101"), d(15);
	const char* buf = (~ a).getVec();
	std::string str = "1";
	EXPECT_EQ(str[0], buf[0]);
	buf = (~ b).getVec();
	str = "0101";
	for (int i = 0; i < b.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	buf = (~ c).getVec();
	str = "11001010";
	for (int i = 0; i < c.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
	buf = (~ d).getVec();
	str = "0000";
	for (int i = 0; i < d.getSize(); i++)
		EXPECT_EQ(str[i], buf[i]);
}