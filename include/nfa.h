#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

class NFA {
public:
    NFA(size_t size, int start_vertex);
    void add_edge(int first_vertex, int second_vertex, char letter);
    void set_terminal(int vertex);
    bool is_word_in_language(const std::string& word) const;

private:
    int start_vertex_;
    std::vector<std::map<char, std::set<int>>> edges_;
    std::vector<bool> terminal_;

    template<class ForwardIterator>
    std::set<int> get_finish_state_(std::set<int> state, ForwardIterator start, ForwardIterator finish) const;
    std::set<int> get_next_state_(const std::set<int>& state, char letter) const;
    bool is_terminal_(const std::set<int>& state) const;
};
