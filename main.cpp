#include "header.h"

FILE* logs = fopen("Logs", "w");

int main(void) {

    Stack stk  = {};
    Stack stk1 = {};
    printf("%lu\n", CANARY(&stk));
    
    FUNC_REPORT(stackCtor(&stk, 0), &stk)
    type a = {};
    type b = {};
    FUNC_REPORT(stackCtor(&stk1, 0), &stk1)
    FUNC_REPORT(stackPush(&stk, 8), &stk)
    FUNC_REPORT(stackPush(&stk1, 9), &stk1)
    FUNC_REPORT(stackPop(&stk1, &a), &stk1)
    FUNC_REPORT(stackPop(&stk, &b), &stk)
    printf("//////////////%d\n", a + b);
    FUNC_REPORT(stackDtor(&stk), &stk);
    FUNC_REPORT(stackDtor(&stk1), &stk1);
    FUNC_REPORT(stackDtor(&stk1), &stk1);

    fclose(logs);
    return 0;
}