#include "mp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 128

int main()
{
	char buffer[BUFFERSIZE];
	int len;
	dll_t* dll = (dll_t*) malloc(sizeof(dll_t));
	dll->head = NULL;
	dll->tail = NULL;
	printInstructions();
	while (1==1){
		printf("Enter a command: ");
		if (fgets(buffer, BUFFERSIZE, stdin) != NULL){
			len = (int) strlen(buffer);
			buffer[len-1] = '\0';
			int input = atoi(buffer);
			switch(input) {
				case 1:
					printf("creating a new mp3:\n");
					addAtTail(askUserToCreateMP3(), dll);
					break;
				case 2:
					printf("deleting mp3 by artist:\n");
					askUserToDeleteMP3(dll);
					break;
				case 3:
					printf("printing the list head to tail:\n");
					printDLL(dll);
					break;
				case 4:
					printf("printing the list tail to head:\n");
					printDLLInverse(dll);
					break;
				case 5:
					printInstructions();
					break;
				case 6:
					deleteDLL(dll);
					return 0;
				default:
					printf("invalid input!!!\n");
					break;
			}
		}
		printLine();
	}
	deleteDLL(dll);
	return 0;
}

// takes an mp3 pointer and a DLL pointer, adds the mp3 to the end of the DLL
void addAtTail(mp3_t* target_mp3, dll_t* dll) {
	if (NULL == dll->head) {
		dll->head = target_mp3;
		dll->tail = target_mp3;
		target_mp3->next = NULL;
		target_mp3->prev = NULL;
	}
	else {
		dll->tail->next = target_mp3;
		target_mp3->prev = dll->tail;
		target_mp3->next = NULL;
		dll->tail = target_mp3;
	}
	printf("\t%s's song has been added to the list\n", target_mp3->artist);
}

// takes an mp3 pointer and prints it
void printMP3(mp3_t* target_mp3) {
	printf("Artist: [%s], Title: [%s], Year: [%d], Runtime: [%d], Next: [%p], Prev: [%p]\n", 
		target_mp3->artist,
		target_mp3->title,
		target_mp3->year,
		target_mp3->runtime,
		target_mp3->next,
		target_mp3->prev);
}

// takes an mp3 pointer, frees its two char* attributes, then also frees itself
// Note: frees the given mp3
void deleteMP3(mp3_t* target_mp3) {
	free(target_mp3->artist);
	free(target_mp3->title);
	free(target_mp3);
}

// takes 6 attribute values of a mp3, constructs a mp3 with given values, and then returns the address of the mp3
// Note: allocates spaces for the created mp3 on the heap
mp3_t* makeMP3(char* artist, char* title, int year, int runtime, mp3_t* next, mp3_t* prev) {
	mp3_t* tmp_mp3 = (mp3_t*) malloc(sizeof(mp3_t));
	tmp_mp3->artist = artist;
	tmp_mp3->title = title;
	tmp_mp3->year = year;
	tmp_mp3->runtime = runtime;
	tmp_mp3->next = next;
	tmp_mp3->prev = prev;
	return tmp_mp3;
}

// takes a DLL pointer, and prints it head to tail
void printDLL(dll_t* dll) {
	mp3_t* tmp_mp3 = dll->head;
	if (NULL == tmp_mp3) {
		printf("\tthe list is empty\n");
		return;
	}
	int counter = 1;
	while (NULL != tmp_mp3) {
		printf("\t%d. ", counter++);
		printMP3(tmp_mp3);
		tmp_mp3 = tmp_mp3->next;
	}
}

// takes a DLL pointer, and prints it tail to head
void printDLLInverse(dll_t* dll) {
	mp3_t* tmp_mp3 = dll->tail;
	if (NULL == tmp_mp3) {
		printf("\tthe list is empty\n");
		return;
	}
	int counter = -1;
	while (NULL != tmp_mp3) {
		printf("\t%d. ", counter--);
		printMP3(tmp_mp3);
		tmp_mp3 = tmp_mp3->prev;
	}
}

