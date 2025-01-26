#include <stdio.h>
#include "ula.h"
#define NOMINMAX
#include <windows.h>
// using namepace std;

int main(){
    char function[2000];
    char vars[2000];
    printf("Enter Formula: ");
    fgets(function, sizeof(function), stdin);
    printf("Enter Varibles : ");
    fgets(vars, sizeof(vars), stdin);
    char buf[2000];
    strncpy(buf, function,strlen(function));
    printf("Computation of Formula: %f", strToFuncEval(buf,vars));
    return 0;
  
}
//3X^(Y+3)
//X:10,Y:5