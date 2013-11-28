#ifndef __WATCARD_H
#define __WATCARD_H

#include <uFuture.h>

class WATCard {
    WATCard( const WATCard & );            // prevent copying
    WATCard &operator=( const WATCard & );
    unsigned int balance;
  public:
    WATCard() : balance(0) {};
    typedef Future_ISM<WATCard *> FWATCard; // future watcard pointer
    void deposit( unsigned int amount );
    void withdraw( unsigned int amount );
    unsigned int getBalance();
};

#endif
