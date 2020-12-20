/********************************************/
/*                                          */
/*   class file represent a genaric array   */
/*    list with basic search algorithm.     */
/*      by. Ahmed Salem @18-12-2020         */
/*                                          */
/********************************************/

#ifndef _ARRAY_LIST_H
#define _ARRAY_LIST_H

#include <vector>
#include "global.h"
#include "exception.h"

namespace ds
{
    template<typename T>
    class ArrayList
    {
    private:
        INT _size;
        INT _count;
        T* _array;
    private:
        void shiftElements(INT, INT = 1);
    public:
        // construct array with size of 3
        ArrayList<T>();
        ArrayList<T>(INT);
        ArrayList<T>(const ArrayList<T>&);
        ~ArrayList();
    public:
        BOOLEAN add(T);
        BOOLEAN exists(T);
        BOOLEAN remove(T);
        BOOLEAN removeAt(INT);
        T get(INT);

        INT getSize();
        INT getCount();
    };
}



/********************************************/
/*                                          */
/*             implementaions               */
/*                                          */
/********************************************/


template<typename T>
ds::ArrayList<T>::ArrayList()
{
    this->_size  = 3;
    this->_count = 0;
    this->_array = new T[this->_size];
}


template<typename T>
ds::ArrayList<T>::ArrayList(INT size)
{
    if(size < 0) 
        throw ds::exception("NEGATIVE_ARRAY_SIZE_NOT_ALLOWED");

    this->_size  = size;
    this->_count = 0;
    this->_array = new T[this->_size];
}


template<typename T>
ds::ArrayList<T>::ArrayList(const ArrayList<T>& list)
{
    this->_size  = list._size;
    this->_count = list._count;
    this->_array = new T[this->_size];

    for (INT i = 0; i < this->_count; i++)
    {
        this->_array[i] = list._array[i];
    }
}


template<typename T>
ds::ArrayList<T>::~ArrayList()
{
    delete[] _array;
}


template<typename T>
BOOLEAN ds::ArrayList<T>::add(T item)
{
    if(this->_count == this->_size)
    {
        if(this->_size < INT32_MAX)
        {
            // increase array size
            INT increase = this->_size / 10;
            increase = increase > 10 ? increase : 10;

            this->_size += increase;                        // add increase to size
            if(this->_size < 0) this->_size = INT32_MAX;    // check for overflow

            T *temp = this->_array;
            this->_array = new T[this->_size];

            // copy elements from old array to new one
            for (INT i = 0; i < this->_count; i++)
            {
                this->_array[i] = temp[i];
            }
            delete[] temp;
        }
        else 
        {
            return FALSE;
        }
    }

    this->_array[this->_count++] = item;
    return TRUE;
}


template<typename T>
BOOLEAN ds::ArrayList<T>::exists(T item)
{
    for (INT i = 0; i < this->_count; i++)
    {
        if(this->_array[i] == item)
            return TRUE;
    }
    return FALSE;
}


template<typename T>
void ds::ArrayList<T>::shiftElements(INT atIndex, INT shift)
{
    INT count = this->_count - atIndex - shift;  // count till end
    INT shifted = atIndex + shift;               // start shifted index

    for (INT i = 0; i < count; i++)
    {
        this->_array[atIndex + i] = this->_array[shifted + i];
    }
}


template<typename T>
BOOLEAN ds::ArrayList<T>::remove(T item)
{
    for (INT i = 0; i < this->_count; i++)
    {
        if(this->_array[i] == item)
        {
            this->shiftElements(i);
            this->_count--;
            return TRUE;
        }
    }
    
    return FALSE;
}


template<typename T>
BOOLEAN ds::ArrayList<T>::removeAt(INT index)
{
    if(index < 0) throw ds::negativeIndexNotAllowedException();
    if(index >= this->_count) return FALSE;
    
    this->shiftElements(index);
    this->_count--;
    return TRUE;
}


template<typename T>
T ds::ArrayList<T>::get(INT index)
{
    if(index < 0) throw ds::negativeIndexNotAllowedException();
    if(index >= this->_count) throw ds::exception("OUT_OF_RANGE_EXCEPTION");
    
    return this->_array[index];
}


template<typename T>
INT ds::ArrayList<T>::getCount()
{
    return this->_count;
}


template<typename T>
INT ds::ArrayList<T>::getSize()
{
    return this->_size;
}


#endif // !_ARRAY_LIST_H