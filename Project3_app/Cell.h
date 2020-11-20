#pragma once

enum Condition
{
	EMPTY,
	FREE_NUMBER,
	BUSY_NUMBER
};

class Cell
{
public:
	Cell();
	void set_number(int num);
	void set_condition(Condition cond);
	unsigned int get_number() const;
	Condition get_condition() const;
private:
	unsigned int number;
	Condition condition;

};