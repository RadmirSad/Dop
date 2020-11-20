#include "Lotto_card.h"
#include <cstdlib> 
#include <ctime>
#include <cmath>
#include <vector>

Lotto_card::Lotto_card()
{
	height = 3;
	cells = new (std::nothrow) Cell * [height];

	if (cells == nullptr) throw "bad_alloc";

	int good_alloc = 0;
	for (int i = 0; i < height; i++)
	{
		cells[i] = new (std::nothrow) Cell[width];

		if (cells[i] == nullptr)
		{
			for (int j = 0; j < good_alloc; j++)
			{
				delete[] cells[j];
			}
			delete[] cells;
			throw "bad_alloc";
		} else good_alloc++;
		
	}

	generate_numbers();
}

Lotto_card::Lotto_card(int height)
{
	height = abs(height);
	this->height = height;

	cells = new (std::nothrow) Cell * [height];
	if (cells == nullptr) throw "bad_alloc";
	
	int good_alloc = 0;
	for (int i = 0; i < height; i++)
	{
		cells[i] = new (std::nothrow) Cell[width];

		if (cells[i] == nullptr)
		{
			for (int j = 0; j < good_alloc; j++)
			{
				delete[] cells[j];
			}
			delete[] cells;
			throw "bad_alloc";
		}
		else good_alloc++;
	}

	generate_numbers();
}

Lotto_card::Lotto_card(const Lotto_card& obj)
{
	this->height = obj.height;
	cells = new (std::nothrow) Cell * [height];
	if (cells == nullptr) throw "bad_alloc";

	int good_alloc = 0;
	for (int i = 0; i < height; i++)
	{
		cells[i] = new (std::nothrow) Cell[width];

		if (cells[i] == nullptr)
		{
			for (int j = 0; j < good_alloc; j++)
			{
				delete[] cells[j];
			}
			delete[] cells;
			throw "bad_alloc";
		}
		else good_alloc++;
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			this->cells[i][j].set_condition(obj.cells[i][j].get_condition());
			this->cells[i][j].set_number(obj.cells[i][j].get_number());
		}
	}

}

Lotto_card::Lotto_card(Lotto_card&& obj)
{
	this->height = obj.height;
	this->cells = obj.cells;

	obj.cells = nullptr;
	obj.height = 0;
}

Lotto_card::~Lotto_card()
{
	for (int i = 0; i < height; i++)
	{
		delete[] cells[i];
	}
	delete[] cells;
}

void Lotto_card::generate_numbers()
{
	srand(time(NULL));
	Sleep(1000);

	int w_nums = 5; //необходимое количество чисел для генерации на одну строку	
	int unique_nums = this->height * w_nums; //количество уникальных чисел
	int* uq_nums_arr = new int[unique_nums]; //массив уникальных чисел
	int it_nums = 0; //итератор для массива уникальных чисел

	for (int h_i = 0; h_i < this->height; h_i++)
	{
		w_nums = 5;
		for (int w_j = 0; w_j < this->width; w_j++)
		{
			if (w_nums < this->width - w_j)
			{
				if (rand() % 10 >= 5)
				{
					cells[h_i][w_j].set_number(generate_rand_num(h_i, w_j, uq_nums_arr, it_nums));
					cells[h_i][w_j].set_condition(FREE_NUMBER);

					--w_nums;
				}
			}
			else
			{
				cells[h_i][w_j].set_number(generate_rand_num(h_i, w_j, uq_nums_arr, it_nums));
				cells[h_i][w_j].set_condition(FREE_NUMBER);

				--w_nums;
			}

			if (w_nums <= 0) break;
		}
	}

	delete[] uq_nums_arr;
}

unsigned int Lotto_card::get_width() const
{
	return this->width;
}

unsigned int Lotto_card::get_height() const
{
	return this->height;
}

