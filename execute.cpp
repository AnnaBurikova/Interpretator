#include "execute.h"

#include <iostream>
#include <string>
#include <cstdio>
#include <ctype.h>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>



void Executer::execute ( vector<Lex> & poliz ) {
    Lex pc_el;
    stack <Lex> arglex;
    string stt;
    int isstr=0;
    Lex i, j;
    int index = 0, size = poliz.size();
    cout << "Size of poliz: " << size << endl;
    while ( index < size ) {
        pc_el = poliz [ index ];
        switch ( pc_el.t_lex ) {
            case POLIZ_ADDRESS: case POLIZ_LABEL:
                arglex.push ( pc_el );
                break;
            case LEX_NUM:
                arglex.push( Lex(LEX_INT, pc_el.get_value()));
                break;
                
            case LEX_STR:
                arglex.push ( Lex(LEX_STRING, 0, pc_el.get_value_s()));
                break;
 
            case LEX_ID:
            	//if (pc_el.get_type()==LEX_INT)
            	//{
            		int p;
				    p = pc_el.get_value ();
				    if ( Lex::TID[p].get_assign () ) {
				    	arglex.push ( Lex(Lex::TID[p].get_type(), Lex::TID[p].get_value(), Lex::TID[p].get_value_s() ));
				      break;
				    }
				    else
				    {
				    	cout << "Error in " << pc_el.nst << endl
;				      throw "POLIZ: indefinite identifier";
				}
				//}
				/*else
				{
					isstr=1;
					i = pc_el.get_value ();
				    if ( TID[i].get_assign () ) {
				      argss.push ( TID[i].get_value_s () );
				      break;
				    }
				    else
				      throw "POLIZ: indefinite identifier";
				} */
 
            case LEX_NOT:
                from_st ( arglex, i);
                arglex.push( Lex(LEX_INT, !(i.get_value())) );
                break;
 
            case LEX_OR:
                from_st ( arglex, i); 
                from_st ( arglex, j);
                arglex.push ( Lex(LEX_INT, j.get_value() || i.get_value()) );
                break;
 
            case LEX_AND:
                from_st ( arglex, i );
                from_st ( arglex, j );
                arglex.push ( Lex(LEX_INT, j.get_value() && i.get_value()) );
                break;
 
            case POLIZ_GO:
                from_st ( arglex, i );
                index = i.get_value() - 1;
                break;
 
            case POLIZ_FGO:
                from_st ( arglex, i );
                from_st ( arglex, j );
                if ( !(j.get_value()) ) index = i.get_value() - 1;
                break;
 
            case LEX_WRITE:
                from_st ( arglex, j );
                if (j.get_type()==LEX_INT)
                	cout << j.get_value() << endl;
                else
                	cout << j.get_value_s() << endl;
                break;
 
            case LEX_READ:
                int k;
                from_st ( arglex, i );
                if ( Lex::TID[i.get_value()].get_type () == LEX_INT ) {
                    cout << "Input int value for " << Lex::TID[i.get_value()].get_name () << endl;
                    cin >> k;
                    Lex::TID[i.get_value()].put_value (k);
                	Lex::TID[i.get_value()].put_assign ();
                }
                else {
                    while (1) {
                        cout << "Input string value for " << Lex::TID[i.get_value()].get_name() << endl;
                        cin >> stt;
                        /*if ( j != "true" && j != "false" ) {
                            cout << "Error in input:true/false" << endl;
                            continue;
                        } */
                        //k = ( j == "true" ) ? 1 : 0;
                        break;
                    }
                    Lex::TID[i.get_value()].put_value (stt);
                	Lex::TID[i.get_value()].put_assign ();
                }
                break;
 
            case LEX_PLUS:
                from_st ( arglex, i );
                from_st ( arglex, j );
                if (i.get_type()==LEX_INT)
                	arglex.push ( Lex(LEX_INT, i.get_value() + j.get_value()) );
                else
                	arglex.push ( Lex(LEX_STRING, 0, j.get_value_s() + i.get_value_s()) );
                break;
 
            case LEX_TIMES:
                from_st ( arglex, i );
                from_st ( arglex, j );
                arglex.push ( Lex(LEX_INT, i.get_value() * j.get_value()) );
                break;
 
            case LEX_MINUS:
                from_st ( arglex, i );
                from_st ( arglex, j );
                arglex.push ( Lex(LEX_INT, j.get_value() - i.get_value()) );
                break;
 
            case LEX_SLASH:
                from_st ( arglex, i );
                from_st ( arglex, j );
                if (i.get_value()!=0) {
                    arglex.push ( Lex(LEX_INT, j.get_value() / i.get_value()) );
                    break;
                }
                else
                {
                	cout << "Error in str " << pc_el.nst << endl;
                    throw "POLIZ:divide by zero";
                }
 
            case LEX_EQ:
                from_st ( arglex, i );
                from_st ( arglex, j );
                if (i.get_type()==LEX_INT)
                	arglex.push ( Lex(LEX_INT, i.get_value() == j.get_value()) );
                else
                	arglex.push ( Lex(LEX_INT, i.get_value_s() == j.get_value_s()) );
                break;
 
            case LEX_LSS:
                from_st ( arglex, i );
                from_st ( arglex, j );
                if (i.get_type()==LEX_INT)
                	arglex.push ( Lex(LEX_INT, j.get_value() < i.get_value()) );
                else
                	arglex.push ( Lex(LEX_INT, j.get_value_s() < i.get_value_s()) );
                break;
 
            case LEX_GTR:
                from_st ( arglex, i );
                from_st ( arglex, j );
                if (i.get_type()==LEX_INT)
                	arglex.push ( Lex(LEX_INT, j.get_value() > i.get_value()) );
                else
                	arglex.push ( Lex(LEX_INT, j.get_value_s() > i.get_value_s()) );
                break;
 
            case LEX_LEQ:
                from_st ( arglex, i );
                from_st ( arglex, j );
                arglex.push ( Lex(LEX_INT, j.get_value() <= i.get_value()) );
                break;
 
            case LEX_GEQ:
                from_st ( arglex, i );
                from_st ( arglex, j );
                arglex.push ( Lex(LEX_INT, j.get_value() >= i.get_value()) );
                break;
 
            case LEX_NEQ:
                from_st ( arglex, i );
                from_st ( arglex, j );
                if (i.get_type()==LEX_INT)
                	arglex.push ( Lex(LEX_INT, j.get_value() != i.get_value()) );
                else
                	arglex.push ( Lex(LEX_INT, j.get_value_s() != i.get_value_s()) );
                break;
 
            case LEX_ASSIGN:
                from_st ( arglex, i );
                from_st ( arglex, j );
                if (i.get_type()==LEX_INT)
                {
                	Lex::TID[j.get_value()].put_value (i.get_value());
                	Lex::TID[j.get_value()].put_assign ();
                }
                else
                {
                	Lex::TID[j.get_value()].put_value (i.get_value_s());
                	Lex::TID[j.get_value()].put_assign ();
                }
                break;
 
            default:
            	 cout << "Error in str " << pc_el.nst << endl;
                throw "POLIZ: unexpected elem";
        }//end of switch
        ++index;
    };//end of while
    cout << "Finish of executing!!!" << endl;
}

void Interpretator::interpretation () {
	pars.analyze ();
    E.execute ( pars.poliz );
}
