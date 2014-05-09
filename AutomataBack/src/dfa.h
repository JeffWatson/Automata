#ifndef DFA_H
#define DFA_H

#include "common.h"


class DFA
{
public:
    typedef pair<q_S, input> transition;

    /* starting q_S
    the transitions table and also sets for final states
	*/
	
    map<transition, q_S> transitions_table;
    q_S start;
    set<q_S> final;

    string simulate(string in)
    {
        q_S cur_state = start;

        for (string::const_iterator i = in.begin(); i != in.end(); ++i)
        {
            transition trans = make_pair(cur_state, *i);

            if (transitions_table.find(trans) == transitions_table.end())
                return "REJECT";

            cur_state = transitions_table[trans];
        }

        if (final.find(cur_state) != final.end())
            return "ACCEPT";
        else
            return "REJECT";
    }

	

    void show()
        {
            cout << "\\documentclass{article}" << endl << endl;
            cout << "\\usepackage{tikz}" << endl;
    	    cout << "\\usetikzlibrary{automata,positioning}" << endl;
            cout << "\\begin{document}" << endl;
            cout << "\\begin{tikzpicture}[shorten >=1pt,node distance=2cm,on grid,auto]" << endl;


            bool accepting[transitions_table.size()];
            bool existing[transitions_table.size()];

            for(int i = 0; i < transitions_table.size(); i ++) {
                accepting[i] = false;
                existing[i] = false;
            }

            for (set<q_S>::const_iterator i = final.begin(); i != final.end(); ++i) {
                accepting[*i] = true;
            }


            for (   map<transition, q_S>::const_iterator i = transitions_table.begin();
                    i != transitions_table.end(); ++i)
            {
                existing[(i->first).first] = true;

            }



            for(int i = 0; i < transitions_table.size(); i ++) {
                if(i ==0 && existing[i]) {
                    cout << "\\node[state,initial] (" << i << ") {" << i << "};" << endl;
                } else if (existing[i]) {
                    cout << "\\node[state";
                    if(accepting[i]) {
                        cout << ",accepting] (" << i << ") ";
                    } else {
                        cout << "] (" << i << ")";
                    }if(i %2 == 0) {
                        cout << "[below right=of " << i -1 << "] {" << i << "};" << endl;
                    } else {
                        cout << "[above right=of " << i -1 << "] {" << i << "};" << endl;
                    }
                }
            }//for
    	cout << "\\path[->]" << endl;
    		map<transition, q_S>::const_iterator i = transitions_table.begin();
    	map<transition, q_S>::const_iterator i_last = --transitions_table.end();

    	cout << endl << endl;
    	int x = 0;
    	for (;	i != i_last; ++i) {

    				if(x == (i->first).first){
    					if((i->first).first == i->second){
    						cout << "(" << (i->first).first << ") " << "edge [loop above] node " << "{"<< (i->first).second << "} " <<  "()" <<endl;
    					}else{
    						cout << "(" << (i->first).first << ") " << "edge [bend right]  node  " << "{"<< (i->first).second << "} " <<  "(" << i->second - 1 << ")" <<endl;

    					}
    					x++;
    				} else {
    					if((i->first).first == i->second){
    						cout << "edge [loop above] node " << "{"<< (i->first).second << "} " <<  "()" <<endl;
    					}else{
    						cout << "edge [bend right] node" << "{"<< (i->first).second << "} " <<  "(" << i->second - 1 << ")" <<endl;

    					}
    				}
    	}//for


    	i = i_last;
    //need the same if statements for last element
    	if(x == (i->first).first){
    					if((i->first).first == i->second){
    						cout << "(" << (i->first).first << ") " << "edge [loop above] node " << "{"<< (i->first).second << "} " <<  "()" ;
    					}else{
    						cout << "(" << (i->first).first << ") " << "edge [bend right]  node " << "{"<< (i->first).second << "} " <<  "(" << i->second - 1 << ")" ;

    					}
    					x++;
    				} else {
    					if((i->first).first == i->second){
    						cout << "edge [loop above] node " << "{"<< (i->first).second << "} " <<  "()" ;
    					}else{
    						cout << "edge [bend right]  node " << "{"<< (i->first).second << "} " <<  "(" << i->second - 1 << ")" ;

    					}
    				}
    				cout << ";" << endl;
    				cout << "\\end{tikzpicture}" << endl;
    				cout << "\\end{document}" << endl;

        }

};



#endif // DFA_H
