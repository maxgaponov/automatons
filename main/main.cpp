#include <automaton.h>
#include <iostream>
#include <string>

void automaton_by_regex(std::istream& in, std::ostream& out) {
    std::string regexp_str;
    in >> regexp_str;
    out << Automaton(regexp_str).minimized() << std::endl;
}

int main() {
    automaton_by_regex(std::cin, std::cout);
    return 0;
}
