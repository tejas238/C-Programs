//doMath.c by Tejas Menon, CS201, last edited 11/20.
//Purpose: This program performs arithmetic on decimal/hexadecimal integers passed as arguments. A menu displays 
//         the different operations to be performed on the arguments.

#include "stdlib.h"
#include "stdio.h"
#include "string.h" //for function ststr()

typedef void func(char*argv[],int argc); //The general template for all functions 

func addition,subtraction,multiplication,division,modulo,reverse; //all the different operations to be performed

//This structure allows for one function pointer to point to several functions of the same type
struct dispatchStruct {
	func * toRun;
};

int printMenu(char*[],int); //prints the menu and stores user input

int 
main(int argc,char *argv[]) {
	
	if (argc<2 || argc>16) { printf("Too many, or no arguments entered. Try again!\n"); return 0;}
	char * menuText[] = {"Exit","Addition","Subtraction","Multiplication","Division","Modulo","Reverse Input"};
	struct dispatchStruct dispatch[] = {{addition},{subtraction},{multiplication},{division},{modulo},{reverse}}; //Each element is a func pointer
	int input = printMenu(menuText,7); //stores user input
	if (input) dispatch[input-1].toRun(argv,argc); //If exit is not requested, the corresponding function is run
	return 1;
}

//This function prints the menu and intercepts user input
int
printMenu(char*menuText[],int menuSize) {

	printf("Choose an option from the menu below:\n\n");
	for(int i=0;i<menuSize;++i) {
		printf("%d %s\n",i,menuText[i]); //numbers printed alongside options
	}
	putchar('\n');
	int input;
	int success = scanf("%d",&input);
	if (success) while(getchar() != '\n'); //removes extra bytes in buffer
	while (!success || input > menuSize-1 || input < 0) { 
		printf("Try again: ");
		success = scanf("%d",&input);
		if (success) while(getchar() != '\n');
        }
	return input;
}

//This function converts a char* in either hex/decimal format to an integer.
//A hexadecimal is detected by either a 'OX' or 'Ox' at the beginning of the argument
int
strToDec(char*toConv) {

	int arg;
	if (strstr(toConv,"0x") || strstr(toConv,"0X")) arg = (int)strtoul(toConv,NULL,0); //unsigned long casted to an int
	else arg = (int)strtoul(toConv,NULL,10);
	return arg;
}

//This function adds all arguments from left to right; the argument being in either hex or decimal format
void
addition(char*argv[],int argc) {
	
	int sum = 0;
	for(int i=1;i<argc;++i) {
		sum += strToDec(argv[i]);
	}
	printf("The sum of all the arguments is : %d\n",sum);
}

//This function takes the difference of all arguments from left to right
void
subtraction(char*argv[],int argc) {
	
	int difference = strToDec(argv[1]);
	for(int i=2;i<argc;++i) {
		difference -= strToDec(argv[i]);
	}
	printf("The difference of all arguments is : %d\n",difference);
}

//This function calculates the product of all arguments from left to right
void
multiplication(char*argv[],int argc) {

	int product = 1;
	for(int i=1;i<argc;++i) {
		product *= strToDec(argv[i]);
	}
	printf("The product of all arguments is : %d\n",product);
}

//This function calculates arg1/arg2 as a float from argv
void 
division(char*argv[],int argc) {

	float div;
	if (argc==2 || !strToDec(argv[2])) { printf("Cannot divide with one argument or zero second argument! Try again\n"); return; }
	else div = (float)strToDec(argv[1])/strToDec(argv[2]); //division promoted to a float
	printf("The division of the first two arguments is : %f\n",div);
}

//This fn calculates arg1 mod arg2 as an integer from argv
void
modulo(char*argv[],int argc) {
	
	int modded;
	if (argc==2 || !strToDec(argv[2])) {printf("Cannot mod with one argument or zero second argument! Try again\n"); return; }
	else modded = strToDec(argv[1])%strToDec(argv[2]);
	printf("The remainder of the division of the first two arguments is : %d\n",modded);
}

//This function reverses the input argument string so that it reads from right to left
void
reverse(char*argv[],int argc) {

	char*last; //pointer traverses from the last char in word to the first 
	printf("Here are your arguments reversed: ");
	for(int i=argc-1;i>0;--i) {
		last = argv[i]+strlen(argv[i])-1;
		while(last != argv[i]-1) {
			printf("%c",*last);
			--last;
		}
		printf(" "); //space after each word
	}
	printf("\n");
}
