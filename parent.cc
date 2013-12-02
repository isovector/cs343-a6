#include "parent.h"

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay) :
    printer(prt), bank(bank), parentalDelay(parentalDelay), numStudents(numStudents)
{
}

#define print(state, varargs...) printer.print(Printer::Parent, state, ##varargs)

Parent::~Parent() {
    print('F');
}

void Parent::main() {
    print('S');
    
    while( true )
    {
        _Accept( ~Parent )
        {
            break;
        }
        _Else 
        {
            unsigned int amount = mprand( 1, 3 );
            unsigned int studentID = mprand( numStudents - 1 );
            yield(parentalDelay);
            
            print('D', studentID, amount);
            bank.deposit( studentID, amount );
        }
    }
}

#undef print
