// Copyright (C) Dragusin Daniela-Alexandra (311CA / 2021-2022)
#include "show.h"

/*Functie ce afiseaza cartile continute de un pachet
  al carui index este primit ca parametru.*/
void show_deck(list_t *decks, int index)
{
	if(!verify_deck_index(decks, index)) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}

	printf("Deck %d:\n", index);

	node_t *aux_deck = get_nth_node(decks, index);
	list_t *aux_cards = aux_deck->data;
	int size = aux_cards->size;
	node_t *aux_card = aux_cards->head;

	for (int i = 0; i < size; i++) {
		card_t *aux_info = aux_card->data;
		printf("\t%d %s\n", aux_info->value, aux_info->symbol);

		aux_card = aux_card->next;
	}
}

/*Functie ce afiseaza continutul tuturor pachetelor de carti existente.*/
void show_all(list_t *decks)
{
	for (int i = 0; i < decks->size; i++) {
		show_deck(decks, i);
	}
}
