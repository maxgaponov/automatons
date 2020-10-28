#include <gtest/gtest.h>
#include <automaton_manip.h>

TEST(test_manip, zero) {
    Automaton atm = automaton_zero();
    EXPECT_FALSE(atm.is_word_in_language(""));
    EXPECT_FALSE(atm.is_word_in_language("a"));
    EXPECT_FALSE(atm.is_word_in_language("b"));
    EXPECT_FALSE(atm.is_word_in_language("abaab"));
}

TEST(test_manip, one) {
    Automaton atm = automaton_one();
    EXPECT_TRUE(atm.is_word_in_language(""));
    EXPECT_TRUE(atm.is_word_in_language("a"));
    EXPECT_TRUE(atm.is_word_in_language("b"));
    EXPECT_TRUE(atm.is_word_in_language("abaab"));
}

TEST(text_manip, letter) {
    Automaton atm = automaton_letter('b');
    EXPECT_TRUE(atm.is_word_in_language("b"));
    EXPECT_FALSE(atm.is_word_in_language(""));
    EXPECT_FALSE(atm.is_word_in_language("a"));
    EXPECT_FALSE(atm.is_word_in_language("ba"));
    EXPECT_FALSE(atm.is_word_in_language("abaab"));
}

TEST(text_manip, iteration) {
    Automaton pre_atm = automaton_letter('a');
    Automaton atm = automaton_iteration(pre_atm);
    EXPECT_TRUE(atm.is_word_in_language("a"));
    EXPECT_TRUE(atm.is_word_in_language("aaaaa"));
    EXPECT_TRUE(atm.is_word_in_language(""));
    EXPECT_FALSE(atm.is_word_in_language("b"));
    EXPECT_FALSE(atm.is_word_in_language("ba"));
}

TEST(text_manip, concat) {
    Automaton pre_atm1 = automaton_letter('a');
    Automaton pre_atm2 = automaton_letter('b');
    Automaton atm = automaton_concat(pre_atm1, pre_atm2);
    EXPECT_TRUE(atm.is_word_in_language("ab"));
    EXPECT_FALSE(atm.is_word_in_language("a"));
    EXPECT_FALSE(atm.is_word_in_language("b"));
    EXPECT_FALSE(atm.is_word_in_language(""));
    EXPECT_FALSE(atm.is_word_in_language("ba"));
}

TEST(text_manip, atm_union) {
    Automaton pre_atm1 = automaton_letter('a');
    Automaton pre_atm2 = automaton_letter('b');
    Automaton atm = automaton_union(pre_atm1, pre_atm2);
    EXPECT_TRUE(atm.is_word_in_language("a"));
    EXPECT_TRUE(atm.is_word_in_language("b"));
    EXPECT_FALSE(atm.is_word_in_language(""));
    EXPECT_FALSE(atm.is_word_in_language("ab"));
    EXPECT_FALSE(atm.is_word_in_language("ba"));
}
