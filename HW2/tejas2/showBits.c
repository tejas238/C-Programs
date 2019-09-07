//showBits.c by Tejas Menon, CS201, last edited 10/21.
//Purpose: This program prints the common bits between two integers in four formats-
//	   in readable binary, hexadecimal, signed and unsigned integers. The two integers
//	   to be compared are passed in as program arguments.

#include <stdlib.h>
#include <stdio.h>

void printBits(unsigned int,int); //This function recursively prints the position of every common bit at each of the 32 positions

int
main(int argc,char * argv[])
{
	if (argc != 3) { //First argument to argv is the path and name of the file
		printf("Incorrect number of arguments. Try again!\n"); 
		return 0;
	}
	unsigned int commonBits = (unsigned int) strtol(argv[1],NULL,0)&strtol(argv[2],NULL,0); //Arguments must preceed with '0x' to denote hexadecimal
	printf("Bits ");
	printBits(commonBits,0); //start comparisons from the 0th position
	printf(" are common between the two numbers. Hexadecimal: 0x%x Signed: %d Unsigned: %u\n",commonBits,commonBits,commonBits);
	return 1;
}

//Increments pos for each recursive call until pos exceeds 31 i.e the MSB
void 
printBits(unsigned int commonBits,int pos)
{
	if (pos == 32) return;
	if (commonBits&(1<<pos)) printf("%d,",pos);
	printBits(commonBits,++pos);
}
