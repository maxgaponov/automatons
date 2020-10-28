#pragma once
#include <automaton.h>

Automaton automaton_zero();
Automaton automaton_one();
Automaton automaton_letter(char letter);
Automaton automaton_iteration(const Automaton& atm);
Automaton automaton_concat(const Automaton& atm_l, const Automaton& atm_r);
Automaton automaton_union(const Automaton& atm_l, const Automaton& atm_r);
