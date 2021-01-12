#ifndef _TRIE_H_
#define _TRIE_H_

#include "global.h"
#include "exception.h"
#include "HashTable.h"

namespace ds
{
    class TrieNode
    {
    private:
        HashTable<char, TrieNode*> children_;
        BOOLEAN isCompleteWord_;
        char character_;
    public:
        TrieNode(char character, BOOLEAN isCompleteWord = FALSE);
        ~TrieNode();
    public:
        TrieNode* addChild(char character, BOOLEAN isCompleteWord = FALSE);
        BOOLEAN hasChild(char character);
        BOOLEAN removeChild(char character);
        TrieNode* getChild(char character);

        void getChildren(TrieNode** &children, INT &count);
        INT getChildrenCount();
        BOOLEAN hasChildren();

        char getCharacter();
        void setCompleteWord(BOOLEAN isCompleteWord);
        BOOLEAN isCompleteWord();
    };


    class SuggestTraverser
    {
    private:
        INT maxCount_;
        INT currentCount_;
        TrieNode** nodes_;
    protected:
        SuggestTraverser();
    public:
        SuggestTraverser(TrieNode* node, INT maxCount);
        SuggestTraverser(const SuggestTraverser&);
        ~SuggestTraverser();
    public:
        virtual BOOLEAN advance(char c);
        virtual BOOLEAN retreat();
        virtual char* getSuggests(INT &count);
        virtual const char* getWord();
    };


    class NullSuggestTraverser : public SuggestTraverser
    {
    public:
        NullSuggestTraverser();
    public:
        BOOLEAN advance(char c) override;
        BOOLEAN retreat() override;
        char* getSuggests(INT &count) override;
        const char* getWord() override;
    };


    class Trie
    {
    private:
        const static char HEAD_CHARACTER = '*';
        TrieNode* head_;
        INT count_;
    private:
        INT countWords(ds::TrieNode* parent);
        BOOLEAN removeWholeWord(ds::TrieNode* current, const char* word);
        BOOLEAN removeWholePrefix(ds::TrieNode* current, const char* word, INT &removedCount);
    public:
        Trie();
        ~Trie();
    public:
        BOOLEAN addWord(const char* word);
        BOOLEAN removeWord(const char* word);
        BOOLEAN removePrefix(const char* word);
        BOOLEAN wordExists(const char* word);
        //
        SuggestTraverser getSuggests(char start);
        INT getCount();
    };



}

#endif // !_TRIE_H_