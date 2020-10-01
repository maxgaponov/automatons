#include <gtest/gtest.h>
#include <automaton_regex.h>

TEST(test_regex, zero) {
    Automaton atm("0");
    EXPECT_FALSE(atm.is_word_in_language(""));
    EXPECT_FALSE(atm.is_word_in_language("a"));
    EXPECT_FALSE(atm.is_word_in_language("b"));
    EXPECT_FALSE(atm.is_word_in_language("abaab"));
}

TEST(test_regex, one) {
    Automaton atm("1");
    EXPECT_TRUE(atm.is_word_in_language(""));
    EXPECT_TRUE(atm.is_word_in_language("a"));
    EXPECT_TRUE(atm.is_word_in_language("b"));
    EXPECT_TRUE(atm.is_word_in_language("abaab"));
}

TEST(text_regex, letter) {
    Automaton atm("b");
    EXPECT_TRUE(atm.is_word_in_language("b"));
    EXPECT_FALSE(atm.is_word_in_language(""));
    EXPECT_FALSE(atm.is_word_in_language("a"));
    EXPECT_FALSE(atm.is_word_in_language("ba"));
    EXPECT_FALSE(atm.is_word_in_language("abaab"));
}

TEST(text_regex, word) {
    Automaton atm("abaa");
    EXPECT_TRUE(atm.is_word_in_language("abaa"));
    EXPECT_FALSE(atm.is_word_in_language(""));
    EXPECT_FALSE(atm.is_word_in_language("a"));
    EXPECT_FALSE(atm.is_word_in_language("b"));
    EXPECT_FALSE(atm.is_word_in_language("abaab"));
}

TEST(text_regex, star) {
    Automaton atm("ab*");
    EXPECT_TRUE(atm.is_word_in_language("a"));
    EXPECT_TRUE(atm.is_word_in_language("ab"));
    EXPECT_TRUE(atm.is_word_in_language("abbb"));
    EXPECT_FALSE(atm.is_word_in_language(""));
    EXPECT_FALSE(atm.is_word_in_language("b"));
    EXPECT_FALSE(atm.is_word_in_language("ba"));
    EXPECT_FALSE(atm.is_word_in_language("aba"));
}

TEST(text_regex, plus) {
    Automaton atm("ab+ba");
    EXPECT_TRUE(atm.is_word_in_language("ab"));
    EXPECT_TRUE(atm.is_word_in_language("ba"));
    EXPECT_FALSE(atm.is_word_in_language(""));
    EXPECT_FALSE(atm.is_word_in_language("a"));
    EXPECT_FALSE(atm.is_word_in_language("abba"));
    EXPECT_FALSE(atm.is_word_in_language("bb"));
}

TEST(text_regex, complex_regex) {
    Automaton atm("(ab)*a*+((a+b)(a+b))*");
    EXPECT_TRUE(atm.is_word_in_language("ab"));
    EXPECT_TRUE(atm.is_word_in_language("ba"));
    EXPECT_TRUE(atm.is_word_in_language("aaaabb"));
    EXPECT_TRUE(atm.is_word_in_language("ababaa"));
    EXPECT_TRUE(atm.is_word_in_language("abbb"));
    EXPECT_FALSE(atm.is_word_in_language("bab"));
    EXPECT_FALSE(atm.is_word_in_language("bba"));
    EXPECT_FALSE(atm.is_word_in_language("aab"));
}
