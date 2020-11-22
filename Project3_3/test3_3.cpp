#include "pch.h"
#include "D:\Program\Lab\Proj2.3.1\Project3_3\BinVector_dyn.cpp"

TEST(BinConstr, InitDef)
{
	BinVector a, b;
	std::string str;
	a.GetVect(str);
	int s1 = a.GetSize(), s2 = b.GetSize();
	EXPECT_EQ(0, s1);
	EXPECT_EQ(0, s2);
	EXPECT_EQ(str, "0");
	b.GetVect(str);
	EXPECT_EQ(str, "0");
}

TEST(BinConstr, InitInt)
{
	BinVector a(0), b(1), c(1015), d(45), e(-54); //1111110111  101101
	std::string str;
	a.GetVect(str);
	EXPECT_EQ(0, a.GetSize());
	EXPECT_EQ(str, "0");
	str = "";
	b.GetVect(str);
	EXPECT_EQ(1, b.GetSize());
	EXPECT_EQ(str, "1");
	str = "";
	c.GetVect(str);
	EXPECT_EQ(10, c.GetSize());
	EXPECT_EQ(str, "1111110111");
	str = "";
	d.GetVect(str);
	EXPECT_EQ(6, d.GetSize());
	EXPECT_EQ(str, "101101");
	EXPECT_EQ(6, e.GetSize());
	EXPECT_EQ(str, "101101");
}

TEST(BinConstr, InitStr)
{
	BinVector a("110010"), b(""), c("00011101101011100"), d("100011000");
	std::string str;
	a.GetVect(str);
	EXPECT_EQ(6, a.GetSize());
	EXPECT_EQ(str, "110010");
	b.GetVect(str);
	EXPECT_EQ(0, b.GetSize());
	EXPECT_EQ(str, "0");
	c.GetVect(str);
	EXPECT_EQ(17, c.GetSize());
	EXPECT_EQ(str, "00011101101011100");
	d.GetVect(str);
	EXPECT_EQ(9, d.GetSize());
	EXPECT_EQ(str, "100011000");
	EXPECT_THROW(BinVector e("aas45"), std::invalid_argument);
}

TEST(BinConstr, InitCopy)
{
	BinVector a("110010"), b(""), c("00011101101011100"), d("100011000"), dop_a(a), dop_b(b), dop_c(c), dop_d(d);
	std::string str;
	dop_a.GetVect(str);
	EXPECT_EQ(6, dop_a.GetSize());
	EXPECT_EQ(str, "110010");
	dop_b.GetVect(str);
	EXPECT_EQ(0, dop_b.GetSize());
	EXPECT_EQ(str, "0");
	dop_c.GetVect(str);
	EXPECT_EQ(17, dop_c.GetSize());
	EXPECT_EQ(str, "00011101101011100");
	dop_d.GetVect(str);
	EXPECT_EQ(9, dop_d.GetSize());
	EXPECT_EQ(str, "100011000");
}

TEST(BinMeth, Oper_OR)
{
	BinVector a("110010"), b(""), c("00011101101011100"), d("100011000"), res;
	std::string str;
	res = a | b;
	res.GetVect(str);
	EXPECT_EQ(6, res.GetSize());
	EXPECT_EQ(str, "110010");
	res = a | c;
	res.GetVect(str);
	EXPECT_EQ(17, res.GetSize());
	EXPECT_EQ(str, "00011101101111110");
	res = a | d;
	res.GetVect(str);
	EXPECT_EQ(9, res.GetSize());
	EXPECT_EQ(str, "100111010");
	res = b | a;
	res.GetVect(str);
	EXPECT_EQ(6, res.GetSize());
	EXPECT_EQ(str, "110010");
	res = b | b;
	res.GetVect(str);
	EXPECT_EQ(0, res.GetSize());
	EXPECT_EQ(str, "0");
	res = b | c;
	res.GetVect(str);
	EXPECT_EQ(17, res.GetSize());
	EXPECT_EQ(str, "00011101101011100");
	res = b | d;
	res.GetVect(str);
	EXPECT_EQ(9, res.GetSize());
	EXPECT_EQ(str, "100011000");
	res = c | d;
	res.GetVect(str);
	EXPECT_EQ(17, res.GetSize());
	EXPECT_EQ(str, "00011101101011100");
}

