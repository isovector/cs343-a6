#ifndef __WATCARD_H
#define __WATCARD_H

#include "uFuture.h"

class WATCard {
    unsigned int balance;
    
    WATCard( const WATCard & );            // prevent copying
    WATCard &operator=( const WATCard & );
  public:
    WATCard();
    
    void deposit( unsigned int amount );
    void withdraw( unsigned int amount );
    unsigned int getBalance();
};

// future watcard pointer
typedef Future_ISM<WATCard *> FWATCard;

#endif
