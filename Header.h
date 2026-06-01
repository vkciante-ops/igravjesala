#define _CRT_SECURE_NO_WARNINGS

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

/* =========================================================
   [9] MAKRO KONSTANTE
   ========================================================= */
#define MAX_TRIES 6
#define WORD_FILE "words.txt"
#define BACKUP_FILE "backup.txt"

/* =========================================================
   [4] ENUM
   koristi se za izbornik
   ========================================================= */
typedef enum {
    MENU_PLAY = 1,
    MENU_ADD,
    MENU_UPDATE,
    MENU_DELETE,
    MENU_LIST,
    MENU_SORT,
    MENU_SEARCH,
    MENU_BACKUP,
    MENU_EXIT
} MenuOption;

/* =========================================================
   [3][4][13] STRUCT + TYPEDEF
   ========================================================= */
typedef struct {
    char *text;
} Word;

/* =========================================================
   [8] EXTERN GLOBALNE VARIJABLE
   ========================================================= */
extern Word *words;
extern int wordCount;

/* CRUD */
void loadWords();
void saveWords();
void addWord();
void updateWord();
void deleteWord();
void listWords();

/* igra */
void playGame();
char* getRandomWord();
void drawHangman(int tries);

/* sortiranje i pretraga */
void sortWords();
void searchWord();
int compareWords(const void *a, const void *b);

/* [25] REKURZIJA */
int recursiveBinarySearch(char *key, int left, int right);

/* backup */
void backupFile();

/* [26] POKAZIVAČ NA FUNKCIJU */
void executeOperation(void (*func)());

#endif
