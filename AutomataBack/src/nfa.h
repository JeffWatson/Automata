

#ifndef NFA_H
#define NFA_H

#include "common.h"


class NFA
{
public:
  
    NFA(unsigned size_, q_S initial_, q_S final_);

    NFA(const NFA& other) :
            initial(other.initial), final(other.final),
            size(other.size), transitions_table(other.transitions_table), 
            inputs(other.inputs)
    {}

    NFA& operator=(const NFA& other);

    /*

	Adds a transition between two states
    */
    void add_trans(q_S from, q_S to, input in);

    /* 
	
	Fills states 0 up to other.size with other's states
    */
    void fill_states(const NFA& other);

    
    void shift_states(unsigned shift);

   
    void append_empty_state();

    /* 
	
	Returns a set of NFA states from which there is a transition on input
     symbol inp from some q_S s in states
    */
    set<q_S> move(set<q_S> states, input inp);

    /*
	Prints out the NFA
    */
    void show();

    bool is_legal_state(q_S s);

    q_S initial;
    q_S final;
    unsigned size;
    vector<vector<input> > transitions_table;

    
    set<input> inputs;
};


NFA build_nfa_basic(input in);
NFA build_nfa_alter(NFA nfa1, NFA nfa2);
NFA build_nfa_concat(NFA nfa1, NFA nfa2);
NFA build_nfa_star(NFA nfa);

#endif 
