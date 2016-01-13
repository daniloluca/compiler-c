#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

char look; /* O caracter lido "antecipadamente" (lookahead) */

/* protótipos */
void init();

void nextChar();
void error(char *fmt, ...);

void fatal(char *fmt, ...);
void expected(char *fmt, ...);

void match(char c);
char getName();

int getNum();
void emit(char *fmt, ...);

int term();
int expression();
void add();
void subtract();
void multiply();
void divide();
void factor();
void ident();
int isAddOp(char c);
void assignment();

/* PROGRAMA PRINCIPAL */
int main(){
        init();
        assignment();
        
        if (look != '\n')
            expected("NewLine");
            
        printf("%d\n", expression());

        return 0;
}

/* inicialização do compilador */
void init(){
        nextChar();
}

/* lê próximo caracter da entrada */
void nextChar(){
        look = getchar();
}

/* exibe uma mensagem de erro formatada */

void error(char *fmt, ...){
        va_list args;

        fputs("Error: ", stderr);

        va_start(args, fmt);

        vfprintf(stderr, fmt, args);
        va_end(args);

        fputc('\n', stderr);
}

/* exibe uma mensagem de erro formatada e sai */

void fatal(char *fmt, ...){
        va_list args;

        fputs("Error: ", stderr);

        va_start(args, fmt);

        vfprintf(stderr, fmt, args);
        va_end(args);

        fputc('\n', stderr);

        exit(1);

}

/* alerta sobre alguma entrada esperada */
void expected(char *fmt, ...){

        va_list args;

        fputs("Error: ", stderr);

        va_start(args, fmt);
        vfprintf(stderr, fmt, args);

        va_end(args);

        fputs(" expected!\n", stderr);

        exit(1);
}

/* verifica se entrada combina com o esperado */
void match(char c){
        if (look != c)
                expected("'%c'", c);

        nextChar();
}

/* recebe o nome de um identificador */
char getName(){
        char name;

        if (!isalpha(look))

                expected("Name");
        name = toupper(look);

        nextChar();

        return name;
}

/* recebe um número inteiro */

int getNum(){
        char num;
        
        if (!isdigit(look))

                expected("Integer");
        num = look;
        nextChar();

        return num - '0';
}

/* emite uma instrução seguida por uma nova linha */
void emit(char *fmt, ...){
        va_list args;

        putchar('\t');

        va_start(args, fmt);
        vprintf(fmt, args);

        va_end(args);

        putchar('\n');

}

/* analisa e traduz uma expressão */
int term(){
        int val;
        
        val = getNum();
        while (isMulOp(look)) {

                switch (look) {
                  case '*':
                        match('*');

                        val *= getNum();
                        break;
                  case '/':

                        match('/');
                        val /= getNum();

                        break;
                }
        }

        return val;

}

 /* reconhece e traduz uma expressão */
int expression(){
        
         int val;
        
        if (isAddOp(look))
        
                val = 0;
        else
                val = term();
        
        while (isAddOp(look)) {
                switch (look) {
        
                  case '+':
                        match('+');
                        val += term();
        
                        break;
                  case '-':
                        match('-');
        
                        val -= term();
                        break;
                }
        
        }
        

}

/* reconhece e traduz uma adição */
void add(){
        match('+');
        term();
        emit("POP BX");
        
        emit("ADD AX, BX");
}

/* reconhece e traduz uma subtração */
void subtract(){
        match('-');

        term();
        emit("POP BX");
        
        emit("SUB AX, BX");
        emit("NEG AX");
}

/* analisa e traduz um fator matemático */
void factor(){
        if (look == '(') {
        
                match('(');
                expression();
                match(')');

        } else if(isalpha(look))
                ident();
        else
                emit("MOV AX, %c", getNum());
}

/* reconhece e traduz uma multiplicação */

void multiply(){
        match('*');
        factor();

        emit("POP BX");
        emit("IMUL BX");
}

/* reconhece e traduz uma divisão */
void divide(){
        match('/');

        factor();
        emit("POP BX");
        emit("XCHG AX, BX");

        emit("CWD");
        emit("IDIV BX");
}

/* analisa e traduz um identificador */
void ident(){
        char name;

        name = getName();
        if (look == '(') {

                match('(');
                match(')');
                emit("CALL %c", name);

        } else
                emit("MOV AX, [%c]", name);
}

int isAddOp(char c){
        return (c=='+' || c=='-');
}

/* analisa e traduz um comando de atribuição */
void assignment(){
        char name;

        name = getName();

        match('=');
        expression();
        emit("MOV [%c], AX", name);

}