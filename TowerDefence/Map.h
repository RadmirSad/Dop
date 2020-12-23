#pragma once

#ifndef _MAP_H_
#define _MAP_H_

#include "Vect.h"
#include "Light.h"
#include "Dark.h"
#include <sstream>
#include <fstream>

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
	LAIR,
	EMPTY
};

enum EnTypes
{
	KID,
	BB,
	HELICOPTER,
	TEEN,
	BILLY,
	ADAM
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
};

class Map
{
private:
	int** Fields = nullptr;
	int Dim = 10;
	int Level = 1;
	Castle MyCast;
	MyVector<Lair> Lairs;
	MyVector<Enemy*> Monsters;
	MyVector<Wall> Walls;
	MyVector<Tower> Towers;
	MyVector<Node*> Ways;

	int GenerStartMap();

	void InstallLevel();
	int ChangeLevel(int NewLvl);
	int IsLevelsExist();
	int ChangeType(int NewType, int x, int y);
	int ChangeCellType();
	int CheckEmpty();
	int CheckCast();
	int IsRoadExist();
	void AddEnemy();

	int ChangeRoad();
	int Revive();
	template <class Type>
	int Kill(const Iter<Type>& Object);
	int DownloadMap();
	int SaveMap();
	int BuildWays();
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




template <class number>
int Get_info(number& a)
{
	int flag = 0;
	std::string dop;
	getline(std::cin, dop);
	if (dop.length() == 0) return 0;
	for (int i = 0; i < dop.length(); i++)
		if ((dop[i] < '0') || (dop[i] > '9')) flag = 1;
	if (flag) return 0;
	std::stringstream ss;
	ss << dop;
	ss >> a;
	return 1;
}

template <class number>
void Get_num(number& num)
{
	int flag = 0;
	while (!flag)
		if (Get_info(num) > 0) flag = 1;
		else std::cout << "Incorrect symbols. Try again:" << std::endl;
}

#endif