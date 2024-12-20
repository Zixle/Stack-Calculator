#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "stack.h"



int math(stack , stack , stack , int* );
void zerodivi ( int zero ) {
    printf("Error - division by 0\n");
}
int findpos(stack l){
    int pos = 0, value = 0;
    int high = top(l);
    stack temp = createStack();
    push(temp, top(l));
    pop(l);
    pos++;
    while(!isEmpty(l)){
        if (top(l) > high){
            high = top(l);
            value = pos;
        }
        push(temp, top(l));
        pop(l);
        pos++;
    }
    while(!isEmpty(temp)){
        push(l, top(temp));
        pop(temp);
    }
    freeStack(temp);
    return value;
}
int findPrecedence(char sym){
    if (sym == '^') return 5;
    else if (sym == '*' || sym == '/' || sym == '%') return 4;
    else if (sym == '+' || sym == '-') return 3;
    else if (sym == '>') return 2;
    else return 0;
}
stack switchStack(stack s){
    stack temp = createStack();
    while (!isEmpty(s)){
        push(temp, top(s));
        pop(s);
    }
    freeStack(s);
    return temp;
}
int add(int num1, int num2){
    num1= num1- '0';
    num2= num2- '0';
    return num1+num2 + '0';
}
int sub(int num1, int num2){
    num1= num1- '0';
    num2= num2- '0';
    return num1-num2 + '0';
}
int multi(int num1, int num2){
    num1= num1- '0';
    num2= num2- '0';
    return num2*num1 + '0';
}
int divi(int num1, int num2){
     num1= num1- '0';
    num2= num2- '0';
    if (num2 == 0){
        zerodivi(num2);
    }
    return (num1/num2) + '0';
    
}
int modulo(int num1, int num2){
    num1= num1- '0';
    num2= num2- '0';
    return (num1%num2) + '0';
    
}
/*
int checkVar(int num, int* variable){
    if (num >= 'a' && num <= 'z'){

    }
}
*/
int math(stack nums, stack syms, stack pre, int *variable){

    while (!isEmpty(syms)){
        int i = 0, pos = 0;
        
        pos = findpos(pre); // position of the highest precedence
        stack tempnum = createStack();
        stack tempsym = createStack();
        stack temppre = createStack();
        while(i < pos){
            if (pos == 0) break;
            push(tempsym, top(syms));
            pop(syms);
            push(tempnum, top(nums));
            pop(nums);
            push(temppre, top(pre));
            pop(pre);
            i++;
        }
    
        int a = top(syms);
       
    if (a == '+'){
        int digit1 = top(nums);
        pop(nums);
        int digit2 = top(nums);
        pop(nums);
        int res = add(digit1, digit2);
        push(nums, res);
    }
    else if(a== '-'){
        int digit1 = top(nums);
        pop(nums);
        int digit2 = top(nums);
        pop(nums);
        int res = sub(digit1, digit2);
        push(nums, res);
    }
    else if (a == '*'){
        int digit1 = top(nums);
        pop(nums);
        int digit2 = top(nums);
        pop(nums);
        int res = multi(digit1, digit2);
        push(nums, res);
    }
    else if (a == '/'){
        int digit1 = top(nums);
        pop(nums);
        int digit2 = top(nums);
        pop(nums);
        int res = divi(digit1, digit2);
        push(nums, res);
        
    }
    else if (a == '^'){
        int digit1 = top(nums);
        pop(nums);
        int digit2 = top(nums);
        pop(nums);
        int res = pow(digit1 - '0', digit2 - '0');
        push(nums, res + '0');
    }
    else if (a == '%'){
        int digit1 = top(nums);
        pop(nums);
        int digit2 = top(nums);
        pop(nums);
        int res = modulo(digit1, digit2);
        push(nums, res);
    }
    else if (a == '>'){
        int digit = top(nums); //letter
        pop(nums);
        int var = top(nums);
        pop(nums);
        push(nums, digit);
        variable[var - 'a'] = digit - '0';
    }
    
    
    pop(syms);
    pop(pre);
    while(!isEmpty(tempsym)){
        push(syms, top(tempsym));
        pop(tempsym);
        push(nums, top(tempnum));
        pop(tempnum);
        push(pre, top(temppre));
        pop(temppre);
    }
    freeStack(tempnum); freeStack(tempsym); freeStack(temppre);
    }
    return top(nums);
}

