#pragma once

#ifndef _DESTRUCT_H_
#define _DESTRUCT_H_

#include "Tile.h"

class Castle;

/** @brief Класс уничтожаемых объектов*/
class Destruct
{
protected:
	double MaxHealth = 0; //!< Максимальное здоровье объекта
	double Health = 0;	  //!< Здоровье объекта
	Tile Field;			  //!< Клетка объекта

/**
@brief Метод для изменения значения максимального здоровья
@param MHp Новое значение максимального здоровья
@return Целочисленное значение, обозначающее успешную или безуспешную работу метода
*/
	int SetMaxHealth(double MHp);
public:
/** @brief Пустой конструктор */
	Destruct() { ; }
/**
@brief Инициализирующий конструктор по существующей клетке
@param MHp Значение максимального здоровья
@param NewTile Клетка, на которой будет находится объект
@throw invalid_argument Если значение здоровья равно нулю или ниже нуля
*/
	Destruct(double MHp, const Tile& NewTile);
/**
@brief Инициализирующий конструктор по координатам
@param MHp Значение максимального здоровья
@param x0 Значение координаты по оси X
@param y0 Значение координаты по оси Y
@throw invalid_argument Если Если значение здоровья равно нулю или ниже нуля
*/
	Destruct(double MHp, int x0, int y0);
/**
@brief Метод для получения значения здоровья объекта
@return Здоровье объекта
*/
	double GetHealth() const { return Health; }
/**
@brief Метод для получения значения максимального здоровья объекта
@return Максимальное здоровье объекта
*/
	double GetMaxHealth() const { return MaxHealth; }
/**
@brief Метод для получения значения координат клетки
@param x1 Значение координаты по оси X
@param y1 Значение координаты по оси Y
*/
	void GetCoord(int& x1, int& y1) const { Field.GetCoord(x1, y1); }
/**
@brief Метод для изменения координат клетки
@param x1 Значение координаты по оси X
@param y1 Значение координаты по оси Y
*/
	void ChangeTile(int x1, int y1) { Field.ChangeTile(x1, y1); }
/**
@brief Метод для изменения клетки объекта
@param NewField Новая клетка объекта
*/
	void ChangeTile(const Tile& NewField) { Field.ChangeTile(NewField); }
/** 
@brief Метод для получения клетки объекта
@return Текущая клетка объекта
*/
	Tile GetTile() const { return Field; }
/**
@brief Метод для нанесения урона объекту
@param Значение урона
@throw invalid_argument Если значение урона равно нулю или меньше нуля
@return Целочисленное значение, обозначающее успешную или безуспешную работу метода
*/
	int TakeDamage(double Hp);
};

/** @brief Класс объектов, которые можно ремонтировать*/
class Building : public Destruct
{
protected:
	int CostOfRepair = 0; //!< Цена ремонта объекта
	double HpIncrease = 0;//!< Значение, на которое увеличится здоровье объекта
public:
/** @brief Пустой конструктор */
	Building(): Destruct() { ; }
/**
@brief Инициализирующий конструктор по существующей клетке
@param Cost Значение цены ремонта объекта
@param Inc Значение увеличения здоровья после ремонта
@param MHp Значение максимального здоровья объекта
@param NewField Клетка объекта
*/
	Building(int Cost, double Inc, double MHp, const Tile& NewField);
/**
@brief Инициализирующий конструктор по координатам
@param Cost Значение цены ремонта объекта
@param Inc Значение увеличения здоровья после ремонта
@param MHp Значение максимального здоровья объекта
@param x0 Значение координаты по оси X
@param y0 Значение координаты по оси Y
*/
	Building(int Cost, double Inc, double MHp, int x0, int y0);
/**
@brief Метод для получения цены ремонта
@return Значение цены ремонта объекта
*/
	int GetCostRep() const { return CostOfRepair; }
/**
@brief Метод для получения значения повышения здоровья
@return Значение увеличения здоровья после ремонта
*/
	double GetHpInc() const { return HpIncrease; }
/**
@brief Метод для ремонта объекта
@param MyCast Замок для вычета денег из баланса равному значению цены ремонта объекта
@return Целочисленное значение, обозначающее успешную или безуспешную работу метода
*/
	int Repair(Castle& MyCast);
};

#endif