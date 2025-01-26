#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#ifndef mathFuncs

#define mathFuncs




struct retVal{
    int index;
    double ret;
};

struct functionParse{
    int index;
    bool verd;
};


struct vars{
    char names[128][128];
    double vals [128];
};


struct var{
    char name[128];
    int index;
};

double addSub(char function[], int index, struct vars varsDict);
double evalFunction(char function[], struct vars varsDict);

struct retVal getCoef(char function[], int i){
    
    struct retVal ret;
    double coef = 0;
    while(i<strlen(function) && function[i] >=48 && function[i]<=57){
        coef*=10;
        int adder = function[i]-48;
        coef+=adder;
        i++;
    }
    if(function[i] != '.'){
        ret.ret = coef;
        ret.index = i;
        return ret;
    }
    i+=1;
    double mult = 1;
    while(i<strlen(function) && function[i] >=48 && function[i]<=57){
        mult/=10;
        double val = (function[i]-48);
        coef+=val*mult;
        i++;
    }
    ret.ret = coef;
    ret.index = i;
    return ret;

}

struct vars getVarsDict(char vars[]){
    struct vars varsDict;
    int count = 0;
    for(int i = 0; i<strlen(vars); i++){
        int j = i;
        while(j<strlen(vars)){
            if(vars[j] == ':'){
                strncpy(varsDict.names[count], vars+i, j-i);
                struct retVal ret = getCoef(vars, j+1);
                varsDict.vals[count] = ret.ret;
                i = ret.index+1;
                count++;
            }
            j++;
        }
    }
    return varsDict;
}

struct var getVar(char function[], int i){
    struct var varsDict;
    int j = i;
    while(function[j]>=65 && function[j]<=90){
        j++;
    }
    strncmp(varsDict.name,function+i,j-i);
    varsDict.index = j;
    return varsDict;
}

bool coefVar(char a, char b){
    if((a>=65 && a<=90) && (b>=48 && b<=57)){
        return true;
    }
    if((b>=65 && b<=90) && (a>=48 && a<=57)){
        return true;
    }
    return false;
}

bool isCoef(char a){
    if((a>=48 && a<=57)){
        return true;
    }
    return false;
}

bool isVar(char a){
    if((a>=65 && a<=90)){
        return true;
    }
    return false;
}

struct functionParse isFunction(char function[],int index){
    struct functionParse ret;
    int parenCount = 0;
    bool functionalTerm = false;
    for(int i = index; i<=strlen(function); i++){
        if(i<strlen(function) && function[i] == '('){
            parenCount++;
        }else if(i<strlen(function) && function[i] == ')'){
            parenCount--;
        }
        if(function[i] == '*' || function[i] == '/' || function[i] == '^' || function[i] == '(' || (i-1>=0 && i<strlen(function) && coefVar(function[i],function[i-1]))){
            functionalTerm = true;
        }

        if((parenCount == 0 && (function[i] == '+' || function[i] == '-' || i==strlen(function))) && functionalTerm){
            ret.verd = true;
            ret.index = i;
            return ret;
        }

    }
    ret.verd = false;
    ret.index = -1;
    return ret;
}

double f(double x, double c, int power) {
    double val = 1;
    for(int i = 0; i<power; i++){
        val=val*x;
    }
    return val-c;  
}

double bisection(double (*func)(double,double,int), double a, double b, double tolerance, int max_iter, double c, double power) {
    
    int iter = 0;
    double m;
    while ((b - a) / 2 > tolerance && iter < max_iter) {
        m = (a + b) / 2;
        if (func(m,c,power) == 0) {
            break;
        }   
        if (func(a,c,power) * func(m,c,power) < 0) {
            b = m; 
        }else{
            a = m;  
        }
        iter++;
    }
    return m;  
}

double power(double base, double expo){
    if(expo>-.0000001&expo<.0000001){
        return 1;
    }
    bool isNeg = expo<0?true:false;
    expo = isNeg?expo*-1:expo;
    double ret = expo<1?1:base;
    while(expo>1){
        ret*=ret;
        expo-=1;
    }
    expo=(expo>=1)?expo-1:expo;
    int root = (int)(floor((1/expo)));
    ret*=bisection(f,0,base+1,.00000001,100, base , root);

    return isNeg?1/ret:ret;
}


