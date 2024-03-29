#ifndef __WATCARD_OFFICE_H
#define __WATCARD_OFFICE_H

//_Monitor WATCard;
#include "watcard.h"
#include "MPRNG.h"
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
            Printer &printer;
            Bank &bank;
            WATCardOffice &office;
            void main();
          public:
            Courier( Printer &printer, Bank &bank, WATCardOffice &office ) : printer(printer), bank(bank), office(office) {};
            virtual ~Courier();
    };                 // communicates with bank

    Printer &printer;
    void main();
    unsigned int numCouriers;

    std::list<WATCardOffice::Job*> jobList;
    std::list<WATCardOffice::Courier*> courierList;
  public:
    
    _Event Lost {};                        // uC++ eWATCARD_OFFICEception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    virtual ~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif
