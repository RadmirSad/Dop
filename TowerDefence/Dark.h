#pragma once

#ifndef _DARK_H_
#define _DARK_H_

#include "Map.h"
#include "Light.h"

class Lair
{
private:
	std::vector<Kid> Kids;
	std::vector<BigBoy> BigBoys;
	std::vector<Plane> Planes;
	std::vector<Teenager> Teenagers;
	std::vector<Billy> Billies;
	std::vector<BlackAdam> Adams;
	std::vector<Tile> WayForPlane;
	Node* WaysForOthers;
public:
	Lair();
};

class Alive
{
private:
	std::vector<Kid> Kids;
	std::vector<BigBoy> BigBoys;
	std::vector<Plane> Planes;
	std::vector<Teenager> Teenagers;
	std::vector<Billy> Billies;
	std::vector<BlackAdam> Adams;
public:
	Alive();
	template <class Type>
	int Revive(Type Monster);
	template <class Type>
	int Kill(Type Monster);
};

/*=========================== Enemies ===========================*/

class Enemy: public Destruct
{
protected:
	double DamPerSec = 0;
	int Speed = 0;
	double SpeedOfRegen = 0;
	int TimeOfExit = 0;
public:
	Enemy(): Destruct() { ; };
	Enemy(double MyDam, int Sp, double Reg, int Time, double NewHp, int x = 0, int y = 0); //: DamPerSec(MyDam), Speed(Sp), SpeedOfRegen(Reg), TimeOfExit(Time), Destruct(NewHp, x, y) { ; }
	double GetDam() const { return DamPerSec; }
	int GetSpeed() const { return Speed; }
	double GetReg() const { return SpeedOfRegen; }
	int GetTime() const { return TimeOfExit; }

	int DoDamage();
	int Regen();
	int Increase();
	int Reduce();
};

class Kid : public Enemy
{
public:
	Kid() : Enemy() { ; }
	Kid(int Lvl, int time, double Damage = 15, int Sp = 2, double Reg = 5, double NewHp = 50, int x = 0, int y = 0); //: Enemy(Damage, Sp, Reg, time, NewHp, x, y) { ; }
	int DoStep();
};

class BigBoy : public Enemy
{
public:
	BigBoy() { ; }
	BigBoy(int Lvl, int time, double Damage = 30, int Sp = 1, double Reg = 15, double NewHp = 100, int x = 0, int y = 0); // :Enemy(Damage, Sp, Reg, time, NewHp, x, y) { ; }
	int DoStep();
};

class Plane : public Enemy
{
public:
	Plane() { ; }
	Plane(int Lvl, int time, double Damage = 20, int Sp = 2, double Reg = 5, double NewHp = 70, int x = 0, int y = 0); //:Enemy(Damage, Sp, Reg, time, NewHp, x, y) { ; }
	int DoStep();
};

/*================================ Supervillains ==============================*/

enum Auras
{
	DAMAGE,
	SPEED,
	REGEN,
	HP
};

class Supervillain
{
protected:
	int RadOfAuras = 0;
	double AurasRatio[4]{};
	int ChangeRad(int NewRad);
	int ChangeAur(int Num, int NewAurRat);
public:
	Supervillain() { ; }
	Supervillain(int Rad, double DopDam = 1, double DopSp = 1, double DopReg = 1, double DopHp = 1);
	int GetRadius() const { return RadOfAuras; }
	int GetAuras(int* MyAur) const;
};

class Teenager: public Supervillain, public Kid
{
public:
	Teenager() : Supervillain(), Kid() { ; }
	Teenager(int Lvl, int time, int RadOfAur = 3, double DopDam = 1.2, double DopSp = 2, double DopReg = 1.1, double DopHp = 1.2,
		double Damage = 15, int Sp = 2, double Reg = 5, double NewHp = 50, int x = 0, int y = 0);
};

class Billy: public Supervillain, public BigBoy
{
public:
	Billy() : Supervillain(), BigBoy() { ; }
	Billy(int Lvl, int time, int RadOfAur = 5, double DopDam = 1.8, double DopSp = 1, double DopReg = 1.5, double DopHp = 1.4,
		double Damage = 30, int Sp = 1, double Reg = 15, double NewHp = 100, int x = 0, int y = 0);
};

class BlackAdam : public Supervillain, public Plane
{
public:
	BlackAdam() : Supervillain(), Plane() { ; }
	BlackAdam(int Lvl, int time, int RadOfAur = 5, double DopDam = 1.5, double DopSp = 1.5, double DopReg = 1.3, double DopHp = 1.3,
		double Damage = 20, int Sp = 2, double Reg = 5, double NewHp = 70, int x = 0, int y = 0);
};
#endif