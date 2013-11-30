#include "student.h"
#include "watcard.h"

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
        unsigned int maxPurchases ) :
    printer(prt), server(nameServer), office(cardOffice), id(id), maxPurchases(maxPurchases)
{
}
        
void Student::main() 
{
    unsigned int numPurchases = mprand( 1, maxPurchases );
    unsigned int flavour = mprand( 3 ); //
    WATCard::FWATCard card = office.create( id, 5 );
    server.getMachine( id );
}
