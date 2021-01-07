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
	int fir[] = { 15, 25, 10, 15, 7, 15, 11, 48, 15, 755, 99, 77, 21, 64, 74, 10, 48, 40 };
	MyVector<int> a(18, fir);
	MyVector<int> b = a;
	EXPECT_EQ(b.GetSize(), 18);
	std::stringstream str;
	str << b;
	EXPECT_EQ(str.str(), "{ 15 25 10 15 7 15 11 48 15 755 99 77 21 64 74 10 48 40 }");
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
	a.Insert(buf, 18);
	EXPECT_EQ(a.GetSize(), 9);
	str.str("");
	str << a;
	EXPECT_EQ(str.str(), "{ 1 15 5 9 10 18 22 45 45 }");
	buf = a.cend();
	a.Insert(buf, 5);
	EXPECT_EQ(a.GetSize(), 10);
	str.str("");
	str << a;
	EXPECT_EQ(str.str(), "{ 1 15 5 9 10 18 22 45 45 5 }");
	buf = a.cend();
	a.Insert(buf, 59);
	EXPECT_EQ(a.GetSize(), 11);
	str.str("");
	str << a;
	EXPECT_EQ(str.str(), "{ 1 15 5 9 10 18 22 45 45 5 59 }");
	buf = a.cend() + 1;
	EXPECT_EQ(a.Insert(buf, 10), BAD);
}

TEST(VectMeth, Erase)
{
	int buf[] = { 1, 5, 9, 10, 45, 45, 8, 61, 90, 70, 21, 18 };
	MyVector<int> a(12, buf);
	ConstIter<int> fir = a.cend() - 6, sec = a.cend() - 4;
	a.Erase(fir, sec);
	EXPECT_EQ(a.GetSize(), 10);
	std::stringstream str;
	str << a;
	EXPECT_EQ(str.str(), "{ 1 5 9 10 45 45 90 70 21 18 }");
	fir = a.cbegin() + 3;
	sec = a.cend() - 3;
	a.Erase(fir, sec);
	EXPECT_EQ(a.GetSize(), 6);
	str.str("");
	str << a;
	EXPECT_EQ(str.str(), "{ 1 5 9 70 21 18 }");
	fir = a.cbegin(), sec = a.cbegin() + 1;
	std::cout << std::endl << *fir << std::endl << std::endl;
	a.Erase(fir, sec);
	EXPECT_EQ(a.GetSize(), 5);
	str.str("");
	str << a;
	EXPECT_EQ(str.str(), "{ 5 9 70 21 18 }");
}

TEST(VectMeth, Find)
{
	int buf[] = { 1, 5, 9, 10, 45, 45, 8, 61, 90, 70 }, index = 0;
	MyVector<int> a(10, buf);
	index = a.find(5);
	EXPECT_EQ(a[index], 5);
	index = a.find(45);
	EXPECT_EQ(a[index], 45);
}

TEST(IterConstr, Init)
{
	int k[] = { 0, 5, 4 };
	MyVector<int> a(3, k), b(3, k);
	ConstIter<int> one(a.cbegin()), two(a.cbegin()), three(b.cbegin());
	Iter<int> fir(a.begin()), sec(a.begin() + 1), third(b.begin() + 2);
	EXPECT_EQ(*fir, 0);
	EXPECT_EQ(*third, 4);
	EXPECT_EQ(*sec, 5);
	EXPECT_EQ(*one, 0);
	EXPECT_EQ(*two, 0);
	EXPECT_EQ(*three, 0);
}

TEST(IterMeth, OperIsEq)
{
	int k[] = { 0, 5, 4 };
	MyVector<int> a(3, k), b(3, k);
	ConstIter<int> one(a.cbegin()), two(a.cbegin()), three(b.cbegin());
	Iter<int> fir(a.begin()), sec(b.begin()), third(b.begin());
	EXPECT_EQ(fir == sec, 0);
	EXPECT_EQ(sec == third, 1);
	EXPECT_EQ(one == two, 1);
	EXPECT_EQ(two == three, 0);
}

TEST(IterMeth, OperIsntEq)
{
	int k[] = { 0, 5, 4 };
	MyVector<int> a(3, k), b(3, k);
	ConstIter<int> one(a.cbegin()), two(a.cbegin()), three(b.cbegin());
	Iter<int> fir(a.begin()), sec(b.begin()), third(b.begin());
	EXPECT_EQ(fir != sec, 1);
	EXPECT_EQ(sec != third, 0);
	EXPECT_EQ(one != two, 0);
	EXPECT_EQ(two != three, 1);
}

TEST(IterMeth, IncDec)
{
	int k[] = { 0, 5, 4, 15, 7 };
	MyVector<int> a(5, k);
	ConstIter<int> one(a.cend());
	Iter<int> fir(a.begin());
	EXPECT_EQ(++fir, &(a[1]));
	EXPECT_EQ(++fir, &(a[2]));
	EXPECT_EQ(--fir, &(a[1]));
	EXPECT_EQ(--one, &(a[4]));
	EXPECT_EQ(--one, &(a[3]));
	EXPECT_EQ(++one, &(a[4]));
}

TEST(IterMeth, PlMin)
{
	int k[] = { 0, 5, 4, 15, 7 };
	MyVector<int> a(5, k);
	ConstIter<int> one(a.cend());
	Iter<int> fir(a.begin());
	fir = fir + 4;
	EXPECT_EQ(fir, &(a[4]));
	EXPECT_EQ(fir - 1, &(a[3]));
	one = one - 3;
	EXPECT_EQ(one, &(a[2]));
	EXPECT_EQ(one + 1, &(a[3]));
}

TEST(IterMeth, OperVal)
{
	int k[] = { 0, 5, 4, 15, 7 };
	MyVector<int> a(5, k);
	ConstIter<int> one(a.cend());
	Iter<int> fir(a.begin());
	EXPECT_EQ(*fir, 0);
	EXPECT_EQ(*(fir + 2), 4);
	EXPECT_EQ(*(one - 1), 7);
	++one;
	EXPECT_EQ(*(one - 4), 5);
}

TEST(IterMeth, OperAdr)
{
	int k[] = { 0, 5, 4, 15, 7 };
	MyVector<int> a(5, k);
	ConstIter<int> one(a.cend()), two(a.cbegin());
	Iter<int> fir(a.begin()), sec(a.end());
	EXPECT_EQ(&(fir), &(a[0]));
	EXPECT_EQ(&(two + 2), &(a[2]));
	EXPECT_EQ(&(one - 1), &(a[4]));
	EXPECT_EQ(&(sec - 3), &(a[2]));
}