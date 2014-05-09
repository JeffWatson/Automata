#include <iostream>
#include <assert.h>
#include "nfa.h"

using namespace std;

NFA::NFA(unsigned size_, q_S initial_, q_S final_)
        : initial(initial_), final(final_), size(size_)
{
    assert(is_legal_state(initial));
    assert(is_legal_state(final));

    vector<input> epsilon_row(size, NONE);

    /* 
	
	
	Initialize transitions_table with an epsilon, no transitions
     between its states
    */
    for (unsigned i = 0; i < size; ++i)
        transitions_table.push_back(epsilon_row);
}


NFA& NFA::operator=(const NFA& other)
{
    if (this == &other)
        return *this;

    initial = other.initial;
    final = other.final;
    size = other.size;
    transitions_table = other.transitions_table;

    return *this;
}


bool NFA::is_legal_state(q_S s)
{
    /* 
	The states have their size by now
	
    */
    if (s < 0 || s >= size)
        return false;

    return true;
}


void NFA::add_trans(q_S from, q_S to, input in)
{
    assert(is_legal_state(from));
    assert(is_legal_state(to));

    transitions_table[from][to] = in;

    if (in != EPS)
        inputs.insert(in);
}


void NFA::shift_states(unsigned shift)
{
    unsigned new_size = size + shift;

    if (shift < 1)
        return;

    /* new empty transition table (new size)
    */
    vector<input> epsilon_row(new_size, NONE);
    vector<vector<input> > new_trans_table(new_size, epsilon_row);

    /* 
	the transitions will be inserted in a new table that will have their new locations
	
    */
    for (q_S i = 0; i < size; ++i)
    {
        for (q_S j = 0; j < size; ++j)
        {
            new_trans_table[i + shift][j + shift] = transitions_table[i][j];
        }
    }

    // NFA members need to be updated, this will update them
    size = new_size;
    initial += shift;
    final += shift;
    transitions_table = new_trans_table;
}


void NFA::fill_states(const NFA& other)
{
    for (q_S i = 0; i < other.size; ++i)
    {
        for (q_S j = 0; j < other.size; ++j)
        {
            transitions_table[i][j] = other.transitions_table[i][j];
        }
    }

    for (   set<input>::const_iterator i = other.inputs.begin(); 
            i != other.inputs.end(); ++i)
        inputs.insert(*i);
}


void NFA::append_empty_state()
{
    //add new row
    vector<input> epsilon_row(size + 1, NONE);
    transitions_table.push_back(epsilon_row);

    // add new colum
    for (q_S i = 0; i < size; ++i)
        transitions_table[i].push_back(NONE);

    size += 1;
}





set<q_S> NFA::move(set<q_S> states, input inp)
{
    set<q_S> result;

    
    for (   set<q_S>::const_iterator state_i = states.begin(); 
            state_i != states.end(); ++state_i)
    {
        // for each transition from this q_S
        //
        for (   vector<input>::const_iterator trans_i = transitions_table[*state_i].begin(); 
                trans_i != transitions_table[*state_i].end(); ++trans_i)
        {
            
            if (*trans_i == inp)
            {
                q_S u = trans_i - transitions_table[*state_i].begin();
                result.insert(u);
            }
        }
    }

    return result;
}





//Basic NFA with input

NFA build_nfa_basic(input in)
{
    NFA basic(2, 0, 1);
    basic.add_trans(0, 1, in);

    return basic;
}


// (nfa1|nfa2)

NFA build_nfa_alter(NFA nfa1, NFA nfa2)
{
    /*
	The NFA will contain all the states. 
	1 & 2 are going to be always the initial and final states
	Initial q_S will be first, then regular states

    */

    // initial q_S
    nfa1.shift_states(1);

    // room for nfa1
    nfa2.shift_states(nfa1.size);

    
    // nfa2
    
    NFA new_nfa(nfa2);

    // nfa1's places switched
    //
    new_nfa.fill_states(nfa1);

    
    new_nfa.add_trans(0, nfa1.initial, EPS);
    new_nfa.add_trans(0, nfa2.initial, EPS);
    new_nfa.initial = 0;

  
    new_nfa.append_empty_state();

    // Set new final q_S
    //
    new_nfa.final = new_nfa.size - 1;
    new_nfa.add_trans(nfa1.final, new_nfa.final, EPS);
    new_nfa.add_trans(nfa2.final, new_nfa.final, EPS);

    return new_nfa;
}


// concatenation  (nfa1nfa2)
NFA build_nfa_concat(NFA nfa1, NFA nfa2)
{
    /*

	nfa1 will come first, followed by nfa2 

    */
    nfa2.shift_states(nfa1.size - 1);

    /* create a new nfa and initialize it with (the shifted)
     nfa2
    */
    NFA new_nfa(nfa2);

    /* 
	the states in nfa1 will take their place with the new one 
	
     note: nfa1's final q_S overwrites nfa2's initial q_S,
    the transition from nfa2's initial q_S now transits from nfa1's final q_S
    */
    new_nfa.fill_states(nfa1);

    
    new_nfa.initial = nfa1.initial;

    return new_nfa;
}



NFA build_nfa_star(NFA nfa)
{
  
    nfa.shift_states(1);

    // make room for the new final q_S
    //
    nfa.append_empty_state();

    // add new transitions
    //
    nfa.add_trans(nfa.final, nfa.initial, EPS);
    nfa.add_trans(0, nfa.initial, EPS);
    nfa.add_trans(nfa.final, nfa.size - 1, EPS);
    nfa.add_trans(0, nfa.size - 1, EPS);

    nfa.initial = 0;
    nfa.final = nfa.size - 1;

    return nfa;
}






