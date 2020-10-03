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

TEST(text_regex, complex_regex2) {
    Automaton atm("(a+b)*(aa(a+b)*bb+aba)b*ab*");
    EXPECT_TRUE(atm.is_word_in_language("aabba"));
    EXPECT_TRUE(atm.is_word_in_language("abaab"));
    EXPECT_TRUE(atm.is_word_in_language("abaa"));
    EXPECT_FALSE(atm.is_word_in_language("babb"));
    EXPECT_FALSE(atm.is_word_in_language("aaaaaaa"));
    EXPECT_FALSE(atm.is_word_in_language("babab"));
    EXPECT_FALSE(atm.is_word_in_language("aab"));
    EXPECT_FALSE(atm.is_word_in_language("baa"));
}

void atm_diff(const Automaton& atm1, const Automaton& atm2, const std::string& str) {
    EXPECT_NE(atm1.is_word_in_language(str), atm2.is_word_in_language(str));
}

TEST(text_regex, inv_regex) {
    Automaton pre_atm("(a(ab+b(ba)*a)*)*");
    Automaton atm = pre_atm.inversed();
    atm_diff(pre_atm, atm, "aabba");
    atm_diff(pre_atm, atm, "abaab");
    atm_diff(pre_atm, atm, "abaa");
    atm_diff(pre_atm, atm, "babb");
    atm_diff(pre_atm, atm, "aaaaaaa");
    atm_diff(pre_atm, atm, "babab");
    atm_diff(pre_atm, atm, "aab");
    atm_diff(pre_atm, atm, "baa");
}
