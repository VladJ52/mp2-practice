#include "scan_table.h"
#include <gtest.h>

TEST(ScanTab, can_create_empty)
{
	ASSERT_NO_THROW(ScanTab<int> t(2));
}

TEST(ScanTab, can_copied_from_empty)
{
	ScanTab<int> t(2);
	ASSERT_NO_THROW(ScanTab<int> tt(t));
}

TEST(ScanTab, can_create_not_empty)
{
	ASSERT_NO_THROW(ScanTab<int> t(2));
}

TEST(ScanTab, can_copied_from_not_empty)
{
	ScanTab<int> t(2);
	ASSERT_NO_THROW(ScanTab<int> tt(t));
}

TEST(ScanTab, can_realloc_memory_when_is_necessary)
{
	ScanTab<int> t;
	ASSERT_NO_THROW(t.insert("1", 2));
}

TEST(ScanTab, can_reset)
{
	ScanTab<int> t;
	t.insert("1", 1);
	t.reset();
	EXPECT_EQ(t.getcurrind(), 0);
}

TEST(ScanTab, can_setnext)
{
	ScanTab<int> t(4);
	t.insert("1", 1);
	t.insert("2", 1);
	t.reset();
	t.set();
	EXPECT_EQ(t.getcurrind(), 1);
}

TEST(ScanTab, can_get_current_data)
{
	ScanTab<int> t;
	t.insert("1", 1);
	t.reset();
	t.set();
	EXPECT_EQ(t.getcurr(), 1);
}

TEST(ScanTab, can_insert)
{
	ScanTab<int> t;
	ASSERT_NO_THROW(t.insert("1", 1));
}

TEST(ScanTab, throw_when_getcurr_with_no_records)
{
	ScanTab<int> t;
	ASSERT_ANY_THROW(t.getcurr());
}

TEST(ScanTab, throw_when_set_with_no_records)
{
	ScanTab<int> t;
	ASSERT_ANY_THROW(t.set());
}

TEST(ScanTab, cannot_search_when_table_is_empty)
{
	ScanTab<int> t;
	ASSERT_ANY_THROW(t.search("1"));
}

TEST(ScanTab, can_search)
{
	ScanTab<int> t;
	t.insert("1", 1);
	EXPECT_EQ(t.search("1"), 1);
}

/*TEST(ScanTab, can_search2)
{
	ScanTab<int> t(10);
	t.insert("2", 1);
	t.insert("3", 2);
	t.reset();
	ASSERT_ANY_THROW(t.search("1"));
}*/

TEST(ScanTab, can_del1)
{
	ScanTab<int> t;
	t.insert("1", 1);
	t.del("1");
	EXPECT_EQ(t.IsEmpty(), true);
}

TEST(ScanTab, can_del2)
{
	ScanTab<int> t(4);
	//t.insert("3", 5);
	t.insert("1", 1);
	t.insert("2", 2);
	t.del("1");
	t.del("2");
	EXPECT_EQ(t.IsEmpty(), true);
}

TEST(ScanTab, cannot_del_from_empty_table)
{
	ScanTab<int> t;
	ASSERT_ANY_THROW(t.del("1"));
}