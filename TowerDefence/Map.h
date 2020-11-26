#pragma once

#ifndef _MAP_H_
#define _MAP_H_

#include <iostream>
#include <vector>

/*=============================== Map ===============================*/

enum Types
{
	ROAD,
	VALLEY,
	BASIN,
	MOUNTAIN,
	TOWER,
	WALL,
	CASTLE
};

enum TypesForUsability
{
	BAD,
	GOOD,
	DEAD,
	ALIVE
};

class Tile
{
private:
	int x = 0;
	int y = 0;
	int Type = VALLEY;
public:
	Tile() { ; }
	Tile(const int x0, const int y0) { x = x0; y = y0; }
	void ChangeTile(const int x1, const int y1) { x = x1; y = y1; }
	void GetCoord(int& x1, int& y1) const { x1 = x; y1 = y; }
	int GetType() const { return Type; }
	int ChangeType(const int NewType);
};

class Node
{
private:
	Node** Pointers = nullptr;
	int NumOfNodes = 0;
	Tile Field;
public:
	Node() : Field() { ; }
	int BuildWays();
};

template <class MyObj>
class GlobalObjects
{
private:
	int Level = 1;
	vector<MyObj> Objects;
public:
	GlobalObjects() : Objects() { ; }
	GlobalObjects(const int NumOfOb) : Objects(NumOfOb) { ; }
	int AddObj(const int Index);
	int DelObj(const int Index);
};

class Map
{
private:
	Tile** Fields = nullptr;
	int Dim = 10;
	GlobalObjects<Tile> WayForPlane;
	int GenerStartMap();
public:
	Map() { GenerStartMap(); }
	~Map() {
		for (int k = 0; k < Dim; k++)
			delete[] Fields[k];
		delete[] Fields;
	}
	void CheckMap();
	int GetDim() const { return Dim; };
	int GetCoordType(const Tile&) const;
	int GetCoordType(const int x, const int y) const;
};

#endif