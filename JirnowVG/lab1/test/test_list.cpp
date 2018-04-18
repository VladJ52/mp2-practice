#include "node.h"
#include "list.h"
#include <gtest.h>


TEST(node, can_create_empty)
{
	ASSERT_NO_THROW(node<int> a);
}

TEST(node, can_create_copied)
{
	node<int> a;
	node<int> b(a);
	EXPECT_EQ(b, a);
}

TEST(node, can_create_with_data)
{
	node<int> a(1);
	EXPECT_EQ(a.data, 1);
}


TEST(node, can_assign)
{
	node<int> a;
	node<int> b(12);
	a = b;
	EXPECT_EQ(a.data, 12);
}
//========================================================================================//


TEST(list, can_create_empty)
{
	ASSERT_NO_THROW(list<int> l);
}

TEST(list, can_create_copied)
{
	list<int> a;
	a.insertup(20);
	ASSERT_NO_THROW(list<int> b(a));
}

TEST(list, can_get_currdata)
{
	list<int> a;
	a.insertup(20);
	a.gotohead();
	a.gotonext();
	EXPECT_EQ(a.getcurdata(), 20);
}

TEST(list, can_insert_up_and_to_tail)
{
	list<int> a;
	a.insertup(11);
	a.insert_to_tail(12);
	a.gotohead();
	a.gotonext();
	EXPECT_EQ(a.getcurdata(), 11);
	a.gotonext();
	EXPECT_EQ(a.getcurdata(), 12);
}


class TestList : public ::testing::Test
{
protected:
	list<int> l1;
	list<int> l2;
public:
	TestList()
	{
		l1.insertup(1);		   l2.insertup(3);
		l1.insert_to_tail(2);  l2.insert_to_tail(4);
	}
	~TestList()
	{
		l1.clean();
		l2.clean();
	}
};

TEST_F(TestList, can_clean)
{
	ASSERT_NO_THROW(l1.clean());
}

TEST_F(TestList, can_delete_element)
{
	l1.del(l1.search(1));
	l1.gotohead();
	l1.gotonext();
	EXPECT_EQ(l1.getcurdata(), 2);
}

TEST_F(TestList, can_search_data)
{
	ASSERT_NO_THROW(l1.search(1));
}

TEST_F(TestList, can_assign)
{
	l2 = l1;
	l2.gotohead();
	l2.gotonext();
	EXPECT_EQ(l2.getcurdata(), 1);
	l2.gotonext();
	EXPECT_EQ(l2.getcurdata(), 2);
}
