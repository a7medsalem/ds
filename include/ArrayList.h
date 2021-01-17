/********************************************/
/*                                          */
/*   class file represent a genaric array   */
/*    list with basic search algorithm.     */
/*      by. Ahmed Salem @18-12-2020         */
/*                                          */
/********************************************/

#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_

#include <string>
#include <functional>
#include "global.h"
#include "exception.h"
#include "IString.h"
#include "ICollection.h"

namespace ds
{
    /**
     * Linear data structure to store arbitrary data with dynamic size.
     * @tparam T the type of data stored in the list
     */
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
        void shiftArray(INT atindex, INT shift = 1);
        void shiftRange(INT atindex, INT count, INT shift = 1);
        void reallocate(INT offset = 0);
    public:
        /**
         * Construct a list with default size of 3.
         */
        ArrayList<T>();
        /**
         * Construct a list with size as given.
         * @param size initial size of the list.
         */
        ArrayList<T>(INT size);
        /**
         * Copy constructor for ArrayList.
         * @param list List to be copied.
         */
        ArrayList<T>(const ArrayList<T>& list);
        ~ArrayList();
    public:
        /**
         * Add element to the end of the array, return false if array reached max limit.
         * @param item item to be added.
         * @return boolean to be true if element added to list, otherwise false.
         */
        BOOLEAN add(T item);
        /**
         * Insert element at start of the array, return false if array reached max limit.
         * @param item item to be added.
         * @return boolean to be true if element added to list, otherwise false.
         */
        BOOLEAN insert(T item);
        /**
         * Check if element exists in the list.
         * @param item item to be checked.
         * @return boolean to be true if element exists, otherwise false.
         */
        BOOLEAN contains(T item);

        BOOLEAN removeOne(T);
        BOOLEAN removeOne(std::function<BOOLEAN(const T&)> predicate);
        BOOLEAN removeAll(T);
        BOOLEAN removeAll(std::function<BOOLEAN(const T&)> predicate);
        BOOLEAN removeAt(INT);
        BOOLEAN removeFirst();
        BOOLEAN removeLast();

        T* begin();
        T* end();
        
        T& pop();
        T& get(INT);
        INT getIndexOf(T item);
        void getIndicesOf(T item, INT* &indices, INT &count);

        /**
        * Get size of list.
        * @returns current size of inner array.
        */
        INT getSize();
        /**
        * Get count of elements in the list.
        * @returns count of array elements.
        */
        INT getCount();
        T& operator[](INT);
        
        T* toArray(INT &count) const override;
        std::string toString() override;
    };
}



/********************************************/
/*                                          */
/*                ArrayList                 */
/*                                          */
/********************************************/



/**
 * Construct a list with default size of 3.
 */
template<typename T>
ds::ArrayList<T>::ArrayList()
{
    this->maxSize_  = INT32_MAX;
    this->factor_   = 2;
    this->size_     = 3;
    this->count_    = 0;

    this->array_ = new T[this->size_];
}

/**
 * Construct a list with size as given.
 * @param size initial size of the list.
 */
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
void ds::ArrayList<T>::reallocate(INT offset)
{
    INT newArraySize = this->factor_ * this->size_;                     // size of the new allocation
    if(newArraySize > this->maxSize_ ||  newArraySize < 0)              // check for max size and over flow
        newArraySize = this->maxSize_;                  

    T* newArray = new T[newArraySize];                                  // allocate new array
    memcpy(newArray + offset, this->array_, this->count_ * sizeof(T));  // copy members from old to new array

    this->size_ = newArraySize;                                         // update ArrayList size

    T* temp = this->array_;                                             // keep pointer to old array
    this->array_ = newArray;                                            // make array pointer point to the new allocation
    delete[] temp;                                                      // free old array space
}

template<typename T>
void ds::ArrayList<T>::shiftArray(INT atindex, INT shift)
{
    INT count = this->count_ - atindex - shift;  // count till end
    this->shiftRange(atindex, count, shift);
}

template<typename T>
void ds::ArrayList<T>::shiftRange(INT atindex, INT count, INT shift)
{
    INT shiftIndex = atindex + shift;    // calculate shift index
    memmove(this->array_ + atindex, this->array_ + shiftIndex, count * sizeof(T));
}

