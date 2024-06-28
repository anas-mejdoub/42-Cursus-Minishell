#include <stdlib.h>

int main()
{
    char *p = malloc(1);
    printf("%d", (int *)p);
}