#include <stdio.h>
#include "test_extern_dois.h"
extern int a = 51;

void alu();

int main(){
    alu();
    printf("valor: %d\n",a);
}

