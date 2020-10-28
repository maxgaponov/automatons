#include <automaton_manip.h>

Automaton automaton_zero() {
    return Automaton(1, 0);
}

Automaton automaton_one() {
    Automaton atm(1, 0);
    for (char letter : atm.letters()) {
        atm.add_edge(0, 0, letter);
    }
    atm.set_terminal(0);
    return atm;
}

Automaton automaton_letter(char letter) {
    Automaton atm(2, 0);
    atm.add_edge(0, 1, letter);
    atm.set_terminal(1);
    return atm;
}

Automaton automaton_iteration(const Automaton& atm) {
    int new_start = atm.get_size();
    Automaton result = atm;
    result.resize(result.get_size());
    for (char letter : atm.letters()) {
        for (int vertex = 0; vertex < atm.get_size(); ++vertex) {
            if (atm.is_terminal(vertex)) {
                for (int dest_v : atm.get_next_state({atm.get_start_vertex()}, letter)) {
                    result.add_edge(vertex, dest_v, letter);
                }
            }
        }
    }
    result.set_terminal(atm.get_start_vertex());
    return result;
}

Automaton automaton_concat(const Automaton& atm_l, const Automaton& atm_r) {
    if (atm_l.get_size() == 0) {
        return atm_r;
    }
    if (atm_r.get_size() == 0) {
        return atm_l;
    }
    Automaton result = atm_l;
    result.remove_terminals();
    result.resize(result.get_size() + atm_r.get_size());
    for (char letter : atm_l.letters()) {
        for (int vertex = 0; vertex < atm_r.get_size(); ++vertex) {
            for (int dest_v : atm_r.get_next_state({vertex}, letter)) {
                result.add_edge(vertex + atm_l.get_size(), dest_v + atm_l.get_size(), letter);
            }
            if (atm_r.is_terminal(vertex)) {
                result.set_terminal(vertex + atm_l.get_size());
            }
        }
    }
    for (char letter : atm_l.letters()) {
        for (int vertex = 0; vertex < atm_l.get_size(); ++vertex) {
            if (atm_l.is_terminal(vertex)) {
                for (int dest_v : atm_r.get_next_state({atm_r.get_start_vertex()}, letter)) {
                    result.add_edge(vertex, dest_v + atm_l.get_size(), letter);
                }
                if (atm_r.is_terminal(atm_r.get_start_vertex())) {
                    result.set_terminal(vertex);
                }
            }
        }
    }
    return result;
}

Automaton automaton_union(const Automaton& atm_l, const Automaton& atm_r) {
    if (atm_l.get_size() == 0) {
        return atm_r;
    }
    if (atm_r.get_size() == 0) {
        return atm_l;
    }
    Automaton result = atm_l;
    result.resize(result.get_size() + atm_r.get_size());
    for (char letter : atm_l.letters()) {
        for (int vertex = 0; vertex < atm_r.get_size(); ++vertex) {
            for (int dest_v : atm_r.get_next_state({vertex}, letter)) {
                result.add_edge(vertex + atm_l.get_size(), dest_v + atm_l.get_size(), letter);
            }
            if (atm_r.is_terminal(vertex)) {
                result.set_terminal(vertex + atm_l.get_size());
            }
        }
    }
    for (char letter : atm_l.letters()) {
        for (int dest_v : atm_r.get_next_state({atm_r.get_start_vertex()}, letter)) {
            result.add_edge(atm_l.get_start_vertex(), dest_v + atm_l.get_size(), letter);
        }
    }
    return result;
}
