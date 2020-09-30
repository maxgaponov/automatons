#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>

class Automaton {
public:
    Automaton();
    Automaton(size_t size, int start_vertex);
    Automaton determined() const;
    Automaton minimized() const;
    bool is_word_in_language(const std::string& word) const;
    std::set<int> get_next_state(const std::set<int>& state, char letter) const;
    void add_edge(int first_vertex, int second_vertex, char letter);
    void set_terminal(int vertex);
    void set_start_vertex(int vertex);
    size_t get_size() const;
    void resize(size_t size);
    int get_start_vertex() const;
    char get_first_letter() const;
    char get_last_letter() const;
    bool is_terminal(int vertex) const;
    bool is_terminal(const std::set<int>& state) const;
private:
    char first_letter_ = 'a';
    char last_letter_ = 'b';
    size_t size_ = 0;
    int start_vertex_ = 0;
    std::vector<std::map<char, std::set<int>>> edges_;
    std::vector<bool> terminal_;

    template<class ForwardIterator>
    std::set<int> get_finish_state_(std::set<int> state, ForwardIterator start, ForwardIterator finish) const;
    int build_dfa_subgraph_(Automaton& atm, const std::set<int>& state, std::map<std::set<int>, int>& indices, int& cur_index) const;
    void minimize_iteration_(std::vector<int>& color) const;

friend std::ostream& operator<<(std::ostream& os, const Automaton& atm);
};

std::ostream& operator<<(std::ostream& os, const Automaton& atm);
