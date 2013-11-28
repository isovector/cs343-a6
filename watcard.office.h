#ifndef __WATCARD_OFFICE_H
#define __WATCARD_OFFICE_H

//_Monitor WATCard;
#include "watcard.h"
#include <list>
_Monitor Printer;
_Monitor Bank;

_Task WATCardOffice 
{
    struct Job 
    {                           // marshalled arguments and return future
        struct JobArgList 
        {
            unsigned int id;
            unsigned int amount;
            WATCard *card;
            JobArgList(  unsigned int id, unsigned int amount, WATCard *card) : id(id), amount(amount), card(card) {};
        };
        JobArgList args;
        WATCard::FWATCard result;                   // return future
        Job( JobArgList args ) : args(args) {}
    };

    _Task Courier {
            Bank &bank;
            WATCardOffice &office;
            void main();
          public:
            Courier( Bank &bank, WATCardOffice &office ) : bank(bank), office(office) {};
    };                 // communicates with bank

    Printer &printer;
    void main();

    std::list<Job> jobList;
  public:
    
    _Event Lost {};                        // uC++ eWATCARD_OFFICEception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif
