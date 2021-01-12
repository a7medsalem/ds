#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <string.h>
#include "global.h"
#include "LinkedList.h"


namespace ds
{
    template<typename K, typename V>
    struct KeyValuePair
    {
    public:
        K key;
        V value;
    public:
        KeyValuePair();
        KeyValuePair(K key, V value);
        KeyValuePair(const KeyValuePair<K,V>& pair);
    };

    template<typename K, typename V>
    struct KeyValuePairProxy 
    {
        LinkedList<KeyValuePair<K,V>>* list;
        KeyValuePair<K,V> pair;
        KeyValuePairProxy(LinkedList<KeyValuePair<K,V>>* list, KeyValuePair<K,V> pair)
        {
            this->list = list;
            this->pair = pair;
        }

        operator V() 
        {
            return this->pair.value;
        }
        V& operator=(const V& other) 
        {
            K key = this->pair.key;
            this->pair = ds::KeyValuePair<K,V>(key, other);

            list->removeFirst([key](const ds::KeyValuePair<K,V> item) -> BOOLEAN { return item.key == key; });
            list->add(this->pair);
            return this->pair.value;
        }
   };

    template<typename K, typename V>
    class HashTable
    {
    private:
        INT size_;
        INT count_;
        INT sizeLimit_;
        INT maxSubCount_;
        INT subCountLimit_;
        LinkedList<KeyValuePair<K,V>>* *array_;
    private:
        INT hash(K key);
        void updateSubCount(INT count);
        void expand();
        void shrink();
    public:
        HashTable<K,V>();
        HashTable<K,V>(INT);
        ~HashTable<K,V>();
    public:
        BOOLEAN add(K,V);
        BOOLEAN hasKey(K);
        BOOLEAN remove(K);
        
        V& get(K);
        ds::KeyValuePairProxy<K,V> operator[](K key);
        INT getCount();
        KeyValuePair<K,V>* toArray(INT &count);
    };
    


    template<typename KeyType>
    struct Hash
    {
        static INT getHash(INT size, KeyType key)
        {
            return key % size;
        }
    };

    #include <cstdint>
    template<typename KeyType>
    struct Hash<KeyType*>
    {
        static INT getHash(INT size, KeyType* key)
        {
            std::uintptr_t integer = reinterpret_cast<std::uintptr_t>(key);
            return integer % size;
        }
    };

    template<>
    struct Hash<INT>
    {
        static INT getHash(INT size, INT key)
        {
            return key % size;
        }
    };

    template<>
    struct Hash<char*>
    {
        static INT getHash(INT size, char* key)
        {
            INT sum = 0;
            INT counter = 0;
            while (key[counter] != '\0')
            {
                sum += key[counter];
                counter++;
            }
            
            return sum % size;
        }
    };

    template<>
    struct Hash<const char*>
    {
        static INT getHash(INT size, const char* key)
        {
            INT sum = 0;
            INT counter = 0;
            while (key[counter] != '\0')
            {
                sum += key[counter];
                counter++;
            }
            
            return sum % size;
        }
    };

    template<>
    struct Hash<std::string>
    {
        static INT getHash(INT size, std::string key)
        {
            return Hash<const char*>::getHash(size, key.c_str());
        }
    };
}



template<typename K, typename V>
inline BOOLEAN operator==(const ds::KeyValuePairProxy<K,V>& lhs, const V& rhs)
{
    return lhs.pair.value == rhs;
}




/********************************************/
/*                                          */
/*              KeyValuePair                */
/*                                          */
/********************************************/

template<typename K, typename V>
ds::KeyValuePair<K,V>::KeyValuePair() : key(), value()
{
}

template<typename K, typename V>
ds::KeyValuePair<K,V>::KeyValuePair(K key, V value)
{
    this->key   = key;
    this->value = value;
}

template<typename K, typename V>
ds::KeyValuePair<K,V>::KeyValuePair(const ds::KeyValuePair<K,V> &pair)
{
    this->key   = pair.key;
    this->value = pair.value;
}



/********************************************/
/*                                          */
/*               HashTable                  */
/*                                          */
/********************************************/



template<typename K, typename V>
void ds::HashTable<K,V>::updateSubCount(INT count)
{
    if(count > this->maxSubCount_) this->maxSubCount_ = count;
}

template<typename K, typename V>
void ds::HashTable<K,V>::expand()
{
    INT oldSize = this->size_;
    this->size_ *= 10;
    if(this->size_ < 0) this->size_ = 1e9;

    if(size_ == oldSize) return;

    LinkedList<KeyValuePair<K,V>>** temp = this->array_;
    this->array_ = new LinkedList<KeyValuePair<K,V>>**[this->size_];

    for (INT i = 0; i < oldSize; i++)
    {
        if(temp[i] != NULL)
        {
            // move to new one
            delete temp[i];
        }
    }
    delete [] temp;
}



template<typename K, typename V>
ds::HashTable<K,V>::HashTable()
{
    this->size_  = 1e3;
    this->count_ = 0;
    this->sizeLimit_ = INT32_MAX;
    this->maxSubCount_ = 0;
    this->subCountLimit_ = this->size_ / 100;

    this->array_ = new LinkedList<ds::KeyValuePair<K,V>>*[this->size_];
    for (INT i = 0; i < this->size_; i++)
    {
        this->array_[i] = NULL;
    }
}

template<typename K, typename V>
ds::HashTable<K,V>::HashTable(INT initialSize)
{
    this->size_  = initialSize;
    this->count_ = 0;
    this->sizeLimit_ = INT32_MAX;
    this->maxSubCount_ = 0;
    this->subCountLimit_ = this->size_ / 100 > 5 ? this->size_ / 100 : 5;

    this->array_ = new LinkedList<ds::KeyValuePair<K,V>>*[this->size_];
    for (INT i = 0; i < this->size_; i++)
    {
        this->array_[i] = NULL;
    }
}

template<typename K, typename V>
ds::HashTable<K,V>::~HashTable()
{
    for (INT i = 0; i < this->size_; i++)
    {
        if(this->array_[i]) delete this->array_[i];
    }
    delete [] this->array_;
}


template<typename K, typename V>
INT ds::HashTable<K,V>::hash(K key)
{
    return ds::Hash<K>::getHash(this->size_, key);
}

template<typename K, typename V>
BOOLEAN ds::HashTable<K,V>::hasKey(K key)
{
    INT hashed = this->hash(key);
    if(this->array_[hashed] == NULL) return FALSE;

    return this->array_[hashed]->exists( [key](const ds::KeyValuePair<K,V> &item) -> BOOLEAN { return item.key == key; } );
}

template<typename K, typename V>
BOOLEAN ds::HashTable<K,V>::add(K key, V value)
{
    //if(this->maxSubCount_ > this->subCountLimit_) this->expand();

    INT hashed = this->hash(key);
    if(this->array_[hashed] == NULL)
    {
        this->array_[hashed] = new ds::LinkedList<ds::KeyValuePair<K,V>>();
    }
    else
    {
        if(this->array_[hashed]->exists( [key](const ds::KeyValuePair<K,V> &pair) -> BOOLEAN { return pair.key == key; } )/*exists*/ )/*if*/
            throw ds::exception("KEY_ALREADY_EXISTS");
    }
    
    this->array_[hashed]->add(ds::KeyValuePair<K,V>(key, value));
    this->count_++;


    this->updateSubCount(this->array_[hashed]->getCount());
    return TRUE;
}

template<typename K, typename V>
BOOLEAN ds::HashTable<K,V>::remove(K key)
{
    INT hashed = this->hash(key);
    if(this->array_[hashed] == NULL) return FALSE;

    BOOLEAN removed = this
                        ->array_[hashed]
                        ->removeFirst([key](const ds::KeyValuePair<K,V> &pair) -> BOOLEAN { return pair.key == key; });

    if(removed) 
    {
        this->count_--;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
}

template<typename K, typename V>
V& ds::HashTable<K,V>::get(K key)
{
    INT hashed = this->hash(key);
    if(this->array_[hashed] == NULL) throw ds::keyNotFoundException();

    static KeyValuePair<K,V> result;
    if(this->array_[hashed]->findFirst([key](const ds::KeyValuePair<K,V> &pair) -> BOOLEAN { return pair.key == key; }, result))
    {
        return result.value;
    }
    else
    {
        throw ds::keyNotFoundException();
    }
    
}

template<typename K, typename V>
ds::KeyValuePairProxy<K,V> ds::HashTable<K,V>::operator[](K key)
{
    INT hashed = this->hash(key);
    if(this->array_[hashed] == NULL) throw ds::keyNotFoundException();

    KeyValuePair<K,V> result;
    if(this->array_[hashed]->findFirst([key](const ds::KeyValuePair<K,V> &pair) -> BOOLEAN { return pair.key == key; }, result))
    {
        return ds::KeyValuePairProxy<K,V>(this->array_[hashed], result);
    }
    else
    {
        throw ds::keyNotFoundException();
    }
}


template<typename K, typename V>
INT ds::HashTable<K,V>::getCount()
{
    return this->count_;
}


template<typename K, typename V>
ds::KeyValuePair<K,V>* ds::HashTable<K,V>::toArray(INT &count)
{
    count = this->count_;
    ds::KeyValuePair<K,V>* pairs = new ds::KeyValuePair<K,V>[count];

    INT counter = 0;
    for (INT i = 0; i < this->size_; i++)
    {
        if(this->array_[i] == NULL) continue;

        INT linkedCount = 0;
        ds::KeyValuePair<K,V>* linekedArray = this->array_[i]->toArray(linkedCount);
        for (INT j = 0; j < linkedCount; j++)
        {
            pairs[counter++] = linekedArray[j];
        }
        delete[] linekedArray;
    }
    
    return pairs;
}

#endif // !_HASH_TABLE_H