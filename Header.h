#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<errno.h>

/* ================= KONSTANTE ================= */

#define MAX_TRIES 6
#define WORD_FILE "words.txt"
#define BACKUP_FILE "words_backup.txt"

/* ================= IZBORNIK ================= */

typedef enum {
	MENU_PLAY = 1,
	MENU_ADD,
	MENU_DELETE,
	MENU_LIST,
	MENU_SORT,
	MENU_SEARCH,
	MENU_BACKUP,
	MENU_EXIT
} MenuOption;

/* ================= STRUCT ================= */
typedef struct {
	char* text;
} Word;

/* ================= GLOBALE ================= */
extern Word* words;
extern int wordCount;

/* ================= FUNKCIJE ================= */

/* CRUD */
void loadWords();
void saveWords();
void addWord();
void deleteWord();
void listWords();

/* GAME */
void playGame();
char* getRandomWord();
void drawHangman(int tries);

/* SORT + SEARCH */
int compareWords(const void* a, const void* b);
void sortWords();
void searchWord();

/* FILE OPS */
void backupFile();
void restoreFile();

/* REKURZIJA */
int recursiveBinarySearch(char* key, int left, int right);

/* FUNCTION POINTER */
void executeOperation(void (*func)());

#endif