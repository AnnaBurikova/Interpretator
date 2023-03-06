#include <iostream>
#include <string>
#include <cstdio>
#include <ctype.h>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>

#include "execute.h"


int main () {
    try {
        Interpretator I ( "dev.txt" );
        I.interpretation ();
        return 0;
    }
    catch ( char c ) {
    	cout << "Error in str " << Lex::numb_of_str << endl;
        cout << "unexpected symbol " << c << endl;
        return 1;
    }
    catch ( Lex l ) {
    	cout << "Error in str " << Lex::numb_of_str << endl;
        cout << "unexpected lexeme" << l << endl;
        return 2;
    }
    catch ( const char *source ) {
        cout << source << endl;
        return 3;
    }
}
