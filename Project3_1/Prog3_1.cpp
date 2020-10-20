#include "BinVector.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	int sw = 0, &dop = sw, ent = 0;
	BinVector my_vect;
	std::cout << "Выберите способ инициализации вектора:" << std::endl
		<< "1. Двоичное число." << std::endl
		<< "2. Десятичное число" << std::endl;
	while (ent == 0)
	{
		Get_num(dop, 0);
		switch (sw)
		{
		case 1:
			std::cout << "Введите число:" << std::endl;
			my_vect.setVec(10);
			ent = 1;
			break;
		case 2:
			std::cout << "Введите число:" << std::endl;
			my_vect.setVec(2);
			ent = 1;
			break;
		default:
			std::cout << "Способа с таким номером не существует. Попробуйте снова:" << std::endl;
			break;
		}
	}
	ent = 0;
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
			SetVect(link);
			break;
		}
		case 7:
		{
			std::cout << "Введённый вектор : { ";
			int i, ind = my_vect.getSize();
			char* buf = my_vect.getVec();
			for (i = 0; i < ind; i++)
			{
				std::cout << buf[i];
				if (i + 1 != ind) std::cout << ", ";
			}
			std::cout << " }" << std::endl;
			break;
		}
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
