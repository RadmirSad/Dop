#include "pch.h"
#include "D:\Program\Lab\TowerDefence\Vect.h"

TEST(VectConst, Def) 
{
	MyVector<int> a;
	EXPECT_EQ(0, a.GetSize());
	EXPECT_EQ(10, a.GetDopSize());
}

TEST(VectConst, Init)
{
	int k[] = { 0, 4, 8, 3 };
	MyVector<int> a(4, k);
	EXPECT_EQ(a.GetSize(), 4);
	EXPECT_EQ(a.GetDopSize(), 10);
	std::stringstream str;
	str << a;
	EXPECT_EQ(str.str(), "{ 0 4 8 3 }");
	EXPECT_THROW(MyVector<int> c(-1, k), std::out_of_range);
	EXPECT_THROW(MyVector<int> d(5, nullptr), std::invalid_argument);
}

TEST(VectConst, Copy)
{
	int fir[] = { 11, 48, 5, 1, 54 };
	MyVector<int> a(5, fir);
	MyVector<int> b(a);
	EXPECT_EQ(b.GetSize(), 5);
	std::stringstream str;
	str << b;
	EXPECT_EQ(str.str(), "{ 11 48 5 1 54 }");
}

TEST(VectMeth, Oper_Eq)
{
	int fir[] = { 15, 25, 10, 15, 7 };
	MyVector<int> a(5, fir);
	MyVector<int> b = a;
	EXPECT_EQ(b.GetSize(), 5);
	std::stringstream str;
	str << b;
	EXPECT_EQ(str.str(), "{ 15 25 10 15 7 }");
}

TEST(VectMeth, Oper_Ind)
{
	int fir[] = { 15, 25, 10, 15, 7 };
	MyVector<int> a(5, fir);
	for (int i = 0; i < 5; i++)
		EXPECT_EQ(a[i], fir[i]);
}

TEST(VectMeth, Oper_Out)
{
	int fir[] = { 1, 5, 9, 10, 45, 45 }, sec[] = { 100, 45, 55, 1 };
	MyVector<int> a(6, fir), b(4, sec);
	std::stringstream str;
	str << a;
	EXPECT_EQ(str.str(), "{ 1 5 9 10 45 45 }");
	str.str("");
	str << b;
	EXPECT_EQ(str.str(), "{ 100 45 55 1 }");
}

TEST(VectMeth, Insert)
{
	int fir[] = { 1, 5, 9, 10, 45, 45 };
	MyVector<int> a(6, fir);
	ConstIter<int> buf = a.cbegin();
	a.Insert(buf, 15);
	EXPECT_EQ(a.GetSize(), 7);
	std::stringstream str;
	str << a;
	EXPECT_EQ(str.str(), "{ 1 15 5 9 10 45 45 }");
	for (buf = a.cbegin(); *buf != a[4]; ++buf);
	a.Insert(buf, 22);
	EXPECT_EQ(a.GetSize(), 8);
	str.str("");
	str << a;
	EXPECT_EQ(str.str(), "{ 1 15 5 9 10 22 45 45 }");
	buf = a.cend() + 1;
	EXPECT_EQ(a.Insert(buf, 10), BAD);
}

TEST(VectMeth, Erase)
{
	int buf[] = { 1, 5, 9, 10, 45, 45, 8, 61, 90, 70 };
	MyVector<int> a(10, buf);
	ConstIter<int> fir = a.cend() - 4, sec = a.cend() - 2;
	a.Erase(fir, sec);
	EXPECT_EQ(a.GetSize(), 8);
	std::stringstream str;
	str << a;
	EXPECT_EQ(str.str(), "{ 1 5 9 10 45 45 90 70 }");
	fir = a.cbegin() + 3;
	sec = a.cend() - 3;
	a.Erase(fir, sec);
	EXPECT_EQ(a.GetSize(), 6);
	str.str("");
	str << a;
	EXPECT_EQ(str.str(), "{ 1 5 9 45 90 70 }");
	fir = a.cbegin(), sec = a.cbegin() + 1;
	a.Erase(fir, sec);
	EXPECT_EQ(a.GetSize(), 5);
	str.str("");
	str << a;
	EXPECT_EQ(str.str(), "{ 5 9 45 90 70 }");
}