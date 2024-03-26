#include "/mp2-lab4-polinoms/include/polynom.h"

//Monom's functions

Monom::Monom()
{
	coeff = 0;
	pow = 0;
}
Monom::Monom(double _coeff, short _pow) :coeff(_coeff), pow(_pow)
{

}

//setter and getter

void Monom::SetCoef(double _coeff)
{
	coeff = _coeff;
}
double Monom::GetCoef()
{
	return coeff;
}

void Monom::SetPow(short _pow)
{
	pow = _pow;
}
short Monom::GetPow()
{
	return pow;
}
//Получить степень по цифрам
std::vector<short> Monom::GetPowOnDigits()
{
	short tmp;
	std::vector<short> Tmp;
	tmp = pow / 100;
	Tmp.push_back(tmp);
	tmp = (pow / 10) % 10;
	Tmp.push_back(tmp);
	tmp = pow % 10;
	Tmp.push_back(tmp);

	return Tmp;
}

bool Monom::operator<(const Monom& m2)
{
	return pow < m2.pow;
}
bool Monom::operator>(const Monom& m2)
{
	return pow > m2.pow;
}
bool Monom::operator==(const Monom& m2)
{
	return pow == m2.pow;
}
std::ostream& operator<<(std::ostream& os, Monom& m)
{
	std::vector<short> step = m.GetPowOnDigits();
	std::cout << abs(m.GetCoef());
	std::string stroka = "xyz";
	int i = 0;
	for (short el : step)
	{
		if (el == 0) continue;
		std::cout <<"*"<< stroka[i++];
		if (el >= 2)
		{
			std::cout << "^(" << el<<")";
		}
	}
	return os;
}

//------------------------------------------------------------------------------


//Polynoms's functions
void Polynom::sort()//Вызывается только после ввода, проверка на пустоту не требуется
{
	polynom.sort();
}
void Polynom::destroy_duplicates()//Вызывается только после merge и умножения, слить пустой список нельзя, проверка не требуется
{
	Node<Monom> *i =polynom.head();
	if (i == nullptr) return;

	while (i->next!=nullptr)
	{
		Node<Monom>* j = i->next;
		if (i->data.GetPow() == j->data.GetPow())
		{
			double coef1 = i->data.GetCoef();
			double coef2 = j->data.GetCoef();

			i->data.SetCoef(coef1 + coef2);
			i->next = j->next;
			delete j;
		}
		else
		{
			i = j;
		}
	}
	polynom.SetTail(i);
}

List<Monom> Polynom::merge(List<Monom> &b)//возвращает "слитый" список БЕЗ ДУБЛИКАТОВ
{
	Node<Monom>* i = polynom.head();
	Node<Monom>* j = b.head();
	if (i == nullptr && j == nullptr)
		throw "Merge Two Empty Lists!";
	List<Monom> new_poly;
	while (i != nullptr && j != nullptr)
	{
		if (i->data.GetPow() <= j->data.GetPow())
		{
			Monom tmp(i->data.GetCoef(), i->data.GetPow());
			new_poly.push_back(tmp);
			i = i->next;
		}
		else
		{
			Monom tmp(j->data.GetCoef(), j->data.GetPow());
			new_poly.push_back(tmp);
			j = j->next;
		}
	}

	while (i != nullptr)
	{
		Monom tmp(i->data.GetCoef(), i->data.GetPow());
		new_poly.push_back(tmp);
		i = i->next;
	}

	while (j != nullptr)
	{
		Monom tmp(j->data.GetCoef(), j->data.GetPow());
		new_poly.push_back(tmp);
		j = j->next;
	}
	return new_poly;
}
void Polynom::delete_zeros()
{
	Node<Monom>* i = polynom.head();
	while (i != nullptr && i->data.GetCoef() == 0)
	{
		Node<Monom>* j = i;
		i = i->next;
		delete j;
		polynom.SetHead(i);
	}
	if (polynom.head() == nullptr) return;
	while (i->next != nullptr)
	{
		Node<Monom>* j = i->next;
		if (j->data.GetCoef() == 0)
		{
			i->next = j->next;
			delete j;
		}
		else
		{
			i = j;
		}
	}
	if (i->data.GetCoef() == 0)
	{
		polynom.clear();
	}
	else
	{
		polynom.SetTail(i);
	}
}
Polynom::Polynom()
{

}
Polynom::Polynom(const List<Monom>& poly)
{
	polynom = poly;
	sort();
	destroy_duplicates();
	delete_zeros();
}

void Polynom::push_back(Monom& m)
{
	polynom.push_back(m);
}

Polynom Polynom::operator+(Polynom& p2)
{
	Polynom tmp(merge(p2.polynom));
	//не сортируем,т.к храним списки сортированными
	tmp.destroy_duplicates();
	tmp.delete_zeros();
	return tmp;
}
Polynom Polynom::operator-(Polynom& p2)
{
	double c = -1.0;
	Polynom tmp = p2 * c;
	Polynom tmp1(merge(tmp.polynom));
	//не сортируем,т.к храним списки сортированными
	tmp1.destroy_duplicates();
	tmp1.delete_zeros();
	return tmp1;
}
Polynom Polynom::operator*(Polynom& p2)
{
	Polynom new_poly;
	Node<Monom>* i = GetHead();
	while (i != nullptr)
	{
		Node<Monom>* j = p2.GetHead();
		while (j != nullptr)
		{
			Monom c1 = i->data;
			Monom c2 = j->data;
			std::vector<short> pow1 = c1.GetPowOnDigits();
			std::vector<short> pow2 = c2.GetPowOnDigits();
			std::vector<short> pow3(3);
			for (int l = 0; l < 3; ++l)
			{
				pow3[l] = pow1[l] + pow2[l];
				if (pow3[l] > 9)
					throw "Power more than 9!";
			}
			Monom c3(c1.GetCoef() * c2.GetCoef(), pow3[0] * 100 + pow3[1] * 10 + pow3[2]);
			new_poly.push_back(c3);
			j = j->next;
		}
		i = i->next;
	}
	new_poly.sort();
	new_poly.destroy_duplicates();
	new_poly.delete_zeros();
	return new_poly;
}
Polynom Polynom::operator*(double c)
{
	Polynom new_poly;
	Node<Monom>* i = polynom.head();
	while (i != nullptr)
	{
		double coef = i->data.GetCoef();
		Monom val(coef * c, i->data.GetPow());
		new_poly.push_back(val);
		i = i->next;
	}
	new_poly.delete_zeros();
	return new_poly;
}

std::ostream& operator<<(std::ostream& os, Polynom& p)
{
	Node<Monom>* i = p.GetHead();
	bool first = 1;
	while (i != nullptr)
	{
		if (!first || i->data.GetCoef()<0)
		{
			if (i->data.GetCoef() > 0)
				std::cout << " + ";
			else
				std::cout << " - ";
		}
		first = 0;
		std::cout << i->data;
		i = i->next;
	}
	return os;
}