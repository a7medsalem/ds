#include "gtest/gtest.h"

#include "global.h"
#include "Heap.h"
#include "IComparer.h"


class IntComparer : public ds::IComparer<INT>
{
public:
    IntComparer(){};
    BYTE compare(INT number, INT other) const override;
};

BOOLEAN IntComparer::compare(INT number, INT other) const
{
    if(number  > other) return 1;
    else if(number < other) return -1;
    else return 0;
}


TEST(_HeapTests, add_item)
{
    IntComparer *comparer = new IntComparer();
    ds::Heap<INT> heap = ds::Heap<INT>::createMinHeap(comparer);

    heap.add(5);
    heap.add(7);
    heap.add(10);
    heap.add(4);
}


TEST(_HeapTests, poll_item)
{
    IntComparer *comparer = new IntComparer();
    ds::Heap<INT> heap = ds::Heap<INT>::createMinHeap(comparer);

    heap.add(5);
    heap.add(7);
    heap.add(10);
    heap.add(4);
    heap.add(12);
    heap.add(25);
    heap.add(1);
    heap.add(17);
    heap.add(32);
    heap.add(0);

    EXPECT_EQ(0, heap.poll());
    EXPECT_EQ(1, heap.poll());
    EXPECT_EQ(4, heap.poll());
    EXPECT_EQ(5, heap.poll());
    EXPECT_EQ(7, heap.poll());
    EXPECT_EQ(10, heap.poll());
    EXPECT_EQ(12, heap.poll());
    EXPECT_EQ(17, heap.poll());
    EXPECT_EQ(25, heap.poll());
    EXPECT_EQ(32, heap.poll());
}

