#include "pch.h"
#include "D:\Program\Lab\TowerDefence\Tile.cpp"

TEST(TileConst, DefConst)
{
	Tile a;
	int x = 0, y = 0;
	a.GetCoord(x, y);
	EXPECT_EQ(0, x);
	EXPECT_EQ(0, y);
}

TEST(TileConst, InitConst)
{
	Tile a(1, 4), b(2, 3);
	int x = 0, y = 0;
	a.GetCoord(x, y);
	EXPECT_EQ(1, x); EXPECT_EQ(4, y);
	b.GetCoord(x, y);
	EXPECT_EQ(2, x); EXPECT_EQ(3, y);
	EXPECT_THROW(Tile c(-5, 1), std::invalid_argument);
}

TEST(TileConst, CopyConst)
{
	Tile a(34, 10), b(a);
	int x = 0, y = 0;
	b.GetCoord(x, y);
	EXPECT_EQ(34, x); EXPECT_EQ(10, y);
}

TEST(TileMeth, Change)
{
	Tile a(1, 5), b;
	a.ChangeTile(4, 2);
	int x = 0, y = 0;
	a.GetCoord(x, y);
	EXPECT_EQ(4, x); EXPECT_EQ(2, y);
	b.ChangeTile(a);
	b.GetCoord(x, y);
	EXPECT_EQ(4, x); EXPECT_EQ(2, y);
}

TEST(TileMeth, Oper)
{
	Tile a(1, 4), b(1, 4), c(3, 2);
	EXPECT_EQ(1, a == b);
	EXPECT_EQ(0, a == c);
}


TEST(NodeConst, DefConst)
{
	Node a;
	Tile dop;
	int x = 0, y = 0;
	EXPECT_EQ(dop, a.GetTile());
	a.GetCoord(x, y);
	EXPECT_EQ(0, x); EXPECT_EQ(0, y);
	EXPECT_EQ(1, a.GetPrior());
	EXPECT_EQ(0, a.GetSize());
}

TEST(NodeConst, InitConst)
{
	Node a(1, 4, 2);
	Tile dop(1, 4);
	int x = 0, y = 0;
	a.GetCoord(x, y);
	EXPECT_EQ(dop, a.GetTile());
	EXPECT_EQ(1, x); EXPECT_EQ(4, y);
	EXPECT_EQ(2, a.GetPrior());
	EXPECT_EQ(0, a.GetSize());
}

TEST(NodeMeth, NodeInsert)
{
	Node a(1, 2), b(3, 6, 2), c(4, 2);
	Tile dop(1, 2);
	a.Insert(a.cend(), &b); a.Insert(a.cend(), &c);
	EXPECT_EQ(2, a.GetSize());
	EXPECT_EQ(dop, a.GetTile());
	EXPECT_EQ(&b, a.GetPoint(0)); EXPECT_EQ(&c, a.GetPoint(1));
	a.Clear();
	EXPECT_EQ(0, a.GetSize());
}

TEST(NodeMeth, ChangePrior)
{
	Node a(1, 2), b(3, 6, 2), c(4, 2);
	a.ChangePrior(), b.ChangePrior(), c.ChangePrior();
	EXPECT_EQ(2, a.GetPrior()); EXPECT_EQ(1, b.GetPrior()); EXPECT_EQ(2, c.GetPrior());
}