void Lotto_card::card_output(std::ostream& out) const
{
	if (this->height == 0)
	{
		out << "This card is empty!" << std::endl;
		return;
	}


	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (this->cells[i][j].get_condition() == FREE_NUMBER)
			{
				if (j == 0)
				{
					out << "[ " << this->cells[i][j].get_number() << "] ";
				}
				else out << "[" << this->cells[i][j].get_number() << "] ";

			}
			else if (this->cells[i][j].get_condition() == BUSY_NUMBER)
			{
				if (j == 0)
				{
					out << "< " << this->cells[i][j].get_number() << "> ";
				}
				else out << "<" << this->cells[i][j].get_number() << "> ";

			}
			else out << "[  ] ";
		}
		out << std::endl;
	}
	return;
}

int Lotto_card::put_keg(unsigned int keg)
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if ((cells[i][j].get_condition() == FREE_NUMBER) && (cells[i][j].get_number() == keg))
			{
				cells[i][j].set_condition(BUSY_NUMBER);
				return 1;
			}
			else if ((cells[i][j].get_condition() == BUSY_NUMBER) && (cells[i][j].get_number() == keg))
			{
				//throw "This number already busy!";
				return 2;
			}
		}
	}
	//throw "There is no such number!";
	return 0;
}

unsigned int Lotto_card::how_many_busy() const
{
	int many = 0;

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (cells[i][j].get_condition() == BUSY_NUMBER)
			{
				many++;
			}
		}
	}

	return many;
}

Condition Lotto_card::is_cell_busy(int i, int j) const
{
	return cells[i][j].get_condition();
}

void Lotto_card::check_for_busy_lines()
{
	bool busy;

	for (int i = 0; i < this->height; i++)
	{
		busy = true;
		for (int j = 0; j < this->width; j++)
		{
			if (cells[i][j].get_condition() == FREE_NUMBER)
			{
				busy = false;
				break;
			}
		}

		if (busy) delete_busy_line(i);
	}
}

void Lotto_card::get_remained_numbers(std::vector<int>* array) const
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (cells[i][j].get_condition() == FREE_NUMBER)
			{
				array->push_back(cells[i][j].get_number());
			}
		}
	}
}

Lotto_card& Lotto_card::operator=(const Lotto_card& obj)
{
	if (this == &obj) return *this; //сам себя себе присвоил

	Cell** t_cells = new (std::nothrow) Cell * [obj.height];
	if (t_cells == nullptr) throw "bad_alloc";

	int good_alloc = 0;
	for (int i = 0; i < obj.height; i++)
	{
		t_cells[i] = new (std::nothrow) Cell[this->width];

		if (t_cells[i] == nullptr)
		{
			for (int j = 0; j < good_alloc; j++)
			{
				delete[] t_cells[j];
			}
			delete[] t_cells;
			throw "bad_alloc";
		}
		else good_alloc++;
	}

	for (int i = 0; i < obj.height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			t_cells[i][j].set_condition(obj.cells[i][j].get_condition());
			t_cells[i][j].set_number(obj.cells[i][j].get_number());
		}
	}

	for (int i = 0; i < this->height; i++)
	{
		delete[] cells[i];
	}
	delete[] cells;

	this->height = obj.height;
	this->cells = t_cells;

	return *this;
}

Lotto_card& Lotto_card::operator--(int)
{
	Lotto_card temp_lotto(*this);
	this->check_for_busy_lines();
	return temp_lotto;
}

Condition Lotto_card::operator()(int i, int j) const
{
	return this->is_cell_busy(i, j);
}

void Lotto_card::operator()(int keg)
{
	this->put_keg(keg);
}

std::ostream& operator<< (std::ostream& out, const Lotto_card& lotto)
{
	lotto.card_output(out);
	return out;
}

std::istream& operator>> (std::istream& in, Lotto_card& lotto)
{
	int keg_num;
	in >> keg_num;

	if (in.good())
	{
		lotto.put_keg(keg_num);
	}
	else
	{
		in.clear();
		in.ignore(in.rdbuf()->in_avail());
	}


	return in;
}

void Lotto_card::delete_busy_line(int height_i)
{
	Cell** t_cells = new Cell * [this->height - 1];
	int t_i = 0;

	for (int i = 0; i < this->height; i++)
	{
		if (i != height_i)
		{
			t_cells[t_i] = cells[i];
			t_i++;
		}
	}

	delete[] cells;

	cells = t_cells;
	this->height--;
}

