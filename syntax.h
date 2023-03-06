#ifndef SYNTAX_H
#define SYNTAX_H

#include "lex.h"

#include <iostream>
#include <string>
#include <cstdio>
#include <ctype.h>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>

class Parser {
    Lex          curr_lex;
    type_of_lex  c_type;
    int          c_val;
    string s_val;
    Scanner      scan;
    stack < int >           st_int;
    stack < type_of_lex >   st_lex;
    void  P();
    void  D1();
    void  D(type_of_lex);
    void  B();
    void  S();
    void  E();
    void  E1();
    void  T();
    void  F();
    void  dec ( type_of_lex type);
    void  check_id ();
    void  check_op ();
    void  check_not ();
    void  eq_type ();
    void  eq_bool ();
    void  check_id_in_read ();
    void  gl () {
        curr_lex  = scan.get_lex ();
        c_type    = curr_lex.get_type ();
        s_val=curr_lex.get_value_s();
        c_val     = curr_lex.get_value ();
    }
public:
    vector <Lex> poliz;
    Parser ( const char *program ):
    scan (program) 
    { }
    void  analyze();
};

#endif
