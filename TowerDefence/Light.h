#pragma once

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Destruct.h"

class Building;
class Wall;
class Castle;
class Tower;
class Tile;
class Enemy;

/*=======================Destructible objects========================*/

class Wall : public Building
{
private:
	int Price = 100;
	int TypeOfCell = EMPTY;
public:
	Wall() { Building(50, 50, 100, 0, 0); }
	Wall(double coef, int x, int y): Building(50, 50 * coef, 100 * coef, x, y) { }
	Wall(double coef, const Tile& Field): Building(50, 50 * coef, 100 * coef, Field) { }
	int GetPr() const { return Price; }
};

class Castle: public Building
{
private:
	int Revenue = 15;
	double CashBalance = 50;
	int CostOfUpg = 150;

	int ChangeRevenue(int NewRev);
public:
	Castle(): Building(100, 100, 250, 0, 0) { ; }
	Castle(double coef, int x = 0, int y = 0);
	int GetRev() const { return Revenue; }
	double Cash() const { return CashBalance; }
	int CostOfUp() const { return CostOfUpg; }
	void Upgrade(double coef);
	int BuySmth(double Cost);
	void Multiply(double coef);
	friend class Map;
};

/*======================== Towers ========================*/

class Tower
{
protected:
	double CostOfUp = 20;
	int Price = 25;
	double DamPerSec = 15;
	int Radius = 4;
	Tile Field;
	Enemy* Tracker = nullptr;
public:
	Tower() : Field() { ; }
	Tower(double coef, int NewPr, double NewDam, int NewRad, const Tile& MyField, double CUp = 20): Price((int)(NewPr* coef)),
		DamPerSec(NewDam), Radius(NewRad), Field(MyField), CostOfUp(coef * CUp) { ; }
	Tower(double coef, int x, int y, double NewDam = 15, int NewRad = 4, int NewPr = 25, double CUp = 20) : Price((int)(NewPr * coef)),
		DamPerSec(NewDam), Radius(NewRad), Field(x, y), CostOfUp(coef* CUp) { ; }
	double GetCostOfUp() const { return CostOfUp; }
	int GetPr() const { return Price; }
	double GetDam() const { return DamPerSec; }
	int GetRad() const { return Radius; }
	void GetCoord(int& x1, int& y1) const { Field.GetCoord(x1, y1); }
	void ChangeTile(int x1, int y1) { Field.ChangeTile(x1, y1); }
	void ChangeTile(const Tile& NewField) { Field.ChangeTile(NewField); }

	int ToDamage(Map& MyMap);
	int Upgrade(Map& MyMap);
	Enemy* FindEnemy(const Map& MyMap);
};

#endif