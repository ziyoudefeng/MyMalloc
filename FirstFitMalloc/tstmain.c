
#include <stdio.h>
#include "FirstFitMalloc.h"

int
main(void)
{
    char *p = (char *)first_malloc(sizeof(char));
    *p = 'a';
    printf("p addr = %p\t*p = %c\n", p, *p);
    char *q = (char *)first_malloc(sizeof(char));
    *q = 'b';
    printf("q addr = %p\t*q = %c\n", q, *q);

    char *s = "abcdefghijklmnopqrstuvwxyz";
    printf("s addr = %p\t*s = %s\n", &s, s);


    return 0;
}
