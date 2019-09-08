//A3 by Tejas Menon, CS201, last edited 11/4.
//Purpose: This file contains the functions to parse a number in IEEE 754 float to its decimal equivalent.
//         It takes as arguments three inputs- the bitsizes of the fraction, exponent and the actual number to convert. 
//    	   The constraint on the maximum fraction and exponent bits are noted below.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void printFloat(unsigned long,unsigned long,unsigned long); //This function takes as arguments the numbers parsed from argv, and performs the conversion

int 
main(int argc,char * argv[])
{
	unsigned long fracBits = strtoul(argv[1],NULL,10); //get fraction bitzise in decimal
	unsigned long expBits = strtoul(argv[2],NULL,10); //get exponent bitsize in decimal
	unsigned long num = strtoul(argv[3],NULL,16); //get float number encoded in hexadecimal

	//wrong inputs invalidated	
	if (fracBits > 10 || fracBits < 2) {
		printf("Fraction bits must be between 2 and 10. Try again!\n");
		return 0;
	}
	
	if (expBits > 5 || expBits < 3) {
		printf("Exponent bits must be between 3 and 5. Try again!\n");
		return 0;
	}

        //If num has a MSB outside of bounds
 	if ((num >> fracBits+expBits+1) > 0) {
		printf("The number to evaluate is not commensurate with the bit lengths specified\n");
		return 0;
	}
	printFloat(fracBits,expBits,num);
	return 1;
}

//This function can display normalized, denormalized, NaN and infinite floats
void
printFloat(unsigned long fracBits,unsigned long expBits,unsigned long num)
{
	
	unsigned long fracNum = num & ((1 << fracBits) -1); //Gets the frac section from num
	unsigned long  signBit = num & ((1 << (fracBits+expBits))); //signBit is zero if the number is positive
	unsigned long expNumMask = ((1 << expBits) -1); //Creates a 0xFFF...FF mask the size of expBits
	unsigned long expNum = num & (expNumMask << fracBits); //retrives exp portion from num
	expNum = expNum >> fracBits; //gets the actual exp
	
	if (expNum == expNumMask && fracNum > 0) { 
		printf("The parsed number is: NaN\n");
		return;
	}
	if (expNum == expNumMask && fracNum == 0 && signBit == 0) {
		printf("The parsed number is: +inf\n");
		return;
	}
	if (expNum == expNumMask && fracNum == 0 && signBit > 0) {
		printf("The parsed number is: -inf\n");
		return;
	}
	
	unsigned long bias = expNumMask >> 1; //bias is always the largest +ve 2wo's complement number
	long E = 0;
	if (expNum == 0) E = 1 - bias; //denormalized
	else E = expNum - bias; //normalized
	
	double M = fracNum/(pow(2,fracBits)); //gets fraction in decimal
	if (expNum > 0) M = M + 1; //for all normalized cases

 	float parsed = M * pow(2,E); //actual number in float format. Information cannot be lost due to size constraints imposed above (max size is 16 bits)
	if (signBit) printf("The parsed number is: -%f\n",parsed);
	else printf("The parsed number is: %f\n",parsed);
}

