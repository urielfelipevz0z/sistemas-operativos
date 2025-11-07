#include <stdio.h>

int main(){
    int Q = 0;
    for(Q = 4; Q > 0; Q--){
        printf("For: %d\n",Q);
    }
    if(Q == 0){
        printf("Q = %d\n",Q);
    }


    return 0;
}