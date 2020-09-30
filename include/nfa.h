#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>

class NFA {
public:
    NFA();
    NFA(size_t size, int start_vertex);
    void add_edge(int first_vertex, int second_vertex, char letter);
    void set_terminal(int vertex);
    bool is_word_in_language(const std::string& word) const;
    size_t get_size() const;
    std::set<int> get_next_state(const std::set<int>& state, char letter) const;
    bool is_terminal(const std::set<int>& state) const;
    int get_start_vertex() const;
protected:
    char first_letter_ = 'a';
    char last_letter_ = 'b';
    size_t size_ = 0;
    int start_vertex_ = 0;

    std::vector<std::map<char, std::set<int>>> edges_;
    std::vector<bool> terminal_;
    template<class ForwardIterator>
    std::set<int> get_finish_state_(std::set<int> state, ForwardIterator start, ForwardIterator finish) const;

friend std::ostream& operator<<(std::ostream& os, const NFA& atm);
};

std::ostream& operator<<(std::ostream& os, const NFA& atm);
