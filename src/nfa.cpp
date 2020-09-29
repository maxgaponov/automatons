#include <nfa.h>

NFA::NFA(size_t size, int start_vertex) : start_vertex_(start_vertex), edges_(size), terminal_(size) {}

void NFA::add_edge(int first_vertex, int second_vertex, char letter) {
    edges_[first_vertex][letter].insert(second_vertex);
}

void NFA::set_terminal(int vertex) {
    terminal_[vertex] = true;
}

bool NFA::is_word_in_language(const std::string &word) const {
    std::set start_state = {start_vertex_};
    std::set<int> finish_state = get_finish_state_(start_state, word.begin(), word.end());
    return is_terminal_(finish_state);
}

template<class ForwardIterator>
std::set<int> NFA::get_finish_state_(std::set<int> state, ForwardIterator start, ForwardIterator finish) const {
    ForwardIterator it = start;
    while (it != finish) {
        state = get_next_state_(state, *it);
        ++it;
    }
    return state;
}

std::set<int> NFA::get_next_state_(const std::set<int> &state, char letter) const {
    std::set<int> next_state;
    for (int vertex : state) {
        auto it = edges_[vertex].find(letter);
        if (it != edges_[vertex].end())  {
            const std::set<int>& available_vertices = it->second;
            next_state.insert(available_vertices.begin(), available_vertices.end());
        }
    }
    return next_state;
}

bool NFA::is_terminal_(const std::set<int> &state) const {
    return std::any_of(state.begin(), state.end(), [this](int v) { return terminal_[v]; } );
}
