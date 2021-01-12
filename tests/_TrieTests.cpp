#include "gtest/gtest.h"

#include "global.h"
#include "Trie.h"


TEST(_TrieNodeTests, create_node)
{
    ds::TrieNode node('a', FALSE);

    EXPECT_EQ('a'   , node.getCharacter());
    EXPECT_EQ(FALSE , node.isCompleteWord());
    EXPECT_EQ(0     , node.getChildrenCount());
    EXPECT_EQ(FALSE , node.hasChildren());
}

TEST(_TrieNodeTests, add_child)
{
    ds::TrieNode node('a', FALSE);
    ds::TrieNode* child = node.addChild('t', TRUE);
    
    EXPECT_EQ('a'   , node.getCharacter());
    EXPECT_EQ(FALSE , node.isCompleteWord());
    EXPECT_EQ(1     , node.getChildrenCount());
    EXPECT_EQ(TRUE  , node.hasChildren());

    EXPECT_EQ('t'   , child->getCharacter());
    EXPECT_EQ(TRUE  , child->isCompleteWord());
    EXPECT_EQ(0     , child->getChildrenCount());
    EXPECT_EQ(FALSE , child->hasChildren());
}


TEST(_TrieTests, create_trie)
{
    ds::Trie trie;

    EXPECT_EQ(0, trie.getCount());
}

TEST(_TrieTests, add_word)
{
    ds::Trie trie;

    EXPECT_EQ(TRUE, trie.addWord("word"));
    EXPECT_EQ(1, trie.getCount());
}

TEST(_TrieTests, remove_word)
{
    ds::Trie trie;

    EXPECT_EQ(TRUE, trie.addWord("word"));
    EXPECT_EQ(1, trie.getCount());

    EXPECT_EQ(TRUE, trie.removeWord("word"));
    EXPECT_EQ(0, trie.getCount());
}

TEST(_TrieTests, remove_word_with_just_prefix)
{
    ds::Trie trie;

    EXPECT_EQ(TRUE, trie.addWord("word"));
    EXPECT_EQ(1, trie.getCount());

    EXPECT_EQ(FALSE, trie.removeWord("wor"));
    EXPECT_EQ(1, trie.getCount());
}

TEST(_TrieTests, remove_prefix_all_trie)
{
    ds::Trie trie;

    EXPECT_EQ(TRUE, trie.addWord("word"));
    EXPECT_EQ(TRUE, trie.addWord("words"));
    EXPECT_EQ(TRUE, trie.addWord("worry"));
    EXPECT_EQ(3, trie.getCount());

    EXPECT_EQ(TRUE, trie.removePrefix("wor"));
    EXPECT_EQ(0, trie.getCount());
}


TEST(_TrieTests, remove_prefix_pratial)
{
    ds::Trie trie;

    EXPECT_EQ(TRUE, trie.addWord("base"));  // 1
    EXPECT_EQ(TRUE, trie.addWord("no"));    // 2
    EXPECT_EQ(TRUE, trie.addWord("not"));   // 3
    EXPECT_EQ(TRUE, trie.addWord("note"));  // 4
    EXPECT_EQ(TRUE, trie.addWord("notes")); // 5
    EXPECT_EQ(TRUE, trie.addWord("word"));  // 6 ---
    EXPECT_EQ(TRUE, trie.addWord("words")); // 7 ---
    EXPECT_EQ(TRUE, trie.addWord("wordz")); // 8 ---
    EXPECT_EQ(TRUE, trie.addWord("worry")); // 9
    EXPECT_EQ(9, trie.getCount());

    EXPECT_EQ(TRUE, trie.removePrefix("word"));
    EXPECT_EQ(6, trie.getCount());
}


TEST(_TrieTests, get_suggest)
{
    ds::Trie trie;

    EXPECT_EQ(TRUE, trie.addWord("to"));    // 1
    EXPECT_EQ(TRUE, trie.addWord("too"));
    EXPECT_EQ(TRUE, trie.addWord("tool"));
    EXPECT_EQ(TRUE, trie.addWord("tools")); // 5
    EXPECT_EQ(TRUE, trie.addWord("took"));
    EXPECT_EQ(TRUE, trie.addWord("tooth"));
    EXPECT_EQ(TRUE, trie.addWord("tower"));
    EXPECT_EQ(TRUE, trie.addWord("top"));
    EXPECT_EQ(TRUE, trie.addWord("toy"));
    EXPECT_EQ(TRUE, trie.addWord("ton"));   // 13
    EXPECT_EQ(TRUE, trie.addWord("tone"));
    EXPECT_EQ(TRUE, trie.addWord("touch")); // 10
    EXPECT_EQ(TRUE, trie.addWord("tomato"));

    EXPECT_EQ(13, trie.getCount());

    ds::SuggestTraverser suggest = trie.getSuggests('t');
    INT count = 0;
    suggest.getSuggests(count);
    EXPECT_EQ(1, count);

    suggest.advance('o');
    suggest.getSuggests(count);
    EXPECT_EQ(7, count);

    suggest.advance('o');
    suggest.getSuggests(count);
    EXPECT_EQ(3, count);
}