#define _CRT_SECURE_NO_WARNINGS

#include "header.h"

/* ================= GLOBALE ================= */
Word* words = NULL;
int wordCount = 0;

/* ================= FILE ================= */

void loadWords() {
	FILE* f = fopen(WORD_FILE, "r");
	if (!f) return; /* 14.  Zaštita parametara kod svih funkcija. */

	char buffer[100];

	while (fgets(buffer, sizeof(buffer), f)) {
		buffer[strcspn(buffer, "\n")] = 0;

		words = realloc(words, (wordCount + 1) * sizeof(Word));
		words[wordCount].text = malloc(strlen(buffer) + 1);
		strcpy(words[wordCount].text, buffer);
		wordCount++;
	}

	fclose(f);
}

void saveWords() {
	FILE* f = fopen(WORD_FILE, "w");
	if (!f) return;

	for (int i = 0; i < wordCount; i++) {
		fprintf(f, "%s\n", words[i].text);
	}

	fclose(f);
}

/* ================= CRUD ================= */

void addWord() {
	char buffer[100];
	printf("Unesi rijec: ");
	scanf("%s", buffer);

	words = realloc(words, (wordCount + 1) * sizeof(Word));
	words[wordCount].text = malloc(strlen(buffer) + 1); /* 17. Koristiti funkcije malloc(), calloc(), realloc(), free() – neku od njih, ako ne i sve.*/
	strcpy(words[wordCount].text, buffer);
	wordCount++;

	saveWords();
}

void deleteWord() {
	char buffer[100]; /* 15. Koristiti stati?ki zauzeta polja gdje su potrebna, nikako ne koristiti VLA polja.  */
	printf("Rijec za brisanje: ");
	scanf("%s", buffer);

	for (int i = 0; i < wordCount; i++) {
		if (strcmp(words[i].text, buffer) == 0) {

			free(words[i].text); /* 18. Sigurno brisanje memorije koja je dinami?ki zauzeta, anuliranje memorijskog prostora,
							 provjera pokaziva?a kako se ne bi dogodila pogreška double free() i anuliranje svih pokaziva?a
							 koji su bili usmjereni na memorijski prostor koji se dinami?ki zauzeo. */

			for (int j = i; j < wordCount - 1; j++)
				words[j] = words[j + 1];

			wordCount--;
			words = realloc(words, wordCount * sizeof(Word));

			saveWords();
			return;
		}
	}

	printf("Nije pronadeno.\n");
}

void listWords() {
	for (int i = 0; i < wordCount; i++) {
		printf("%d. %s\n", i + 1, words[i].text);
	}
}

/* ================= GAME ================= */

char* getRandomWord() {
	if (wordCount == 0) return NULL;
	return words[rand() % wordCount].text;
}

void drawHangman(int tries) {
	static int last = -1; /* 6. Primjena klju?ne rije?i static za globalne i lokalne varijable. */
	if (last == tries) return;
	last = tries;

	printf("\nPokusaji: %d\n", tries);
}

void playGame() {
	char* word = getRandomWord();
	if (!word) return;

	int len = strlen(word);
	char* guess = calloc(len + 1, 1);

	for (int i = 0; i < len; i++) guess[i] = '_';

	int tries = MAX_TRIES;
	char c;

	while (tries > 0) {
		printf("\nRijec: %s\n", guess);
		drawHangman(tries);

		scanf(" %c", &c);

		int found = 0;

		for (int i = 0; i < len; i++) {
			if (word[i] == c) {
				guess[i] = c;
				found = 1;
			}
		}

		if (!found) tries--;

		if (strcmp(word, guess) == 0) {
			printf("POBJEDA!\n");
			break;
		}
	}

	free(guess);
}
/* ================= SORT ================= */

int compareWords(const void* a, const void* b) {
	Word* w1 = (Word*)a;
	Word* w2 = (Word*)b;
	return strcmp(w1->text, w2->text);
}

void sortWords() {
	qsort(words, wordCount, sizeof(Word), compareWords); /* 23.  Sortiranje – preporuka koristiti ugra?enu qsort() funkciju, ina?e se može koristiti bilo koja funkcija sortiranja.  */
	saveWords();
}

/* ================= SEARCH ================= */

int recursiveBinarySearch(char* key, int left, int right) {
	if (left > right) return -1;

	int mid = (left + right) / 2;

	int cmp = strcmp(words[mid].text, key);

	if (cmp == 0) return mid;
	if (cmp > 0)
		return recursiveBinarySearch(key, left, mid - 1);
	else
		return recursiveBinarySearch(key, mid + 1, right);
}

void searchWord() {
	char buffer[100];
	printf("Trazi rijec: ");
	scanf("%s", buffer);

	int res = recursiveBinarySearch(buffer, 0, wordCount - 1);

	if (res != -1)
		printf("Nadeno: %s\n", words[res].text);
	else
		printf("Nije nadeno.\n");
}

/* ================= FILE OPS ================= */

void backupFile() {
	FILE* src = fopen(WORD_FILE, "r");
	FILE* dst = fopen(BACKUP_FILE, "w");

	if (!src || !dst) {
		perror("Greska"); /* 22. Upravljati s pogreškama, errno, perror(), strerror(), feof(), ferror() – neku od njih ako ne sve. */
		return;
	}

	char c;
	while ((c = fgetc(src)) != EOF)
		fputc(c, dst);

	fclose(src); /* 19.  Datoteke, koristiti tekstualnu ili binarnu, provjera pokaziva?a i zatvaranje datoteke. */
	fclose(dst);
}

void restoreFile() {
	rename(BACKUP_FILE, WORD_FILE); /* 21. Koristiti funkcije remove(), rename(), po potrebi implementirati funkciju za kopiranje datoteka.*/
}

/* ================= FUNCTION POINTER ================= */

void executeOperation(void (*func)()) {
	func();
}