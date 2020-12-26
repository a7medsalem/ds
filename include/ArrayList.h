/********************************************/
/*                                          */
/*   class file represent a genaric array   */
/*    list with basic search algorithm.     */
/*      by. Ahmed Salem @18-12-2020         */
/*                                          */
/********************************************/

#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_

#include <vector>
#include <string>
#include "global.h"
#include "exception.h"
#include "IString.h"

namespace ds
{
    template<typename T>
    class ArrayList : public ds::IString
    {
    private:
        INT size_;
        INT count_;
        T* array_;
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
        std::string toString() override;

        T& operator[](INT);
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
    this->size_  = 3;
    this->count_ = 0;
    this->array_ = new T[this->size_];
}


template<typename T>
ds::ArrayList<T>::ArrayList(INT size)
{
    if(size < 0) 
        throw ds::exception("NEGATIVE_ARRAY_SIZE_NOT_ALLOWED");

    this->size_  = size;
    this->count_ = 0;
    this->array_ = new T[this->size_];
}


template<typename T>
ds::ArrayList<T>::ArrayList(const ArrayList<T>& list)
{
    this->size_  = list.size_;
    this->count_ = list.count_;
    this->array_ = new T[this->size_];

    for (INT i = 0; i < this->count_; i++)
    {
        this->array_[i] = list.array_[i];
    }
}


template<typename T>
ds::ArrayList<T>::~ArrayList()
{
    delete[] array_;
}


template<typename T>
BOOLEAN ds::ArrayList<T>::add(T item)
{
    if(this->count_ == this->size_)
    {
        if(this->size_ < INT32_MAX)
        {
            // increase array size
            INT increase = this->size_ / 10;
            increase = increase > 10 ? increase : 10;

            this->size_ += increase;                        // add increase to size
            if(this->size_ < 0) this->size_ = INT32_MAX;    // check for overflow

            T *temp = this->array_;
            this->array_ = new T[this->size_];

            // copy elements from old array to new one
            for (INT i = 0; i < this->count_; i++)
            {
                this->array_[i] = temp[i];
            }
            delete[] temp;
        }
        else 
        {
            return FALSE;
        }
    }

    this->array_[this->count_++] = item;
    return TRUE;
}


template<typename T>
BOOLEAN ds::ArrayList<T>::exists(T item)
{
    for (INT i = 0; i < this->count_; i++)
    {
        if(this->array_[i] == item)
            return TRUE;
    }
    return FALSE;
}


template<typename T>
void ds::ArrayList<T>::shiftElements(INT atIndex, INT shift)
{
    INT count = this->count_ - atIndex - shift;  // count till end
    INT shifted = atIndex + shift;               // start shifted index

    for (INT i = 0; i < count; i++)
    {
        this->array_[atIndex + i] = this->array_[shifted + i];
    }
}


template<typename T>
BOOLEAN ds::ArrayList<T>::remove(T item)
{
    for (INT i = 0; i < this->count_; i++)
    {
        if(this->array_[i] == item)
        {
            this->shiftElements(i);
            this->count_--;
            return TRUE;
        }
    }
    
    return FALSE;
}


template<typename T>
BOOLEAN ds::ArrayList<T>::removeAt(INT index)
{
    if(index < 0) throw ds::negativeIndexNotAllowedException();
    if(index >= this->count_) return FALSE;
    
    this->shiftElements(index);
    this->count_--;
    return TRUE;
}


template<typename T>
T ds::ArrayList<T>::get(INT index)
{
    if(index < 0) throw ds::negativeIndexNotAllowedException();
    if(index >= this->count_) throw ds::outOfRangeException();
    
    return this->array_[index];
}


template<typename T>
INT ds::ArrayList<T>::getCount()
{
    return this->count_;
}


template<typename T>
INT ds::ArrayList<T>::getSize()
{
    return this->size_;
}


template<typename T>
std::string ds::ArrayList<T>::toString()
{
    return "ArrayList of " + std::to_string(this->count_) + " elements, with size of " + std::to_string(this->size_);
}

template<typename T>
T& ds::ArrayList<T>::operator[](INT index)
{
    if(index < 0) throw ds::negativeIndexNotAllowedException();
    if(index >= this->count_) throw ds::outOfRangeException();

    return this->array_[index];
}

#endif // !_ARRAY_LIST_H_