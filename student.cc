#include "student.h"

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
        unsigned int maxPurchases ) :
    printer(prt), server(nameServer), office(cardOffice)
{
}
        
void Student::main() {
}
