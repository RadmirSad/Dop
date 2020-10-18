#include "BinVector.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	int sw = 0, &dop = sw, ent = 0;
	BinVector my_vect;
	std::cout << "�������� ������ ������������� �������:" << std::endl
		<< "1. �������� �����." << std::endl
		<< "2. ���������� �����" << std::endl;
	while (ent == 0)
	{
		Get_num(dop, 0);
		switch (sw)
		{
		case 1:
			std::cout << "������� �����:" << std::endl;
			my_vect.setVec(10);
			ent = 1;
			break;
		case 2:
			std::cout << "������� �����:" << std::endl;
			my_vect.setVec(2);
			ent = 1;
			break;
		default:
			std::cout << "������� � ����� ������� �� ����������. ���������� �����:" << std::endl;
			break;
		}
	}
	ent = 0;
	while (ent == 0)
	{
		std::cout << "�������� ���������� ��������:" << std::endl
			<< "1. ���������� ����������� ���������� ��������: ���������� ��� ���� ��������" << std::endl
			<< "2. ���������� ����������� ���������� ��������: � ���� ��������" << std::endl
			<< "3. ���������� ����������� ���������� �������� ����������� ���" << std::endl
			<< "4. ��������� ������������" << std::endl
			<< "5. ��������� �������, ������������� ����� � ������ ���������, ������������ ����� � ������ ����" << std::endl
			<< "6. ����������������� �������" << std::endl
			<< "7. ����� �������" << std::endl
			<< "8. ���������� ������ ���������." << std::endl;
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
			std::cout << "�������� ������ : { ";
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
			std::cout << "���������� ������." << std::endl;
			ent = 1;
			break;
		default:
			std::cout << "������� � ����� ������� �� ����������. ���������� �����:" << std::endl;
			break;
		}
	}
	return 0;
}