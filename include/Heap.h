/*****************************************************************/
/*                                                               */
/*   Implementation of Max/Min Heap using linear dynamic array   */
/*                      by. Ahmed Salem                          */
/*                                                               */
/*****************************************************************/

#ifndef _HEAP_H
#define _HEAP_H

#include <functional>
#include "global.h"
#include "ArrayList.h"
#include "IComparer.h"
#include "exception.h"

namespace ds
{
    template<typename T>
    class Heap
    {
    private:
        ArrayList<T> list_;
    private:
        void swap(INT, INT);
        INT getParentIndex(INT);
        INT getLeftChildIndex(INT);
        INT getRghtChildIndex(INT);
        BOOLEAN hasParent(INT);
        BOOLEAN hasLeftChild(INT);
        BOOLEAN hasRghtChild(INT);
        T& getLeftChild();
        T& getRghtChild();
        void heapifyUp(INT startIndex);
        void heapifyDown(INT startIndex);
        BOOLEAN removeAt(INT index);
    protected:
        Heap();
        Heap(IComparer<T>*);
        std::function<BOOLEAN(T, T)> comparerFunc_;
        IComparer<T> *comparer_;
        void readjust();
    public:
        ~Heap();
    public:
        BOOLEAN add(T item);
        T poll();
        T& peek();
        BOOLEAN removeOne(T item);
        BOOLEAN removeAll(T item);
    public:
        static Heap<T> createMaxHeap(IComparer<T>*);
        static Heap<T> createMinHeap(IComparer<T>*);
    };
}



/********************************************/
/*                                          */
/*                  Heap                    */
/*                                          */
/********************************************/

template<typename T>
ds::Heap<T>::Heap()
{
    // no thing to do here
}

template<typename T>
ds::Heap<T>::Heap(IComparer<T> *comparer) : list_()
{
    this->comparer_ = comparer;
}

template<typename T>
ds::Heap<T>::~Heap()
{
    // no thing to do here
}

template<typename T>
void ds::Heap<T>::swap(INT index, INT other)
{
    T temp = this->list_[index];

    this->list_[index] = this->list_[other];
    this->list_[other] = temp;
}

template<typename T>
INT ds::Heap<T>::getParentIndex(INT childIndex)
{
    return (INT)((childIndex - 1) / 2);
}

template<typename T>
INT ds::Heap<T>::getLeftChildIndex(INT parentIndex)
{
    return (parentIndex * 2) + 1;
}

template<typename T>
INT ds::Heap<T>::getRghtChildIndex(INT parentIndex)
{
    return (parentIndex * 2) + 2;
}

template<typename T>
BOOLEAN ds::Heap<T>::hasParent(INT index)
{
    return index != 0;
}

template<typename T>
BOOLEAN ds::Heap<T>::hasLeftChild(INT parentIndex)
{
    return this->getLeftChildIndex(parentIndex) < this->list_.getCount();
}

template<typename T>
BOOLEAN ds::Heap<T>::hasRghtChild(INT parentIndex)
{
    return this->getRghtChildIndex(parentIndex) < this->list_.getCount();
}

template<typename T>
void ds::Heap<T>::heapifyUp(INT startIndex)
{
    INT index = startIndex;
    INT parentIndex;

    // while it has parent,
    // and compare function return ture "what means that first paramter should be higher in order than second"
    // swap the two elements
    while 
        (
        this->hasParent(index) && 
        this->comparerFunc_(this->list_[index], this->list_[parentIndex = this->getParentIndex(index)])
        )
    {
        this->swap(index, parentIndex);
        index = parentIndex;
    }
}

template<typename T>
void ds::Heap<T>::heapifyDown(INT startIndex)
{
    INT index = startIndex;
    INT leftIndex;
    while ((leftIndex = this->getLeftChildIndex(index)) < this->list_.getCount())
    {
        INT swapIndex;
        INT rghtIndex = leftIndex + 1;
        if(rghtIndex < this->list_.getCount() && this->comparerFunc_(this->list_[rghtIndex], this->list_[leftIndex]))
        {
            // if it has right, and right is more worth than left
            // swap with right
            swapIndex = rghtIndex;
        }
        else
        {
            // swap with left
            swapIndex = leftIndex;
        }

        if(!this->comparerFunc_(this->list_[index], this->list_[swapIndex]))
        {
            this->swap(index, swapIndex);
            index = swapIndex;
        }
        else
        {
            break;
        }
    }
}

template<typename T>
void ds::Heap<T>::readjust()
{
    INT count = this->list_.getCount();
    
    for (INT i = 0; i < count; i++)
    {
        if(this->hasParent(i) && this->comparerFunc_(this->list_[i], this->list_[this->getParentIndex(i)]))
        {
            this->heapifyUp(i);
        }
        else
        {
            this->heapifyDown(i); 
        }
    }
}

template<typename T>
BOOLEAN ds::Heap<T>::add(T item)
{
    INT index = this->list_.getCount();
    if(this->list_.add(item))
    {
        this->heapifyUp(index);
        return TRUE;
    }

    return FALSE;
}
 
template<typename T>
T& ds::Heap<T>::peek()
{
    if(this->list_.getCount() == 0) throw ds::emptyCollectionException();
    
    return this->list_.get(0);
}

template<typename T>
T ds::Heap<T>::poll()
{
    if(this->list_.getCount() == 0) throw ds::emptyCollectionException();

    if(this->list_.getCount() == 1)
    {
        T top = this->list_[0];
        this->list_.removeAt(0);
        return top;
    }
    else
    {
        INT lastIndex = this->list_.getCount() - 1;

        T top = this->list_[0];
        this->list_[0] = this->list_[lastIndex];
        this->list_.removeLast();

        // heapify down the top element
        this->heapifyDown(0);
        return top;
    }
    
}

template<typename T>
BOOLEAN ds::Heap<T>::removeAt(INT index)
{
    // if index less than 0, return
    if(index < 0) return FALSE;
    // if element was the last one, remove it without modify the heap
    if(index == this->list_.getCount() - 1) this->list_.removeLast();
    
    // replace last element with removed element
    this->list_[index] = this->list_.pop();

    if(this->hasParent(index) && this->comparerFunc_(this->list_[index], this->list_[this->getParentIndex(index)]))
    {
        this->heapifyUp(index);
    }
    else
    {
        this->heapifyDown(index);
    }
    
    return TRUE;
}

template<typename T>
BOOLEAN ds::Heap<T>::removeOne(T item)
{
    INT index = this->list_.getIndexOf(item);
    return this->removeAt(index);
}

template<typename T>
BOOLEAN ds::Heap<T>::removeAll(T item)
{
    INT count; INT* indices = NULL;
    this->list_.getIndicesOf(item, indices, count);

    if(count > 0)
    {
        for (INT i = count-1; i >= 0; i--)
        {
            this->removeAt(indices[i]);
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
}

template<typename T>
ds::Heap<T> ds::Heap<T>::createMaxHeap(ds::IComparer<T>* comparer)
{
    ds::Heap<T> heap(comparer);
    heap.comparerFunc_ = [comparer](T item, T other) -> BOOLEAN
    { 
        return comparer->compare(item, other) >= 0;;
    };

    return heap;
}

template<typename T>
ds::Heap<T> ds::Heap<T>::createMinHeap(ds::IComparer<T>* comparer)
{
    ds::Heap<T> heap(comparer);
    heap.comparerFunc_ = [comparer](T item, T other) -> BOOLEAN
    { 
        return comparer->compare(item, other) <= 0;;
    };

    return heap;
}

#endif // !_HEAP_H