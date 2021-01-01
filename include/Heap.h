#ifndef _HEAP_H
#define _HEAP_H

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
        IComparer<T> *comparer_;
        BOOLEAN (*comparerFunc_)(IComparer<T>*, T,T);
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
    protected:
        Heap(IComparer<T>*);
    public:
        ~Heap();
    public:
        BOOLEAN add(T);
        T poll();
        T& peek();
        BOOLEAN remove(T);
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
BOOLEAN ds::Heap<T>::add(T item)
{
    INT index = this->list_.getCount();
    if(this->list_.add(item))
    {
        INT parentIndex;
        while 
            (
            this->hasParent(index) && 
            this->comparerFunc_(this->comparer_, this->list_[index], this->list_[parentIndex = this->getParentIndex(index)])
            )
        {
            this->swap(index, parentIndex);
            index = parentIndex;
        }
        
        return TRUE;
    }

    return FALSE;
}

template<typename T>
T& ds::Heap<T>::peek()
{
    if(this->list_.getCount() == 0) throw ds::emptyCollectionException();
    
    return this>list_[0];
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
        this->list_.removeAt(lastIndex);

        INT index = 0;
        INT leftIndex;
        while ((leftIndex = this->getLeftChildIndex(index)) < this->list_.getCount())
        {
            INT swapIndex;
            INT rghtIndex = leftIndex + 1;
            if(rghtIndex < this->list_.getCount() && this->comparerFunc_(this->comparer_, this->list_[rghtIndex], this->list_[leftIndex]))
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

            if(!this->comparerFunc_(this->comparer_, this->list_[index], this->list_[swapIndex]))
            {
                this->swap(index, swapIndex);
                index = swapIndex;
            }
            else
            {
                break;
            }
        }

        return top;
    }
    
}


template<typename T>
ds::Heap<T> ds::Heap<T>::createMaxHeap(ds::IComparer<T>* comparer)
{
    ds::Heap<T> heap(comparer);
    heap.comparerFunc_ = [](IComparer<T>* comp, T item, T other) -> BOOLEAN
    { 
        return comp->compare(item, other) >= 0;;
    };

    return heap;
}

template<typename T>
ds::Heap<T> ds::Heap<T>::createMinHeap(ds::IComparer<T>* comparer)
{
    ds::Heap<T> heap(comparer);
    heap.comparerFunc_ = [](IComparer<T>* comp, T item, T other) -> BOOLEAN
    { 
        return comp->compare(item, other) <= 0;;
    };

    return heap;
}

#endif // !_HEAP_H