#include "header.h"
extern FILE* logs;

static int capacity_calc(int elements_amount);
static int stackResize(Stack* stk, int upper);


int stackCtor(Stack* stk, int capacity) {
    CHECK_PTR(stk)
    verifyStack(stk);
    STACK_DUMP(stk)

    stk->data = (type*) calloc ( (int) pow(2, (int) (log(capacity) / log(2)) + 1 ), sizeof(type));
    stk->capacity = (int) pow(2, (int) (log(capacity) / log(2)) + 1 );

    for (int i = 0; i < stk->capacity; i++){
        stk->data[i] = poison;
    }
    STACK_CREATION_INFO(stk)
    STACK_DUMP(stk)
    return 0;
}


int stackDtor(Stack* stk) {
    CHECK_PTR(stk)
    STACK_DUMP(stk)

    stk->capacity = 0;
    stk->size = 0;

    free(stk->data);
    stk->data = (type*) 0xBEBE;
    return 0;
}


int stackPush(Stack* stk, type value) {
    CHECK_PTR(stk)
    STACK_DUMP(stk)

    if (stk->size + 1 > stk->capacity){
        if (stackResize(stk, 1) == 1){
            fprintf(logs, "Error in %s on %d line: not enough memory for stack\n\n\n", __FUNCTION__, __LINE__);
            return 1;
        }
    }
    stk->size ++;
    stk->data[stk->size - 1] = value;

    return 0;
}


static int stackResize(Stack* stk, int upper) {
    CHECK_PTR(stk)
    STACK_DUMP(stk)

    if (upper) {
        if (stk->capacity == 0) {
            stk->capacity = 1;
            
            if (realloc(stk->data, sizeof(type) * 1) != nullptr) {
                for (int i = stk->size; i < stk->capacity; i++) {
                    stk->data[i] = poison;
                }

                return 0;
            }
            else return 1;
        }

        if (realloc(stk->data, sizeof(type) * stk->capacity * 2) != nullptr) {
            stk->capacity *= 2;
            for (int i = stk->size; i < stk->capacity; i++) {
                    stk->data[i] = poison;
            }

            return 0;
        }
        else return 1;
    }
    else{
        realloc(stk->data, sizeof(type) * (stk->capacity / 2));
        stk->capacity /=2;
        return 0;
    }
}


type stackPop(Stack* stk){
    STACK_DUMP(stk)

    type elem = stk->data[--stk->size];
    stk->data[stk->size] = poison;

    while (stk->capacity / 2 - stk->size > 3) {
        stackResize(stk, 0);
    }
    return elem;
}


int verifyStack(Stack* stk){
    int isNotOk = 0;        

    if (stk->data == (type*) 0xBEBE) {                                                              
        stk->status = ERR_STACK_ALREADY_CLEANED;                     
        isNotOk = 1;                                                                                  
    }                                                                                                 
    if (stk->size > stk->capacity) {                                                              
        stk->status = ERR_SIZE_GREATER_CAPACITY;                       
        isNotOk = 1;                                                                                  
    } 

    for (int i = stk->size; i < stk->capacity; i++){
        if (stk->data[i] != poison){
            stk->status = ERR_EMPTY_ELEM_ISNT_POISONED;
        }
    }

    return isNotOk; 
}


void stackDump(const Stack* stk, const char* func_name, const char* stack_name){
    fprintf(logs, "Stack <> adress[%p] \"%s\" at %s\n", stk, stack_name, func_name);
    fprintf(logs, "---------------------------------------------------------------------------------\n");
    fprintf(logs, "STATUS = %16s\n" "stack size = %12d\n" "stack capacity = %8d\n" 
            "data [%p]\n", (stk->status == OK) ? "OK" : "BROKEN", stk->size, stk->capacity, stk->data);

    if (stk->status){
        switch (stk->status){
            case ERR_EMPTY_ELEM_ISNT_POISONED:
                fprintf(logs, "Empty element isn't poisoned\n");
                break;

            case ERR_SIZE_GREATER_CAPACITY:
                fprintf(logs, "Stack size if greater than stack capacity\n");
                break;

            case ERR_STACK_ALREADY_CLEANED:
                fprintf(logs, "Stack has been already cleaned before\n");
                break;
        }
    }
    else{
        for (int i = 0; i < stk->size; i++){
            fprintf(logs, "*data[%d] = %d\n", i, stk->data[i]);
        }
        for (int i = stk->size; i < stk->capacity; i++){
            fprintf(logs, "*data[%d] = %X\n", i, stk->data[i]);
        }
    }

    fprintf(logs, "---------------------------------------------------------------------------------\n\n\n");
}