#pragma once
#include <automaton.h>
#include <automaton_manip.h>

template<class RandomAccessIterator, class Function>
RandomAccessIterator get_first_elem_by_cond(RandomAccessIterator start, RandomAccessIterator finish, Function cond) {
    auto it = start;
    int balance = 0;
    do {
        if (*it == '(') {
            ++balance;
        }
        if (*it == ')') {
            --balance;
        }
        if (cond(*it) && balance == 0) {
            break;
        }
        ++it;
    } while (it != finish);
    return it;
}

template<class RandomAccessIterator>
RandomAccessIterator get_first_free_plus(RandomAccessIterator start, RandomAccessIterator finish) {
    return get_first_elem_by_cond(start, finish, [](char letter) { return letter == '+'; });
}

template<class RandomAccessIterator>
RandomAccessIterator get_first_free_position(RandomAccessIterator start, RandomAccessIterator finish) {
    return get_first_elem_by_cond(start, finish, [](char letter) { return true; });
}

template<class RandomAccessIterator>
Automaton build_automaton_from_regex(RandomAccessIterator start, RandomAccessIterator finish) {
    int length = finish - start;
    if (length == 0) {
        return Automaton();
    }
    if (length == 1) {
        if (*start == '0') {
            return automaton_zero();
        } else if (*start == '1') {
            return automaton_one();
        } else {
            return automaton_letter(*start);
        }
    }
    auto it = get_first_free_plus(start, finish);
    if (it != finish) {
        Automaton atm_l = build_automaton_from_regex(start, it);
        Automaton atm_r = build_automaton_from_regex(it + 1, finish);
        return automaton_union(atm_l, atm_r);
    } else {
        it = get_first_free_position(start, finish) + 1;
        if (it == finish) {
            return build_automaton_from_regex(start + 1, finish - 1);
        }
        Automaton atm_l = build_automaton_from_regex(start, it);
        if (it != finish && *it == '*') {
            atm_l = automaton_iteration(atm_l);
            ++it;
        }
        Automaton atm_r = build_automaton_from_regex(it, finish);
        return automaton_concat(atm_l, atm_r);
    }
}
