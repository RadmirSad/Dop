#pragma once

#ifndef _MAP_H_
#define _MAP_H_

#include "Dark.h"
#include <sstream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>

int GetDist(const Tile& fir, const Tile& sec);
int IsLevelsExist(int NewLevel);
int ThisLevelExist(int Lvl);
void StartGame(Map& MyMap);
int DownloadDial(Map& MyMap);
int CheckCellsForRand(const Map& MyMap);
int OnlyGame(Map& MyMap);

/*=============================== Map ===============================*/

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
	MyVector<Node> Ways;

	int InstallLevel(int flag = 0);
	int ChangeLevel(int NewLvl);
	int ChangeType(int NewType, int x, int y);
	int ChangeCellType();
	int CheckEmptyCells() const;
	int CheckEmptyLairs() const;
	int IsRoadExist() const;
	void AddPoint(int x, int y);
	void AddEnemy(int base_type = -1, int base_time = -1, int num_of_lair = -1);
	void CleanMap();
	void CleanAll();
	void AddEdges(int xsec, int ysec);
	int Dijkstra(const Tile& start, const Tile& end, MyVector<Tile>& way) const;

//	int ChangeRoad();
	int Revive(int IndOfLair, int IndOfEnemy);
	int KillMonst(int IndOfEnemy);
	int BreakWall(int IndOfWall);
	int DownloadMap(int lvl);
	int SaveMap();
	void RandGenerate();
	void FullValley();
//	int BuildWays();
	int CheckMonst(int x0, int y0);
	int CheckPointers(Node* MyNode, int index) const;

public:
	Map() { ; }
	~Map();
	void PrintMap(int flag_for_create = 1);
	int GetDim() const { return Dim; };
	int GetCoordType(const Tile&) const;
	int GetCoordType(int x, int y) const { return Fields[x][y]; }

	int DialogMap();
	int TDamCast(double Dam) { return MyCast.TakeDamage(Dam); }
	int WDamCast(double Dam, int index) { return Walls[index].TakeDamage(Dam); }
	int BuildWall(int x0, int y0);
	int BuildTow(int x0, int y0);
	double GetCoef() const { return (double)(Level + 9) / 10; }
	friend class BigBoy;
	friend class Enemy;
	friend class Tower;
	friend void StartGame(Map& MyMap);
	friend int DownloadDial(Map& MyMap);
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