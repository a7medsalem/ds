#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include "exception.h"
#include "Heap.h"
#include "HashTable.h"

namespace ds
{
    class PriorityComparer : public ds::IComparer<INT>
    {
    public:
        PriorityComparer(){};
        BYTE compare(INT number, INT other) const override
        {
            if(number  > other) return 1;
            else if(number < other) return -1;
            else return 0;
        }
    };

    template<typename T>
    class PriorityQueue : protected Heap<T>
    {
    private:
        HashTable<T, INT>* priorityTable;
    public:
        PriorityQueue();
        ~PriorityQueue();
    public:
        BOOLEAN add(T item, INT priority = 0);
        BOOLEAN updatePriority(T item, INT priority);
        T poll();
        T& peek();
    };
}


template<typename T>
ds::PriorityQueue<T>::PriorityQueue() : ds::Heap<T>::Heap()
{
    this->priorityTable = new ds::HashTable<T, INT>();
    this->comparerFunc_ = [this](T item1, T item2) -> BOOLEAN
    {
        return this->priorityTable->get(item1) <= this->priorityTable->get(item2);
    };
}

template<typename T>
ds::PriorityQueue<T>::~PriorityQueue()
{
    delete this->priorityTable;
}


template<typename T>
BOOLEAN ds::PriorityQueue<T>::add(T item, INT priority)
{
    if(!this->priorityTable->hasKey(item))
    {
        this->priorityTable->add(item, priority);
    }
    else
    {
        if(this->priorityTable->get(item) != priority)
        {
            (*this->priorityTable)[item] = priority;
            this->readjust();
        }
    }
    
    return ds::Heap<T>::add(item);
}

template<typename T>
BOOLEAN ds::PriorityQueue<T>::updatePriority(T item, INT priority)
{
    if(this->priorityTable->get(item) != priority)
    {
        (*this->priorityTable)[item] = priority;
        this->readjust();
    }

    return FALSE;
}

template<typename T>
T ds::PriorityQueue<T>::poll()
{
    T value = ds::Heap<T>::poll();
    this->priorityTable->remove(value);
    return value;
}

template<typename T>
T& ds::PriorityQueue<T>::peek()
{
    return ds::Heap<T>::peek();
}
#endif // !_PRIORITY_QUEUE_H_