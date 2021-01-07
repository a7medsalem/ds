#include "gtest/gtest.h"
#include <string.h>

#include "global.h"
#include "PriorityQueue.h"

TEST(_PriorityQueueTests, create_priority_queue)
{
    ds::PriorityQueue<std::string> queue;

    //EXPECT_NE(NULL, queue);
}

TEST(_PriorityQueueTests, add_element)
{
    ds::PriorityQueue<std::string> queue;

    EXPECT_EQ(TRUE, queue.add("some text", 10));
    EXPECT_EQ(TRUE, queue.add("some text", 15));
}

TEST(_PriorityQueueTests, poll)
{
    ds::PriorityQueue<std::string> queue;

    // EXPECT_EQ(TRUE, queue.add("some text", 10));
    // EXPECT_EQ(TRUE, queue.add("most need", 01));
    // EXPECT_EQ(TRUE, queue.add("some text", 15));
    // EXPECT_EQ(TRUE, queue.add("some text", 65));

    // EXPECT_EQ("most need", queue.poll());
}