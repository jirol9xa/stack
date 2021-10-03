#include <stdio.h>
#include "header.h"

FILE* logs = fopen("Logs", "a");

int main(void){

    Stack stk = {};
    stackCtor(&stk, 20);
    stackPush(&stk, 2);
   
    printf("%d\n%d\n", stackPop(&stk), stk.capacity);
    printf("%d\n", stk.capacity);
    stackDtor(&stk);
    return 0;
}