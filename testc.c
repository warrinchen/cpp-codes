#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int a = 22;
    char* str = "abc";
    char ss[20];
    sprintf(ss, "m55距离是%s", str);
    printf("%s", ss);
    return 0;
}
