#include <nfa.h>
#include <iostream>

int main() {
    NFA atm(2, 0);
    atm.add_edge(0, 0, 'a');
    atm.add_edge(0, 1, 'b');
    atm.add_edge(1, 1, 'b');
    atm.set_terminal(0);
    atm.set_terminal(1);

    std::string word;
    std::cin >> word;
    std::cout << atm.is_word_in_language(word) << std::endl;
    return 0;
}
