// содержит объявление полинома и монома

#ifndef POLY
#define POLY

#include"node.h"

class Monom
{
	double coeff;
	short pow;
public:
	Monom();
	Monom(double _coeff, short _pow);

	//setter and getter

	void SetCoef(double _coeff);
	double GetCoef();

	void SetPow(short _pow);
	short GetPow();
	//Получить степень по цифрам
	std::vector<short> GetPowOnDigits();

	bool operator<(const Monom& m2);
	bool operator>(const Monom& m2);
	bool operator==(const Monom& m2);

	friend std::ostream& operator<<(std::ostream& os, Monom& m);
};

//Единственная проблема которую я не смог решить: удаление мономов
// Поэтому удаление РЕАЛЬНЫХ объектов будет производится через вызов clear()
// C style rules!

class Polynom
{
	List<Monom> polynom;
	void destroy_duplicates();
	void delete_zeros();
	void sort();
	
public:
	
	Polynom();
	Polynom(const List<Monom>& monom);

	void prep()
	{
		sort();
		destroy_duplicates();
		delete_zeros();
	}
	void push_back(Monom& m);
	List<Monom> merge(List<Monom> &b);
	List<Monom> GetListMonom(){ return polynom; }
	void clear(){ polynom.clear(); }
	Polynom operator+( Polynom& p2);
	Polynom operator-(Polynom& p2);
	Polynom operator*(Polynom& p2);
	Polynom operator*(double c);

	Node<Monom>* GetHead()
	{
		return polynom.head();
	}

	friend std::ostream& operator<<(std::ostream& os,Polynom& p);
};

#endif 
