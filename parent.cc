#include "parent.h"

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay) :
    printer(prt), bank(bank), parentalDelay(parentalDelay), numStudents(numStudents)
{
}

void Parent::main() {
    while( true )
    {
        _Accept( ~Parent )
        {
            break;
        }
        _Else 
        {
            unsigned int amount = mprand( 1, 3 );
            unsigned int studentID = mprand( numStudents );
            yield(parentalDelay);
            bank.deposit( studentID, amount );
        }
    }
}
