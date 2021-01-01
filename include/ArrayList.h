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
#include <cmath>
#include "global.h"
#include "exception.h"
#include "IString.h"
#include "ICollection.h"

namespace ds
{
    template<typename T>
    class ArrayList : public ds::IString, public ds::ICollection<T>
    {
    private:
        INT factor_;
        INT maxSize_;
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
        T& get(INT);

        INT getSize();
        INT getCount();
        T& operator[](INT);
        
        T* toArray() const override;
        std::string toString() override;
    };
}



/********************************************/
/*                                          */
/*                ArrayList                 */
/*                                          */
/********************************************/



template<typename T>
ds::ArrayList<T>::ArrayList()
{
    this->maxSize_  = INT32_MAX;
    this->factor_   = 2;
    this->size_     = 3;
    this->count_    = 0;

    this->array_ = new T[this->size_];
}


template<typename T>
ds::ArrayList<T>::ArrayList(INT size)
{
    if(size < 0) 
        throw ds::exception("NEGATIVE_ARRAY_SIZE_NOT_ALLOWED");

    this->maxSize_  = INT32_MAX;
    this->factor_   = 2;
    this->size_     = size;
    this->count_    = 0;

    this->array_ = new T[this->size_];
}


template<typename T>
ds::ArrayList<T>::ArrayList(const ArrayList<T>& list)
{
    this->maxSize_  = list.maxSize_;
    this->factor_   = list.factor_;
    this->size_     = list.size_;
    this->count_    = list.count_;

    this->array_ = new T[this->size_];
    memcpy(this->array_, list.array_, this->count_ * sizeof(T));    
}


template<typename T>
ds::ArrayList<T>::~ArrayList()
{
    delete[] this->array_;
}


template<typename T>
BOOLEAN ds::ArrayList<T>::add(T item)
{
    if(this->count_ == this->size_)
    {
        if(this->size_ < this->maxSize_)
        {
            INT newArraySize = this->factor_ * this->size_;                 // size of the new allocation
            if(newArraySize > this->maxSize_ ||  newArraySize < 0)          // check for max size and over flow
                newArraySize = this->maxSize_;                  

            T* newArray = new T[newArraySize];                              // allocate new array
            memcpy(newArray, this->array_, this->count_ * sizeof(T));       // copy members from old to new array

            this->size_ = newArraySize;                                     // update ArrayList size

            T* temp = this->array_;                                         // keep pointer to old array
            this->array_ = newArray;                                        // make array pointer point to the new allocation
            delete[] temp;                                                  // free old array space
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
T& ds::ArrayList<T>::get(INT index)
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
T& ds::ArrayList<T>::operator[](INT index)
{
    return this->get(index);
}




// IString implementation
template<typename T>
std::string ds::ArrayList<T>::toString()
{
    return "ArrayList of " + std::to_string(this->count_) + " elements, with size of " + std::to_string(this->size_);
}

// ICollection implementaion
template<typename T>
T* ds::ArrayList<T>::toArray() const
{
    T* result = new T[this->count_];
    memcpy(result, this->array_, this->count_ * sizeof(T));
    
    return result;
}


#endif // !_ARRAY_LIST_H_