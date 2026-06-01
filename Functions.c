#include "header.h"

/* =========================================================
   [8] DEFINICIJA GLOBALNIH VARIJABLI
   ========================================================= */
Word *words = NULL;
int wordCount = 0;

/* =========================================================
   [1][19][20][22]
   LOAD WORDS
   CRUD READ + FILES + ERROR + FSEEK
   ========================================================= */
void loadWords() {

    FILE *f = fopen(WORD_FILE, "r");

    /* [14][22] zaštita + perror */
    if (!f) {
        perror("Greška pri otvaranju datoteke");
        return;
    }

    /* =====================================================
       [20] fseek ftell rewind
       ===================================================== */
    fseek(f, 0, SEEK_END);

    long size = ftell(f);

    rewind(f);

    printf("Veličina datoteke: %ld bajtova\n", size);

    /* =====================================================
       [15] STATIČKO POLJE
       ===================================================== */
    char buffer[100];

    while (fgets(buffer, sizeof(buffer), f)) {

        buffer[strcspn(buffer, "\n")] = 0;

        /* =================================================
           [16][17] REALLOC
           ================================================= */
        Word *temp =
            realloc(words, (wordCount + 1) * sizeof(Word));

        if (!temp) {
            perror("Greška realloc");
            fclose(f);
            return;
        }

        words = temp;

        /* =================================================
           [16][17] MALLOC
           ================================================= */
        words[wordCount].text =
            malloc(strlen(buffer) + 1);

        if (!words[wordCount].text) {
            perror("Greška malloc");
            fclose(f);
            return;
        }

        strcpy(words[wordCount].text, buffer);

        wordCount++;
    }

    fclose(f);
}

/* =========================================================
   [1][19]
   SAVE WORDS
   ========================================================= */
void saveWords() {

    FILE *f = fopen(WORD_FILE, "w");

    if (!f) {
        perror("Greška save");
        return;
    }

    for (int i = 0; i < wordCount; i++) {
        fprintf(f, "%s\n", words[i].text);
    }

    fclose(f);
}

/* =========================================================
   [1] CREATE / INSERT
   ========================================================= */
void addWord() {

    char buffer[100];

    printf("Unesi riječ: ");
    scanf("%99s", buffer);

    Word *temp =
        realloc(words, (wordCount + 1) * sizeof(Word));

    if (!temp) {
        perror("Greška realloc");
        return;
    }

    words = temp;

    words[wordCount].text =
        malloc(strlen(buffer) + 1);

    if (!words[wordCount].text) {
        perror("Greška malloc");
        return;
    }

    strcpy(words[wordCount].text, buffer);

    wordCount++;

    saveWords();
}

/* =========================================================
   [1] UPDATE
   ========================================================= */
void updateWord() {

    char oldWord[100];
    char newWord[100];

    printf("Stara riječ: ");
    scanf("%99s", oldWord);

    for (int i = 0; i < wordCount; i++) {

        if (strcmp(words[i].text, oldWord) == 0) {

            printf("Nova riječ: ");
            scanf("%99s", newWord);

            char *temp =
                realloc(words[i].text,
                        strlen(newWord) + 1);

            if (!temp) {
                perror("Greška realloc");
                return;
            }

            words[i].text = temp;

            strcpy(words[i].text, newWord);

            saveWords();

            printf("Riječ ažurirana!\n");

            return;
        }
    }

    printf("Riječ nije pronađena.\n");
}

/* =========================================================
   [1] DELETE
   ========================================================= */
void deleteWord() {

    char buffer[100];

    printf("Riječ za brisanje: ");
    scanf("%99s", buffer);

    for (int i = 0; i < wordCount; i++) {

        if (strcmp(words[i].text, buffer) == 0) {

            /* =============================================
               [18] FREE
               ============================================= */
            free(words[i].text);

            for (int j = i; j < wordCount - 1; j++) {
                words[j] = words[j + 1];
            }

            wordCount--;

            saveWords();

            printf("Riječ obrisana.\n");

            return;
        }
    }

    printf("Riječ nije pronađena.\n");
}

/* =========================================================
   [1] READ
   ========================================================= */
void listWords() {

    for (int i = 0; i < wordCount; i++) {
        printf("%d. %s\n", i + 1, words[i].text);
    }
}

/* =========================================================
   IGRA
   ========================================================= */

/* [12] pokazivač */
char* getRandomWord() {

    if (wordCount == 0)
        return NULL;

    return words[rand() % wordCount].text;
}

/* =========================================================
   [6] STATIC
   ========================================================= */
void drawHangman(int tries) {

    static int last = -1;

    if (last == tries)
        return;

    last = tries;

    printf("Preostalo pokušaja: %d\n", tries);
}

void playGame() {

    char *word = getRandomWord();

    if (!word)
        return;

    int len = strlen(word);

    /* =====================================================
       [17] CALLOC
       ===================================================== */
    char *guess = calloc(len + 1, 1);

    for (int i = 0; i < len; i++)
        guess[i] = '_';

    int tries = MAX_TRIES;

    char c;

    while (tries > 0) {

        printf("\nRiječ: %s\n", guess);

        drawHangman(tries);

        scanf(" %c", &c);

        int found = 0;

        for (int i = 0; i < len; i++) {

            if (word[i] == c) {
                guess[i] = c;
                found = 1;
            }
        }

        if (!found)
            tries--;

        if (strcmp(word, guess) == 0) {
            printf("Pobjeda!\n");
            break;
        }
    }

    free(guess);
}

/* =========================================================
   [23][26] QSORT + FUNCTION POINTER
   ========================================================= */
int compareWords(const void *a, const void *b) {

    Word *w1 = (Word*)a;
    Word *w2 = (Word*)b;

    return strcmp(w1->text, w2->text);
}

void sortWords() {

    qsort(words,
          wordCount,
          sizeof(Word),
          compareWords);

    saveWords();

    printf("Riječi sortirane.\n");
}

/* =========================================================
   [24][25] PRETRAGA + REKURZIJA
   ========================================================= */
int recursiveBinarySearch(char *key,
                          int left,
                          int right) {

    if (left > right)
        return -1;

    int mid = (left + right) / 2;

    int cmp = strcmp(words[mid].text, key);

    if (cmp == 0)
        return mid;

    if (cmp > 0)
        return recursiveBinarySearch(
            key,
            left,
            mid - 1
        );

    return recursiveBinarySearch(
        key,
        mid + 1,
        right
    );
}

void searchWord() {

    char buffer[100];

    printf("Traži riječ: ");

    scanf("%99s", buffer);

    int result =
        recursiveBinarySearch(
            buffer,
            0,
            wordCount - 1
        );

    if (result != -1)
        printf("Pronađeno: %s\n",
               words[result].text);
    else
        printf("Nije pronađeno.\n");
}

/* =========================================================
   [21] RENAME
   ========================================================= */
void backupFile() {

    rename(WORD_FILE, BACKUP_FILE);

    printf("Backup napravljen.\n");
}

/* =========================================================
   [26] POKAZIVAČI NA FUNKCIJE
   ========================================================= */
void executeOperation(void (*func)()) {

    func();
}
