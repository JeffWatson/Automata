
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <assert.h>  
#include "nfa.h"
#include "subset_construct.h"

using namespace std;


class scanner
{
public:
    void init(string data_)
    {
        data = preprocess(data_);
        next = 0;
    }

    char insider(void)
    {
        return (next < data.size()) ? data[next] : 0;
    }

    char pop(void)
    {
        char current = insider();

        if (next < data.size())
            ++next;

        return current;
    }

    unsigned get_pos(void)
    {
        return next;
    }

    friend scanner& current_scan(void);

private:
    scanner()
    {}

    string preprocess(string in);

    string data;
    unsigned next;
};


// Concatenation algorithm (only appropiate characters)
string scanner::preprocess(string in)
{
    string out = "";

    string::const_iterator a = in.begin(), up = a + 1;

    // currenct character will only a
    //
    for (; up != in.end(); ++a, ++up)
    {
        out.push_back(*a);

        if ((isalnum(*a) || *a == ')' || *a == '*' || *a == '?') &&
            (*up != ')' && *up != '|' && *up != '*' && *up != '?'))
            out.push_back('.');
    }

    // don't forget the last char ...
    //
    if (a != in.end())
        out.push_back(*a);

    return out;
}


scanner& current_scan(void)
{
    static scanner my_scan;
    return my_scan;
}



typedef enum {CHR, STAR, QUESTION, ALTER, CONCAT} node_type;


// Parse node
//
struct node
{
    node(node_type type_, char data_, node* left_, node* right_)
            : type(type_), data(data_), left(left_), right(right_)
    {}

    node_type type;
    char data;
    node* left;
    node* right;
};


node* expr();




NFA tree_to_nfa(node* tree)
{
    assert(tree);

    switch (tree->type)
    {
    case CHR:
        return build_nfa_basic(tree->data);
    case ALTER:
        return build_nfa_alter(tree_to_nfa(tree->left), tree_to_nfa(tree->right));
    case CONCAT:
        return build_nfa_concat(tree_to_nfa(tree->left), tree_to_nfa(tree->right));
    case STAR:
        return build_nfa_star(tree_to_nfa(tree->left));
    case QUESTION:
        return build_nfa_alter(tree_to_nfa(tree->left), build_nfa_basic(EPS));
    default:
        assert(0);
    }
}



node* chr()
{
    char data = current_scan().insider();

    if (isalnum(data) || data == 0)
    {
        return new node(CHR, current_scan().pop(), 0, 0);
    }

    cerr 	<< "Parse error: expected alphanumeric, got "
    <<  current_scan().insider() << " at #" << current_scan().get_pos() << endl;
    exit(1);
}


// atom ::= chr
//      |   '(' expr ')'
//
node* atom()
{
    node* atom_node;

    if (current_scan().insider() == '(')
    {
        current_scan().pop();
        atom_node = expr();

        if (current_scan().pop() != ')')
        {
            cerr << "Parse error: expected ')'" << endl;
            exit(1);
        }
    }
    else
    {
        atom_node = chr();
    }

    return atom_node;
}


//   ::= atom '*'
//   |   atom '?'
//   |   atom
//
node* rep()
{
    node* atom_node = atom();

    if (current_scan().insider() == '*')
    {
        current_scan().pop();

        node* rep_node = new node(STAR, 0, atom_node, 0);
        return rep_node;
    }
    else if (current_scan().insider() == '?')
    {
        current_scan().pop();

        node* rep_node = new node(QUESTION, 0, atom_node, 0);
        return rep_node;
    }
    else
    {
        return atom_node;
    }
}


// concat   ::= rep . concat
//          |   rep
//
node* concat()
{
    node* left = rep();

    if (current_scan().insider() == '.')
    {
        current_scan().pop();
        node* right = concat();

        node* concat_node = new node(CONCAT, 0, left, right);
        return concat_node;
    }
    else
    {
        return left;
    }
}


// expr ::= concat '|' expr
//      |   concat
//
node* expr(void)
{
    node* left = concat();

    if (current_scan().insider() == '|')
    {
        current_scan().pop();
        node* right = expr();

        node* expr_node = new node(ALTER, 0, left, right);
        return expr_node;
    }
    else
    {
        return left;
    }
}


int main(int argc, char** argv)
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <regex> <string>" << endl;
        exit(1);
    }
	
    current_scan().init(argv[1]);

    node* n = expr();

    if (current_scan().insider() != 0)
    {
        cerr    << "Parse error: unexpected char " << current_scan().insider() 
                << " at #" << current_scan().get_pos() << endl;
        exit(1);
    }

    NFA nfa = tree_to_nfa(n);
	DFA dfa = subset_construct(nfa);
    dfa.show();

    return 0;
}
