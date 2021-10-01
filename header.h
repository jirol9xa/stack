#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <cmath>
#define type int
#define poison 0xDEAD


enum Error {
            OK = 0, 
            ERR_STACK_ALREADY_CLEANED = 1,
            ERR_SIZE_GREATER_CAPACITY = 2,
            ERR_EMPTY_ELEM_ISNT_POISONED = 4
            };


#define STACK_OK(stack) {                                                                             \
    int isNotOk = 0;                                                                                  \
    if (stack->data == (type*) 0xBEBE) {                                                              \
        fprintf(logs, "[%s:%d] Ops something wrong:"                                                  \
        "the stack has already been cleared\n", __PRETTY_FUNCTION__, __LINE__);                       \
        isNotOk = 1;                                                                                  \
    }                                                                                                 \
    if (stack->size > stack->capacity) {                                                              \
        fprintf(logs, "[%s:%d] Ops something wrong:"                                                  \
        "stack size is greater than capacity\n", __PRETTY_FUNCTION__, __LINE__);                      \
        isNotOk = 1;                                                                                  \
    }                                                                                                 \
    if (isNotOk) return isNotOk;                                                                      \
}


#define STACK_CREATION_INFO(stack){                                                                   \
    fprintf(logs, "Stack \"%s\" was created in function \"%s\" on line %d."                           \
    "Adress %p with adrsss of data: %p\n\n\n", #stack, __PRETTY_FUNCTION__, __LINE__,                 \
    stack, stack->data);                                                                              \
}


#define STACK_DUMP(stack){                                                                            \
    verifyStack(stack);                                                                               \
    stackDump(stack, __func__, #stack);                                                               \
}   


#define CHECK_PTR(arg) {                                                                              \
    if (!arg){                                                                                        \
        fprintf(logs, "[%s:%d] --- %s failed\n\n\n", __func__, __LINE__, #arg);                       \
        return 1;                                                                                     \
    }                                                                                                 \
}


struct Stack{
    type* data;
    int size;
    int capacity;
    Error status;
};


int stackCtor(Stack* stk, int capacity);
int stackDtor(Stack* stk);
int stackPush(Stack* stk, type value);
type stackPop(Stack* stk);
void stackDump(const Stack* stk, const char* func_name, const char* stack_name);
int verifyStack(Stack* stk);
