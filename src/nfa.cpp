#include <nfa.h>

NFA::NFA() {}

NFA::NFA(size_t size, int start_vertex) : size_(size), start_vertex_(start_vertex), edges_(size), terminal_(size) {}

void NFA::add_edge(int first_vertex, int second_vertex, char letter) {
    edges_[first_vertex][letter].insert(second_vertex);
}

void NFA::set_terminal(int vertex) {
    terminal_[vertex] = true;
}

int NFA::get_start_vertex() const {
    return start_vertex_;
}

bool NFA::is_word_in_language(const std::string &word) const {
    std::set start_state = {start_vertex_};
    std::set<int> finish_state = get_finish_state_(start_state, word.begin(), word.end());
    return is_terminal(finish_state);
}

size_t NFA::get_size() const {
    return size_;
}

template<class ForwardIterator>
std::set<int> NFA::get_finish_state_(std::set<int> state, ForwardIterator start, ForwardIterator finish) const {
    ForwardIterator it = start;
    while (it != finish) {
        state = get_next_state(state, *it);
        ++it;
    }
    return state;
}

std::set<int> NFA::get_next_state(const std::set<int> &state, char letter) const {
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

bool NFA::is_terminal(const std::set<int> &state) const {
    return std::any_of(state.begin(), state.end(), [this](int v) { return terminal_[v]; } );
}

std::ostream& operator<<(std::ostream& os, const NFA& atm) {
    os << "Automaton\n";
    os << "Size = " << atm.get_size() << '\n';
    for (int vertex = 0; vertex < atm.get_size(); ++vertex) {
        for (char letter = atm.first_letter_; letter <= atm.last_letter_; ++letter) {
            auto it = atm.edges_[vertex].find(letter);
            if (it != atm.edges_[vertex].end()) {
                for (int dest_vertex : it->second) {
                    os << vertex << " -> " << dest_vertex << " by " << letter << '\n';
                }
            }
        }
    }
    return os;
}
