#pragma once

#ifndef _TILE_H_
#define _TILE_H_
#define DEBUG 1

#include "Vect.h"

/*
@brief Типы клетки
*/
enum Types
{
	BASIN,		/**< Водоём */
	VALLEY,		/**< Равнина */
	MOUNTAIN,	/**< Гора */
	ROAD,		/**< Дорога */
	TOWER,		/**< Башня */
	WALL,		/**< Стена */
	CASTLE,		/**< Замок */
	LAIR,		/**< Логово */
	EMPTY		/**< Пустая клетка */
};

/** @brief Класс для хранения координат объекта */
class Tile
{
protected:
	int X = 0; //!< Координата по оси X
	int Y = 0; //!< Координата по оси Y
public:
/** @brief Пустой конструктор */
	Tile() { ; }
/** 
@brief Инициализирующий конструктор 
@param x0 Координата по оси X
@param y0 Координата по оси Y
@throw invalid_argument Если хотя бы один из параметров меньше нуля
*/
	Tile(int x0, int y0);
/** 
@brief Копирующий конструктор
@param NewTile Клетка, значения которой будут скопированы
*/
	Tile(const Tile& NewTile);
/** 
@brief Метод для смены координат
@param x1 Новое значение координаты по оси X
@param y1 Новое значение координаты по оси Y
*/
	void ChangeTile(int x1, int y1) { X = x1; Y = y1; }
/** 
@brief Метод для смены координат
@param Field Новое значение клетки
*/
	void ChangeTile(const Tile& Field) { X = Field.X; Y = Field.Y; }
/**
@brief Метод для получения координат
@param x1 Получение координаты по оси X
@param y1 Получение координаты по оси Y
*/
	void GetCoord(int& x1, int& y1) const { x1 = X; y1 = Y; }
/**
@brief Перегрузка оператора равенства
@param Dop Вторая клетка, с которой проводится сравнение
*/
	int operator == (const Tile& Dop) const { return ((Dop.X == X) && (Dop.Y == Y)); }
/**
@brief Перегрузка оператора неравенства
@param Dop Вторая клетка, с которой проводится сравнение
*/
	int operator != (const Tile& Dop) const { return ((Dop.X != X) || (Dop.Y != Y)); }
/**
@brief Перегрузка оператора вывода в консоль
@param dop Клетка, значения которой нужно вывести в консоль
@param out Поток, в который будут перенесены значения клетки
*/
	friend std::ostream& operator << (std::ostream& out, const Tile& dop);
};

/**
@brief Класс, использующийся как вершина графа с дополнительным параметром для построения разных путей в зависимости от типа врага
*/
class Node
{
private:
	MyVector<Node*> Pointers;	//!< Вектор указателей на другие узлы
	Tile Field;					//!< Клетка, соответствующая данному узлу
	int Prior = 1;				//!< Дополнительный параметр для построения пути
public:
/** @brief Пустой конструктор */
	Node() : Field() { ; }
/**
@brief Инициализирующий конструктор
@param x Значение координаты по оси X
@param y Значение координаты по оси Y
@param pr Значение доступности клетки для сухопутных монстров
*/
	Node(int x, int y, int pr = 1) : Field(x, y), Prior(pr) { ; }
/** @brief Деструктор */
	~Node() {
		Pointers.Clear();
	}
/**
@brief Метод для получения дополнительного параметра 
@return Значение параметра Prior
*/
	int GetPrior() const { return Prior; }
/**
@brief Метод для получения указателя на другую клетку
@param index Индекс указателя из вектора указателей на другие клетки
@throw out_of_range Если номер превышает значение размера вектора или если ниже нуля
@return Один из указателей на клетку
*/
	Node* GetPoint(int index) const
	{
		if ((index < 0) || (index >= Pointers.GetSize()))
		{
			throw std::out_of_range("Index should be more than 0 and less then size of vector");
			return nullptr;
		}
		return Pointers[index];
	}
/** @brief Метод для получения значения клетки */
	Tile GetTile() const { return Field; }
/** @brief Метод для получения значения координат клетки */
	void GetCoord(int& x1, int& y1) { Field.GetCoord(x1, y1); }
/** @brief Метод для получения итератора на конец вектора указателей */
	ConstIter<Node*> cend() { return Pointers.cend(); }
/** @brief Метод для получения итератора на начало вектора указателей */
	ConstIter<Node*> cbegin() { return Pointers.cbegin();}
/**
@brief Метод для вставки нового указателя на клетку
@param it Значение итератора, начиная с которого нужно вставить элемент
@param MyNode Новый указатель на клетку
*/
	int Insert(ConstIter<Node*> it, Node* MyNode) { return Pointers.Insert(it, MyNode); }
/** @brief Метод для получения размера вектора указателей*/
	int GetSize() const { return Pointers.GetSize(); }
/** @brief Метод для очистки вектора указателей на клетки*/
	void Clear() { Pointers.Clear(); }
/** @brief Метод для смены значения дополнительного параметра */
	void ChangePrior() { Prior = (Prior % 2) + 1; }
};

#endif