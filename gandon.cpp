#include <stdio.h>

int main()
{
    const char a[] = "vova hui sosi";
    for(int i = 0; i <= 1000000000000000000000000000000; i++ )
    {
        printf("%*s\n", i, a);
    }


    return 0;
}