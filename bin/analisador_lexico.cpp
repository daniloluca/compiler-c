#include <stdio.h>
#include <stdlib.h>

#define N 0

using namespace std;

int rowCount=0;
int colCount=0;

char letter;

int initialState = 0;
int finalStates[] = {12};
char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'x', 'y', 'z'};
int transitions[][30] = {
//	 a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
	{N, N, 9, 3, N, 8, N, N, 1, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N}, //q0 - initial
	{N, N, N, N, N, N, N, N, N, N, N, N, N, 2, N, N, N, N, N, N, N, N, N, N, N, N}, //q1
	{N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, 12, N, N, N, N, N, N}, //q2
	{N, N, N, N, N, N, N, N, N, N, N, N, N, N, 4, N, N, N, N, N, N, N, N, N, N, N}, //q3
	{2, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, 5, N, N, N, N, N}, //q4
	{N, 6, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, 12, N, N, N, N, N, N}, //q5
	{N, N, N, N, N, N, N, N, N, N, N, 7, N, N, N, N, N, N, N, N, N, N, N, N, N, N}, //q6
	{N, N, N, N, 12, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N}, //q7
	{N, N, N, N, N, N, N, N, N, N, N, 3, N, N, N, N, N, N, N, N, N, N, N, N, N, N}, //q8
	{N, N, N, N, N, N, N, 10, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N}, //q9
	{11, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N}, //q10
	{N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, 12, N, N, N, N, N, N, N, N}, //q11
	{N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N}  //q12 - final
};

void init();
int getState(int state);
int getLetterId();
int automaton(int state);
void emit(char* message, char letter);

int main(){

	init();

    return 0;
}

void init(){
	while(letter!='\n'){
		if(automaton(initialState) == 12)
			printf(" - Valida!\n");
		else
			printf(" - Invalida!\n");
	}
}

int automaton(int state){
	letter = getchar();
	if(letter!=' ' && letter!='\n'){
		printf("%c", letter); //TODO armazenar
		return automaton(getState(state));
	}
	return state;
}

void emit(char* message, char letter){
	printf("\n%s'%c'\n", message, letter);
	exit(1);
}

int getState(int state){
	return transitions[state][getLetterId()];
}

int getLetterId(){
	for(int i=0; i<sizeof(alphabet); i++)
		if(letter==alphabet[i])
			return i;

	emit("Sintaxe error: ", letter);
}