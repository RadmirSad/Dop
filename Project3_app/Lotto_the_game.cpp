#include "Lotto_card.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	int num_of_players = 0, flag = 1;
	Lotto_card* players = nullptr;
	std::cout << "������� ���������� ������� �� 2 �� 9:" << std::endl;
	while (flag)
	{
		flag = GetNum(num_of_players);
		if (flag) std::cout << "������� ������������ ��������. ���������� �����:" << std::endl;
		else
			if ((num_of_players > 9) || (num_of_players < 2))
			{
				std::cout << "��������� �������� ����� 2 � 9. ���������� �����:" << std::endl;
				flag = 1;
			}
	}
	players = new Lotto_card[num_of_players];
	TheGame(players, num_of_players);
	return 0;
}