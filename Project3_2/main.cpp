#include "BinVector2.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	int sw = 0, & dop = sw, ent = 0;
	std::cout << "Введите число в десятичной системе счисления:" << std::endl;
	Get_num(dop, 0);
	BinVector my_vect(dop);
	while (ent == 0)
	{
		std::cout << "Выберите дальнейшее действие:" << std::endl
			<< "1. Выполнение поразрядной логической операций: включающее ИЛИ двух векторов" << std::endl
			<< "2. Выполнение поразрядной логической операций: И двух векторов" << std::endl
			<< "3. Выполнение поразрядной логической операции исключающее ИЛИ" << std::endl
			<< "4. Получение “дополнения”" << std::endl
			<< "5. Получение вектора, ограниченного слева и справа единицами, исключающего левые и правые нули" << std::endl
			<< "6. Переинициализация вектора" << std::endl
			<< "7. Вывод вектора" << std::endl
			<< "8. Завершение работы программы." << std::endl;
		Get_num(dop, 0);
		switch (sw)
		{
		case 1:
			GetOR(my_vect);
			break;
		case 2:
			GetAND(my_vect);
			break;
		case 3:
			GetXOR(my_vect);
			break;
		case 4:
			GetDOP(my_vect);
			break;
		case 5:
			GetWN(my_vect);
			break;
		case 6:
		{
			BinVector& link = my_vect;
			link.setVector();
			break;
		}
		case 7:
			std::cout << "Введённый вектор : " << my_vect;
			break;
		case 8:
			std::cout << "Завершение работы." << std::endl;
			ent = 1;
			break;
		default:
			std::cout << "Функции с таким номером не существует. Попробуйте снова:" << std::endl;
			break;
		}
	}
	return 0;
}