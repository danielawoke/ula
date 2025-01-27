#include <stdio.h>
#include "ula.h"
#define NOMINMAX
#include <windows.h>
// using namepace std;

int main(){
    while(true){
        char vars[2000];
        char function[2000];
        printf("Enter Formula: ");
        scanf("%s",function);
        if(strcmp(function,"exit") == 0){
            break;
        }        
        
        printf("Enter Varibles : ");
        scanf("%s",vars);
        if(strcmp(vars,"exit") == 0){
            break;
        }
        printf("Computation of Formula: %f\n", strToFuncEval(function,vars));
    }
    return 0;
  
}
//3X^(Y+3)
//X:10,Y:5


//96