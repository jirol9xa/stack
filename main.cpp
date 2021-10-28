#include "header.h"

is_debug_lvl_0(FILE* logs = fopen("Logs", "w"));


int main(void) {
    

    is_debug_lvl_0(fclose(logs));
    return 0;
}