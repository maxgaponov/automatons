#include <automaton.h>

Automaton::Automaton() {}

Automaton::Automaton(size_t size, int start_vertex) : size_(size), start_vertex_(start_vertex), edges_(size), terminal_(size) {}

Automaton Automaton::determined() const {
    std::map<std::set<int>, int> indices;
    int cur_index = 0;
    Automaton atm;
    int v = build_dfa_subgraph(atm, {get_start_vertex()}, indices, cur_index);
    atm.set_start_vertex(v);
    return atm;
}

int Automaton::build_dfa_subgraph(Automaton& atm, const std::set<int> &state, std::map<std::set<int>, int>& indices, int& cur_index) const {
    auto it = indices.find(state);
    if (it != indices.end()) {
        return it->second;
    }
    int state_index = cur_index++;
    indices[state] = state_index;
    atm.resize(atm.get_size() + 1);
    if (is_terminal(state)) {
        atm.set_terminal(state_index);
    }
    for (char letter = first_letter_; letter <= last_letter_; ++letter) {
        int dest_index = build_dfa_subgraph(atm, get_next_state(state, letter), indices, cur_index);
        atm.add_edge(state_index, dest_index, letter);
    }
    return state_index;
}

bool Automaton::is_word_in_language(const std::string &word) const {
    std::set start_state = {start_vertex_};
    std::set<int> finish_state = get_finish_state_(start_state, word.begin(), word.end());
    return is_terminal(finish_state);
}

template<class ForwardIterator>
std::set<int> Automaton::get_finish_state_(std::set<int> state, ForwardIterator start, ForwardIterator finish) const {
    ForwardIterator it = start;
    while (it != finish) {
        state = get_next_state(state, *it);
        ++it;
    }
    return state;
}

std::set<int> Automaton::get_next_state(const std::set<int> &state, char letter) const {
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

void Automaton::add_edge(int first_vertex, int second_vertex, char letter) {
    edges_[first_vertex][letter].insert(second_vertex);
}

void Automaton::set_terminal(int vertex) {
    terminal_[vertex] = true;
}

int Automaton::get_start_vertex() const {
    return start_vertex_;
}

char Automaton::get_first_letter() const {
    return first_letter_;
}

char Automaton::get_last_letter() const {
    return last_letter_;
}

size_t Automaton::get_size() const {
    return size_;
}

bool Automaton::is_terminal(const std::set<int> &state) const {
    return std::any_of(state.begin(), state.end(), [this](int v) { return terminal_[v]; } );
}

void Automaton::resize(size_t size) {
    size_ = size;
    terminal_.resize(size_);
    edges_.resize(size_);
}

void Automaton::set_start_vertex(int vertex) {
    start_vertex_ = vertex;
}

std::ostream& operator<<(std::ostream& os, const Automaton& atm) {
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
