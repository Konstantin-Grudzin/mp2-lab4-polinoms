#include "polynom.h"
#include <gtest.h>


TEST(monom, can_get_coef)
{
	Monom a(3,3);
	EXPECT_EQ(a.GetCoef(), 3);
}

TEST(monom, can_set_coef)
{
	Monom a(3, 3);
	a.SetCoef(4);
	EXPECT_EQ(a.GetCoef(), 4);
}

TEST(monom, can_get_pow)
{
	Monom a(3, 3);
	double t = 3;
	EXPECT_EQ(a.GetPow(),t);
}

TEST(monom, can_set_pow)
{
	Monom a(3, 3);
	short t = 4;
	a.SetPow(t);
	EXPECT_EQ(a.GetPow(), t);
}

TEST(monom, can_check_pow)
{
	Monom a(3, 123);
	auto t = a.GetPowOnDigits();
	EXPECT_EQ(a.GetPow(), t[0] * 100 + t[1] * 10 + t[2]);
}


TEST(monom, can_get_pow_on_digits)
{
	Monom a(3, 123);
	Monom b(3, 101);
	int f1 = a > b;
	int f2 = a < b;
	int f3 = a == b;
	EXPECT_EQ(f1 * 100 + f2 * 10 + f3, 100);
}


//Polynom operator*(Polynom& p2);

TEST(polynom,can_create_polynom)
{
	ASSERT_NO_THROW(Polynom a);
}
TEST(polynom,can_create_polynom_from_list)
{
	List<Monom> a;
	ASSERT_NO_THROW(Polynom b(a));
}
TEST(polynom, can_push_back)
{
	Polynom a;
	Monom b(3, 3);
	a.push_back(b);
	EXPECT_EQ(a.GetHead()->data == b, 1);
}
TEST(polynom, can_sort_monom)
{
	List<Monom> c;
	Monom b(3, 3);
	c.push_back(b);
	Monom d(4, 4);
	c.push_back(d);
	Polynom a(c);
	bool flag = 1;
	auto cur = a.GetHead();
	flag = (cur->data == d);
	cur = cur->next;
	flag *= (cur->data == b);
	EXPECT_EQ(flag, 1);
}
TEST(polynom, can_merge_two_lists)
{
	Polynom a;
	Polynom c;
	Monom b(3, 3);
	a.push_back(b);
	Monom d(4, 4);
	c.push_back(d);
	Polynom e(a.merge(c.GetListMonom()));
	bool flag = 1;
	auto cur = e.GetHead();
	flag = (cur->data == d);
	cur = cur->next;
	flag *= (cur->data == b);
	EXPECT_EQ(flag, 1);
}

TEST(polynom, cant_merge_two_empty_lists)
{
	Polynom a;
	Polynom c;
	ASSERT_ANY_THROW(a.merge(c.GetListMonom()));
}

TEST(polynom, can_sum_two_lists_with_diff_monoms)
{
	Polynom a;
	Polynom c;
	Monom b(3, 3);
	a.push_back(b);
	Monom d(4, 4);
	c.push_back(d);
	Polynom e = a + c;
	bool flag = 1;
	auto cur = e.GetHead();
	flag = (cur->data == d);
	cur = cur->next;
	flag *= (cur->data == b);
	EXPECT_EQ(flag, 1);
}

TEST(polynom, can_sum_two_lists_with_eq_monoms)//здесь тестируется destroy_duplicates, отдельный тест для него не требуется
{
	Polynom a;
	Polynom c;
	Monom b(3, 3);
	a.push_back(b);
	Monom d(4, 3);
	c.push_back(d);
	Polynom e = a + c;
	bool flag = 1;
	auto cur = e.GetHead();
	flag = (cur->data.GetCoef() == 7 && cur->next == nullptr);
	EXPECT_EQ(flag, 1);
}

TEST(polynom, can_sub_two_lists_with_diff_monoms)
{
	Polynom a;
	Polynom c;
	Monom b(3, 3);
	a.push_back(b);
	Monom d(4, 4);
	c.push_back(d);
	Polynom e = a - c;
	bool flag = 1;
	auto cur = e.GetHead();
	flag = (cur->data.GetCoef() == -d.GetCoef());
	cur = cur->next;
	flag *= (cur->data == b);
	EXPECT_EQ(flag, 1);
}

TEST(polynom, can_sub_two_lists_with_eq_monoms)
{
	Polynom a;
	Polynom c;
	Monom b(3, 3);
	a.push_back(b);
	Monom d(4, 3);
	c.push_back(d);
	Polynom e = a - c;
	bool flag = 1;
	auto cur = e.GetHead();
	flag = (cur->data.GetCoef() == -1 && cur->next == nullptr);
	EXPECT_EQ(flag, 1);
}

TEST(polynom, can_multiply_polynom_by_real_number)
{
	Polynom a;
	Monom b(-1, 1);
	a.push_back(b);
	Polynom c = a * (-1);
	auto cur = c.GetHead();
	EXPECT_EQ(cur->data.GetCoef(), 1);
}

TEST(polynom, can_delete_zeros)//функция в вычитании эквивалентна, т.к вычитание корректно, то и проверять для случая вычитания смысла не имеет
{
	Polynom a;
	Polynom b;
	Monom c(3, 3);
	Monom d(-3, 3);
	a.push_back(c);
	b.push_back(d);
	Polynom e = a + b;
	bool flag = (e.GetHead() == nullptr);
	EXPECT_EQ(flag, 1);
}

TEST(polynom, can_mul_polynoms)
{
	Polynom a;
	Monom b(1, 1);
	a.push_back(b);
	b.SetCoef(1); b.SetPow(2);
	a.push_back(b);

	Polynom c;
	Monom d(1, 1);
	c.push_back(d);
	d.SetCoef(1); d.SetPow(2);
	c.push_back(d);

	Monom t1(1, 4), t2(2, 3), t3(1, 2);
	Polynom e = a * c;
	auto cur = e.GetHead();
	bool flag = (cur->data == t1) * (cur->next->data == t2) * (cur->next->next->data == t3);
	EXPECT_EQ(flag, 1);
}

TEST(polynom, throw_then_power_more_9)
{
	Polynom a;
	Monom b(1, 4);
	a.push_back(b);
	Polynom c;
	Monom d(1, 6);
	c.push_back(d);

	ASSERT_ANY_THROW(a * c);
}