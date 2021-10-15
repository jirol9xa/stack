#include "header.h"

is_debug_lvl_0(FILE* logs = fopen("Logs", "w"));


int main(void) {
    Stack stk  = {};
    Stack stk1 = {};
    
    stackCtor(&stk, 100);
    stackPush(&stk, 10);
    type a = {};
    stackPop(&stk, &a);

    is_debug_lvl_0(fclose(logs));
    return 0;
}