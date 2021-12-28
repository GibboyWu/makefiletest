#include "Hello.h"
#include <stdio.h>
#include <string.h>
//#include "Hello_sm.h"
#if 1
#define getOwner(fsm) (fsm)->_owner



static void HelloState_receiveBuff(struct HelloContext *const fsm, char* buff)
{
    getState(fsm)->Default(fsm);
}

static void HelloState_receiveSpecial(struct HelloContext *const fsm, char* buff)
{
    getState(fsm)->Default(fsm);
}

static void HelloState_Default(struct HelloContext *const fsm)
{
    State_Default(fsm);
}

#define HelloMap_Idle_receiveBuff HelloState_receiveBuff
#define HelloMap_Idle_receiveSpecial HelloState_receiveSpecial
#define HelloMap_Idle_Default HelloState_Default
#define HelloMap_Busy_receiveBuff HelloState_receiveBuff
#define HelloMap_Busy_receiveSpecial HelloState_receiveSpecial
#define HelloMap_Busy_Default HelloState_Default
#define HelloMap_DefaultState_receiveBuff HelloState_receiveBuff
#define HelloMap_DefaultState_receiveSpecial HelloState_receiveSpecial

#undef HelloMap_Idle_Default
static void HelloMap_Idle_Default(struct HelloContext *const fsm)
{
    struct Hello *ctxt = getOwner(fsm);
    const struct HelloState* EndStateName = getState(fsm);

    clearState(fsm);
    Hello_ProcessDefault(ctxt);
    setState(fsm, EndStateName);

}

#undef HelloMap_Idle_receiveBuff
static void HelloMap_Idle_receiveBuff(struct HelloContext *const fsm, char* buff)
{
    struct Hello *ctxt = getOwner(fsm);

    clearState(fsm);
    Hello_ProcessReceive(ctxt, buff);
    setState(fsm, &HelloMap_Busy);

}

const struct HelloState HelloMap_Idle = {
    HelloMap_Idle_receiveBuff,
    HelloMap_Idle_receiveSpecial,
    HelloMap_Idle_Default,
    0
};

#undef HelloMap_Busy_Default
static void HelloMap_Busy_Default(struct HelloContext *const fsm)
{
    struct Hello *ctxt = getOwner(fsm);
    const struct HelloState* EndStateName = getState(fsm);

    clearState(fsm);
    Hello_ProcessDefault(ctxt);
    setState(fsm, EndStateName);

}

#undef HelloMap_Busy_receiveBuff
static void HelloMap_Busy_receiveBuff(struct HelloContext *const fsm, char* buff)
{

    setState(fsm, &HelloMap_Busy);

}

#undef HelloMap_Busy_receiveSpecial
static void HelloMap_Busy_receiveSpecial(struct HelloContext *const fsm, char* buff)
{
    struct Hello *ctxt = getOwner(fsm);

    clearState(fsm);
    Hello_Process(ctxt, buff);
    setState(fsm, &HelloMap_Idle);

}

const struct HelloState HelloMap_Busy = {
    HelloMap_Busy_receiveBuff,
    HelloMap_Busy_receiveSpecial,
    HelloMap_Busy_Default,
    1
};

#ifdef NO_HELLO_SM_MACRO
void HelloContext_Init(struct HelloContext *const fsm, struct Hello *const owner)
{
    FSM_INIT(fsm, &HelloMap_Idle);
    fsm->_owner = owner;
}

void HelloContext_receiveBuff(struct HelloContext *const fsm, char* buff)
{
    const struct HelloState* state = getState(fsm);

    assert(state != NULL);
    setTransition(fsm, "receiveBuff");
    state->receiveBuff(fsm, buff);
    setTransition(fsm, NULL);
}

void HelloContext_receiveSpecial(struct HelloContext *const fsm, char* buff)
{
    const struct HelloState* state = getState(fsm);

    assert(state != NULL);
    setTransition(fsm, "receiveSpecial");
    state->receiveSpecial(fsm, buff);
    setTransition(fsm, NULL);
}
#endif
#endif

struct  Hello HelloEntiy;

void Hello_init(struct  Hello *this)
{
    /* data */
    printf("Hello init\n");

    memset(this,0,sizeof(struct Hello));

    HelloContext_Init(&this->_fsm,this);

};
//添加以下状态机中的实现函数
 void Hello_ReceiveBuff(struct Hello *this,char *buff)
 {
     printf("Hello_ReceiveBuf\n");
     HelloContext_receiveBuff(&this->_fsm,buff);
 }

void Hello_ReceiveSpecial(struct Hello *this,char *buff)
{
    printf("Hello_ReceiveSpecial\n");
    HelloContext_receiveSpecial(&this->_fsm,buff);
}

 void Hello_ProcessReceive(struct Hello *this, char *buff)
{
    printf("Hello_ProcessReceive\n");
}
void Hello_Process(struct Hello *this,char *buff)
{
    printf("Hello_Process");
}
void Hello_ProcessDefault()
{
    printf("hello default\n");
}


//将生成的状态机直接拷贝到当前文件中，因分开多个文件编译调试需要makefile，而makefile暂时编写调试未成功
int main()
{
    Hello_init(&HelloEntiy);
    char *buff ="abbf";
    Hello_ReceiveBuff(&HelloEntiy,buff);
    Hello_ReceiveSpecial(&HelloEntiy,buff);

    printf("%d\r\n",HelloEntiy._fsm._previous_state);
    printf("%d\r\n",HelloEntiy._fsm._state);
    printf("%d\r\n",HelloEntiy._fsm._owner);
    printf("%d\r\n",HelloEntiy._fsm._stack_curr);
    printf("%d\r\n",HelloEntiy._fsm._stack_max);
    printf("%d\r\n",HelloEntiy._fsm._stack_start);

    return 0;
}
