#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include "Map.h"

/*=======================Destructible objects========================*/

class Destruct
{
private:
	int MaxHealth = 0;
	int Health = 0;
protected:
	Destruct() { ; };
	Destruct(int MHp);
	int GetHealth() const { return Health; }
	int GetMaxHealth() const { return MaxHealth; }
	int SetMaxHealth(const int MHp);
	int TakeDamage(const int Hp);
};

class Castle: public Destruct
{
private:
	int Revenue = 10;
	int CashBalance = 0;
	int Level = 1;
	int CostOfRepair = 100;
	int SpeedOfRepair = 5;
	int HpIncrease = 100;
public:
	Castle(const int x, const int y) : Destruct(200) { ; }
	void LevelUp();
};

class Wall : public Destruct
{
private:
	int Price = 50;
	int CostOfRepair = 30;
	int TimeOfRepair = 8;
public:
	Wall() : Destruct(50) { ; }
};



#endif