#define _CRT_SECURE_NO_WARNINGS

#include "header.h"

int main() {

    srand((unsigned)time(NULL));

    loadWords();

    /* =====================================================
       [2] PRIMITIVNI TIP
       ===================================================== */
    int choice;

    do {

        /* =================================================
           [10] IZBORNIK
           ================================================= */
        printf("\n===== VJEŠALA =====\n");
        printf("1. Igraj\n");
        printf("2. Dodaj riječ\n");
        printf("3. Ažuriraj riječ\n");
        printf("4. Obriši riječ\n");
        printf("5. Ispiši riječi\n");
        printf("6. Sortiraj riječi\n");
        printf("7. Pretraži riječ\n");
        printf("8. Backup datoteke\n");
        printf("9. Izlaz\n");

        scanf("%d", &choice);

        /* ================================================
           [11] ENUM U SWITCHU
           ================================================ */
        switch ((MenuOption)choice) {

            case MENU_PLAY:
                executeOperation(playGame);
                break;

            case MENU_ADD:
                executeOperation(addWord);
                break;

            case MENU_UPDATE:
                executeOperation(updateWord);
                break;

            case MENU_DELETE:
                executeOperation(deleteWord);
                break;

            case MENU_LIST:
                executeOperation(listWords);
                break;

            case MENU_SORT:
                sortWords();
                break;

            case MENU_SEARCH:
                searchWord();
                break;

            case MENU_BACKUP:
                backupFile();
                break;

            case MENU_EXIT:
                printf("Izlaz...\n");
                break;

            default:
                printf("Neispravan unos.\n");
        }

    } while (choice != MENU_EXIT);

    /* =====================================================
       [18] FREE MEMORIJE
       ===================================================== */
    for (int i = 0; i < wordCount; i++) {
        free(words[i].text);
    }

    free(words);

    return 0;
}
