#include "polynom.h"

void wait()
{
	char c;
	do
	{
		std::cout << "\nInput #, when you ready to continue";
		std::cin >> c;
	} while (c != '#');
}
void print_vector_of_polynoms(std::vector<Polynom>& mas)
{
	for (auto el : mas)
		std::cout << el<<std::endl;
	wait();
}
void Get_Polynom(Polynom& tmp)
{
	std::cout << "How much monoms do you have?\n";
	int size; std::cin >> size;
	List<Monom> t1;
	for (int i = 0; i < size; ++i)
	{
		std::cout << "Input coefficient:";
		double coeff; std::cin >> coeff;
		std::cout << "Input powers of x,y,z (without spaces and less than 9!):";
		int pow; std::cin >> pow;
		while(pow>=1000)
		{
			std::cout << "\nWrong input!";
			std::cin >> pow;
		}
		Monom tmp(coeff, pow);
		t1.push_back(tmp);
	}
	Polynom t2(t1);
	t2.prep();
	std::cout << "Your monom is:" << " " << t2 << std::endl;
	tmp = t2;
	wait();
}
void delete_polynom(std::vector<Polynom> &mas,int pos)
{
	std::vector<Polynom> tmp;
	for (int i = 0; i < mas.size(); ++i)
	{
		if (i != pos)
			tmp.push_back(mas[i]);
	}
	mas = tmp;
}

void sum_poly(std::vector<Polynom>& mas, int pos1, int pos2)
{
	if (pos1 >= mas.size() || pos2 >= mas.size() || pos1<0 || pos2<0)
	{
		std::cout << "\nWrong position";
		wait();
		return;
	}
	Polynom tmp = mas[pos1] + mas[pos2];
	std::cout << "Where is your polinom\n" << tmp << std::endl;
	std::cout << "Do you want to save it (Yes(1) / No(0))?";
	int chs; std::cin >> chs;
	if (chs)
		mas.push_back(tmp);
}
void sub_poly(std::vector<Polynom>& mas, int pos1, int pos2)
{
	if (pos1 >= mas.size() || pos2 >= mas.size() || pos1 < 0 || pos2 < 0)
	{
		std::cout << "\nWrong position";
		wait();
		return;
	}
	Polynom tmp = mas[pos1] - mas[pos2];
	std::cout << "Where is your polinom\n" << tmp << std::endl;
	std::cout << "Do you want to save it (Yes(1) / No(0))?";
	int chs; std::cin >> chs;
	if (chs)
		mas.push_back(tmp);
}
void mul_poly(std::vector<Polynom>& mas, int pos1, int pos2)
{
	if (pos1 >= mas.size() || pos2 >= mas.size() || pos1 < 0 || pos2 < 0)
	{
		std::cout << "\nWrong position";
		wait();
		return;
	}
	try
	{
		Polynom tmp = mas[pos1] * mas[pos2];
		std::cout << "Where is your polinom\n" << tmp << std::endl;
		std::cout << "Do you want to save it (Yes(1) / No(0))?";
		int chs; std::cin >> chs;
		if (chs)
			mas.push_back(tmp);
	}
	catch (std::string ex)
	{
		std::cout << ex;
	}
}
int main()
{
	std::vector<Polynom> mas;
	do
	{
		system("cls");
		std::cout << "Hello user! What do you want?:\n1.print all polynoms\n2.print one polynom\n3.add polynom to list\n4.delete polynom from list\n5.Add polynoms\n6.Subscript polynoms\n7.Multiply polynoms\n8.Exit (Test is end. Hooray!)";
		int choose;
		std::cin >> choose;
		if (choose == 1)
		{
			print_vector_of_polynoms(mas);
		}
		else if (choose == 2)
		{
			if (!mas.size())
			{
				std::cout << "Sorry Link, i cant print you polinom, come back when you get one!\n";
				wait();
				continue;
			}
			std::cout << "You have:" << mas.size() << "polynoms, which one you want to print?";
			int pos; std::cin >> pos;
			if (pos > mas.size() || pos<=0)
			{
				std::cout << "\nWrong position!";
				wait();
				continue;
			}
			std::cout << mas[pos - 1];
			wait();
		}
		else if(choose==3)
		{
			std::cout << "Give me polynom";
			Polynom tmp;
			Get_Polynom(tmp);
			mas.push_back(tmp);
		}
		else if (choose == 4)
		{
			if (!mas.size())
			{
				std::cout << "Sorry Link, i cant delete you polinom, come back when you get one!\n";
				wait();
				continue;
			}
			std::cout << "You have:" << mas.size() << "polynoms, which one you want to delete?";
			int pos; std::cin >> pos;
			delete_polynom(mas,pos - 1);
		}
		else if (choose == 5)
		{
			if (mas.size() < 2)
			{
				std::cout << "Sorry Link, i cant sum you polinoms, come back when you get two!\n";
				wait();
				continue;
			}
			std::cout << "You have" << mas.size() << "polynoms, what you do want to sum?";
			int pos1, pos2; std::cin >> pos1 >> pos2;
			sum_poly(mas,pos1 - 1, pos2 - 1);
		}
		else if (choose == 6)
		{
			if (mas.size() < 2)
			{
				std::cout << "Sorry Link, i cant sub you polinoms, come back when you get two!\n";
				wait();
				continue;
			}
			std::cout << "You have" << mas.size() << "polynoms, what you do want to sub?";
			int pos1, pos2; std::cin >> pos1 >> pos2;
			sub_poly(mas,pos1 - 1, pos2 - 1);
		}
		else if (choose == 7)
		{
			if (mas.size() < 2)
			{
				std::cout << "Sorry Link, i cant mul you polinoms, come back when you get two!\n";
				wait();
				continue;
			}
			std::cout << "You have" << mas.size() << "polynoms, what you do want to multiply?";
			int pos1, pos2; std::cin >> pos1 >> pos2;
			mul_poly(mas,pos1 - 1, pos2 - 1);
		}
		else
		{
			break;
		}
	} while (1);
	for (Polynom el : mas)
		el.clear();
}
