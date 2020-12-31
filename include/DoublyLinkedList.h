#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "global.h"
#include "exception.h"
#include "IString.h"
#include "ArrayList.h"

namespace ds
{
    template<typename T>
    class DoublyLinkedListNode
    {
    private:
        T value_;
        DoublyLinkedListNode *prev_;
        DoublyLinkedListNode *next_;
    public:
        DoublyLinkedListNode<T>(T);
        ~DoublyLinkedListNode<T>();
    public:
        //
        T& getValue();
        void setValue(T);
        //
        DoublyLinkedListNode* getNext();
        void setNext(DoublyLinkedListNode*);
        DoublyLinkedListNode* getPrev();
        void setPrev(DoublyLinkedListNode*);
    };


    template<typename T>
    class DoublyLinkedList
    {
    private:
        INT count_;
        DoublyLinkedListNode<T> *head_;
        DoublyLinkedListNode<T> *tail_;
    private:
        ds::DoublyLinkedListNode<T>* getNode(INT);
        ds::DoublyLinkedListNode<T>* getHeadNode();
        ds::DoublyLinkedListNode<T>* getTailNode();
    public:
        DoublyLinkedList<T>();
        DoublyLinkedList<T>(ArrayList<T>&);
        ~DoublyLinkedList<T>();
    public:
        BOOLEAN insert(T);
        BOOLEAN add(T);
        BOOLEAN removeAt(INT);
        BOOLEAN removeHead();
        BOOLEAN removeTail();
        T& get(INT);
        void set(INT, T);

        T& getHead();
        T& getTail();

        void reverse();
        INT getCount();
        T& operator[](INT);
    };

}



/********************************************/
/*                                          */
/*          DoublyLinkedListNode            */
/*                                          */
/********************************************/

template<typename T>
ds::DoublyLinkedListNode<T>::DoublyLinkedListNode(T value)
{
    this->next_ = NULL;
    this->prev_ = NULL;
    this->value_ = value;
}

template<typename T>
ds::DoublyLinkedListNode<T>::~DoublyLinkedListNode()
{
    // nothing to destruct
}

template<typename T>
void ds::DoublyLinkedListNode<T>::setNext(DoublyLinkedListNode<T> *nextNode)
{
    this->next_ = nextNode;
}

template<typename T>
ds::DoublyLinkedListNode<T>* ds::DoublyLinkedListNode<T>::getPrev()
{
    return this->prev_;
}

template<typename T>
void ds::DoublyLinkedListNode<T>::setPrev(DoublyLinkedListNode<T> *prevNode)
{
    this->prev_ = prevNode;
}

template<typename T>
ds::DoublyLinkedListNode<T>* ds::DoublyLinkedListNode<T>::getNext()
{
    return this->next_;
}

template<typename T>
void ds::DoublyLinkedListNode<T>::setValue(T value)
{
    this->value_ = value;
}

template<typename T>
T& ds::DoublyLinkedListNode<T>::getValue()
{
    return this->value_;
}






/********************************************/
/*                                          */
/*            DoublyLinkedList              */
/*                                          */
/********************************************/


template<typename T>
ds::DoublyLinkedList<T>::DoublyLinkedList()
{
    this->count_ = 0;
    this->head_ = NULL;
    this->tail_ = NULL;
}

template<typename T>
ds::DoublyLinkedList<T>::~DoublyLinkedList()
{
    while (this->head_)
    {
        ds::DoublyLinkedListNode<T> *temp = this->head_;
        this->head_ = this->head_->getNext();
        delete temp;
    }
}

template<typename T>
BOOLEAN ds::DoublyLinkedList<T>::add(T value)
{
    if(this->count_ == INT32_MAX) return FALSE;
    
    ds::DoublyLinkedListNode<T> *node = new ds::DoublyLinkedListNode<T>(value);
    if(!this->head_)
    {
        this->head_ = node;
        this->tail_ = node;
    }
    else
    {
        node->setPrev(this->tail_);
        this->tail_->setNext(node);
        this->tail_ = node;
    }
    
    this->count_++;
    return TRUE;
}

template<typename T>
BOOLEAN ds::DoublyLinkedList<T>::insert(T value)
{
    if(this->count_ == INT32_MAX) return FALSE;
    
    ds::DoublyLinkedListNode<T> *node = new ds::DoublyLinkedListNode<T>(value);
    if(!this->head_)
    {
        this->head_ = node;
        this->tail_ = node;
    }
    else
    {
        node->setNext(this->head_);
        this->head_->setPrev(node);
        this->head_ = node;
    }
    
    this->count_++;
    return TRUE;
}