// takes a DLL pointer and a char* artist, goes through the DLL and removes all entries with that artist.
// Note: also frees the mp3s when deleting them
void removeByArtist(dll_t* dll, char* artist) {
	mp3_t* current_mp3 = dll->head;
	int counter = 0;
	while (NULL != current_mp3) {
		if (!strcmp(current_mp3->artist, artist)){
			mp3_t* next_mp3 = current_mp3->next;
			if (dll->head == current_mp3 && dll->tail == current_mp3) {
				dll->head = NULL;
				dll->tail = NULL;
			}
			else if (dll->head == current_mp3) {
				dll->head = current_mp3->next;
				current_mp3->next->prev = NULL;
			}
			else if (dll->tail == current_mp3) {
				dll->tail = current_mp3->prev;
				current_mp3->prev->next = NULL;
			}
			else {
				current_mp3->prev->next = current_mp3->next;
				current_mp3->next->prev = current_mp3->prev;
			}
			deleteMP3(current_mp3);
			current_mp3 = next_mp3;
			counter++;
		}
		else {
			current_mp3 = current_mp3->next;
		}
	}
	printf("\t%d songs of this artist have been delete\n", counter);
	return;
}

// helper function to keep things nice & neat
void printLine(){
	printf("-----------------------------------\n");
}

// takes a DLL pointer, deletes every mp3 within that DLL, then frees the DLL itself
// Note: frees all mp3s with the DLL, also frees the DLL
void deleteDLL(dll_t* dll){
	while (NULL != dll->head) {
		mp3_t* tmp_next = dll->head->next;
		deleteMP3(dll->head);
		dll->head = tmp_next;
	}
	free(dll);
}

// prints the available instructions
void printInstructions() {
	printf("Please type in instructions as integers and hit return:\n\t(1)add a new mp3\n\t(2)delete mp3s by artist\n\t"
		"(3)print the list head to tail\n\t(4)print the list tail to head\n\t(5)reprint this instruction sheet\n\t(6)exit the program\n");
}

// asks the user to input values, then creates a mp3 on the heap, and returns the address
// Note: allocates spaces for the mp3 on the heap
mp3_t* askUserToCreateMP3() {
	char local_buffer[BUFFERSIZE];
	int length;
	char* artist;
	char* title;
	int year;
	int runtime;
	while (1==1){
		printf("Please enter artist: ");
		if (fgets(local_buffer, BUFFERSIZE, stdin) != NULL){
			length = (int) strlen(local_buffer);
			local_buffer[length-1] = '\0';
			artist = (char*) malloc(length);
			strcpy(artist, local_buffer);
		}
		printf("Please enter title: ");
		if (fgets(local_buffer, BUFFERSIZE, stdin) != NULL){
			length = (int) strlen(local_buffer);
			local_buffer[length-1] = '\0';
			title = (char*) malloc(length);
			strcpy(title, local_buffer);
		}
		printf("Please enter year: ");
		if (fgets(local_buffer, BUFFERSIZE, stdin) != NULL){
			length = (int) strlen(local_buffer);
			year = atoi(local_buffer);
			if (year == 0) {
				continue;
			}
		}
		printf("Please enter runtime: ");
		if (fgets(local_buffer, BUFFERSIZE, stdin) != NULL){
			length = (int) strlen(local_buffer);
			runtime = atoi(local_buffer);
			if (runtime == 0) {
				continue;
			}
		}
		return makeMP3(artist, title, year, runtime, NULL, NULL);
	}
	return NULL;
}

// takes a DLL pointer. Asks the user to input an artist name, then deletes all entries of the DLL with that artist.
// Note: frees any mp3 in DLL if mp3's artist is the same as the given one
void askUserToDeleteMP3(dll_t* dll){
	char local_buffer[BUFFERSIZE];
	int length;
	char* artist;
	printf("Please enter artist: ");
	if (fgets(local_buffer, BUFFERSIZE, stdin) != NULL){
		length = (int) strlen(local_buffer);
		local_buffer[length-1] = '\0';
		artist = (char*) malloc(length);
		strcpy(artist, local_buffer);
	}
	removeByArtist(dll, artist);
	free(artist);
	return;
}