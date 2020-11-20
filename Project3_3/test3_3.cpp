#include "pch.h"
#include "D:\Program\Lab\Proj2.3.1\Project3_3\BinVector_dyn.cpp"

TEST(BinConstr, InitDef)
{
	BinVector a, b;
	int s1 = a.GetSize(), s2 = b.GetSize();
	EXPECT_EQ(0, s1);
	EXPECT_EQ(0, s2);
}

TEST(BinConstr, InitInt)
{
	BinVector a(0), b(1), c(1015), d(45), e(-54); //1111110111  101101
	EXPECT_EQ(0, a.GetSize());
	EXPECT_EQ(1, b.GetSize());
	EXPECT_EQ(10, c.GetSize());
	EXPECT_EQ(6, d.GetSize());
	EXPECT_EQ(6, e.GetSize());
}

TEST(BinConstr, InitStr)
{
	BinVector a("110010"), b(""), c("00011101101011100"), d("100011000");
	EXPECT_EQ(6, a.GetSize());
	EXPECT_EQ(0, b.GetSize());
	EXPECT_EQ(17, c.GetSize());
	EXPECT_EQ(9, d.GetSize());
	EXPECT_THROW(BinVector d("aas45"), std::invalid_argument);
}

TEST(BinConstr, InitCopy)
{
	BinVector a("110010"), b(""), c("00011101101011100"), d("100011000"), dop_a(a), dop_b(b), dop_c(c), dop_d(d);
	EXPECT_EQ(6, a.GetSize());
	EXPECT_EQ(0, b.GetSize());
	EXPECT_EQ(17, c.GetSize());
	EXPECT_EQ(9, d.GetSize());
}

TEST(BinMeth, Oper_OR)
{
	BinVector a("110010"), b(""), c("00011101101011100"), d("100011000"), res;
	res = a | b;
	EXPECT_EQ(6, res.GetSize());
	res = a | c;
	EXPECT_EQ(17, res.GetSize());
	res = a | d;
	EXPECT_EQ(9, res.GetSize());
	res = b | a;
	EXPECT_EQ(6, res.GetSize());
	res = b | b;
	EXPECT_EQ(0, res.GetSize());
	res = b | c;
	EXPECT_EQ(17, res.GetSize());
	res = b | d;
	EXPECT_EQ(9, res.GetSize());
	res = c | d;
	EXPECT_EQ(17, res.GetSize());
}

TEST(BinMeth, Oper_AND)
{
	BinVector a("110010"), b(""), c("00011101101011100"), d("100011000"), res;
	res = a & b;
	EXPECT_EQ(6, res.GetSize());
	res = a & c;
	EXPECT_EQ(17, res.GetSize());
	res = a & d;
	EXPECT_EQ(9, res.GetSize());
	res = b & a;
	EXPECT_EQ(6, res.GetSize());
	res = b & b;
	EXPECT_EQ(0, res.GetSize());
	res = b & c;
	EXPECT_EQ(17, res.GetSize());
	res = b & d;
	EXPECT_EQ(9, res.GetSize());
	res = c & d;
	EXPECT_EQ(17, res.GetSize());
}

TEST(BinMeth, Oper_XOR)
{
	BinVector a("110010"), b(""), c("00011101101011100"), d("100011000"), res;
	res = a;
	res ^= a;
	EXPECT_EQ(6, res.GetSize());
	res = a;
	res ^= b;
	EXPECT_EQ(6, res.GetSize());
	res = a;
	res ^= c;
	EXPECT_EQ(17, res.GetSize());
	res = a;
	res ^= d;
	EXPECT_EQ(9, res.GetSize());
	res = b;
	res ^= c;
	EXPECT_EQ(17, res.GetSize());
	res = b;
	res ^= d;
	EXPECT_EQ(9, res.GetSize());
	res = c;
	res ^= d;
	EXPECT_EQ(17, res.GetSize());
}

TEST(BinMeth, Oper_DOP)
{
	BinVector a("110010"), b(""), c("00011101101011100"), d("100011000"), res;
	res = ~a;
	EXPECT_EQ(6, res.GetSize());
	res = ~b;
	EXPECT_EQ(0, res.GetSize());
	res = ~c;
	EXPECT_EQ(17, res.GetSize());
	res = ~d;
	EXPECT_EQ(9, res.GetSize());
}

TEST(BinMeth, Oper_WN)
{
	BinVector a("110010"), b(""), c("00011101101011100"), d("100011000"), res;
	a.WN(res);
	EXPECT_EQ(5, res.GetSize());
	b.WN(res);
	EXPECT_EQ(0, res.GetSize());
	c.WN(res);
	EXPECT_EQ(12, res.GetSize());
	d.WN(res);
	EXPECT_EQ(6, res.GetSize());
}

TEST(BinMeth, Oper_EQ)
{
	BinVector a("110010"), b(""), c("00011101101011100"), d("100011000"), res;
	res = a;
	EXPECT_EQ(6, res.GetSize());
	res = b;
	EXPECT_EQ(0, res.GetSize());
	res = c;
	EXPECT_EQ(17, res.GetSize());
	res = d;
	EXPECT_EQ(9, res.GetSize());
}