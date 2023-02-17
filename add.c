// Copyright (C) Dragusin Daniela-Alexandra (311CA / 2021-2022)
#include "add.h"

/*Functie ce verifica daca valoarea si simbolul unei carti sunt corecte.*/
int valid_pair(int value, char symbol[MAX_SYMBOL])
{
	if (value < 1 || value > 14)
		return 0;

	if (strcmp(symbol, "HEART") && strcmp(symbol, "CLUB") &&
		strcmp(symbol, "DIAMOND") && strcmp(symbol, "SPADE"))
		return 0;

	return 1;
}

/*Functie ce adauga un nou pachet la sfarsitul listei de pachete.
  Numarul de carti pe care le va contine este primit ca parametru.
  Este creata o noua lista de -nr- carti, apoi un nou pachet ce le contine.
  Pachetul este adaugat pe pozitia finala.*/
void add_deck(list_t *decks, int nr)
{
	int value, added = 0;
	char symbol[MAX_SYMBOL];

	list_t *cards = create_list(sizeof(card_t));

	while (cards->size < nr) {
		scanf("%d", &value);
		scanf("%s", symbol);

		if (valid_pair(value, symbol)) {
			add_card(cards, cards->size, value, symbol);
			added++;
		} else {
			printf("The provided card is not a valid one.\n");
		}
	}

	node_t *new_deck = create_node(cards, sizeof(list_t));
	free(cards);

	if (decks->size == 0) {
		decks->head = new_deck;
		new_deck->next = NULL;
		new_deck->prev = NULL;
	} else {
		node_t *aux = get_nth_node(decks, decks->size - 1);
		aux->next = new_deck;
		new_deck->prev = aux;
	}

	decks->size++;
	printf("The deck was successfully created with %d cards.\n", nr);
}

/*Functie ce adauga un numar de carti intr-un anumit pachet.
  Numarul cartilor si indexului pachetului sunt citite de la tastatura.
  In continuare se citesc -nr- carti, se verifica corectitudinea fiecareia,
  iar in caz afirmativ, cartea este adugata in pachetul cu indexul precizat.*/
void add_cards(list_t *decks)
{
	int index, nr, added = 0;
	char symbol[MAX_SYMBOL], value[MAX_STRING];
	scanf("%d%d", &index, &nr);

	if(!verify_buff())
		return;

	if(!verify_deck_index(decks, index)) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}

	node_t *aux_deck = get_nth_node(decks, index);
	list_t *cards = aux_deck->data;

	while (added < nr) {
		scanf("%s", value);
		scanf("%s", symbol);

		int value1 = atoi(value);

		if (valid_pair(value1, symbol)) {
			add_card(cards, cards->size, value1, symbol);
			added++;
		} else {
			char buff[100];
			fgets(buff, 100, stdin);
			printf("The provided card is not a valid one.\n");
		}
	}

	printf("The cards were successfully added to deck %d.\n", index);
}
