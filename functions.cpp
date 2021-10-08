#include "header.h"
extern FILE* logs;

static int capacity_calc(int elements_amount);
static int stackResize(Stack* stk, int upper);
static int memcpy(void* destination, void* sourse, int element_size);
static int hashCalc(Stack* stk);
static unsigned int MurmurHash2(char* key, unsigned int len);


int stackCtor(Stack* stk, int capacity) 
{
    #if  DEBUG_LVL > 0
        CHECK_PTR(stk)
        STACK_DUMP(stk)
    #endif

    stk->data = (type*) calloc ( 1 , sizeof(type) * (int) pow(2, (int) (log(capacity) / log(2)) + 1 ));

    #if DEBUG_LVL > 1
        void* temp_ptr = realloc(stk->data, sizeof(type) * (int) pow(2, (int) (log(capacity) / log(2)) + 1 ) + 24);
        if (temp_ptr != nullptr) {
            stk->data = (int*) temp_ptr;
        }
        else {
            fprintf(logs, "%s failed, not enough memory for safety stack\n", __func__);
            return 1;
        }
    
        stk->egg     = 0xFEE1DEAD^((int64_t) stk);
        stk->chicken = 0xFEE1DEAD^((int64_t) stk);
        memcpy(stk->data, &(stk->egg), sizeof(int64_t));
        memcpy((char*) stk->data + 8 + stk->capacity, &(stk->egg), sizeof(int64_t));
        stk->hash = hashCalc(stk);
    #endif

    stk->capacity = (int) pow(2, (int) (log(capacity) / log(2)) + 1 );

    for (int i = 0; i < stk->capacity; i++) {
        stk->data[i] = POISON;
    }

    #if DEBUG_LVL > 0
        STACK_CREATION_INFO(stk)
        STACK_DUMP(stk)
    #endif

    return 0;
}


int stackDtor(Stack* stk) 
{
    #if DEBUG_LVL > 0
        CHECK_PTR(stk)
        STACK_DUMP(stk)
    #endif

    stk->capacity = 0;
    stk->size = 0;

    free(stk->data);
    stk->data = (type*) 0xBEBE;
    stk->hash = hashCalc(stk);
    return 0;
}


int stackPush(Stack* stk, type value) 
{
    #if DEBUG_LVL > 0
        CHECK_PTR(stk)
        STACK_DUMP(stk)
    #endif

    if (stk->size + 1 > stk->capacity) {
        if (stackResize(stk, 1) == 1) {
            fprintf(logs, "Error in %s on %d line: not enough memory for stack\n\n\n", __FUNCTION__, __LINE__);

            #if DEBUG_LVL > 0
                FUNC_REPORT(ERR_PUSH_FAILED,stk)
            #endif

            return 1;
        }
    }
    stk->size ++;
    stk->data[stk->size - 1] = value;

    if (hashCalc(stk) == ERR_INVALID_PTR) return ERR_INVALID_PTR;

    return 0;
}


static int stackResize(Stack* stk, int upper) 
{
    #if DEBUG_LVL > 0
        CHECK_PTR(stk)
        STACK_DUMP(stk)
    #endif
    if (upper) {
        void* temp_ptr = nullptr;
        if (stk->capacity == 0) {
            stk->capacity = 1;
            
            temp_ptr = realloc(stk->data, sizeof(type) * 1);
            if (temp_ptr != nullptr) {
                for (int i = stk->size; i < stk->capacity; i++) {
                    stk->data[i] = POISON;
                }

                return 0;
            }
            else {

            #if DEBUG_LVL > 0
                FUNC_REPORT(ERR_REALLOC_FAILED,stk)
            #endif 

            return 1;
            }
        }
        temp_ptr = realloc(stk->data, sizeof(type) * stk->capacity * 2);
        if (temp_ptr != nullptr) {
            stk->capacity *= 2;
            for (int i = stk->size; i < stk->capacity; i++) {
                    stk->data[i] = POISON;
            }

            return 0;
        }
        else {

            #if DEBUG_LVL > 0
                FUNC_REPORT(ERR_REALLOC_FAILED, stk)
            #endif 
            
            return 1;
        }
    }
    else {
        realloc(stk->data, sizeof(type) * (stk->capacity / 2));
        stk->capacity /=2;
        return 0;
    }
}


int stackPop(Stack* stk, type* param)
{
    #if DEBUG_LVL > 0
        STACK_DUMP(stk)
    #endif

    memcpy(param, &(stk->data[--stk->size]), sizeof(type));
    stk->data[stk->size] = POISON;

    while (stk->capacity / 2 - stk->size > 3) {
        stackResize(stk, 0);
    }

    if (hashCalc(stk) == ERR_INVALID_PTR) return ERR_INVALID_PTR;
    return 0;
}


