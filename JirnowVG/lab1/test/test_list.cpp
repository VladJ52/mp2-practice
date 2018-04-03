#include "node.h"
#include "list.h"
#include <gtest.h>


TEST(node, can_create_node_and_list)
{
	ASSERT_NO_THROW(node<int> a);
}

TEST(node, can_create_node_from_node)
{
	node<int> a;
	node<int> b(a);
	EXPECT_EQ(b, a);
}

TEST(node, can_create_node_with_const)
{
	node<int> a(1);
	EXPECT_EQ(a.data, 1);
}

/*TEST(node, can_create_node_with_full_param)
{
	const node<int> b(3);
	node<int> a(2, &b);
	EXPECT_EQ(a.data, 2);
	EXPECT_EQ(a.next, b);
}*/