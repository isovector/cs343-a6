#ifndef __PARENT_H
#define __PARENT_H

#include "printer.h"
#include "bank.h"

_Task Parent {
    Printer &printer;
    Bank &bank;
    
    void main();
    
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif
