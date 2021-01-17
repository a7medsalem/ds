Data Structures

* ArrayList { Linear Structure - Dynamic Size - Indexed[] } : IString, ICollection
    - add(item)                         // tested
    - insert(item)                      // tested
    - contains(item)
    - removeOne(item)
    - removeOne(fn::predicate)
    - removeAll(item)
    - removeAll(fn::predicate)
    - removeAt(index)
    - removeFirst()
    - removeLast()
    - pop()
    - get(index)
    - getSize()
    - getCount()

* LinkedList { Linear Structure - Dynamic Size - Indexed[] } : ICollection
    - add(item)
    - insert(item)
    - contains(item)
    - contains(fn::predicate)
    - findFirst(fn::predicate)
    - findAll(fn::predicate)
    - removeFirst(item)
    - removeFisrt(fn::predicate)
    - removeAll(item)
    - removeAll(fn::predicate)
    - removeAt(index)
    - removeHead()
    - removeTail()
    - getHead()
    - getTail()
    - getCount()
    - reverse()
    - get(index)
    - set(index, item)

* DoublyLinkedList { Linear Structure - Dynamic Size - Indexed[] }
    - add(item)
    - insert(item)
    - removeAt(index)
    - removeHead()
    - removeTail()
    - getHead()
    - getTail()
    - getCount()
    - reverse()
    - get(index)
    - set(index, item)



* Notes for testing 
--gtest_filter=SUIT_CASE.*                  : run all tests in SUIT_CASE
--gtest_filter=SUIT_CASE.*-SUIT_CASE.TEST   : run all tests in SUIT_CASE except SUIT_CASE.TEST
--gtest_filter=-*WORD*                      : run all tests except tests contains WORD
