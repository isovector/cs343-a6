#ifndef __WATCARD_OFFICE_H
#define __WATCARD_OFFICE_H

#include "printer.h"
#include "bank.h"
#include "watcard.h"

// eat a fat dick, uc++
#define Args int

_Task WATCardOffice {
    Printer &printer;
    Bank &bank;
    
    struct Job {                           // marshalled arguments and return future
        Args args;                         // call arguments (YOU DEFINE "Args")
        FWATCard result;                   // return future
        Job( Args args ) : args( args ) {}
    };
    _Task Courier {  };                 // communicates with bank

    void main();
  public:
    _Event Lost {};                        // uC++ eWATCARD_OFFICEception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    FWATCard create( unsigned int sid, unsigned int amount );
    FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif
