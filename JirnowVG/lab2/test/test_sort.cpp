#include "sort_table.h"
#include <gtest.h>

TEST(SortTab, can_create_empty)
{
	ASSERT_NO_THROW(SortTab<int> t);
}

TEST(SortTab, can_copied_from_empty)
{
	SortTab<int> t;
	ASSERT_NO_THROW(SortTab<int> tt(t));
}

TEST(SortTab, can_create_not_empty)
{
	ASSERT_NO_THROW(SortTab<int> t(2));
}

TEST(SortTab, can_copied_from_not_empty)
{
	SortTab<int> t(2);
	ASSERT_NO_THROW(SortTab<int> tt(t));
}

TEST(SortTab, can_realloc_memory_when_is_necessary)
{
	SortTab<int> t;
	ASSERT_NO_THROW(t.insert("1", 2));
}

TEST(SortTab, can_reset)
{
	SortTab<int> t;
	t.insert("1", 1);
	t.reset();
	EXPECT_EQ(t.getcurrind(), 0);
}

TEST(SortTab, can_setnext)
{
	SortTab<int> t;
	t.insert("1", 1);
	t.insert("2", 1);
	t.reset();
	t.set();
	EXPECT_EQ(t.getcurrind(), 1);
}

TEST(SortTab, can_get_current_data)
{
	SortTab<int> t;
	t.insert("1", 1);
	t.reset();
	t.set();
	EXPECT_EQ(t.getcurr(), 1);
}

TEST(SortTab, can_insert)
{
	SortTab<int> t;
	ASSERT_NO_THROW(t.insert("1", 1));
}

TEST(SortTab, throw_when_getcurr_with_no_records)
{
	SortTab<int> t;
	ASSERT_ANY_THROW(t.getcurr());
}

TEST(SortTab, throw_when_set_with_no_records)
{
	SortTab<int> t;
	ASSERT_ANY_THROW(t.set());
}

TEST(SortTab, cannot_search_when_table_is_empty)
{
	SortTab<int> t;
	ASSERT_ANY_THROW(t.search("1"));
}

TEST(SortTab, can_search)
{
	SortTab<int> t;
	t.insert("1", 1);
	EXPECT_EQ(t.search("1"), 1);
}


TEST(SortTab, can_del)
{
	SortTab<int> t;
	t.insert("1", 1);
	t.del("1");
	EXPECT_EQ(t.IsEmpty(), true);
}

TEST(SortTab, can_del2)
{
	SortTab<int> t;
	t.insert("1", 1);
	t.insert("2", 2);
	t.del("1");
	t.del("2");
	EXPECT_EQ(t.IsEmpty(), true);
}

TEST(SortTab, cannot_del_from_empty_table)
{
	SortTab<int> t;
	ASSERT_ANY_THROW(t.del("1"));
}