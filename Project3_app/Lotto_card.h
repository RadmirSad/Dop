#pragma once
#include "Cell.h"
#include <vector>
#include <ostream>
#include <iostream>


#include "windows.h"
#include <sstream>

class Lotto_card
{
public:
	Lotto_card();
	Lotto_card(int height);
	Lotto_card(const Lotto_card& obj);
	Lotto_card(Lotto_card&& obj);
	~Lotto_card();

	unsigned int get_width() const;
	unsigned int get_height() const;

	void card_output(std::ostream& out) const; //пока что красивый вывод только при height < 10
	int put_keg(unsigned int keg);
	unsigned int how_many_busy() const;
	Condition is_cell_busy(int i, int j) const;
	void check_for_busy_lines();
	void get_remained_numbers(std::vector<int>* array) const;

	Lotto_card& operator= (const Lotto_card& obj);
	Lotto_card& operator-- (int);
	Condition operator() (int i, int j) const;
	void operator() (int keg);
	friend std::ostream& operator<< (std::ostream& out, const Lotto_card& lotto);
	friend std::istream& operator>> (std::istream& in, Lotto_card& lotto);

private:
	unsigned int height;
	static const int width = 9;
	Cell** cells;

	void generate_numbers();
	bool check_unique_nums(int num, const int* arr, int size) const;
	unsigned int generate_rand_num(int h_i, int w_j, int* uq_nums_arr, int& it_nums);
	void delete_busy_line(int height_i);
};

int GetNum(int& a);
void TheGame(Lotto_card*& players, int num_of_players);
void CheckCells(Lotto_card& player, int my_num, int& num_of_err);