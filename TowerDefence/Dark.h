#pragma once

#ifndef _DARK_H_
#define _DARK_H_

#include "Map.h"
#include "Light.h"

class Lair
{
private:
	MyVector<Enemy*> Enemies;
	Tile Field;
public:
	Lair();
	void GetCoord(int& x1, int& y1) const { Field.GetCoord(x1, y1); }
	void ChangeTile(int x1, int y1) { Field.ChangeTile(x1, y1); }
};

/*=========================== Enemies ===========================*/

class Enemy: public Destruct
{
protected:
	double DamPerSec = 0;
	int Speed = 0;
	double SpeedOfRegen = 0;
	int TimeOfExit = 0;
	Node* MyWay = nullptr;
public:
	Enemy(): Destruct() { ; };
	Enemy(double MyDam, int Sp, double Reg, int Time, double NewHp, int x = 0, int y = 0); //: DamPerSec(MyDam), Speed(Sp), SpeedOfRegen(Reg), TimeOfExit(Time), Destruct(NewHp, x, y) { ; }
	double GetDam() const { return DamPerSec; }
	int GetSpeed() const { return Speed; }
	double GetReg() const { return SpeedOfRegen; }
	int GetTime() const { return TimeOfExit; }

	int DoDamage();
	int ChangeTime(int NewTime);
	int Regen();
	int Increase();
	int Reduce();
	virtual int DoStep() = 0;
	virtual int GetType() = 0;
};

class Kid : public Enemy
{
public:
	Kid() : Enemy() { ; }
	Kid(int Lvl, int time, double Damage = 15, int Sp = 2, double Reg = 5, double NewHp = 50, int x = 0, int y = 0); //: Enemy(Damage, Sp, Reg, time, NewHp, x, y) { ; }
	int DoStep();
	int GetType() { return KID; }
};

class BigBoy : public Enemy
{
public:
	BigBoy() { ; }
	BigBoy(int Lvl, int time, double Damage = 30, int Sp = 1, double Reg = 15, double NewHp = 100, int x = 0, int y = 0); // :Enemy(Damage, Sp, Reg, time, NewHp, x, y) { ; }
	int DoStep();
	int GetType() { return BB; }
};

class Helicopter : public Enemy
{
public:
	Helicopter() { ; }
	Helicopter(int Lvl, int time, double Damage = 20, int Sp = 2, double Reg = 5, double NewHp = 70, int x = 0, int y = 0); //:Enemy(Damage, Sp, Reg, time, NewHp, x, y) { ; }
	int DoStep();
	int GetType() { return HELICOPTER; }
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
	int GetType() { return TEEN; }
};

class Billy: public Supervillain, public BigBoy
{
public:
	Billy() : Supervillain(), BigBoy() { ; }
	Billy(int Lvl, int time, int RadOfAur = 5, double DopDam = 1.8, double DopSp = 1, double DopReg = 1.5, double DopHp = 1.4,
		double Damage = 30, int Sp = 1, double Reg = 15, double NewHp = 100, int x = 0, int y = 0);
	int GetType() { return BILLY; }
};

class BlackAdam : public Supervillain, public Helicopter
{
public:
	BlackAdam() : Supervillain(), Helicopter() { ; }
	BlackAdam(int Lvl, int time, int RadOfAur = 5, double DopDam = 1.5, double DopSp = 1.5, double DopReg = 1.3, double DopHp = 1.3,
		double Damage = 20, int Sp = 2, double Reg = 5, double NewHp = 70, int x = 0, int y = 0);
	int GetType() { return ADAM; }
};
#endif