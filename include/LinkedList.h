#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "global.h"
#include "exception.h"
#include "IString.h"
#include "ArrayList.h"

namespace ds
{
    template<typename T>
    class LinkedListNode : public IString
    {
    private:
        T value_;
        LinkedListNode *next_;
    public:
        LinkedListNode<T>(T);
        ~LinkedListNode<T>();
    public:
        //
        T& getValue();
        void setValue(T);
        //
        LinkedListNode* getNext();
        void setNext(LinkedListNode*);
        //
        std::string toString() override;
    };


    template<typename T>
    class LinkedList
    {
    private:
        INT count_;
        LinkedListNode<T> *head_;
        LinkedListNode<T> *tail_;
    private:
        ds::LinkedListNode<T>* getNode(INT);
        ds::LinkedListNode<T>* getHeadNode();
        ds::LinkedListNode<T>* getTailNode();
    public:
        LinkedList<T>();
        LinkedList<T>(ArrayList<T>&);
        ~LinkedList<T>();
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
/*             implementaions               */
/*                                          */
/********************************************/

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

template<typename T>
std::string ds::LinkedListNode<T>::toString()
{
    return "LinkedListNode";
}





template<typename T>
ds::LinkedList<T>::LinkedList()
{
    this->count_ = 0;
    this->head_ = NULL;
    this->tail_ = NULL;
}

template<typename T>
ds::LinkedList<T>::~LinkedList()
{
    while (this->head_)
    {
        ds::LinkedListNode<T> *temp = this->head_;
        this->head_ = this->head_->getNext();
        delete temp;
    }
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
    if(!this->tail_) return FALSE;
    
    ds::LinkedListNode<T>* current = NULL;
    if(this->count_ > 1)
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

    while (current)
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


#endif // !_LINKED_LIST_H_