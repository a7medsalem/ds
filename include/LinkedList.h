#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <functional>
#include "global.h"
#include "exception.h"
#include "IString.h"
#include "ArrayList.h"

namespace ds
{
    template<typename T>
    class LinkedListNode
    {
    private:
        T value_;
        LinkedListNode *next_;
    public:
        LinkedListNode<T>();
        LinkedListNode<T>(T value);
        ~LinkedListNode<T>();
    public:
        //
        T& getValue();
        void setValue(T value);
        //
        LinkedListNode* getNext();
        void setNext(LinkedListNode* node);
    };


    template<typename T>
    class LinkedList : public ds::ICollection<T>
    {
    private:
        INT count_;
        LinkedListNode<T> *head_;
        LinkedListNode<T> *tail_;
        LinkedListNode<T> *outOfRange_;
    private:
        ds::LinkedListNode<T>* getNode(INT index);
        ds::LinkedListNode<T>* getHeadNode();
        ds::LinkedListNode<T>* getTailNode();
    public:
        LinkedList<T>();
        LinkedList<T>(ArrayList<T>& list);
        ~LinkedList<T>();
    public:
        BOOLEAN insert(T item);
        BOOLEAN add(T item);
        BOOLEAN contains(T item) const;
        BOOLEAN contains(std::function<BOOLEAN(const T&)> predicate) const;
        
        BOOLEAN findFirst(std::function<BOOLEAN(const T&)> predicate, T &result) const;
        BOOLEAN findAll(std::function<BOOLEAN(const T&)> predicate, T* &result, INT &count) const;

        BOOLEAN removeFirst(T item);
        BOOLEAN removeFirst(std::function<BOOLEAN(const T&)> predicate);
        BOOLEAN removeAll(T item);
        BOOLEAN removeAll(std::function<BOOLEAN(const T&)> predicate);
        BOOLEAN removeAt(INT index);
        BOOLEAN removeHead();
        BOOLEAN removeTail();

        void set(INT index, T value);

        T& get(INT index);
        T& getHead();
        T& getTail();
        T& operator[](INT index);
        INT getCount();

        void reverse();
        T* toArray(INT &count) const override;
    public:
        template<typename IType>
        struct Iterator
        {
        private:
            LinkedListNode<IType>* ptr_;
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = IType;
            using pointer           = IType*;
            using reference         = IType&;
        public:
            Iterator(LinkedListNode<IType>* ptr) : ptr_(ptr) {}
        public:
            IType& operator*() const { return this->ptr_->getValue(); }
            IType* operator->() { return &this->ptr_->getValue(); }
            // Prefix increment
            Iterator& operator++() { this->ptr_ = this->ptr_->getNext(); return *this; }  
            // Postfix increment
            Iterator operator++(INT) 
            { 
                Iterator temp = *this; 
                ++(*this);
                return temp; 
            }
            operator IType() 
            {
                return this->ptr_->getValue();
            }
            friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr_ == b.ptr_; };
            friend bool operator== (const Iterator& a, const IType& b) { return a.ptr_->getValue() == b; };
            friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr_ != b.ptr_; };  
            friend bool operator!= (const Iterator& a, const IType& b) { return a.ptr_->getValue() != b; };
        };
        
        Iterator<T> begin();
        Iterator<T> end();
    };

}

/********************************************/
/*                                          */
/*             LinkedListNode               */
/*                                          */
/********************************************/


template<typename T>
ds::LinkedListNode<T>::LinkedListNode()
{
    this->next_ = NULL;
}

template<typename T>
ds::LinkedListNode<T>::LinkedListNode(T value)
{
    this->next_ = NULL;
    this->value_ = value;
}

template<typename T>
ds::LinkedListNode<T>::~LinkedListNode()
{
    // nothing to destruct
}

template<typename T>
void ds::LinkedListNode<T>::setNext(LinkedListNode<T> *nextNode)
{
    this->next_ = nextNode;
}

template<typename T>
ds::LinkedListNode<T>* ds::LinkedListNode<T>::getNext()
{
    return this->next_;
}

template<typename T>
void ds::LinkedListNode<T>::setValue(T value)
{
    this->value_ = value;
}

template<typename T>
T& ds::LinkedListNode<T>::getValue()
{
    return this->value_;
}



/********************************************/
/*                                          */
/*               LinkedList                 */
/*                                          */
/********************************************/


template<typename T>
ds::LinkedList<T>::LinkedList()
{
    this->count_ = 0;
    this->head_ = NULL;
    this->tail_ = NULL;
    this->outOfRange_ = new ds::LinkedListNode<T>();
}

template<typename T>
ds::LinkedList<T>::~LinkedList()
{
    ds::LinkedListNode<T>* current = this->head_;
    while (current && current != this->outOfRange_)
    {
        ds::LinkedListNode<T> *temp = current;
        current = current->getNext();
        delete temp;
    }
    if(this->outOfRange_) delete this->outOfRange_;
}

template<typename T>
BOOLEAN ds::LinkedList<T>::add(T value)
{
    if(this->count_ == INT32_MAX) return FALSE;
    
    ds::LinkedListNode<T> *node = new ds::LinkedListNode<T>(value);
    if(!this->head_)
    {
        this->head_ = node;
        this->tail_ = node;
    }
    else
    {
        this->tail_->setNext(node);
        this->tail_ = node;
    }
    
    this->tail_->setNext(this->outOfRange_);
    this->count_++;
    return TRUE;
}

template<typename T>
BOOLEAN ds::LinkedList<T>::insert(T value)
{
    if(this->count_ == INT32_MAX) return FALSE;
    
    ds::LinkedListNode<T> *node = new ds::LinkedListNode<T>(value);
    if(!this->head_)
    {
        this->head_ = node;
        this->tail_ = node;
        this->tail_->setNext(this->outOfRange_);
    }
    else
    {
        node->setNext(this->head_);
        this->head_ = node;
    }
    
    this->count_++;
    return TRUE;
}

template<typename T>
BOOLEAN ds::LinkedList<T>::contains(T item) const
{
    ds::LinkedListNode<T> *current = this->head_;
    while (current && current != this->outOfRange_)
    {
        if(current->getValue() == item) return TRUE;
        current = current->getNext();
    }

    return FALSE;
}

template<typename T>
BOOLEAN ds::LinkedList<T>::contains(std::function<BOOLEAN(const T&)> predicate) const
{
    ds::LinkedListNode<T> *current = this->head_;
    while (current && current != this->outOfRange_)
    {
        if(predicate(current->getValue())) return TRUE;
        current = current->getNext();
    }

    return FALSE;
}


template<typename T>
BOOLEAN ds::LinkedList<T>::findFirst(std::function<BOOLEAN(const T&)> predicate, T &result) const
{
    ds::LinkedListNode<T> *current = this->head_;
    while (current && current != this->outOfRange_)
    {
        if(predicate(current->getValue()))
        {
            result = current->getValue();
            return TRUE;
        }
        current = current->getNext();
    }
    return FALSE;
}

template<typename T>
BOOLEAN ds::LinkedList<T>::findAll(std::function<BOOLEAN(const T&)> predicate, T* &resultArray, INT &count) const
{
    count = 0;
    T *temp = new T[this->count_];

    ds::LinkedListNode<T> *current = this->head_;
    while (current && current != this->outOfRange_)
    {
        if(predicate(current->getValue()))
        {
            temp[count++] = current->getValue();
        }
        current = current->getNext();
    }

    if(count == 0) return FALSE;
    else
    {
        resultArray = new T[count];
        INT size = count * sizeof(T);
        memcpy(resultArray, temp, size);
        delete [] temp;
        return TRUE;
    }
    
}

template<typename T>
ds::LinkedListNode<T>* ds::LinkedList<T>::getNode(INT index)
{
    if(index < 0) throw ds::negativeIndexNotAllowedException();
    if(index >= this->count_) throw ds::outOfRangeException();

    if(index == 0) return this->head_;
    if(index == this->count_ - 1) return this->tail_;

    INT counter = 0;
    ds::LinkedListNode<T> *current = this->head_;
    while (counter != index)
    {
        current = current->getNext();
        counter++;
    }
    
    return current;
}

template<typename T>
ds::LinkedListNode<T>* ds::LinkedList<T>::getHeadNode()
{
    return this->head_;
}

template<typename T>
ds::LinkedListNode<T>* ds::LinkedList<T>::getTailNode()
{
    return this->tail_;
}

template<typename T>
BOOLEAN ds::LinkedList<T>::removeFirst(T item)
{
    return this->removeFirst([item](const T& listItem) -> BOOLEAN { return item == listItem; });
}

template<typename T>
BOOLEAN ds::LinkedList<T>::removeAll(T item)
{
    return this->removeAll([item](const T& listItem) -> BOOLEAN { return item == listItem; });
}

template<typename T>
BOOLEAN ds::LinkedList<T>::removeFirst(std::function<BOOLEAN(const T&)> predicate)
{
    if(count_ == 0) return FALSE;
    if(predicate(this->head_->getValue())) return this->removeHead();
    
    ds::LinkedListNode<T>* prev = this->head_;
    ds::LinkedListNode<T>* current = this->head_->getNext();
    while (current && current != this->outOfRange_)
    {
        if(predicate(current->getValue()))
        {
            prev->setNext(current->getNext());
            if(current == this->tail_) this->tail_ = prev;
            delete current;
            
            this->count_--;
            return TRUE;
        }
        else
        {
            prev = current;
            current = current->getNext();
        }
    }

    return FALSE;
}


