#include <stdio.h>
#include <stdlib.h>

int main() {
    char str[] = "bg %%123";
    int num = atoi(str+5);
    printf("The number is %d\n", num);
    printf("String: %s\n", str+5);
    return 0;
}


