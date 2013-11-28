#ifndef __STUDENT_H
#define __STUDENT_H

_Task Student {
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maSTUDENTPurchases );
};

#endif
