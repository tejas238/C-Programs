//typing_word_game.c file Tejas Menon, CS201, last edited 10/4.
//Purpose: This file contains the functions necessary for outputting words at random
//         for the user and ensuring that each word output is unique for each of the 9
//         'draws'. Effieciency is guaranteed as rand() calls occur only once for each draw.
//         This program uses the sys/time.h library native to unix.

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h> 
#include <string.h> //USED ONLY FOR STRNCMP() FUNCTION (-Wall shows up warnings otherwise)

char ** init(); //This function initializes a 'sentence' to hold all the words and returns a pointer to it
void input_rand(char**sentence); //This function randomely picks a word from the array and swaps it with the one at the last non-NULL index

int
main() 
{
 	struct timeval i_clock; //initial
	struct timeval f_clock; //final
	struct timeval diff; //difference
	char ** sentence = init();
	printf("This game will test your typing speed. Hit \"a\\n\" to start the timer\n");
	char c[2];
	int success = scanf("%1s",c);
	if (success) while(getchar() != '\n'); //inputstream flushed
	gettimeofday(&i_clock,NULL); //timer started
	srand(i_clock.tv_usec); //random seed
	for(int i=0;i<9;++i) {
		input_rand(sentence);
	}
	gettimeofday(&f_clock,NULL);
 	timersub(&f_clock,&i_clock,&diff);
	printf("Time taken: %ld seconds and %ld usec\n",diff.tv_sec,diff.tv_usec);
	free(sentence);
}

//This function dynamically allocates the words "The quick brown fox...the lazy dog" to a size 9 sentence
char** 
init() 
{
	char ** sentence = (char**)malloc(sizeof(char*)*9);
	sentence[0] = (char*)malloc(sizeof(char)*4); strncpy(sentence[0],"The",4); //remainder of sentence padded with \0
	sentence[1] = (char*)malloc(sizeof(char)*6); strncpy(sentence[1],"quick",6);
        sentence[2] = (char*)malloc(sizeof(char)*6); strncpy(sentence[2],"brown",6);
	sentence[3] = (char*)malloc(sizeof(char)*4); strncpy(sentence[3],"fox",4);
	sentence[4] = (char*)malloc(sizeof(char)*6); strncpy(sentence[4],"jumps",6);
	sentence[5] = (char*)malloc(sizeof(char)*5); strncpy(sentence[5],"over",5);
	sentence[6] = (char*)malloc(sizeof(char)*4); strncpy(sentence[6],"the",4);
	sentence[7] = (char*)malloc(sizeof(char)*5); strncpy(sentence[7],"lazy",5);
        sentence[8] = (char*)malloc(sizeof(char)*4); strncpy(sentence[8],"dog",4); 
	return sentence;
}

//This function ensures that rand calls are only performed once to produce unique 'draws' by deallocating 
//the word at a random index and then assigning that char* ptr to the last non-NULL word before making it NULL.
//For example at the beginning, from a draw of 9 words, if 3 is the index to be displayed, this word will be deallocated
//and the word at index 8 will be assigned to index 3. After this, index 8 will be made NULL.
void 
input_rand(char**sentence) 
{
	int f_index = 9;
	for(int i=0;i<9;++i) {
		if (!(sentence[i]) && (f_index == 9)) f_index = i; //finds the first NULL index
        }
	int w_index = rand()%f_index; //The word to be chosen from this range
	printf("Word: %s\n",sentence[w_index]);
	char input[11];
	printf("Your input: ");
	int success = scanf("%10s",input);
	if (success) while(getchar() != '\n');
	while (strncmp(input,sentence[w_index],10)) {
		printf("Try again: ");
		success = scanf("%10s",input);
		if (success) while(getchar() != '\n');
        }
	char * hold = sentence[w_index];
	sentence[w_index] = sentence[f_index-1];
	free(hold);
	sentence[f_index-1] = NULL;
}	
