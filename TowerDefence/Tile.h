#pragma once

#ifndef _TILE_H_
#define _TILE_H_
#define DEBUG 1

#include "Vect.h"

enum Types
{
	BASIN,
	VALLEY,
	MOUNTAIN,
	ROAD,
	TOWER,
	WALL,
	CASTLE,
	LAIR,
	EMPTY
};

class Tile
{
protected:
	int X = 0;
	int Y = 0;
public:
	Tile() { ; }
	Tile(int x0, int y0);
	Tile(const Tile& NewTile);
	void ChangeTile(int x1, int y1) { X = x1; Y = y1; }
	void ChangeTile(const Tile& Field) { X = Field.X; Y = Field.Y; }
	void GetCoord(int& x1, int& y1) const { x1 = X; y1 = Y; }
	int operator == (const Tile& Dop) const { return ((Dop.X == X) && (Dop.Y == Y)); }
	int operator != (const Tile& Dop) const { return ((Dop.X != X) || (Dop.Y != Y)); }
	friend std::ostream& operator << (std::ostream& out, const Tile& dop);
};

class Node
{
private:
	MyVector<Node*> Pointers;
	Tile Field;
	int Prior = 1;
public:
	Node() : Field() { ; }
	Node(int x, int y, int pr = 1) : Field(x, y), Prior(pr) { ; }
	~Node() {
		Pointers.Clear();
	}
	int GetPrior() const { return Prior; }
	Node* GetPoint(int index) const
	{
		if ((index < 0) || (index >= Pointers.GetSize()))
		{
			throw std::out_of_range("Index should be more than 0 and less then size of vector");
			return nullptr;
		}
		return Pointers[index];
	}
	Tile GetTile() const { return Field; }
	void GetCoord(int& x1, int& y1) { Field.GetCoord(x1, y1); }
	ConstIter<Node*> cend() { return Pointers.cend(); }
	ConstIter<Node*> cbegin() { return Pointers.cbegin();}
	int Insert(ConstIter<Node*> it, Node* MyNode) { return Pointers.Insert(it, MyNode); }
	int GetSize() const { return Pointers.GetSize(); }
	void Clear() { Pointers.Clear(); }
	void ChangePrior() { Prior = (Prior % 2) + 1; }
};

#endif