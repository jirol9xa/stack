#include <stdio.h>
#include "header.h"

FILE* logs = fopen("Logs", "w");

int main(void){
    FILE* logFile = fopen("Logs", "w");

    Stack stk = {};
    stackCtor(&stk, 0);
    stackPush(&stk, 2);

    printf("%d\n%d\n", stackPop(&stk), stk.capacity);

    stackDtor(&stk);
    return 0;
}