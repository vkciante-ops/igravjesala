#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
int main() {
	srand(time(NULL));

	loadWords();

	int choice;
	char searchBuf[100];

	do {
		printf("\n===== HANGMAN =====\n");
		printf("1. Play\n");
		printf("2. Add word\n");
		printf("3. Delete word\n");
		printf("4. List words\n");
		printf("5. Sort words (qsort)\n");
		printf("6. Search word (binary recursion)\n");
		printf("7. Backup file\n");
		printf("8. Exit\n");
		printf("Choice: ");

		scanf("%d", &choice);

		switch ((MenuOption)choice) {

		case MENU_PLAY:
			executeOperation(playGame);
			break;

		case MENU_ADD:
			executeOperation(addWord);
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
			printf("Exit...\n");
			break;
		}

	} while (choice != MENU_EXIT);

	for (int i = 0; i < wordCount; i++)
		free(words[i].text);

	free(words);

	return 0;
}