#ifndef __PARENT_H
#define __PARENT_H

#include "printer.h"
#include "bank.h"

_Task Parent {
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif
