// Copyright (C) Dragusin Daniela-Alexandra (311CA / 2021-2022)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "add.h"
#include "del.h"
#include "show.h"
#include "functions.h"

int main()
{
    list_t *decks = create_list(sizeof(list_t));
	int index, index_card, nr, index1, index2;

	while (1) {
		char command[20];
		scanf("%s", command);

		if (strcmp(command, "ADD_DECK") == 0) {
			scanf("%d", &nr);
			if(verify_buff())
				add_deck(decks, nr);
		} else if (strcmp(command, "DEL_DECK") == 0) {
			scanf("%d", &index);
			if(verify_buff())
				del_deck(decks, index, 1);
		} else if (strcmp(command, "DEL_CARD") == 0) {
			scanf("%d%d", &index, &index_card);
			if(verify_buff())
				del_card(decks, index, index_card, 1);
		} else if (strcmp(command, "SHOW_DECK") == 0) {
			scanf("%d", &index);
			if(verify_buff())
				show_deck(decks, index);
		} else if (strcmp(command, "SHOW_ALL") == 0) {
			if(verify_buff())
				show_all(decks);
		} else if (strcmp(command, "SHUFFLE_DECK") == 0) {
			scanf("%d", &index);
			if(verify_buff())
				shuffle_deck(decks, index);
		} else if (strcmp(command, "REVERSE_DECK") == 0) {
			scanf("%d", &index);
			if(verify_buff())
				reverse_deck(decks, index);
		}  else if (strcmp(command, "MERGE_DECKS") == 0) {
			scanf("%d%d", &index1, &index2);
			if(verify_buff())
				merge_decks(decks, index1, index2);
		} else if (strcmp(command, "SPLIT_DECK") == 0) {
			scanf("%d%d", &index1, &index2);
			if(verify_buff())
				split_deck(decks, index1, index2);
		} else if (strcmp(command, "SORT_DECK") == 0) {
			scanf("%d", &index);
			if(verify_buff())
				sort_deck(decks, index);
		} else if (strcmp(command, "ADD_CARDS") == 0) {
			add_cards(decks);
		} else if (strcmp(command, "DECK_NUMBER") == 0) {
			if(verify_buff())
				deck_number(decks);
		} else if (strcmp(command, "DECK_LEN") == 0) {
			scanf("%d", &index);
			if(verify_buff())
				deck_len(decks, index);
		} else if (strcmp(command, "EXIT") == 0) {
			exit_program(&decks);
			return 0;
		} else {
			char buff[100];
			fgets(buff, 100, stdin);
			printf("Invalid command. Please try again.\n");
		}
	}
    return 0;
}
