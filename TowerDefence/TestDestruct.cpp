#include "pch.h"
#include "D:\Program\Lab\TowerDefence\Destruct.cpp"
#include "D:\Program\Lab\TowerDefence\Light.cpp"
#include "D:\Program\Lab\TowerDefence\Dark.cpp"
#include "D:\Program\Lab\TowerDefence\Map.cpp"
#include "D:\Program\Lab\TowerDefence\Game.cpp"

TEST(DestructConst, DefConst)
{
	Destruct a;
	Tile dop;
	EXPECT_EQ(dop, a.GetTile());
	EXPECT_EQ(0, a.GetHealth()); EXPECT_EQ(0, a.GetMaxHealth());
}

TEST(DestructConst, InitConst)
{
	Tile dop(2, 8);
	Destruct a(10, 1, 2), b(15, dop);
	EXPECT_EQ(dop, b.GetTile());
	EXPECT_EQ(10, a.GetHealth()); EXPECT_EQ(15, b.GetHealth());
	int x = 0, y = 0;
	a.GetCoord(x, y);
	EXPECT_EQ(1, x); EXPECT_EQ(2, y);
}

TEST(DestructMeth, Damage)
{
	Destruct a(10, 1, 3), b(25, 2, 4), c(20, 1, 4);
	a.TakeDamage(5.5); b.TakeDamage(27);
	EXPECT_EQ(4.5, a.GetHealth()); EXPECT_EQ(0, b.GetHealth());
	EXPECT_THROW(c.TakeDamage(-1), std::invalid_argument);
}

TEST(BuildConst, DefConst)
{
	Building a;
	Destruct dop;
	EXPECT_EQ(dop.GetTile(), a.GetTile()); EXPECT_EQ(dop.GetHealth(), a.GetHealth()); EXPECT_EQ(0, a.GetCostRep()); EXPECT_EQ(0, a.GetHpInc());
}

TEST(BuildConst, InitConst)
{
	Building a(10, 15, 20, 1, 5); Tile dop(1, 5);
	EXPECT_EQ(10, a.GetCostRep()); EXPECT_EQ(15, a.GetHpInc()); EXPECT_EQ(20, a.GetHealth()); EXPECT_EQ(dop, a.GetTile());
}

TEST(BuildMeth, Repair)
{
	Castle C(1, 1, 1);
	Building a(10, 15, 20, 1, 5);
	a.TakeDamage(17);
	a.Repair(C);
	EXPECT_EQ(18, a.GetHealth()); EXPECT_EQ(40, C.Cash());
}