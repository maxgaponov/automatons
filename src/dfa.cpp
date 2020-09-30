#include <dfa.h>

DFA::DFA(const NFA& atm) : NFA() {
    std::map<std::set<int>, int> indices;
    int cur_index = 0;
    build_subgraph(atm, {atm.get_start_vertex()}, indices, cur_index);
}

int DFA::build_subgraph(const NFA& atm, const std::set<int> &state, std::map<std::set<int>, int> &indices, int &cur_index) {
    auto it = indices.find(state);
    if (it != indices.end()) {
        return it->second;
    }
    int state_index = cur_index++;
    indices[state] = state_index;
    ++size_;
    edges_.resize(size_);
    terminal_.resize(size_);
    if (atm.is_terminal(state)) {
        set_terminal(state_index);
    }
    for (char letter = first_letter_; letter <= last_letter_; ++letter) {
        int dest_index = build_subgraph(atm, atm.get_next_state(state, letter), indices, cur_index);
        edges_[state_index][letter].insert(dest_index);
    }
    return state_index;
}
