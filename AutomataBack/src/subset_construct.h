#ifndef SUBSET_CONSTRUCT_H
#define SUBSET_CONSTRUCT_H

#include "nfa.h"
#include "dfa.h"


set<q_S> build_eps_closure(NFA nfa, set<q_S> states);
DFA subset_construct(NFA nfa);


#endif // SUBSET_CONSTRUCT_H