#include <automaton.h>
#include <iostream>

void minimize_automaton(std::istream& in, std::ostream& out) {
    int size, edge_cnt, terminal_cnt, start_vertex;
    in >> size >> edge_cnt >> terminal_cnt >> start_vertex;
    Automaton atm(size, start_vertex);
    for (int i = 0; i < edge_cnt; ++i) {
        int vertex_from, vertex_to;
        char letter;
        in >> vertex_from >> vertex_to >> letter;
        atm.add_edge(vertex_from, vertex_to, letter);
    }
    for (int i = 0; i < terminal_cnt; ++i) {
        int vertex;
        in >> vertex;
        atm.set_terminal(vertex);
    }
    out << atm.minimized();
}

int main() {
    minimize_automaton(std::cin, std::cout);
    return 0;
}
