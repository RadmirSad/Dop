#pragma once

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Destruct.h"


class Map;
class Building;
class Castle;
class Tower;
class Tile;
class Enemy;


/*=======================Destructible objects========================*/

/** @brief Класс объекта типа "Стена" */
class Wall : public Building
{
private:
	int Price = 100; //!< Цена постройки объекта
public:
	/** @brief Пустой конструктор */
	Wall(): Building(50, 50, 100, 0, 0) { ; }
/** 
@brief Инициализирующий конструктор по координатам
@param coef Коэффициент уровня объекта
@param x Значение координаты по оси X
@param y Значение координаты по оси Y
@throw invalid_argument Если коэффициент меньше 1
*/
	Wall(double coef, int x, int y): Building(50, 50 * coef, 100 * coef, x, y) 
	{ if (coef < 1) throw std::invalid_argument("Impossible value of level"); }
/**
@brief Инициализирующий конструктор по существующей клетке
@param coef Коэффициент уровня объекта
@param Field Значение клетки
*/
	Wall(double coef, const Tile& Field): Building(50, 50 * coef, 100 * coef, Field) { }
/**
@brief Метод для получения цены объекта
@return Цена постройки объекта
*/
	int GetPr() const { return Price; }
};

/** @brief Класс объекта типа "Замок" */
class Castle: public Building
{
private:
	int Revenue = 15;		//!< Доход замка в секунду
	double CashBalance = 50;//!< Баланс замка
	int CostOfUpg = 150;	//!< Цена улучшения замка

/**
@brief Метод для изменения дохода замка
@param NewRev Новое значение дохода
@throw invalid_argument Если значение дохода равно нулю или ниже нуля
@return Целочисленное значение, обозначающее успешную или безуспешную работу метода
*/
	int ChangeRevenue(int NewRev);
public:
/** @brief Пустой конструктор*/
	Castle(): Building(100, 100, 250, 0, 0) { ; }
/**
@brief Инициализирующий конструктор по координатам
@param coef Коэффициент уровня объекта
@param x Значение координаты по оси X
@param y Значение координаты по оси Y
@throw invalid_argument Если коэффициент меньше 1
*/
	Castle(double coef, int x = 0, int y = 0);
/**
@brief Метод для получения значения дохода
@return Значение дохода замка в секунду
*/
	int GetRev() const { return Revenue; }
/**
@brief Метод для получения баланса
@return Значение баланса замка
*/
	double Cash() const { return CashBalance; }
/**
@brief Метод для получения цены улучшения
@return Значение цены улучшения замка
*/
	int CostOfUp() const { return CostOfUpg; }
/**
@brief Метод улучшения замка
@detailed Данный метод увеличивает цену улучшения на 100 * coef, доход на 15 * coef, 
цену ремонта на 75 * coef, максимальное здоровье на 60 * coef
@param coef Коэффициент уровня объекта
@throw invalid_argument Если коэффициент меньше 1
@return Целочисленное значение, обозначающее успешную или безуспешную работу метода
*/
	int Upgrade(double coef);
/**
@brief Метод для вычета денег из баланса
@param Cost Значение, которое нужно вычесть
@throw invalid_argument Если вычитаемое значение меньше или равно 0
@return Целочисленное значение, обозначающее успешную или безуспешную работу метода
*/
	int BuySmth(double Cost);
/**
@brief Метод для умножения всех параметров на коэффициент
@param coef Коэффициент уровня объекта
@throw invalid_argument Если коэффициент меньше 1
*/
	void Multiply(double coef);
/** @brief Метод для возврата всех параметров в базовое состояние */
	void SetBasicParams();
/** @brief Метод для получения дохода */
	void TakeMoney() { CashBalance += Revenue; }

	friend class Map;
};

/*======================== Towers ========================*/

/** @brief Класс объекта типа "Башня"*/
class Tower
{
protected:
	double CostOfUp = 20;		//!< Цена улучшения
	int Price = 25;				//!< Цена постройки
	double DamPerSec = 15;		//!< Урон башни в секунду
	int Radius = 4;				//!< Радиус поражения
	Tile Field;					//!< Клетка башни
	Enemy* Tracker = nullptr;	//!< Отслеживаемый враг
public:
/** @brief Пустой конструктор */
	Tower() : Field() { ; }
/**
@brief Инициализирующий конструктор по существующей клетке
@param coef Коэффициент уровня объекта
@param NewPr Значение цены постройки
@param NewDam Значение урона
@param NewRad Значение радиуса
@param CUp Значение цены улучшения
@param MyField Клетка объекта
@throw invalid_argument Если коэффициент меньше 1
@throw invalid_argument Если один из параметров меньше или равен нулю
*/
	Tower(double coef, const Tile& MyField, int NewPr = 25, double NewDam = 15, int NewRad = 4, double CUp = 20);
/**
@brief Инициализирующий конструктор по координатам
@param coef Коэффициент уровня объекта
@param NewPr Значение цены постройки
@param NewDam Значение урона
@param NewRad Значение радиуса
@param CUp Значение цены улучшения
@param x Значение координаты по оси X
@param y Значение координаты по оси Y
@throw invalid_argument Если коэффициент меньше 1
@throw invalid_argument Если один из параметров меньше или равен нулю
*/
	Tower(double coef, int x, int y, double NewDam = 15, int NewRad = 4, int NewPr = 25, double CUp = 20);
/**
@brief Метод для получения цены улучшения
@return Цена улучшения башни
*/
	double GetCostOfUp() const { return CostOfUp; }
/**
@brief Метод для получения цены постройки
@return Цена постройки башни
*/
	int GetPr() const { return Price; }
/** 
@brief Метод для получения значения урона башни
@return Значение получаемого башней урона
*/
	double GetDam() const { return DamPerSec; }
/**
@brief Метод для получения радиуса поражения
@return Значение радиуса поражения башни
*/
	int GetRad() const { return Radius; }
/**
@brief Метод для получения координат башни
@param x1 Значение координаты по оси X
@param y1 Значение координаты по оси Y
*/
	void GetCoord(int& x1, int& y1) const { Field.GetCoord(x1, y1); }
/**
@brief Метод для получения клетки башни
@return Клетка башни
*/
	Tile GetTile() const { return Field; }
/**
@brief Метод для изменения координат башни
@param x1 Новое значение координаты по оси X
@param y1 Новое значение координаты по оси Y
*/
	void ChangeTile(int x1, int y1) { Field.ChangeTile(x1, y1); }
/**
@brief Метод для изменения клетки башни
@param NewField Новое значение клетки
*/
	void ChangeTile(const Tile& NewField) { Field.ChangeTile(NewField); }

	friend class Map;
/**
@brief Метод для нанесения урона по наблюдаемому врагу
Данная функция наносит урон по врагу, за которым башня ведёт наблюдение. 
Если наблюдаемый враг отсутствует, то башня ищет врага, попадающего в радиус поражения, среди существующих врагов.
Если враг уничтожен, то вызывается соответствующая функция класса типа "Карта".
@param MyMap Изменяемый объект типа "Карта"
@return Целочисленное значение кода операции
*/
	int ToDamage(Map& MyMap);
/**
@brief Метод для улучшения башни
@param MyMap Изменяемый объект типа "Карта"
@return Целочисленное значение кода операции
*/
	int Upgrade(Map& MyMap);
/**
@brief Метод, с помощью которого можно найти врага, находящегося в радиусе поражения
@param MyMap Изменяемый объект типа "Карта"
@return Указатель на врага, за которым можно вести наблюдение
*/
	Enemy* FindEnemy(const Map& MyMap);
};

#endif