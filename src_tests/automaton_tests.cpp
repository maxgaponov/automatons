#include <gtest/gtest.h>
#include <automaton.h>
#include <functional>

void check_if_determined(const Automaton& atm) {
    for (int v = 0; v < atm.get_size(); ++v) {
        for (char letter = atm.get_first_letter(); letter <= atm.get_last_letter(); ++letter) {
            EXPECT_EQ(atm.get_next_state({v}, letter).size(), 1);
        }
    }
}

void tester(const Automaton& atm, const std::function<void(const Automaton&)>& test, size_t min_size) {
    test(atm);

    Automaton datm = atm.determined();
    check_if_determined(datm);
    test(datm);

    Automaton mdatm = datm.minimized();
    check_if_determined(mdatm);
    EXPECT_EQ(mdatm.get_size(), min_size);
    test(mdatm);
}

void test_astar_bstar(const Automaton& atm) {
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

TEST(test_atm, gtest_astar_bstar) {
    Automaton atm(2, 0);
    atm.add_edge(0, 0, 'a');
    atm.add_edge(0, 1, 'b');
    atm.add_edge(1, 1, 'b');
    atm.set_terminal(0);
    atm.set_terminal(1);
    tester(atm, test_astar_bstar, 3);
}

void test_abstar_a(const Automaton& atm) {
    EXPECT_TRUE(atm.is_word_in_language("a"));
    EXPECT_TRUE(atm.is_word_in_language("aba"));
    EXPECT_TRUE(atm.is_word_in_language("ababa"));
    EXPECT_TRUE(atm.is_word_in_language("abababa"));

    EXPECT_FALSE(atm.is_word_in_language(""));
    EXPECT_FALSE(atm.is_word_in_language("b"));
    EXPECT_FALSE(atm.is_word_in_language("ab"));
    EXPECT_FALSE(atm.is_word_in_language("abab"));
}

TEST(test_atm, gtest_abstar_a) {
    Automaton atm(3, 1);
    atm.add_edge(1, 2, 'a');
    atm.add_edge(2, 1, 'b');
    atm.add_edge(1, 0, 'a');
    atm.set_terminal(0);
    tester(atm, test_abstar_a, 3);
}

void test_long_regex(const Automaton& atm) {
    EXPECT_TRUE(atm.is_word_in_language("aa"));
    EXPECT_TRUE(atm.is_word_in_language("ab"));
    EXPECT_TRUE(atm.is_word_in_language("bbab"));
    EXPECT_TRUE(atm.is_word_in_language(""));
    EXPECT_TRUE(atm.is_word_in_language("ab"));
    EXPECT_TRUE(atm.is_word_in_language("abab"));

    EXPECT_FALSE(atm.is_word_in_language("baa"));
    EXPECT_FALSE(atm.is_word_in_language("ababaab"));
}

TEST(test_dfa, gtest_long_regex) {
    // (ab)*a* + ((a+b)^2)*
    Automaton atm(6, 0);
    atm.add_edge(0, 1, 'a');
    atm.add_edge(0, 3, 'a');
    atm.add_edge(0, 4, 'a');
    atm.add_edge(0, 4, 'b');
    atm.add_edge(1, 2, 'b');
    atm.add_edge(2, 1, 'a');
    atm.add_edge(2, 3, 'a');
    atm.add_edge(3, 3, 'a');
    atm.add_edge(4, 5, 'a');
    atm.add_edge(4, 5, 'b');
    atm.add_edge(5, 4, 'a');
    atm.add_edge(5, 4, 'b');
    atm.set_terminal(0);
    atm.set_terminal(2);
    atm.set_terminal(3);
    atm.set_terminal(5);
    tester(atm, test_long_regex, 7);
}