double addSub(char function[], int index, struct vars varsDict){
        if(index == 0 && function[index] == '-'){
            index++;
        }
        if(index>=strlen(function)){
            return 0;
        }

        double num1;
        struct functionParse verd = isFunction(function,index);
        if(verd.verd){
            char* nextFunction = (char*)malloc((verd.index-index)*sizeof(char));
            nextFunction[verd.index-index] = '\0';
            strncpy(nextFunction, function+index, verd.index-index);
            num1 = evalFunction(nextFunction,varsDict);
            free(nextFunction);
            if(index-1 == 0 && function[index-1] == '-'){
                num1*=-1;
            }       
            
            if(verd.index>=strlen(function)){
                return num1;
            }
            else if(function[verd.index] == '+'){
                return num1+addSub(function, verd.index+1, varsDict);
            }else if(function[verd.index] == '-'){
                return num1-addSub(function, verd.index+1, varsDict);
            }
        }
        else if(function[index]>=65 && function[index]<=90){
            struct var var = getVar(function, index);
            for(int j = 0; j<sizeof(varsDict.names); j++){
                if(strcmp(var.name, varsDict.names[j])){
                    num1 = varsDict.vals[j];
                    break;
                }
            }     
            if(index-1 == 0 && function[index-1] == '-'){
                num1*=-1;
            }       
            if(var.index>=strlen(function)){
                return num1;
            }
            else if(function[var.index] == '+'){
                return num1+addSub(function, var.index+1, varsDict);
            }else if(function[var.index] == '-'){
                return num1-addSub(function, var.index+1, varsDict);
            }

        }else if(function[index]>=48 && function[index]<=57){
            struct retVal ret = getCoef(function, index);
            num1 = ret.ret;
            if(index-1 == 0 && function[index-1] == '-'){
                num1*=-1;
            }      
            if(ret.index>=strlen(function)){
                return num1;
            }else if(function[ret.index] == '+'){
                return num1+addSub(function, ret.index+1, varsDict);
            }else if(function[ret.index] == '-'){
                return num1-addSub(function, ret.index+1, varsDict);
            }
        }
}