template<typename T>
ds::DoublyLinkedListNode<T>* ds::DoublyLinkedList<T>::getNode(INT index)
{
    if(index < 0) throw ds::negativeIndexNotAllowedException();
    if(index >= this->count_) throw ds::outOfRangeException();

    if(index == 0) return this->head_;
    if(index == this->count_ - 1) return this->tail_;

    INT counter;
    ds::DoublyLinkedListNode<T> *current = NULL;
    if(index < 0.5 * this->count_)
    {
        counter = 0;
        current = this->head_;
        while (counter != index)
        {
            current = current->getNext();
            counter++;
        }
    }
    else
    {
        counter = this->count_ - 1;
        current = this->tail_;
        while (counter != index)
        {
            current = current->getPrev();
            counter--;
        }
    }
    
    return current;
}

template<typename T>
ds::DoublyLinkedListNode<T>* ds::DoublyLinkedList<T>::getHeadNode()
{
    return this->head_;
}

template<typename T>
ds::DoublyLinkedListNode<T>* ds::DoublyLinkedList<T>::getTailNode()
{
    return this->tail_;
}

template<typename T>
BOOLEAN ds::DoublyLinkedList<T>::removeAt(INT index)
{
    if(index < 0) throw ds::negativeIndexNotAllowedException();
    if(index >= this->count_) throw ds::outOfRangeException();

    if(index == 0) return this->removeHead();
    if(index == this->count_ - 1) return this->removeTail();

    ds::DoublyLinkedListNode<T> *target = this->getNode(index);
    target->getPrev()->setNext(target->getNext());
    target->getNext()->setPrev(target->getPrev());
    
    this->count_--;
    delete target;
    return TRUE;
}

template<typename T>
BOOLEAN ds::DoublyLinkedList<T>::removeHead()
{
    if(!this->head_) return FALSE;

    ds::DoublyLinkedListNode<T>* temp = this->head_;
    this->head_ = this->head_->getNext();               
    if(this->head_) this->head_->setPrev(NULL);         // in-case of on node head will be null
    delete temp;

    this->count_--;
    if(this->count_ == 0) this->tail_ = this->head_ = NULL;
    return TRUE;
}

template<typename T>
BOOLEAN ds::DoublyLinkedList<T>::removeTail()
{
    if(!this->tail_) return FALSE;
    
    ds::DoublyLinkedListNode<T>* oldTail = this->tail_;
    this->tail_ = this->tail_->getPrev();
    if(this->tail_) this->tail_->setNext(NULL);

    this->count_--;
    delete oldTail;
    if(this->count_ == 0) this->tail_ = this->head_ = NULL;
    return TRUE;
}

template<typename T>
T& ds::DoublyLinkedList<T>::get(INT index)
{
    return this->getNode(index)->getValue();
}

template<typename T>
T& ds::DoublyLinkedList<T>::getHead()
{
    if(!this->head_) throw ds::emptyCollectionException();
    return this->head_->getValue();
}

template<typename T>
T& ds::DoublyLinkedList<T>::getTail()
{
    if(!this->tail_) throw ds::emptyCollectionException();
    return this->tail_->getValue();
}

template<typename T>
void ds::DoublyLinkedList<T>::set(INT index, T value)
{
    this->getNode(index)->setValue(value);
}

template<typename T>
void ds::DoublyLinkedList<T>::reverse()
{
    if(!this->head_) return;

    ds::DoublyLinkedListNode<T>* current = this->head_;
    ds::DoublyLinkedListNode<T>* next = NULL;
    ds::DoublyLinkedListNode<T>* prev = NULL;

    while (current)
    {
        // store next node
        next = current->getNext();
        // set current next as previous one
        current->setNext(prev);
        current->setPrev(next);

        prev    = current;
        current = next;
    }
    
    this->tail_ = this->head_;
    this->head_ = prev;
}

template<typename T>
INT ds::DoublyLinkedList<T>::getCount()
{
    return this->count_;
}


template<typename T>
T& ds::DoublyLinkedList<T>::operator[](INT index)
{
    return this->get(index);
}


#endif // !_LINKED_LIST_H_