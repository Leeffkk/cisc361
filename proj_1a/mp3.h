typedef struct mp3
{
	char* artist;
	char* title;
	int year;
	int runtime;
	struct mp3* next;
	struct mp3* prev;
} mp3_t;

typedef struct DoublyMP3LinkedList
{
	mp3_t* head;
	mp3_t* tail;
} dll_t;

void addAtTail(mp3_t* target_mp3, dll_t* dll);
void printMP3(mp3_t* target_mp3);
void deleteMP3(mp3_t* target_mp3);
mp3_t* makeMP3(char* artist, char* title, int year, int runtime, mp3_t* next, mp3_t* prev);
void printDLL(dll_t* dll);
void printDLLInverse(dll_t* dll);
void removeByArtist(dll_t* dll, char* artist);
void printLine();
void deleteDLL(dll_t* dll);
void printInstructions();
mp3_t* askUserToCreateMP3();
void askUserToDeleteMP3(dll_t* dll);