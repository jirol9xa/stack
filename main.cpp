#include "header.h"

FILE* logs = fopen("Logs", "a");

int main(void) {

    Stack stk  = {};
    Stack stk1 = {};
    FUNC_REPORT(stackCtor(&stk, 2), &stk)
    type a = {};
    type b = {};
    type c = {};
    FUNC_REPORT(stackCtor(&stk1, 0), &stk)
    FUNC_REPORT(stackPush(&stk, 8), &stk)
    FUNC_REPORT(stackPush(&stk1, 9), &stk)
    FUNC_REPORT(stackPop(&stk1, &a), &stk)
    FUNC_REPORT(stackPop(&stk, &b), &stk)
    printf("//////////////%d\n", a + b);
    FUNC_REPORT(stackDtor(&stk), &stk)
    return 0;
}