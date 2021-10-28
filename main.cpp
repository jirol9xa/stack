#include "header.h"

is_debug_lvl_0(FILE* logs = fopen("Logs", "w"));


int main(void) {
    Stack stk  = {};
    
    FUNC_REPORT(stackCtor(&stk, 1), &stk);

    FUNC_REPORT(stackPush(&stk, 1), &stk);
    FUNC_REPORT(stackPush(&stk, 5), &stk);
    type a = {}, b = {};
    stackPop(&stk, &a);
    stackPop(&stk, &b);
    printf("%d\n", a + b);

    stackDtor(&stk);

    is_debug_lvl_0(fclose(logs));
    return 0;
}