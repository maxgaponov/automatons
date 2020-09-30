#include <gtest/gtest.h>
#include <dfa.h>

TEST(test_dfa, test_astar_bstar) {
    NFA natm(2, 0);
    natm.add_edge(0, 0, 'a');
    natm.add_edge(0, 1, 'b');
    natm.add_edge(1, 1, 'b');
    natm.set_terminal(0);
    natm.set_terminal(1);
    DFA atm(natm);

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

TEST(test_dfa, test_abstar_a) {
    NFA natm(3, 1);
    natm.add_edge(1, 2, 'a');
    natm.add_edge(2, 1, 'b');
    natm.add_edge(1, 0, 'a');
    natm.set_terminal(0);
    DFA atm(natm);

    EXPECT_TRUE(atm.is_word_in_language("a"));
    EXPECT_TRUE(atm.is_word_in_language("aba"));
    EXPECT_TRUE(atm.is_word_in_language("ababa"));
    EXPECT_TRUE(atm.is_word_in_language("abababa"));

    EXPECT_FALSE(atm.is_word_in_language(""));
    EXPECT_FALSE(atm.is_word_in_language("b"));
    EXPECT_FALSE(atm.is_word_in_language("ab"));
    EXPECT_FALSE(atm.is_word_in_language("abab"));
}

TEST(test_dfa, test_regex) {
    // (ab)*a* + ((a+b)^2)*
    NFA natm(6, 0);
    natm.add_edge(0, 1, 'a');
    natm.add_edge(0, 3, 'a');
    natm.add_edge(0, 4, 'a');
    natm.add_edge(0, 4, 'b');
    natm.add_edge(1, 2, 'b');
    natm.add_edge(2, 1, 'a');
    natm.add_edge(2, 3, 'a');
    natm.add_edge(3, 3, 'a');
    natm.add_edge(4, 5, 'a');
    natm.add_edge(4, 5, 'b');
    natm.add_edge(5, 4, 'a');
    natm.add_edge(5, 4, 'b');
    natm.set_terminal(0);
    natm.set_terminal(2);
    natm.set_terminal(3);
    natm.set_terminal(5);
    DFA atm(natm);

    EXPECT_TRUE(atm.is_word_in_language("aa"));
    EXPECT_TRUE(atm.is_word_in_language("ab"));
    EXPECT_TRUE(atm.is_word_in_language("bbab"));
    EXPECT_TRUE(atm.is_word_in_language(""));
    EXPECT_TRUE(atm.is_word_in_language("ab"));
    EXPECT_TRUE(atm.is_word_in_language("abab"));

    EXPECT_FALSE(atm.is_word_in_language("baa"));
    EXPECT_FALSE(atm.is_word_in_language("ababaab"));
}