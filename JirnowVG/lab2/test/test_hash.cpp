#include "hash_table.h"
#include "polinom.h"
#include <gtest.h>

TEST(HashTab, can_create_empty)
{
	ASSERT_NO_THROW(HashTab<int> t(2));
}

TEST(HashTab, can_copied_from_empty)
{
	HashTab<int> t;
	ASSERT_NO_THROW(HashTab<int> tt(t));
}

TEST(HashTab, can_create_not_empty)
{
	ASSERT_NO_THROW(HashTab<int> t(2));
}

TEST(HashTab, can_copied_from_not_empty)
{
	HashTab<int> t(2);
	ASSERT_NO_THROW(HashTab<int> tt(t));
}

TEST(HashTab, can_realloc_memory_when_is_necessary)
{
	HashTab<int> t;
	t.insert("2", 232);
	t.insert("3", 22);
	ASSERT_NO_THROW(t.insert("1", 2));
}

TEST(HashTab, can_reset1)
{
	HashTab<int> t(2);
	t.insert("1", 1);
	t.insert("2", 1);
	t.reset();
	EXPECT_EQ(t.getcurrind(), 0);
}

TEST(HashTab, can_reset2)
{
	HashTab<int> t;
	t.reset();
	EXPECT_EQ(t.getcurrind(), -1);
}

TEST(HashTab, can_setnext)
{
	HashTab<int> t(2);
	t.insert("1", 1);
	t.set();
	EXPECT_EQ(t.getcurrind(), 1);
}

TEST(HashTab, cant_setnext_in_empty_table)
{
	HashTab<int> t;
	ASSERT_ANY_THROW(t.set());
}

TEST(HashTab, can_get_current_data)
{
	HashTab<int> t;
	t.insert("1", 1);
	t.reset();
	t.set();
	EXPECT_EQ(t.getcurr(), 1);
}

TEST(HashTab, can_insert)
{
	HashTab<int> t;
	ASSERT_NO_THROW(t.insert("1", 1));
}

TEST(HashTab, throw_when_getcurr_with_no_records)
{
	HashTab<int> t;
	ASSERT_ANY_THROW(t.getcurr());
}

TEST(HashTab, throw_when_set_with_no_records)
{
	HashTab<int> t;
	ASSERT_ANY_THROW(t.set());
}

TEST(HashTab, cannot_search_when_table_is_empty)
{
	HashTab<int> t;
	ASSERT_ANY_THROW(t.search("1"));
}

TEST(HashTab, can_search)
{
	HashTab<int> t;
	t.insert("1", 1);
	EXPECT_EQ(t.search("1"), 1);
}


TEST(HashTab, can_del1)
{
	HashTab<int> t;
	t.insert("1", 1);
	t.del("1");
	EXPECT_EQ(t.IsEmpty(), true);
}

TEST(HashTab, can_del2)
{
	HashTab<int> t;
	t.insert("1", 1);
	t.insert("2", 2);
	t.del("1");
	t.del("2");
	EXPECT_EQ(t.IsEmpty(), true);
}

TEST(HashTab, cannot_del_from_empty_table)
{
	HashTab<int> t;
	ASSERT_ANY_THROW(t.del("1"));
}
