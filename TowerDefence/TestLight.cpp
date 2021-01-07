#include "pch.h"
/*#include "D:\Program\Lab\TowerDefence\Destruct.cpp"
#include "D:\Program\Lab\TowerDefence\Light.cpp"
#include "D:\Program\Lab\TowerDefence\Dark.cpp"
#include "D:\Program\Lab\TowerDefence\Map.cpp"
#include "D:\Program\Lab\TowerDefence\Game.cpp"*/
#include "D:\Program\Lab\TowerDefence\Light.h"

TEST(WallConst, DefConst)
{
	Wall a;
	EXPECT_EQ(100, a.GetPr()); EXPECT_EQ(50, a.GetCostRep()); EXPECT_EQ(50, a.GetHpInc()); EXPECT_EQ(100, a.GetHealth());
	int x = 0, y = 0;
	a.GetCoord(x, y);
	EXPECT_EQ(0, x); EXPECT_EQ(0, y);
}

TEST(WallConst, InitConst)
{
	Wall a(1.5, 1, 100);
	EXPECT_EQ(100, a.GetPr()); EXPECT_EQ(50 , a.GetCostRep());
	EXPECT_EQ(50 * 1.5, a.GetHpInc()); EXPECT_EQ(100 * 1.5, a.GetHealth());
	int x = 0, y = 0;
	a.GetCoord(x, y);
	EXPECT_EQ(1, x); EXPECT_EQ(100, y);
}


TEST(CastleConst, DefConst)
{
	Castle a;
	EXPECT_EQ(50, a.Cash()); EXPECT_EQ(150, a.CostOfUp()); EXPECT_EQ(100, a.GetCostRep()); EXPECT_EQ(250, a.GetHealth());
	EXPECT_EQ(15, a.GetRev()); EXPECT_EQ(100, a.GetHpInc());
	int x = 0, y = 0;
	a.GetCoord(x, y);
	EXPECT_EQ(0, x); EXPECT_EQ(0, y);
}

TEST(CastleConst, InitConst)
{
	Castle a(1, 4, 1), b(1.5, 3, 2);
	int x = 0, y = 0;
	a.GetCoord(x, y);
	EXPECT_EQ(4, x); EXPECT_EQ(1, y);
	EXPECT_EQ(50 * 1.5, b.Cash()); EXPECT_EQ(1.5 * 150, b.CostOfUp()); EXPECT_EQ(100 * 1.5, b.GetCostRep());
	EXPECT_EQ(250 * 1.5, b.GetHealth()); EXPECT_EQ((int)(15 * 1.5), b.GetRev()); EXPECT_EQ(100 * 1.5, b.GetHpInc());
	b.GetCoord(x, y);
	EXPECT_EQ(3, x); EXPECT_EQ(2, y);
}

TEST(CastleMeth, TakeCash)
{
	Castle a;
	int cash = a.Cash();
	a.TakeMoney();
	EXPECT_EQ(cash + a.GetRev(), a.Cash());
}

TEST(CastleMeth, Buy)
{
	Castle a(1.2);
	a.BuySmth(10);
	EXPECT_EQ(50, a.Cash());
	EXPECT_THROW(a.BuySmth(-11), std::invalid_argument);
}

TEST(CastleMeth, Up)
{
	Castle a;
	for(int i = 0; i < 10; i++)
		a.TakeMoney();
	a.Upgrade(1);
	EXPECT_EQ(50, a.Cash()); EXPECT_EQ(250, a.CostOfUp()); EXPECT_EQ(30, a.GetRev());
	EXPECT_EQ(175, a.GetCostRep()); EXPECT_EQ(310, a.GetHealth());
}

TEST(CastleMeth, Multy)
{
	Castle a;
	a.Multiply(1.2);
	EXPECT_EQ(50 * 1.2, a.Cash()); EXPECT_EQ(1.2 * 150, a.CostOfUp()); EXPECT_EQ(100 * 1.2, a.GetCostRep());
	EXPECT_EQ(250 * 1.2, a.GetHealth()); EXPECT_EQ((int)(15 * 1.2), a.GetRev()); EXPECT_EQ(100 * 1.2, a.GetHpInc());
}

TEST(CastMeth, Basic)
{
	Castle a(1.2);
	a.SetBasicParams();
	EXPECT_EQ(50, a.Cash()); EXPECT_EQ(150, a.CostOfUp()); EXPECT_EQ(100, a.GetCostRep());
	EXPECT_EQ(250, a.GetHealth()); EXPECT_EQ((int)(15), a.GetRev()); EXPECT_EQ(100, a.GetHpInc());
}