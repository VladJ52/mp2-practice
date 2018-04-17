#include "postfix.h"
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
	monom b(2.0, 4);
	EXPECT_EQ(a != b, true);
}

TEST(monom, work_less)
{
	monom a(2.0, 4);
	monom b(3.0, 4);
	EXPECT_EQ(a < b, true);
}

TEST(monom, work_more)
{
	monom a(3.0, 4);
	monom b(2.0, 4);
	EXPECT_EQ(a > b, true);
}

TEST(monom, can_multiply_on_number)
{
	monom a(2.0, 4);
	a = a * 2;
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

