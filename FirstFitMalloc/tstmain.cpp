
#include <iostream>
#include <stdio.h>
#include "FirstFitMalloc.h"
//#include "FirstFitMalloc.c"

using namespace std;

int
main(void)
{
    char *p = (char *)first_malloc(sizeof(char));
    *p = 'a';
    printf("p addr = %p\t*p = %c\n", p, *p);
    char *q = (char *)first_malloc(sizeof(char));
    *q = 'b';
    printf("q addr = %p\t*q = %c\n", q, *q);


    return 0;
}
