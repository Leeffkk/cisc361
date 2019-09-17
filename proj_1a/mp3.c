#include "mp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{

	// printf("hello world\n");

	mp3_t* head = NULL;
	mp3_t* tail = NULL;

	head = (mp3_t*) malloc(sizeof(mp3_t));

	head->artist = (char*) malloc(6);
	strcpy(head->artist, "yufan");
	printf("artist name is [%s]\n", head->artist);

	free(head->artist);
	free(head);

	return 0;
}

