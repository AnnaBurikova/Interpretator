#ifndef EXECUTE_H
#define EXECUTE_H
#include "lex.h"
#include "syntax.h"

#include <iostream>
#include <string>
#include <cstdio>
#include <ctype.h>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>

class Executer {
public:
    void execute ( vector<Lex> & poliz );
};

class Interpretator {
    Parser   pars;
    Executer E;
public:
    Interpretator ( const char* program ):
    pars (program) 
    {}
    void     interpretation ();
};

#endif