// struct vars varsDict
double evalFunction(char function[], struct vars varsDict){

    double num1;
    if(function[0] == '('){ 
        int parenCount = 1;
        int i = 1;
        while(parenCount>0){
            if(function[i] == '('){
                parenCount++;
            }else if(function[i] == ')'){
                parenCount--;
            }
            i++;
        }
        char* nestedVal = (char*)malloc((i-1)*sizeof(char));
        nestedVal[i-2] = '\0';
        strncpy(nestedVal, function+1, i-2);
        num1 = addSub(nestedVal,0,varsDict);
        free(nestedVal);
        if(i>=strlen(function)){
            return num1;
        }
        else if(function[i] == '(' || isVar(function[i]) ){
            char* nextFunction = (char*)malloc((strlen(function)-i)*sizeof(char));
            nextFunction[strlen(function)-i] = '\0';
            strncpy(nextFunction, function+i, strlen(function)-i);
            double ret = num1*evalFunction(nextFunction, varsDict);
            free(nextFunction);
            return ret;
        }
        else if(function[i] == '*'){
            char* nextFunction = (char*)malloc((strlen(function)-i-1)*sizeof(char));
            nextFunction[strlen(function)-i-1] = '\0';
            strncpy(nextFunction, function+i+1, strlen(function)-i-1);
            double ret = num1*evalFunction(nextFunction, varsDict);
            free(nextFunction);
            return ret;


        }
        else if(function[i] == '/'){
            char* nextFunction = (char*)malloc((strlen(function)-i-1)*sizeof(char));
            nextFunction[strlen(function)-i-1] = '\0';
            strncpy(nextFunction, function+i+1, strlen(function)-i-1);
            double ret = num1/evalFunction(nextFunction, varsDict);
            free(nextFunction);
            return ret;

        }else if(function[i] == '^'){
            char* nextFunction = (char*)malloc((strlen(function)-i-1)*sizeof(char));
            nextFunction[strlen(function)-i-1] = '\0';
            strncpy(nextFunction, function+i+1, strlen(function)-i-1);
            double ret = power(num1,evalFunction(nextFunction,varsDict));
            free(nextFunction);
            return ret;

        }



    }else if(isVar(function[0])){
        struct var var = getVar(function,0);
        for(int i = 0; i<128; i++){
            if(strcmp(varsDict.names[i],var.name)){
                num1 = varsDict.vals[i];
            }
        }
        int i = var.index;
        if(i>=strlen(function)){
            return num1;
        }
        else if(function[i] == '(' || isVar(function[i]) ){
            char* nextFunction = (char*)malloc((strlen(function)-i)*sizeof(char));
            nextFunction[strlen(function)-i] = '\0';
            strncpy(nextFunction, function+i, strlen(function)-i);
            double ret = num1*evalFunction(nextFunction, varsDict);
            free(nextFunction);
            return ret;
        }
        else if(function[i] == '*'){
            char* nextFunction = (char*)malloc((strlen(function)-i-1)*sizeof(char));
            nextFunction[strlen(function)-i-1] = '\0';
            strncpy(nextFunction, function+i+1, strlen(function)-i-1);
            double ret = num1*evalFunction(nextFunction, varsDict);
            free(nextFunction);
            return ret;


        }
        else if(function[i] == '/'){
            char* nextFunction = (char*)malloc((strlen(function)-i-1)*sizeof(char));
            nextFunction[strlen(function)-i-1] = '\0';
            strncpy(nextFunction, function+i+1, strlen(function)-i-1);
            double ret = num1/evalFunction(nextFunction, varsDict);
            free(nextFunction);
            return ret;

        }else if(function[i] == '^'){
            char* nextFunction = (char*)malloc((strlen(function)-i-1)*sizeof(char));
            nextFunction[strlen(function)-i-1] = '\0';
            strncpy(nextFunction, function+i+1, strlen(function)-i-1);
            double ret = power(num1,evalFunction(nextFunction,varsDict));
            free(nextFunction);
            return ret;

        }

    }else if(isCoef(function[0])){
        struct retVal var = getCoef(function,0);
        num1 = var.ret;
        int i = var.index;
        if(i>=strlen(function)){
            return num1;
        }
        else if(function[i] == '(' || isVar(function[i]) ){
            char* nextFunction = (char*)malloc((strlen(function)-i)*sizeof(char));
            nextFunction[strlen(function)-i] = '\0';
            strncpy(nextFunction, function+i, strlen(function)-i);
            double ret = num1*evalFunction(nextFunction, varsDict);
            free(nextFunction);
            return ret;
        }
        else if(function[i] == '*'){
            char* nextFunction = (char*)malloc((strlen(function)-i-1)*sizeof(char));
            nextFunction[strlen(function)-i-1] = '\0';
            strncpy(nextFunction, function+i+1, strlen(function)-i-1);
            double ret = num1*evalFunction(nextFunction, varsDict);
            free(nextFunction);
            return ret;


        }
        else if(function[i] == '/'){
            char* nextFunction = (char*)malloc((strlen(function)-i-1)*sizeof(char));
            nextFunction[strlen(function)-i-1] = '\0';
            strncpy(nextFunction, function+i+1, strlen(function)-i-1);
            double ret = num1/evalFunction(nextFunction, varsDict);
            free(nextFunction);
            return ret;

        }else if(function[i] == '^'){
            char* nextFunction = (char*)malloc((strlen(function)-i-1)*sizeof(char));
            nextFunction[strlen(function)-i-1] = '\0';
            strncpy(nextFunction, function+i+1, strlen(function)-i-1);
            double ret = power(num1,evalFunction(nextFunction,varsDict));
            free(nextFunction);
            return ret;

        }
    }
}

double strToFuncEval(char function[], char vars[]){
    struct vars varsDict = getVarsDict(vars);
    double val = addSub(function,0,varsDict);
    return val;    
}

#endif // MYLIB_H