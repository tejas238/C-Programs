//setBits.c file by Tejas Menon, CS201, last edited 10/21.
//Purpose: This program sets certain bits in an unsigned short
//	   depending on the positions indicated my arguments to the 
//	   the program. It produces an output in binary form using 
//         the printBits function that checks for a turned on bit at
//	   each of the 16 positions in the unsigned short.

#include <stdlib.h>
#include <stdio.h>

void printBits(unsigned short toSet,int startAt); //startAt is the binary integer at which to begin bit comparison

int 
main(int argc, char * argv[]) 
{
	if (argc > 17) { // first argument of argv is the path and name of the program
		printf("Number of arguments to setBits must be <= 16. Try again!\n");
		return 0;
	}
	unsigned short toSet = 0;
	for(int i=1;i<argc;++i) { //for each argument
		int num = strtol(argv[i],NULL,10); //converts the argument to an integer
		if (num<0 || num>15) {
			printf("A number exceeded the maximum limit. Use integers between 0 and 15. Try again!\n");
			return 0;
		}
		toSet = toSet | (1 << num); //OR's toSet with num at each of the desired positions
	}
	printf("Here is your input in binary: ");
	printBits(toSet,0x8000); //printing must begin at the 15'th position
	putchar('\n');
	return 1;
}	

//This function prints toSet in binary format from left to right and recursively calls
//itself until the right shifted startAt is rounded to 0
void printBits(unsigned short toSet,int startAt)
{
	if (startAt == 0) return;
	if (toSet&startAt) printf("1");
	else printf("0");
	printBits(toSet,startAt >> 1);
}
