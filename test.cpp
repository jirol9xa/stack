#include "header.h"

int main(void)
{
    char string[] = "ab";
    char* ptr1 = string;
    char** ptr2 = &ptr1;

    char c = *(*ptr2)++;

    printf("%c\n", c);
    return 0;
}