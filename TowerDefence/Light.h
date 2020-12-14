#pragma once

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Map.h"
#include "Dark.h"

/*=======================Destructible objects========================*/

class Destruct
{
protected:
	double MaxHealth = 0;
	double Health = 0;
	Tile Field;

	int SetMaxHealth(double MHp);
	int TakeDamage(double Hp);
public:
	Destruct() { ; }
	Destruct(double MHp, const Tile& NewTile);
	Destruct(double MHp, int x0, int y0);
	int GetHealth() const { return Health; }
	int GetMaxHealth() const { return MaxHealth; }
};

class Building: public Destruct
{
protected:
	int CostOfRepair = 0;
	double SpeedOfRepair = 0; // PerSec
	double HpIncrease = 0;
public:
	Building() { ; }
	Building(int Cost, double Speed, double Inc, double MHp, const Tile& NewField);
	Building(int Cost, double Speed, double Inc, double MHp, int x0, int y0);
	int GetCostRep() const { return CostOfRepair; }
	double GetSpdRep() const { return SpeedOfRepair; }
	double GetHpInc() const { return HpIncrease; }
	int Repair();
};

class Wall : public Building
{
private:
	int Price = 100;
public:
	Wall() { Building(50, 8, 50, 100, 0, 0); }
	Wall(int Lvl, int x, int y); //{ Building(50, 8, 50, 100, x, y); }
	Wall(int Lvl, const Tile& Field); //{ Building(50, 8, 50, 100, Field); }
	int GetPr() const { return Price; }
};

class Castle: public Building
{
private:
	int Revenue = 15;
	int CashBalance = 50;
	int CostOfUpg = 150;

	int ChangeRevenue(int NewRev);
public:
	Castle() { ; }
	Castle(int Lvl, int x = 0, int y = 0); //: Walls(0), Building(100, 5, 100, 250, x, y) { ; }
	int GetRev() const { return Revenue; }
	int Cash() const { return CashBalance; }
	int CostOfUp() const { return CostOfUpg; }
	void Upgrade();
	int BuildWall(int x, int y);
	int BuildTow(int x, int y, int Type);
};

/*======================== Towers ========================*/

class Tower
{
protected:
	int Lvl = 1;
	int Price;
	double DamPerSec;
	int Radius;
	Tile Field;
public:
	Tower() : Field() { ; }
	Tower(int NewPr, double NewDam, int NewRad, const Tile& MyField): Price(NewPr), DamPerSec(NewDam), Radius(NewRad), Field(MyField) { ; }
	Tower(int NewPr, double NewDam, int NewRad, int x, int y) : Price(NewPr), DamPerSec(NewDam), Radius(NewRad), Field(x, y) { ; }
	int GetLvl() const { return Lvl; }
	int GetPr() const { return Price; }
	double GetDam() const { return DamPerSec; }
	int GetRad() const { return Radius; }
};

class Standart : public Tower
{
public:
	Standart(int Lvl, const Tile& MyField, int NewPr = 25, double NewDam = 15, int NewRad = 4); //{ Tower(NewPr, NewDam, NewRad, MyField); };
	Standart(int Lvl, int x, int y, int NewPr = 25, double NewDam = 15, int NewRad = 4); //{ Tower(NewPr, NewDam, NewRad, x, y); }
	int ToDamage();
	int Upgrade();
};

class Cannon : public Tower
{
private:
	int DamRadius = 4;
	int Time = 5;
public:
	Cannon(int Lvl, const Tile& MyField, int NewPr = 25, double NewDam = 50, int NewRad = 5); //{ Tower(NewPr, NewDam, NewRad, MyField); }
	Cannon(int Lvl, int x, int y, int NewPr = 25, double NewDam = 50, int NewRad = 5); //{ Tower(NewPr, NewDam, NewRad, x, y); }
	int GetDamRad() const { return DamRadius; }
	int GetTime() const { return Time; }
	int ToDamage();
	int Upgrage();
};

class Magnet : public Tower
{
public:
	Magnet(int Lvl, const Tile& MyField, int NewPr = 25, double NewDam = 8, int NewRad = 4); //{ Tower(NewPr, NewDam, NewRad, MyField); }
	Magnet(int Lvl, int x, int y, int NewPr = 25, double NewDam = 7, int NewRad = 4); //{ Tower(NewPr, NewDam, NewRad, x, y); }
	int ToDamage();
	int Upgrade();
};


#endif