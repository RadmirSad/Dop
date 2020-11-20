#include "Lotto_card.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	int num_of_players = 0, flag = 1;
	Lotto_card* players = nullptr;
	std::cout << "Введите количество игроков от 2 до 9:" << std::endl;
	while (flag)
	{
		flag = GetNum(num_of_players);
		if (flag) std::cout << "Введено некорректное значение. Попробуйте снова:" << std::endl;
		else
			if ((num_of_players > 9) || (num_of_players < 2))
			{
				std::cout << "Ожидалось значение между 2 и 9. Попробуйте снова:" << std::endl;
				flag = 1;
			}
	}
	players = new Lotto_card[num_of_players];
	TheGame(players, num_of_players);
	return 0;
}