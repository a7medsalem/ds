Data Structures


# You have to clone googletest project to build this project succesfully.
git clone https://github.com/google/googletest.git


* Notes for testing 
--gtest_filter=SUIT_CASE.*                  : run all tests in SUIT_CASE
--gtest_filter=SUIT_CASE.*-SUIT_CASE.TEST   : run all tests in SUIT_CASE except SUIT_CASE.TEST
--gtest_filter=-*WORD*                      : run all tests except tests contains WORD




# Contents

* ArrayList
* LinkedList
* DoubleLinkedList
* HashTable
* Heap
    - Max heap
    - Min heap
* Queue
* Stack
* PriorityQueue
* Trie

* Tree
    - BinarySearchTree
    - AVLTree
    - RedBlackTree




# Functionality

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
    - begin()
    - end90
    - pop()
    - get(index)
    - getIndexOf(item)
    - getIndicesOf(item,indices,count)
    - getSize()
    - getCount()
    //
    - toArray(count)

* LinkedList { Linear Structure - Dynamic Size - Indexed[] } : ICollection
    - add(item)
    - insert(item)
    - contains(item)
    - contains(fn::predicate)
    - findFirst(fn::predicate, result)
    - findAll(fn::predicate, result, count)
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
    //
    - toArray()

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




