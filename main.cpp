#include "header.h"

FILE* logs = fopen("Logs", "w");

int main(void) {

    Stack stk = {};
    FUNC_REPORT(stackCtor(&stk, 0), &stk)
    FUNC_REPORT(stackPush(&stk, 2), &stk)
    FUNC_REPORT(stackPush(&stk, 4), &stk)
    FUNC_REPORT(stackPush(&stk, 8), &stk)

    PRINT_LINE();
    type a = {};
    type b = {};
    type c = {};
    FUNC_REPORT(stackPop(&stk, &a), &stk)
    FUNC_REPORT(stackPop(&stk, &b), &stk)
    FUNC_REPORT(stackPop(&stk, &c), &stk)
    printf("a = %d\nb = %d\nc = %d\n", a, b, c);
    PRINT_LINE();
    FUNC_REPORT(stackDtor(&stk), &stk)
    PRINT_LINE();
    return 0;
}