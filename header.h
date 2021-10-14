/*
    где гарды?
    почему тут инклюды?
*/
#ifndef STDIO
    #define STDIO
    #include <stdio.h>
#endif
#ifndef STDLIB
    #define STDLIB
    #include <stdlib.h>
#endif
#ifndef CTYPE
    #define CTYPE
    #include <ctype.h>
#endif
#ifndef CMATH
    #define CMATH
    #include <cmath>
#endif

#define type int
#define DEBUG_LVL 3
const type POISON = 0xDEAD; 

/*
                    +--> code, при DEBUG_LVL > 1
                    |
is_debug(code) -----+
                    |
                    +--> `пустота`, при !(DEBUG_LVL > 1)
*/

#if DEBUG_LVL > 0
    #define is_debug_lvl_0(code) code
#else
    #define is_debug_lvl_0(code) ;
#endif

#if DEBUG_LVL > 1
    #define is_debug_lvl_1(code) code
#else
    #define is_debug_lvl_1(code) ;
#endif

#ifndef DEBUG
    #define DEBUG
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
            ERR_RIGHT_DATACANARY_DAMAGED   =    1 << 13,
            ERR_RESIZE_FAILED              =    1 << 14,
            ERR_POP_FAILED                 =    1 << 15,
            ERR_DUMP_FAILED                =    1 << 16,
            ERR_STACK_BROKEN               =    1 << 17
        };

        #define STACK_CREATION_INFO(stack) {                                                                  \
            fprintf(logs, "Stack \"%s\" was created in function \"%s\" on line %d."                           \
            "Adress %p with addrreess of data: %p\n\n\n", #stack, __PRETTY_FUNCTION__, __LINE__,              \
            stack, stack->data);                                                                              \
        }

        #define STACK_DUMP(stack) {                                                                           \
            verifyStack(stack);                                                                               \
            stackDump(stack, __func__, #stack);                                                               \
        }   


        #define CHECK_PTR(arg) {                                                                              \
            if (!(arg)) {                                                                                     \
                fprintf(logs, "[%s:%d] --- %s failed\n\n\n", __func__, __LINE__, #arg);                       \
                return ERR_INVALID_PTR;                                                                       \
            }                                                                                                 \
        }

        #define ASSERT_OK(stack) {                                                                            \
            if (stack->status) return ERR_STACK_BROKEN;                                                       \
        }

        #define FUNC_REPORT(func, stack) {                                                                    \
            int status = (int) func;                                                                          \
            if (status) {                                                                                     \
                fprintf(logs, "########################################################################\n"    \
                            "function \"%s\" was failed with error code:\n", #func);                        \
                printError(status);                                                                           \
                fprintf(logs, "\nStack is:\n");                                                               \
                STACK_DUMP(stack)                                                                             \
                fprintf(logs, "########################################################################\n");  \
                return ERR_CALLING_FUNC_FAILED;                                                               \
            }                                                                                                 \
        }

        #define CANARY(Stack) 0xFEE1DEAD^((u_int64_t) Stack)
    #endif

#endif

struct Stack
{
    
    is_debug_lvl_1(u_int64_t egg);
    type* data;
    int size;
    int capacity;
    is_debug_lvl_0(
        int status;
        is_debug_lvl_1(u_int64_t hash);
        is_debug_lvl_1(u_int64_t chicken);  
    ) 
};

/*
    доки?
*/
int stackCtor(Stack* stk, int capacity);
int stackDtor(Stack* stk);
int stackPush(Stack* stk, type value);
type stackPop(Stack* stk, type* param);
void stackDump(const Stack* stk, const char* func_name, const char* stack_name);
void verifyStack(Stack* stk);
void printError(int Error);