#if DEBUG_LVL > 0
    int verifyStack(Stack* stk){
        int isNotOk = 0;        

        if (stk->data == (type*) 0xBEBE) {                                                              
            stk->status |= ERR_STACK_ALREADY_CLEANED;                     
            isNotOk = 1;                                                                                  
        }                                                                                                 
        if (stk->size > stk->capacity) {                                                              
            stk->status |= ERR_SIZE_GREATER_CAPACITY;                       
            isNotOk = 1;                                                                                  
        } 
        if (stk->hash != hashCalc(stk)) {
            stk->status |= ERR_WRONG_HASH;
        }
        if (stk->egg != 0xFEE1DEAD^((int64_t) stk)) {
            stk->status |= ERR_LEFT_CANARY_DAMAGED;
        }
        if (stk->chicken != 0xFEE1DEAD^((int64_t) stk)) {
            stk->status |= ERR_RIGHT_CANARY_DAMAGED;
        }
        if ( *((int64_t*) stk->data) != 0xFEE1DEAD^((int64_t) stk)){
            stk->status |= ERR_LEFT_DATACANARY_DAMAGED;
        }
        if ( *((int64_t*) ((char*) stk->data + 8 + stk->capacity)) != 0xFEE1DEAD^((int64_t) stk)) {
            stk->status |= ERR_RIGHT_DATACANARY_DAMAGED;
        }

        for (int i = stk->size; i < stk->capacity; i++){
            if (stk->data[i] != POISON){
                stk->status |= ERR_EMPTY_ELEM_ISNT_POISONED;
                isNotOk = 1;
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
        else {
            for (int i = 0; i < stk->size; i++){
                fprintf(logs, "*data[%d] = %d\n", i, stk->data[i]);
            }
            for (int i = stk->size; i < stk->capacity; i++){
                fprintf(logs, "*data[%d] = %X\n", i, stk->data[i]);
            }
        }

        fprintf(logs, "---------------------------------------------------------------------------------\n\n\n");
        fclose(logs);
        logs = fopen("Logs", "a");
    }   

#endif


static int memcpy(void* destination, void* sourse, int element_size)
{
    #if DEBUG_LVL > 0
        CHECK_PTR(destination)
        CHECK_PTR(sourse)
    #endif

    char* dest = (char*) destination;
    char* srs = (char*) sourse;

    while (element_size >= 16) {
        *((__int128_t*) dest) = *((__int128_t*) srs);

        dest += 16;
        srs += 16;
        element_size -= 16;
    }
    while (element_size >= 8) {
        *((__int64_t*) dest) = *((__int64_t*) srs);

        dest += 8;
        srs += 8;
        element_size -= 8;
    }
    while (element_size >= 4) {
        *((__int32_t*) dest) = *((__int32_t*) srs);

        dest += 4;
        srs += 4;
        element_size -= 4;
    }
    while (element_size >= 2) {
        *((__int16_t*) dest) = *((__int16_t*) srs);

        dest += 2;
        srs += 2;
        element_size -=2;
    }
    if (element_size == 1) {
        *dest = *srs;
    }

    return 0;
}


#if DEBUG_LVL > 1
    static int hashCalc(Stack* stk) 
    {
        CHECK_PTR(stk)

        stk->hash = 0;
        stk->hash = MurmurHash2((char*) stk, sizeof(Stack)) + MurmurHash2((char*) stk->data, 16 + stk->capacity);

        return 0;
    }
#endif


static unsigned int MurmurHash2(char* key, unsigned int len) 
{
    const unsigned int m = 0x5bd1e995;
    const unsigned int seed = 0;
    const int r = 24;

    unsigned int h = seed ^ len;

    const unsigned char* data = (const unsigned char*) key;
    unsigned int k = 0;

    while (len >= 4) {
        k  = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len) {
    case 3:
        h ^= data[2] << 16;
    case 2:
        h ^= data[1] << 8;
    case 1:
        h ^= data[0];
        h *= m;
    };
    
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}


void printError(int Error) 
{
    switch(Error)
    {
        case 1:
            fprintf(logs, "ERR_CALLING_FUNC_FAILED ");
            break;
        case 1 << 1:
            fprintf(logs, "ERR_STACK_ALREARY_CREATED ");
            break;
        case 1 << 2:
            fprintf(logs, "ERR_EMPTY_ELEM_ISNT_POISONED ");
            break;
        case 1 << 3:
            fprintf(logs, "ERR_SIZE_GREATER_CAPACITY ");
            break;
        case 1 << 4:
            fprintf(logs, "ERR_POP_EMPTY_STACK ");
            break;
        case 1 << 5:
            fprintf(logs, "ERR_RIGHT_CANARY_DAMAGED ");
            break;
        case 1 << 6:
            fprintf(logs, "ERR_LEFT_CANARY_DAMAGED ");
            break;
        case 1 << 7:
            fprintf(logs, "ERR_WRONG_HASH ");
            break;
        case 1 << 8:
            fprintf(logs, "ERR_INVALID_PTR ");
            break;
        case 1 << 9:
            fprintf(logs, "ERR_REALLOC_FAILED ");
            break;
        case 1 << 10:
            fprintf(logs, "ERR_PUSH_FAILED ");
            break;
        case 1 << 11:
            fprintf(logs, "ERR_STACK_ALREADY_CLEANED ");
            break;
        case 1 << 12:
            fprintf(logs, "ERR_LEFT_DATACANARY_DAMAGED ");
            break;
        case 1 << 13:
            fprintf(logs, "ERR_RIGHT_DATACANARY_DAMAGED ");
            break;
        default:
            fprintf(logs, "no errors ");
    }   

}