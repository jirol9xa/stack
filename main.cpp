#include <stdio.h>
#include "header.h"


FILE* logs = fopen("Logs", "a");

int main(void){

    Stack stk = {};
    stackCtor(&stk, 20);
    stackPush(&stk, 2);
    type a = {};
    type b = {};
    stackPop(&stk, &a);
   
    printf("%d\n%d\n", a, stk.capacity);
    printf("%d\n", stk.capacity);
    stackDtor(&stk);
    return 0;
}