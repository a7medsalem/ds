#ifndef _STACK_H_
#define _STACK_H_

#include "global.h"
#include "LinkedList.h"


namespace ds
{
    template<typename T>
    class Stack
    {
    private:
        LinkedList<T> list_;
    public:
        Stack();
        ~Stack();
    public:
        BOOLEAN push(T);
        T& pop();
        T& peek();
        //
        BOOLEAN isEmpty();
        INT getCount();
    };
}



/********************************************/
/*                                          */
/*                  Stack                   */
/*                                          */
/********************************************/


template<typename T>
ds::Stack<T>::Stack() : list_()
{
}

template<typename T>
ds::Stack<T>::~Stack()
{
    // no thing to do here
}

template<typename T>
BOOLEAN ds::Stack<T>::push(T item)
{
    return this->list_.add(item);
}

template<typename T>
T& ds::Stack<T>::pop()
{
    T& value = this->list_.getTail();
    this->list_.removeTail();

    return value;
}

template<typename T>
T& ds::Stack<T>::peek()
{
    return this->list_.getTail();
}

template<typename T>
BOOLEAN ds::Stack<T>::isEmpty()
{
    return this->list_.getCount() == 0;
}

template<typename T>
INT ds::Stack<T>::getCount()
{
    return this->list_.getCount();
}

#endif // !_STACK_H_