#include <gtest/gtest.h>
#include <nfa.h>

TEST(test_nfa, test_astar_bstar) {
    NFA atm(2, 0);
    atm.add_edge(0, 0, 'a');
    atm.add_edge(0, 1, 'b');
    atm.add_edge(1, 1, 'b');
    atm.set_terminal(0);
    atm.set_terminal(1);

    EXPECT_TRUE(atm.is_word_in_language(""));
    EXPECT_TRUE(atm.is_word_in_language("a"));
    EXPECT_TRUE(atm.is_word_in_language("b"));
    EXPECT_TRUE(atm.is_word_in_language("ab"));
    EXPECT_TRUE(atm.is_word_in_language("abb"));
    EXPECT_TRUE(atm.is_word_in_language("aab"));
    EXPECT_TRUE(atm.is_word_in_language("aaa"));
    EXPECT_TRUE(atm.is_word_in_language("aaab"));

    EXPECT_FALSE(atm.is_word_in_language("ba"));
    EXPECT_FALSE(atm.is_word_in_language("aba"));
    EXPECT_FALSE(atm.is_word_in_language("baaab"));
}

TEST(test_nfa, test_abstar_a) {
    NFA atm(3, 1);
    atm.add_edge(1, 2, 'a');
    atm.add_edge(2, 1, 'b');
    atm.add_edge(1, 0, 'a');
    atm.set_terminal(0);

    EXPECT_TRUE(atm.is_word_in_language("a"));
    EXPECT_TRUE(atm.is_word_in_language("aba"));
    EXPECT_TRUE(atm.is_word_in_language("ababa"));
    EXPECT_TRUE(atm.is_word_in_language("abababa"));

    EXPECT_FALSE(atm.is_word_in_language(""));
    EXPECT_FALSE(atm.is_word_in_language("b"));
    EXPECT_FALSE(atm.is_word_in_language("ab"));
    EXPECT_FALSE(atm.is_word_in_language("abab"));
}
