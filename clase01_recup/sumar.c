#include<stdio.h>
#include <stdlib.h> 
int main(int nro_arg, char *arg[]) {
    int v1 = atoi(arg[1]);
    int v2 = atoi(arg[2]);
    int v3 = v1 + v2;
     printf("La suma de %d y %d es %d",v1,v2,v3);
     return 0;
}