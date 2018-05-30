#include "polinom.h"
#include <gtest.h>

TEST(monom, can_create_with_null_param)
{
	monom a;
	EXPECT_EQ(a.coeff, 0.0);
	EXPECT_EQ(a.xyz, 0);
}

TEST(monom, can_create_copied_monom)
{
	monom a(2.0, 4);
	monom b(a);
	EXPECT_EQ(b.coeff, 2.0);
	EXPECT_EQ(b.xyz, 4);
}

TEST(monom, can_create_from_string)
{
	string s = "xyz";
	monom a(s);
	EXPECT_EQ(a.coeff, 1.0);
	EXPECT_EQ(a.xyz, 111);
}

TEST(monom, can_assign)
{
	monom a(2.0, 4);
	monom b(3.0, 2);
	a = b;
	EXPECT_EQ(a.coeff, 3.0);
	EXPECT_EQ(a.xyz, 2);
}

TEST(monom, work_equall)
{
	monom a(2.0, 4);
	monom b(2.0, 4);
	EXPECT_EQ(a == b, true);
}

TEST(monom, work_not_equall)
{
	monom a(3.0, 4);
	monom b(2.0, 5);
	EXPECT_EQ(a != b, true);
}

TEST(monom, work_less)
{
	monom a(2.0, 4);
	monom b(3.0, 5);
	EXPECT_EQ(a < b, true);
}

TEST(monom, work_more)
{
	monom a(3.0, 5);
	monom b(2.0, 4);
	EXPECT_EQ(a > b, true);
}

TEST(monom, can_multiply_on_number_from_right)
{
	monom a(2.0, 4);
	a = a * 2;
	EXPECT_EQ(a.coeff, 4.0);
}

TEST(monom, can_multiply_on_number_from_left)
{
	monom a(2.0, 4);
	a = 2 * a;
	EXPECT_EQ(a.coeff, 4.0);
}


TEST(monom, can_multiply_on_another_monom)
{
	monom a(2.0, 111);
	monom b(3.0, 222);
	monom c;
	c = a*b;
	EXPECT_EQ(c.coeff, 6.0);
	EXPECT_EQ(c.xyz, 333);
}

//====================================================================//

TEST(polinom, can_create_empty)
{
	ASSERT_NO_THROW(polinom a);
}

TEST(polinom, can_create_from_string)
{
	string s = "xyz+2xy";
	ASSERT_NO_THROW(polinom a(s));
}

TEST(polinom, can_create_copied_polinom)
{
	polinom a("x-y");
	ASSERT_NO_THROW(polinom b(a));
}

TEST(polinom, can_assign)
{
	polinom a("x+y");
	polinom b("z-x");
	a = b;
	EXPECT_EQ(a, b);
}

TEST(polinom, right_addition_1)
{
	polinom a("x+y");
	polinom b("x");
	polinom c("2x+y");
	EXPECT_EQ(c, a + b);
}

TEST(polinom, right_addition_2)
{
	polinom a("-x+y");
	polinom b("x");
	polinom c("y");
	EXPECT_EQ(c, a + b);
}

TEST(polinom, right_addition_3)
{
	polinom a("1+x+y");
	polinom b("x");
	polinom c("1+2x+y");
	EXPECT_EQ(c, a + b);
}

TEST(polinom, right_addition_4)
{
	polinom a("xy");
	polinom b("xyz-2x2yz");
	polinom c("xy+xyz-2x2yz");
	EXPECT_EQ(c, a + b);
}

TEST(polinom, right_addition_5)
{
	polinom a("x+y");
	polinom b("-x-y");
	polinom c;
	EXPECT_EQ(c, a + b);
}

TEST(polinom, right_multiply_on_another_polinom_1)
{
	polinom a("x");
	polinom b("y");
	polinom c("xy");
	EXPECT_EQ(c, a*b);
}

TEST(polinom, right_multiply_on_another_polinom_2)
{
	polinom a("x-y");
	polinom b("x+y");
	polinom c("x2-y2");
	EXPECT_EQ(c, a * b);
}

TEST(polinom, right_multiply_on_another_polinom_3)
{
	polinom a("x");
	polinom b("-x");
	polinom c("-x2");
	EXPECT_EQ(c, a * b);
}

TEST(polinom, right_multiply_on_number_1)
{
	polinom a("x-y");
	double b = 10.0;
	polinom c("10x-10y");
	EXPECT_EQ(c, a * b);
}

TEST(polinom, right_multiply_on_number_2)
{
	polinom a("x-y");
	double b = -10.0;
	polinom c("-10x+10y");
	EXPECT_EQ(c, a * b);
}

TEST(polinom, right_multiply_on_number_3)
{
	polinom a("x-y");
	double b = -10.0;
	polinom c("-10x+10y");
	EXPECT_EQ(c, b * a);
}