int parenthesis( const char s[2], char* token, int *variable){
    int parenRes = 0, num = 0;
    stack nums = createStack(), syms = createStack(), pre = createStack();
    while (*token != ')'){
        token = strtok(NULL, s);
        if (*token == '+' || *token == '-' || *token == '*' || *token == '/' || *token == '%' || *token == '^' || *token == '>'){
            push(syms, *token);
            push(pre, findPrecedence(*token));
        }
        else if (*token == '('){
                    parenRes = parenthesis(s, token, variable);
                    push(nums, parenRes);
        }
        else if (*token >= 'a' && *token <= 'z'){
                
                if (variable [*token - 'a'] != 0){ // its already been assigned
                    push(nums, variable [*token - 'a'] + '0');
                
                }
                else {
                    // will later be assigned
                    push(nums , *token);
                    }
                    
                    
        }
        else { // Store the character
            num = atoi(token) + '0';
            push(nums, num);
        }
    }
    nums = switchStack(nums);
    syms = switchStack(syms);
    pre = switchStack(pre);
    int result = math(nums, syms, pre, variable);
    freeStack(nums); freeStack(syms); freeStack(pre);
    return result;
}



int main (void) {
int variable[26]={0};
char str[1000];
const char s[2] = " "; // delimiter - a space
char *token=NULL;


int size=0, num=0, parenRes = 0, finalRes = 0;

    
while (1){
    stack operands = createStack(), operators = createStack(), precedence = createStack();
    printf("? ");
    if (fgets(str,1000,stdin) == NULL || str[0] == '\n') break;
    else {
        
        size = strlen(str);// starts at pos 0, counting null
        
        if(size>0 && str[size -1]== '\n'){
            
            str[size-1]= '\0';//remove newline
        }
        
      
        /* get the first token */
        token = strtok(str, s);
        if (*token == '('){
           parenRes = parenthesis(s, token, variable);
           push(operands, parenRes);
        }
        else if(*token >= 'a' && *token <= 'z'){
                if (variable[*token - 'a'] != 0){
                    push(operands, variable[*token - 'a'] + '0');
                }
                else push(operands, 0 + '0');
            
        }
        else {
              
            num = atoi(token) + '0'; // ascii number
            int num2 = atoi(token);// the integer, if its not a number, meaning its a character, it will convert it to zero
                    if (num2 ==0 ){
                        if (*token == '0'){
                            push(operands, '0');
                        }
                        else {
                            if (*token != '+' && *token != '-' && *token != '*' && *token != '/' && *token != '%' && *token != '(' && *token != ')' && *token != '^' && *token != '>' ){
                            printf("Error - illegal character '%c' \n", *token); return 1;
                            }
                        }
                          }
                    else{
                        push(operands, num);
                    }
                 
            
        }
        /* walk through other tokens */
            while( token != NULL ) {
                token = strtok(NULL, s);
                if (token == NULL) break;
                else if (*token == '+' || *token == '-' || *token == '*' || *token == '/' || *token == '%' || *token == '^' || *token == '>'){
                    push(operators, *token);
                    push(precedence, findPrecedence(*token));
                }
                else if (*token == '('){
                    parenRes = parenthesis(s, token, variable);
                    push(operands, parenRes);
                }
                else if (*token >= 'a' && *token <= 'z'){
                
                    if (variable [*token - 'a'] != 0){ // its already been assigned
                        push( operands, variable [*token - 'a'] + '0');
                
                    }
                    else {
                        // will later be assigned
                        push( operands , *token);
                    }
                    
                    
                }
                else {
                 // 3 digit num or illegal character
                    num = atoi(token) + '0'; // ascii number
                    int num2 = atoi(token);// the integer, if its not a number, meaning its a character, it will convert it to zero
                        if (num2 ==0 ){
                        if (*token == '0'){
                            push(operands, '0');
                        }
                        else {
                            if (*token != '+' && *token != '-' && *token != '*' && *token != '/' && *token != '%' && *token != '(' && *token != ')' && *token != '^' && *token != '>' ){
                            printf("Error - illegal character '%c' \n", *token); return 1;
                            }
                        }
                          }
                        else{
                        push(operands, num);
                        }
                       
                }
                
            }
            if (isEmpty(operators)){
                printf("%d \n", top(operands)-'0');
            }
            else {
                operands = switchStack(operands);
                operators = switchStack(operators);
                precedence = switchStack(precedence);
                finalRes = math(operands, operators, precedence, variable);
                
                printf("%d\n\n", finalRes - '0');
            
            }
            freeStack(operators);
            freeStack(operands);
            freeStack(precedence);
        }
        
    }
return(0);
}


