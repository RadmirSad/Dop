#pragma once

#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include "Vect.h"
#include "Light.h"
#include "Dark.h"

/*=============================== Map ===============================*/

enum Types
{
	ROAD,
	VALLEY,
	BASIN,
	MOUNTAIN,
	TOWER,
	WALL,
	CASTLE,
	LAIR
};

enum TUsability
{
	BAD,
	GOOD,
	DEAD,
	ALIVE
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
	void ChangeTile(const int x1, const int y1) { X = x1; Y = y1; }
	void GetCoord(int& x1, int& y1) const { x1 = X; y1 = Y; }
};

class Node
{
private:
	Node** Pointers = nullptr;
	int NumOfNodes = 0;
	Tile Field;
	int Prior = 1;
public:
	Node() : Field() { ; }
	int BuildWays();
};

/*template <class MyObj>
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
};*/

class Map
{
private:
	int** Fields = nullptr;
	int Dim = 10;
	int Level = 1;
	Castle MyCast;
	std::vector<Lair> Lairs;
	std::vector<Enemy> Monsters;
	std::vector<Wall> Walls;
	std::vector<Tower> Towers;

	int GenerStartMap();
	int ChangeType(int NewType, int x, int y);
	int ChangeRoad();
	int Revive();
	int Kill();
	int DownloadMap();
	int SaveMap();
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
	int GetCoordType(int x, int y) const { return Fields[x][y]; }

	int CreateMap();
	template <class Object>
	int BuildObj(const Object& NewObj);

	friend std::ostream& operator << (std::ostream& out, Map& MyMap);
};

#endif