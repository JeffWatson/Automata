#include "subset_construct.h"


/* 
Epsilon for states that have been assigned the NFA
*/
set<q_S> build_eps_closure(NFA nfa, set<q_S> states)
{
   
    vector<q_S> unchecked_stack(states.begin(), states.end());

    /* epsilon closure is initiliazed 
    */
    set<q_S> eps_closure(states.begin(), states.end());

    while (!unchecked_stack.empty())
    {
        /* 
		will pop t off of the top in the stack
        */
        q_S t = unchecked_stack.back();
        unchecked_stack.pop_back();

        /* 
		
		will label the epsilon on every q_S u with an edge to t
        */
        for (   vector<input>::const_iterator i = nfa.transitions_table[t].begin();
                i != nfa.transitions_table[t].end(); ++i)
        {
            if (*i == EPS)
            {
                q_S u = i - nfa.transitions_table[t].begin();

                // if u is not already in eps_closure, add it and push it onto stack
                //
                if (eps_closure.find(u) == eps_closure.end())
                {
                    eps_closure.insert(u);
                    unchecked_stack.push_back(u);
                }
            }
        }
    }

    return eps_closure;
}



static q_S gen_new_state()
{
    static q_S num = 0;
    return num++;
}


/* 
Subset construction algorithm

*/
DFA subset_construct(NFA nfa)
{
    DFA dfa;

   
    typedef set<q_S> state_rep;
    set<state_rep> marked_states;
    set<state_rep> unmarked_states;

    // gives a number to each q_S in the DFA
    
    map<state_rep, q_S> dfa_state_num;

    set<q_S> nfa_initial;
    nfa_initial.insert(nfa.initial);

    
    state_rep first(build_eps_closure(nfa, nfa_initial));
    unmarked_states.insert(first);

    // initial q_S
   
    q_S dfa_initial = gen_new_state();
    dfa_state_num[first] = dfa_initial;
    dfa.start = dfa_initial;

    while (!unmarked_states.empty())
    {
        /*
		unmarked q_S and mark it 
			remove this q_S from the unmarked set
		
		*/
        state_rep a_state = *(unmarked_states.begin());
        unmarked_states.erase(unmarked_states.begin());
        marked_states.insert(a_state);

        // adding to final q_S of DFA
        if (a_state.find(nfa.final) != a_state.end())
            dfa.final.insert(dfa_state_num[a_state]);


        for (   set<input>::const_iterator inp_i = nfa.inputs.begin(); 
                inp_i != nfa.inputs.end(); ++inp_i)
        {
            // next q_S
            
            state_rep next = build_eps_closure(nfa, nfa.move(a_state, *inp_i));


            
			if(next.empty())
				continue;
          
			if (unmarked_states.find(next) == unmarked_states.end() &&
                marked_states.find(next) == marked_states.end())
			{
                unmarked_states.insert(next);
				dfa_state_num[next] = gen_new_state();
            }

            dfa.transitions_table[make_pair(dfa_state_num[a_state], *inp_i)] = dfa_state_num[next];
        }
    }

    return dfa;
}