unsigned int Lotto_card::generate_rand_num(int h_i, int w_j, int* uq_nums_arr, int& it_nums)
{
	int rand_num;
	int power = 10;

	while (height >= power) power *= 10; //диапазон чисел для одной ячейки лото

	do
	{
		rand_num = rand() % power + power * w_j;

	} while (!check_unique_nums(rand_num, uq_nums_arr, it_nums));

	uq_nums_arr[it_nums] = rand_num;
	it_nums++;

	return rand_num;
}

bool Lotto_card::check_unique_nums(int num, const int* arr, int size) const
{
	if (size == 0) return true;

	for (int i = 0; i < size; i++)
	{
		if (arr[i] == num)
		{
			return false;
		}
	}

	return true;
}

// Dop func

int GetNum(int& a)
{
	std::string dop;
	getline(std::cin, dop);
	if (dop.length() == 0) return 1;
	for (int i = 0; i < dop.length(); i++)
		if ((dop[i] < 48) || (dop[i] > 57)) return 1;
	std::stringstream buf;
	buf << dop;
	buf >> a;
	return 0;
}

void TheGame(Lotto_card*& players, int num_of_players)
{
	int flag_for_win = 0, rnum = 0, ent = 0, flag_for_ent = 0, * num_of_err = new int [num_of_players] {};
	srand(time(0));
	std::string* names = new std::string[num_of_players];
	while(rnum < num_of_players)
	{
		std::cout << "Введите имя " << rnum + 1 << "-го игрока: " << std::endl;
		getline(std::cin, names[rnum]);
		if (names[rnum].length() == 0) std::cout << "Введено некорректное значение." << std::endl;
		else
			rnum++;
	}
	while (!flag_for_win)
	{
		rnum = rand() % 90 + 1;
		std::cout << "Выпало число " << rnum << std::endl;
		for (int num = 0; num < num_of_players; num++)
		{
			flag_for_ent = 0;
			if (num_of_err[num] < 3)
			{
				std::cout << "Ход игрока " << num + 1 << ") " << names[num] << std::endl << "Карта игрока:" << std::endl << players[num] << std::endl
					<< "Имеется ли у вас это число? Помните, что за 3 неверных ответа вы будете наказаны." << std::endl << "1. Да" << std::endl << "2. Нет" << std::endl;
				while (!flag_for_ent)
				{
					int flag = 1;
					while (flag)
					{
						flag = GetNum(ent);
						if (flag) std::cout << "Введено некорректное значение. Попробуйте снова:" << std::endl;
					}
					switch (ent)
					{
					case 1:
					{
						CheckCells(players[num], rnum, num_of_err[num]);
						std::vector<int> arr; 
						players[num].get_remained_numbers(&arr);
						if (arr.size() == 0) flag_for_win = num + 1;
						flag_for_ent = 1;
						break;
					}
					case 2:
						flag_for_ent = 1;
						break;
					default:
						std::cout << "Варианта ответа с таким номером не существует. Выберите корректное значение:" << std::endl;
						break;
					}
				}
			}
			else 
			{
				std::cout << "Ход игрока " << num + 1 << ") " << names[num] << " будет пропущен" << std::endl;
				num_of_err[num] = 0;
			}
		}
	}
	std::cout << "Победил игрок " << flag_for_win << ") " << names[flag_for_win - 1] << "!!!" << std::endl;
}

void CheckCells(Lotto_card& player, int my_num, int& num_of_err)
{
	int err = player.put_keg(my_num);
	switch (err)
	{
	case 0:
		num_of_err++;
		std::cout << "Такого числа в вашем билете нет. Через " << 3 - num_of_err << " ошибок у вас будет пропуск хода." << std::endl;
		break;
	case 1:
		std::cout << "Бочонок с числом " << my_num << " успешно поставлен." << std::endl;
		break;
	case 2:
		std::cout << "Бочонок с таким числом уже был установлен." << std::endl;
		break;
	}
}