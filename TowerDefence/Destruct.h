#pragma once

#ifndef _DESTRUCT_H_
#define _DESTRUCT_H_

#include "Tile.h"

class Castle;

class Destruct
{
protected:
	double MaxHealth = 0;
	double Health = 0;
	Tile Field;

	int SetMaxHealth(double MHp);
public:
	Destruct() { ; }
	Destruct(double MHp, const Tile& NewTile);
	Destruct(double MHp, int x0, int y0);
	double GetHealth() const { return Health; }
	double GetMaxHealth() const { return MaxHealth; }
	void GetCoord(int& x1, int& y1) const { Field.GetCoord(x1, y1); }
	void ChangeTile(int x1, int y1) { Field.ChangeTile(x1, y1); }
	void ChangeTile(const Tile& NewField) { Field.ChangeTile(NewField); }
	Tile GetTile() const { return Field; }
	int TakeDamage(double Hp);
};

class Building : public Destruct
{
protected:
	int CostOfRepair = 0;
	double HpIncrease = 0;
public:
	Building() { ; }
	Building(int Cost, double Inc, double MHp, const Tile& NewField);
	Building(int Cost, double Inc, double MHp, int x0, int y0);
	int GetCostRep() const { return CostOfRepair; }
	double GetHpInc() const { return HpIncrease; }
	int Repair(Castle& MyCast);
};

#endif