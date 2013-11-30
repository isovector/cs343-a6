#ifndef __STUDENT_H
#define __STUDENT_H

#include "printer.h"
#include "nameserver.h"
#include "watcard.office.h"
#include "watcard.h"
#include <uFuture.h>

_Task Student {
    Printer &printer;
    NameServer &server;
    WATCardOffice &office;
    const unsigned int id;
    const unsigned int maxPurchases;
    
    void main();
  public:
    typedef Future_ISM<WATCard *> FWATCard;
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif
