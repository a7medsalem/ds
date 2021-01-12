#include "Trie.h"



/********************************************/
/*                                          */
/*               Trie Node                  */
/*                                          */
/********************************************/


ds::TrieNode::TrieNode(char character, BOOLEAN isCompleteWord) : children_(10)
{
    this->character_ = character;
    this->isCompleteWord_ = isCompleteWord;
}

ds::TrieNode::~TrieNode()
{
    // loop over children and delete them
}


ds::TrieNode* ds::TrieNode::addChild(char character, BOOLEAN isCompleteWord)
{
    if(this->children_.hasKey(character))
    {
        return this->children_[character];
    }
    else
    {
        ds::TrieNode* node = new ds::TrieNode(character, isCompleteWord);
        this->children_.add(character, node);
        
        return node;
    }
}

BOOLEAN ds::TrieNode::hasChild(char character)
{
    return this->children_.hasKey(character);
}

BOOLEAN ds::TrieNode::removeChild(char character)
{
    if(!this->children_.hasKey(character)) return FALSE;

    ds::TrieNode* child = this->children_[character];
    delete child;

    return this->children_.remove(character);
}

ds::TrieNode* ds::TrieNode::getChild(char character)
{
    if(!this->children_.hasKey(character)) return NULL;
    return this->children_[character];
}


void ds::TrieNode::setCompleteWord(BOOLEAN isCompleteWord)
{
    this->isCompleteWord_ = isCompleteWord;
}

BOOLEAN ds::TrieNode::isCompleteWord()
{
    return this->isCompleteWord_;
}

BOOLEAN ds::TrieNode::hasChildren()
{
    return this->children_.getCount() != 0;
}

INT ds::TrieNode::getChildrenCount()
{
    return this->children_.getCount();
}

void ds::TrieNode::getChildren(TrieNode** &children, INT &count)
{
    ds::KeyValuePair<char, ds::TrieNode*> *array = this->children_.toArray(count);
    children = new TrieNode*[count];
    for (size_t i = 0; i < count; i++)
    {
        children[i] = array[i].value;
    }
    
    delete[] array;
}

char ds::TrieNode::getCharacter()
{
    return this->character_;
}


/********************************************/
/*                                          */
/*                   Trie                   */
/*                                          */
/********************************************/


ds::Trie::Trie()
{
    this->head_ = new ds::TrieNode(ds::Trie::HEAD_CHARACTER);
    this->count_ = 0;
}
ds::Trie::~Trie()
{
    delete this->head_;
}


BOOLEAN ds::Trie::addWord(const char* word)
{
    BOOLEAN added = FALSE;
    ds::TrieNode* current = this->head_;

    char c;
    while ((c = *(word++)) != '\0')
    {
        added = TRUE;
        current = current->addChild(c, FALSE);
    };

    if(added)
    {
        current->setCompleteWord(TRUE);
        this->count_++;

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


BOOLEAN ds::Trie::removeWord(const char* word)
{
    if(this->removeWholeWord(this->head_, word))
    {
        this->count_--;
        return TRUE;
    }

    return FALSE;
}

BOOLEAN ds::Trie::removePrefix(const char* word)
{
    INT removed = 0;
    if(this->removeWholePrefix(this->head_, word, removed))
    {
        this->count_ -= removed;
        return TRUE;
    }

    return FALSE;
}

BOOLEAN ds::Trie::removeWholeWord(ds::TrieNode* current, const char* word)
{
    //
    if(current == NULL || word == NULL) return FALSE;

    // reach end of the word
    if(*word == '\0')
    {
        // if there were no children, stop the recursion and return true
        if(current->getChildrenCount() == 0) return TRUE;
        // in case there other words with same prefix
        else return FALSE;
    }
    // didn't reach end of given word
    else
    {   
        // if there no other children, return false
        if(!current->hasChildren()) return FALSE;

        // if there is a child, continue
        ds::TrieNode* child = current->getChild(*word);
        if(child)
        {
            word++;
            BOOLEAN shouldRemove = this->removeWholeWord(child, word);
            if(shouldRemove) current->removeChild(child->getCharacter());
            return shouldRemove;
        }
        else
        {
            return FALSE;
        }
        
    }
    
}

BOOLEAN ds::Trie::removeWholePrefix(ds::TrieNode* current, const char* word, INT &removedCount)
{
    //
    if(current == NULL || word == NULL) return FALSE;

    // reach end of the word
    if(*word == '\0')
    {
        removedCount = this->countWords(current);
        return TRUE;
    }
    // didn't reach end of given word
    else
    {   
        // if there no other children, return false
        if(!current->hasChildren()) return FALSE;

        // if there is a child, continue
        ds::TrieNode* child = current->getChild(*word);
        if(child)
        {
            word++;
            BOOLEAN shouldRemove = this->removeWholePrefix(child, word, removedCount);
            if(shouldRemove) current->removeChild(child->getCharacter());
            return shouldRemove;
        }
        else
        {
            return FALSE;
        }
        
    }
}

INT ds::Trie::countWords(ds::TrieNode* parent)
{
    INT count = parent->isCompleteWord() ? 1 : 0;

    INT childrenCount = parent->getChildrenCount();
    if(childrenCount == 0) return count;

    ds::TrieNode** children = NULL;
    parent->getChildren(children, childrenCount);
    for (INT i = 0; i < childrenCount; i++)
    {
        count += this->countWords(children[i]);
    }

    delete[] children;
    return count;
}

INT ds::Trie::getCount()
{
    return this->count_;
}

ds::SuggestTraverser ds::Trie::getSuggests(char start)
{
    ds::TrieNode* startNode = this->head_->getChild(start);
    if(startNode)
    {
        static ds::SuggestTraverser tranverser(startNode, 100);
        return tranverser;
    }
    else
    {
        static ds::NullSuggestTraverser traverser;
        return traverser;
    }
}


/********************************************/
/*                                          */
/*            SuggestTraverser              */
/*                                          */
/********************************************/

ds::SuggestTraverser::SuggestTraverser()
{
    this->currentCount_ = 0;
    this->maxCount_ = 0;
    this->nodes_ = NULL;
}

ds::SuggestTraverser::SuggestTraverser(TrieNode* node, INT maxCount)
{
    if(maxCount < 1) throw ds::exception("INVALID_WORD_SIZE");

    this->currentCount_ = 1;
    this->maxCount_ = maxCount;

    this->nodes_ = new TrieNode*[maxCount];
    this->nodes_[0] = node;
}

ds::SuggestTraverser::SuggestTraverser(const ds::SuggestTraverser &traverser)
{
    this->maxCount_ = traverser.maxCount_;
    this->currentCount_ = traverser.currentCount_;

    this->nodes_ = new TrieNode*[this->maxCount_];
    for (INT i = 0; i < this->currentCount_; i++)
    {
        this->nodes_[i] = traverser.nodes_[i];
    }
    
}

ds::SuggestTraverser::~SuggestTraverser()
{
    if(this->nodes_) delete[] this->nodes_;
}


BOOLEAN ds::SuggestTraverser::advance(char c)
{
    ds::TrieNode* child = this->nodes_[this->currentCount_-1]->getChild(c);
    if(!child) return FALSE;

    this->nodes_[this->currentCount_++] = child;
    return TRUE;
}

BOOLEAN ds::SuggestTraverser::retreat()
{
    if(this->currentCount_ == 0) return FALSE;

    this->currentCount_--;
    return TRUE;
}

char* ds::SuggestTraverser::getSuggests(INT &count)
{
    ds::TrieNode** children = NULL;
    this->nodes_[this->currentCount_-1]->getChildren(children, count);

    char* array = new char[count];
    for (INT i = 0; i < count; i++)
    {
        array[i] = children[i]->getCharacter();
    }
    
    delete[] children;
    return array;
}

const char* ds::SuggestTraverser::getWord()
{
    std::string word = "";
    for (INT i = 0; i < this->currentCount_; i++)
    {
        word += this->nodes_[i]->getCharacter();
    }
    return word.c_str();
}


/********************************************/
/*                                          */
/*           NullSuggestTraverser           */
/*                                          */
/********************************************/

ds::NullSuggestTraverser::NullSuggestTraverser() 
    : ds::SuggestTraverser()
{
    // no thing to do here
}

BOOLEAN ds::NullSuggestTraverser::advance(char c)
{
    return FALSE;
}

BOOLEAN ds::NullSuggestTraverser::retreat()
{
    return FALSE;
}

char* ds::NullSuggestTraverser::getSuggests(INT &count)
{
    count = 0;
    return NULL;
}

const char* ds::NullSuggestTraverser::getWord()
{
    return "";
}