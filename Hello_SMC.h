#ifndef _HELLO_H__
#define _HELLO_H__
#include "Hello_sm.h"

struct Hello
{
    /* data */
    struct HelloContext _fsm;
    
};

extern struct  Hello HelloEntity;

extern void Hello_ReceiveBuff(struct Hello *this,char *buff);
extern void Hello_ProcessReceive(struct Hello *this, char *buff);

#endif
