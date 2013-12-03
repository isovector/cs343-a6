#include "parent.h"
#include <iostream>

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay) :
    printer(prt), bank(bank), parentalDelay(parentalDelay), numStudents(numStudents)
{
}

Parent::~Parent()
{
    printer.print( Printer::Parent, 'F' );
}

void Parent::main() {
    printer.print( Printer::Parent, 'S' );
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
            printer.print( Printer::Parent, 'D', studentID, amount );
            bank.deposit( studentID, amount );
        }
    }
}

#undef print
