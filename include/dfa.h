#include <nfa.h>

class DFA : public NFA {
public:
    DFA(const NFA& atm);
    DFA minimized() const; // TODO
    void minimize(); // TODO
private:
    int build_subgraph(const NFA& atm, const std::set<int>& state, std::map<std::set<int>, int>& indices, int& cur_index);
};
