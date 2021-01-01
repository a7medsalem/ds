#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "global.h"
#include "LinkedList.h"

namespace ds
{
    template<typename T>
    class Queue
    {
    private:
        LinkedList<T> list_;
    public:
        Queue<T>();
        ~Queue();
    public:
        BOOLEAN enqueue(T);
        T& dequeue();
        T& peek();
        //
        BOOLEAN isEmpty();
        INT getCount();
    };
}


/********************************************/
/*                                          */
/*                  Queue                   */
/*                                          */
/********************************************/

template<typename T>
ds::Queue<T>::Queue() : list_()
{
}

template<typename T>
ds::Queue<T>::~Queue()
{
    // no thing to do here
}

template<typename T>
BOOLEAN ds::Queue<T>::enqueue(T item)
{
    return this->list_.add(item);
}

template<typename T>
T& ds::Queue<T>::dequeue()
{
    T& value = list_.getHead();
    list_.removeHead();

    return value;
}

template<typename T>
T& ds::Queue<T>::dequeue()
{
    return list_.getHead();
}

template<typename T>
BOOLEAN ds::Queue<T>::isEmpty()
{
    return this->list_.getCount() == 0;
}

template<typename T>
INT ds::Queue<T>::getCount()
{
    return this->list_.getCount();
}

#endif // !_QUEUE_H_