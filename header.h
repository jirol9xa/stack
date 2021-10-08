#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <cmath>
#define type int
#define POISON 0xDEAD
#define DEBUG_LVL 3 

#if (DEBUG_LVL > 0)
enum Error {
            OK = 0, 
            ERR_CALLING_FUNC_FAILED        =         1,
            ERR_STACK_ALREARY_CREATED      =    1 << 1,
            ERR_EMPTY_ELEM_ISNT_POISONED   =    1 << 2,
            ERR_SIZE_GREATER_CAPACITY      =    1 << 3,
            ERR_POP_EMPTY_STACK            =    1 << 4,
            ERR_RIGHT_CANARY_DAMAGED       =    1 << 5,
            ERR_LEFT_CANARY_DAMAGED        =    1 << 6,
            ERR_WRONG_HASH                 =    1 << 7,
            ERR_INVALID_PTR                =    1 << 8,
            ERR_REALLOC_FAILED             =    1 << 9,
            ERR_PUSH_FAILED                =    1 << 10,
            ERR_STACK_ALREADY_CLEANED      =    1 << 11,
            ERR_LEFT_DATACANARY_DAMAGED    =    1 << 12,
            ERR_RIGHT_DATACANARY_DAMAGED   =    1 << 13
            };



#define STACK_CREATION_INFO(stack) {                                                                  \
    fprintf(logs, "Stack \"%s\" was created in function \"%s\" on line %d."                           \
    "Adress %p with adrsss of data: %p\n\n\n", #stack, __PRETTY_FUNCTION__, __LINE__,                 \
    stack, stack->data);                                                                              \
}


#define STACK_DUMP(stack) {                                                                           \
    verifyStack(stack);                                                                               \
    stackDump(stack, __func__, #stack);                                                               \
}   


#define CHECK_PTR(arg) {                                                                              \
    if (!arg){                                                                                        \
        fprintf(logs, "[%s:%d] --- %s failed\n\n\n", __func__, __LINE__, #arg);                       \
        return 1 << 8;                                                                                     \
    }                                                                                                 \
}


#define FUNC_REPORT(func_status, stack) {                                                             \
    if (func_status) {                                                                                \
        fprintf(logs, "########################################################################\n"    \
        "function \"%s\" was failed with error code:\n", __func__);                                   \
        printError(func_status);                                                                      \
        fprintf(logs, "Stack is:\n");                                                                 \
        STACK_DUMP(stack)                                                                             \
        fprintf(logs, "########################################################################\n");  \
        return func_status;                                                                           \
    }                                                                                                 \
}   
#endif


struct Stack
{
    #if DEBUG_LVL > 1
        __int64_t egg;
    #endif
    type* data;
    int size;
    int capacity;
    #if (DEBUG_LVL > 0)
        int status;
        #if (DEBUG_LVL > 1)
            __int64_t hash;
            __int64_t chicken;
        #endif   
    #endif
};


int stackCtor(Stack* stk, int capacity);
int stackDtor(Stack* stk);
int stackPush(Stack* stk, type value);
type stackPop(Stack* stk, type* param);
void stackDump(const Stack* stk, const char* func_name, const char* stack_name);
int verifyStack(Stack* stk);
void printError(int Error);