template<typename T>
BOOLEAN ds::LinkedList<T>::removeAll(std::function<BOOLEAN(const T&)> predicate)
{
    BOOLEAN removed = FALSE;
    if(count_ == 0) return removed;

    while (this->count_ > 0 && predicate(this->head_->getValue()))
    {
        this->removeHead();
        removed = TRUE;
    }
    
    ds::LinkedListNode<T>* prev = this->head_;
    ds::LinkedListNode<T>* current = prev ? this->head_->getNext() : NULL;
    while (current && current != this->outOfRange_)
    {
        if(predicate(current->getValue()))
        {
            ds::LinkedListNode<T>* target = current;
            prev->setNext(current->getNext());
            current = current->getNext();
            
            if(target == this->tail_) this->tail_ = prev;
            delete target;
            this->count_--;
            removed = TRUE;
        }
        else
        {
            prev = current;
            current = current->getNext();
        }
    }

    return removed;
}


template<typename T>
BOOLEAN ds::LinkedList<T>::removeAt(INT index)
{
        
    if(index < 0) throw ds::negativeIndexNotAllowedException();
    if(index >= this->count_) throw ds::outOfRangeException();

    if(index == 0) return this->removeHead();
    if(index == this->count_ - 1) return this->removeTail();

    INT counter = 0;
    ds::LinkedListNode<T> *prev = this->head_;
    while (counter != index - 1)
    {
        prev = prev->getNext();
        counter++;
    }
    
    ds::LinkedListNode<T>* target = prev->getNext();
    prev->setNext(target->getNext());
    
    this->count_--;
    delete target;
    return TRUE;
}

template<typename T>
BOOLEAN ds::LinkedList<T>::removeHead()
{
    if(!this->head_) return FALSE;

    ds::LinkedListNode<T>* temp = this->head_;
    this->head_ = this->head_->getNext();
    delete temp;

    this->count_--;
    if(this->count_ == 0) this->tail_ = this->head_ = NULL;
    return TRUE;
}

template<typename T>
BOOLEAN ds::LinkedList<T>::removeTail()
{
    if(!this->tail_) return FALSE;                              // if there were no tail, return
    
    ds::LinkedListNode<T>* current = NULL;
    if(this->count_ > 1)                                        // if count more than 1 element, loop till get prev element to tail
    {
        current = this->head_;
        while (current->getNext() != this->tail_)
        {
            current = current->getNext();
        }
        current->setNext(NULL);
    }
    
    this->count_--;
    delete this->tail_;
    this->tail_ = current;
    if(this->count_ == 0) this->tail_ = this->head_ = NULL;
    if(this->tail_) this->tail_->setNext(this->outOfRange_);
    return TRUE;
}

template<typename T>
T& ds::LinkedList<T>::get(INT index)
{
    return this->getNode(index)->getValue();
}

template<typename T>
T& ds::LinkedList<T>::getHead()
{
    if(!this->head_) throw ds::emptyCollectionException();
    return this->head_->getValue();
}

template<typename T>
T& ds::LinkedList<T>::getTail()
{
    if(!this->tail_) throw ds::emptyCollectionException();
    return this->tail_->getValue();
}

template<typename T>
void ds::LinkedList<T>::set(INT index, T value)
{
    this->getNode(index)->setValue(value);
}

template<typename T>
void ds::LinkedList<T>::reverse()
{
    if(!this->head_) return;

    ds::LinkedListNode<T>* current = this->head_;
    ds::LinkedListNode<T>* next = NULL;
    ds::LinkedListNode<T>* prev = NULL;

    while (current && current != this->outOfRange_)
    {
        // store next node
        next = current->getNext();
        // set current next as previous one
        current->setNext(prev);

        prev    = current;
        current = next;
    }
    
    this->tail_ = this->head_;
    this->head_ = prev;
    if(this->tail_) this->tail_->setNext(this->outOfRange_);
}

template<typename T>
INT ds::LinkedList<T>::getCount()
{
    return this->count_;
}


template<typename T>
T& ds::LinkedList<T>::operator[](INT index)
{
    return this->get(index);
}

template<typename T>
T* ds::LinkedList<T>::toArray(INT &count) const
{
    count = this->count_;
    T* array = new T[count];
    if(count == 0) return array;

    ds::LinkedListNode<T>* current = this->head_;
    INT counter = 0;
    while (current && current != this->outOfRange_)
    {
        array[counter++] = current->getValue();
        current = current->getNext();
    }
    
    return array;
}

template<typename T>
ds::LinkedList<T>::Iterator<T> ds::LinkedList<T>::begin()
{
    return ds::LinkedList<T>::Iterator<T>(this->head_);
}

template<typename T>
ds::LinkedList<T>::Iterator<T> ds::LinkedList<T>::end()
{
    return ds::LinkedList<T>::Iterator<T>(this->outOfRange_);
}

#endif // !_LINKED_LIST_H_