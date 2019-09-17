typedef struct mp3
{
	char* artist;
	char* title;
	int year;
	int runtime;
	struct mp3* next;
	struct mp3* prev;
} mp3_t;