template<typename T>
BOOLEAN ds::ArrayList<T>::add(T item)
{
    if(this->count_ == this->size_)
    {
        if(this->size_ < this->maxSize_)
        {
            this->reallocate();
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
BOOLEAN ds::ArrayList<T>::insert(T item)
{
    if(this->count_ == this->size_)
    {
        if(this->size_ < this->maxSize_)
        {
            this->reallocate(1);
        }
        else 
        {
            return FALSE;
        }
    }
    else
    {
        this->shiftRange(1, this->count_, -1);
    }

    this->array_[0] = item;
    this->count_++;
    return TRUE;
}

template<typename T>
BOOLEAN ds::ArrayList<T>::contains(T item)
{
    for (INT i = 0; i < this->count_; i++)
    {
        if(this->array_[i] == item)
            return TRUE;
    }
    
    return FALSE;
}



template<typename T>
BOOLEAN ds::ArrayList<T>::removeOne(T item)
{
    return this->removeOne([item](const T& arrayItem) -> BOOLEAN { return item == arrayItem; });
}


template<typename T>
BOOLEAN ds::ArrayList<T>::removeOne(std::function<BOOLEAN(const T&)> predicate)
{
    for (INT i = 0; i < this->count_; i++)
    {
        if(predicate(this->array_[i]))
        {
            this->shiftArray(i);
            this->count_--;
            return TRUE;
        }
    }
    return FALSE;
}


template<typename T>
BOOLEAN ds::ArrayList<T>::removeAll(T item)
{
    return this->removeAll([item](const T& arrayItem) -> BOOLEAN { return arrayItem == item; });
}


template<typename T>
BOOLEAN ds::ArrayList<T>::removeAll(std::function<BOOLEAN(const T&)> predicate)
{
    INT atindex     = -1;
    INT foundCount  = 0;
    INT voidSize    = 0;

    for (INT i = 0; i < this->count_; i++)
    {
        if(predicate(this->array_[i]))
        {
            foundCount++;
            if(atindex < 0){ atindex = i; continue; }

            this->shiftRange(atindex - voidSize, i - atindex - 1, voidSize + 1);
            atindex = i;
            voidSize++;
        }
    }
    
    if(atindex != this->count_ -1)
    {
        this->shiftArray(atindex - voidSize, voidSize + 1);
    }

    this->count_ -= foundCount;
    return  foundCount > 0 ? TRUE : FALSE;
}

template<typename T>
BOOLEAN ds::ArrayList<T>::removeAt(INT index)
{
    if(index < 0) throw ds::negativeIndexNotAllowedException();
    if(index >= this->count_) return FALSE;
    
    this->shiftArray(index);
    this->count_--;
    return TRUE;
}

template<typename T>
BOOLEAN ds::ArrayList<T>::removeFirst()
{
    return this->removeAt(0);
}

template<typename T>
BOOLEAN ds::ArrayList<T>::removeLast()
{
    // if there was no element, return false
    if(this->count_ == 0) return FALSE;

    this->count_--;
    return TRUE;
}

template<typename T>
INT ds::ArrayList<T>::getIndexOf(T item)
{
    for (INT i = 0; i < this->count_; i++)
    {
        if(this->array_[i] == item)
        {
            return i;
        }
    }
    return -1;
}

template<typename T>
void ds::ArrayList<T>::getIndicesOf(T item, INT* &indices, INT &count)
{
    count = 0;
    INT* found = new INT[this->count_];

    for (INT i = 0; i < this->count_; i++)
    {
        if(this->array_[i] == item)
        {
            found[count++] = i;
        }
    }

    indices = new T[count];
    memcpy(indices, found, count * sizeof(T));
    delete [] found;
}

template<typename T>
T& ds::ArrayList<T>::get(INT index)
{
    if(index < 0) throw ds::negativeIndexNotAllowedException();
    if(index >= this->count_) throw ds::outOfRangeException();
    
    return this->array_[index];
}

template<typename T>
T& ds::ArrayList<T>::pop()
{
    if(this->count_ == 0) throw ds::emptyCollectionException();

    this->count_--;
    return this->array_[this->count_];
}

/**
* Get count of elements in the list.
* @returns Count of array elements.
*/
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
T* ds::ArrayList<T>::toArray(INT &count) const
{
    count = this->count_;

    T* result = new T[count];
    memcpy(result, this->array_, count * sizeof(T));
    
    return result;
}


template<typename T>
T* ds::ArrayList<T>::begin()
{
    return &this->array_[0];
}

template<typename T>
T* ds::ArrayList<T>::end()
{
    return &this->array_[this->count_];
}

#endif // !_ARRAY_LIST_H_