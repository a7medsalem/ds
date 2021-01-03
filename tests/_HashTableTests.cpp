#include "gtest/gtest.h"

#include "global.h"
#include "HashTable.h"


TEST(_HashTableTests, create_hash_table_with_INT_key)
{
    ds::HashTable<INT, INT> table;
    //
    EXPECT_EQ(TRUE, table.add(1, 100));
    EXPECT_EQ(TRUE, table.add(2, 101));
}

TEST(_HashTableTests, create_hash_table_with_char_key)
{
    ds::HashTable<const char*, INT> table;
    //
    EXPECT_EQ(TRUE, table.add("first", 100));
    EXPECT_EQ(TRUE, table.add("second", 100));
}

TEST(_HashTableTests, create_hash_table_with_pointer)
{
    ds::ArrayList<INT> *list1 = new ds::ArrayList<INT>();
    ds::ArrayList<INT> *list2 = new ds::ArrayList<INT>();


    ds::HashTable<ds::ArrayList<INT>*, INT> table;
    //
    EXPECT_EQ(TRUE, table.add(list1, list1->getCount()));
    EXPECT_EQ(TRUE, table.add(list2, list2->getCount()));
}

TEST(_HashTableTests, has_key)
{
    ds::HashTable<const char*, INT> table;
    //
    EXPECT_EQ(TRUE, table.add("someKey", 100));
    EXPECT_EQ(TRUE, table.add("someOtherKey", 100));
    //
    EXPECT_EQ(TRUE, table.hasKey("someKey"));
    EXPECT_EQ(FALSE, table.hasKey("falseKey"));
}

TEST(_HashTableTests, remove)
{
    ds::HashTable<const char*, INT> table;
    //
    EXPECT_EQ(TRUE, table.add("someKey", 100));
    EXPECT_EQ(TRUE, table.add("someOtherKey", 100));
    //
    EXPECT_EQ(TRUE, table.remove("someKey"));
    EXPECT_EQ(FALSE, table.hasKey("someKey"));
}

TEST(_HashTableTests, remove_with_wrong_key)
{
    ds::HashTable<const char*, INT> table;
    //
    EXPECT_EQ(TRUE, table.add("someKey", 100));
    EXPECT_EQ(TRUE, table.add("someOtherKey", 100));
    //
    EXPECT_EQ(FALSE, table.remove("wrongKey"));
}


TEST(_HashTableTests, get_with_string)
{
    ds::HashTable<const char*, INT> table;
    //
    EXPECT_EQ(TRUE, table.add("someKey", 100));
    EXPECT_EQ(TRUE, table.add("someOtherKey", 100));
    //
    EXPECT_EQ(100, table.get("someKey"));
}

TEST(_HashTableTests, get_with_indexer)
{
    ds::HashTable<const char*, INT> table;
    //
    EXPECT_EQ(TRUE, table.add("someKey", 100));
    EXPECT_EQ(TRUE, table.add("someOtherKey", 150));
    //
    EXPECT_EQ(TRUE, table["someKey"] == 100);
    EXPECT_EQ(TRUE, table["someOtherKey"] == 150);

    table["someOtherKey"] = 50;
    EXPECT_EQ(TRUE, table["someKey"] == 100);
    EXPECT_EQ(TRUE, table["someOtherKey"] == 50);
}