TEST(BinMeth, Oper_AND)
{
	BinVector a("110010"), b(""), c("00011101101011100"), d("100011000"), res;
	std::string str;
	res = a & b;
	res.GetVect(str);
	EXPECT_EQ(6, res.GetSize());
	EXPECT_EQ(str, "000000");
	res = a & c;
	res.GetVect(str);
	EXPECT_EQ(17, res.GetSize());
	EXPECT_EQ(str, "00000000000010000");
	res = a & d;
	res.GetVect(str);
	EXPECT_EQ(9, res.GetSize());
	EXPECT_EQ(str, "000010000");
	res = b & a;
	res.GetVect(str);
	EXPECT_EQ(6, res.GetSize());
	EXPECT_EQ(str, "000000");
	res = b & b;
	res.GetVect(str);
	EXPECT_EQ(0, res.GetSize());
	EXPECT_EQ(str, "0");
	res = b & c;
	res.GetVect(str);
	EXPECT_EQ(17, res.GetSize());
	EXPECT_EQ(str, "00000000000000000");
	res = b & d;
	res.GetVect(str);
	EXPECT_EQ(9, res.GetSize());
	EXPECT_EQ(str, "000000000");
	res = c & d;
	res.GetVect(str);
	EXPECT_EQ(17, res.GetSize());
	EXPECT_EQ(str, "00000000100011000");
}

TEST(BinMeth, Oper_XOR)
{
	BinVector a("110010"), b(""), c("00011101101011100"), d("100011000"), res;
	std::string str;
	res = a;
	res ^= a;
	res.GetVect(str);
	EXPECT_EQ(6, res.GetSize());
	EXPECT_EQ(str, "000000");
	res = a;
	res ^= b;
	res.GetVect(str);
	EXPECT_EQ(6, res.GetSize());
	EXPECT_EQ(str, "110010");
	res = a;
	res ^= c;
	res.GetVect(str);
	EXPECT_EQ(17, res.GetSize());
	EXPECT_EQ(str, "00011101101101110");
	res = a;
	res ^= d;
	res.GetVect(str);
	EXPECT_EQ(9, res.GetSize());
	EXPECT_EQ(str, "100101010");
	res = b;
	res ^= c;
	res.GetVect(str);
	EXPECT_EQ(17, res.GetSize());
	EXPECT_EQ(str, "00011101101011100");
	res = b;
	res ^= d;
	res.GetVect(str);
	EXPECT_EQ(9, res.GetSize());
	EXPECT_EQ(str, "100011000");
	res = c;
	res ^= d;
	res.GetVect(str);
	EXPECT_EQ(17, res.GetSize());
	EXPECT_EQ(str, "00011101001000100");
}

TEST(BinMeth, Oper_DOP)
{
	BinVector a("110010"), b(""), c("00011101101011100"), d("100011000"), res;
	std::string str;
	res = ~a;
	res.GetVect(str);
	EXPECT_EQ(6, res.GetSize());
	EXPECT_EQ(str, "001101");
	res = ~b;
	res.GetVect(str);
	EXPECT_EQ(1, res.GetSize());
	EXPECT_EQ(str, "1");
	res = ~c;
	res.GetVect(str);
	EXPECT_EQ(17, res.GetSize());
	EXPECT_EQ(str, "11100010010100011");
	res = ~d;
	res.GetVect(str);
	EXPECT_EQ(9, res.GetSize());
	EXPECT_EQ(str, "011100111");
}

TEST(BinMeth, Oper_WN)
{
	BinVector a("110010"), b(""), c("00011101101011100"), d("100011000"), res;
	std::string str;
	a.WN(res);
	res.GetVect(str);
	EXPECT_EQ(5, res.GetSize());
	EXPECT_EQ(str, "11001");
	b.WN(res);
	res.GetVect(str);
	EXPECT_EQ(0, res.GetSize());
	EXPECT_EQ(str, "0");
	c.WN(res);
	res.GetVect(str);
	EXPECT_EQ(12, res.GetSize());
	EXPECT_EQ(str, "111011010111");
	d.WN(res);
	res.GetVect(str);
	EXPECT_EQ(6, res.GetSize());
	EXPECT_EQ(str, "100011");
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