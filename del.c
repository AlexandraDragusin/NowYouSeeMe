// Copyright (C) Dragusin Daniela-Alexandra (311CA / 2021-2022)
#include "del.h"

/*Functie ce sterge un pachet din lista de pachete.
  Indexul pachetului ce urmeaza a fi sters este primit ca parametru.
  Este tratat cazul in care pachetul este adaugat la
  inceputul/mijlocul/sfarsitul listei de pachete.
  Este eliberata memoria ocupata de pachet.
  Este afisat un mesaj corespunzator.*/
void del_deck(list_t *decks, int index, int message)
{
	if(!verify_deck_index(decks, index)) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}

	node_t *garbage;

	if (index == 0) {
		garbage = decks->head;

		if(decks->size > 1) {
			decks->head = garbage->next;
			garbage->next->prev = NULL;
			garbage->next = NULL;
		}
	} else {
		node_t *aux = get_nth_node(decks, index - 1);
		garbage = aux->next;

		if(index == decks->size -1) {
			aux->next = NULL;
		} else {
			aux->next = garbage->next;
			garbage->next->prev = aux;
		}

		garbage->prev = NULL;
		garbage->next = NULL;
	}

	list_t *garbage_cards = garbage->data;
	free_list(&garbage_cards);
	free(garbage);

	(decks->size)--;

	if(message)
		printf("The deck %d was successfully deleted.\n", index);
}

/*Functie ce sterge o carte de pe o anumita pozitie a unui pachet.
  Indexul cartii si al pachetului sunt primiti ca parametri.
  Sunt tratate cazurile in care se doreste stergerea cartii de pe pozitia
  de inceput/mijloc/final.
  Este eliberata memoria ocupata de carte.
  In cazul in care in urma stergerii cartii pachetul ramane gol,
  acesta este sters si este eliberata memoria ocupata de el.*/
void del_card(list_t *decks, int i_deck, int i_card, int message)
{
	if(!verify_deck_index(decks, i_deck)) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}

	node_t *deck = get_nth_node(decks, i_deck);
	list_t *cards = deck->data;
	node_t *garbage_card;

	if(!verify_card_index(cards, i_card)) {
		printf("The provided index is out of bounds for deck %d.\n", i_deck);
		return;
	}

	if (i_card == 0) {
		garbage_card = cards->head;

		if(cards->size > 1) {
			cards->head = garbage_card->next;
			garbage_card->next->prev = NULL;
			garbage_card->next = NULL;
		}
	} else {
		node_t *aux_card = get_nth_node(cards, i_card - 1);
		garbage_card = aux_card->next;

		if(i_card == cards->size - 1) {
			aux_card->next = NULL;
		} else {
			aux_card->next = garbage_card->next;
			garbage_card->next->prev = aux_card;
		}
		garbage_card->next = NULL;
		garbage_card->prev = NULL;
	}

	card_t *garbage_data = garbage_card->data;

	free(garbage_data);
	free(garbage_card);

	(cards->size)--;

	if(cards->size == 0) {
		node_t *garbage_deck;
		if(i_deck == 0) {
			garbage_deck = decks->head;

			if(decks->size > 1) {
				decks->head = garbage_deck->next;
				garbage_deck->next->prev = NULL;
				garbage_deck->next = NULL;
			}
		} else {
			node_t *aux_deck = get_nth_node(decks, i_deck - 1);
			garbage_deck = aux_deck->next;

			if(i_deck == decks->size -1) {
				aux_deck->next = NULL;
			} else {
				aux_deck->next = garbage_deck->next;
				garbage_deck->next->prev = aux_deck;
			}

			garbage_deck->prev = NULL;
			garbage_deck->next = NULL;
		}

		list_t *garbage_cards = garbage_deck->data;
		free_list(&garbage_cards);
		free(garbage_deck);
		(decks->size)--;
	}

	if (message)
		printf("The card was successfully deleted from deck %d.\n", i_deck);
}
