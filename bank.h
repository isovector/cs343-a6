#ifndef __BANK_H
#define __BANK_H

#include <vector>
_Monitor Bank {
    std::vector<unsigned int> studentAccounts; 
  public:
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif
