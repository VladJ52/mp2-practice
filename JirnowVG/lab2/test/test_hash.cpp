#include "hash_table.h"
#include <gtest.h>

TEST(HashTab, can_create_empty)
{
	ASSERT_NO_THROW(HashTab<int> t);
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
	ASSERT_NO_THROW(t.insert("1", 2));
}