// Copyright (C) Dragusin Daniela-Alexandra (311CA / 2021-2022)
#include "functions.h"

/*Functie ce inverseaza prima si a doua jumatate a pachetului de carti.
  Este creata o legatura intre ultima si prima carte, astfel incat cartea
  urmatoare ultimei este prima si cea anterioara primei este ultima.
  Este rupta legatura dintre cartile de la mijlocul pachetului.*/
void shuffle_deck(list_t *decks, int index)
{
	if(!verify_deck_index(decks, index)) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}

	node_t *deck = get_nth_node(decks, index);
	list_t *cards = deck->data;
	int n = cards->size;

	if(n > 1) {
		node_t *card = get_nth_node(cards, n - 1);
		card->next = cards->head;
		cards->head->prev = card;

		node_t *new_head = get_nth_node(cards, n/2);
		new_head->prev->next = NULL;
		new_head->prev = NULL;
		cards->head = new_head;
	}

	printf("The deck %d was successfully shuffled.\n", index);
}

/*Functie ce inverseaza ordinea cartilor din pachet.
  Indexul pachetului este primit ca parametru.
  Functia retine continutul ultimei carti, o sterge si apoi adauga o noua
  carte cu aceleasi informatii la inceputul listei.
  Este repetat algoritmul pana cand prima carte ajunge pe ultima pozitie.*/
void reverse_deck(list_t *decks, int index)
{
	if(!verify_deck_index(decks, index)) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}

	node_t *deck = get_nth_node(decks, index);
	list_t *cards = deck->data;

	if(cards->size > 1) {
		for(int i = 0; i < cards->size; i++) {
			node_t *garbage = remove_nth_card(cards, cards->size - 1);
			card_t *data = garbage->data;
			add_card(cards, i, data->value, data->symbol);

			free(data);
			free(garbage);
		}
	}

	printf("The deck %d was successfully reversed.\n", index);
}

/*Functie ce combina doua pachete adaugand cate o carte din fiecare, rand pe rand.
  Este creata o noua lista in care se adauga cate o carte din fiecare pachet.
  Daca vreun pachet ramane fara carti, se continua prin adaugarea cartilor
  din pachetul ce nu este gol.
  Pachetele ce au fost combinate se sterg.
  Noul pachet este adaugat la finalul listei de pachete.
  Este afisat un mesaj specific.*/
void merge_decks(list_t *decks, int index1, int index2)
{
	if(!verify_deck_index(decks, index1) || !verify_deck_index(decks, index2)) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}

	list_t *merged = create_list(sizeof(card_t));
	int i = 0;

	node_t * head1 = get_nth_node(decks, index1);
	node_t *head2 = get_nth_node(decks, index2);
	list_t *list1 = head1->data, *list2 = head2->data;
	node_t *card1 = list1->head, *card2 = list2->head;
	card_t *data1, *data2;

	while (card1 && card2) {
		data1 = card1->data;
		add_card(merged, i++, data1->value, data1->symbol);
		card1 = card1->next;

		data2 = card2->data;
		add_card(merged, i++, data2->value, data2->symbol);
		card2 = card2->next;
	}

	while (card1) {
		data1 = card1->data;
		add_card(merged, i++, data1->value, data1->symbol);
		card1 = card1->next;
	}

	while (card2) {
		data2 = card2->data;
		add_card(merged, i++, data2->value, data2->symbol);
		card2 = card2->next;
	}

	printf("The deck %d and the deck %d were successfully merged.\n",
			index1, index2);

	del_deck(decks, index1, 0);
	if(index1 < index2)
		index2--;
	del_deck(decks, index2, 0);

	node_t *new_deck = create_node(merged, sizeof(list_t));
	free(merged);

	if (decks->size == 0) {
		decks->head = new_deck;
	} else {
		node_t *aux = get_nth_node(decks, decks->size - 1);
		aux->next = new_deck;
		new_deck->prev = aux;
	}

	decks->size++;
}

/*Functie ce imparte un anumit pachet in alte doua pachete dupa un index dat.
  In cazul in care pachetul este impartit dupa un index nul sau egal cu cel al
  ultimului element din lista, nu se schimba nimic.
  In caz contrar, este creata o noua lista ce contine cartile de la indexul
  specificat pana la finalul pachetului.
  Este creat noul pachet ce contine lista de carti.
  Cartile ce au fost adaugate in noul pachet sunt sterse din cel vechi.
  Noul pachet este adaugat in lista de pachete imediat dupa primul.*/
void split_deck(list_t *decks, int index_deck, int index_split)
{
	if(!verify_deck_index(decks, index_deck)) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}

	node_t *deck = get_nth_node(decks, index_deck);
	list_t *cards = deck->data;

	if(!verify_card_index(cards, index_split)) {
		printf("The provided index is out of bounds for deck %d.\n",
				index_deck);
		return;
	}

	if(cards->size > 1 && index_split < cards->size && index_split > 0) {
		list_t *splitted = create_list(sizeof(card_t));

		node_t *card = get_nth_node(cards, index_split);
		card_t *data;

		int added = 0;

		while (card) {
			data = card->data;
			add_card(splitted, added++, data->value, data->symbol);
			card = card->next;
		}

		node_t *new_deck = create_node(splitted, sizeof(list_t));
		free(splitted);

		while (added > 0) {
			del_card(decks, index_deck, index_split, 0);
			added--;
		}

		if (decks->size == 0) {
			decks->head = new_deck;
		} else if (index_deck + 1 < decks->size) {
			node_t *aux = get_nth_node(decks, index_deck);
			new_deck->next = aux->next;
			aux->next->prev = new_deck;
			new_deck->prev = aux;
			aux->next = new_deck;
		} else {
			node_t *aux = get_nth_node(decks, index_deck);
			aux->next = new_deck;
			new_deck->prev = aux;
		}

		decks->size++;

		if (cards->size == 0) {
			del_deck(decks, index_deck, 0);
		}
	}
	printf("The deck %d was successfully split by index %d.\n",
			index_deck, index_split);
}

/*Functie ce sorteaza crescator un pachet de carti.
  Este folosita metoda bulelor, utilizand o functie auxiliara de interschimbare
  Cartile sunt sortate dupa 2 criterii: initial dupa valoarea acestora,
  iar in caz de egalitate, sunt sortate dupa simbol cu ajutorul altei
  functii de comparare.*/
void sort_deck(list_t *decks, int index)
{
	if(!verify_deck_index(decks, index)) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}

	node_t *deck = get_nth_node(decks, index);
	list_t *cards = deck->data;

	if (cards->size > 1) {
		node_t *card1, *card2;
		card_t *data1, *data2;

		for (card1 = cards->head; card1->next; card1 = card1->next) {
			for (card2 = card1->next; card2; card2 = card2->next) {
				data1 = card1->data;
				data2 = card2->data;

				if (data1->value > data2->value)
					swap(data1, data2);

				if (data1->value == data2->value)
					if(!compare_symbol(data1->symbol, data2->symbol))
						swap(data1, data2);
			}
		}
	}

	printf("The deck %d was successfully sorted.\n", index);
}

/*Functie ce elibereaza memoria utilizata de pachete si carti
  si opreste executia programului.*/
void exit_program(list_t **decks)
{
	if((*decks)->size == 0) {
		free(*decks);
		return;
	}

	node_t *aux_deck = (*decks)->head;
	node_t *garbage_deck;
	list_t *aux_cards;

	while (aux_deck) {
		garbage_deck = aux_deck;
		aux_deck = aux_deck->next;

		aux_cards = garbage_deck->data;
		free_list(&aux_cards);
		free(garbage_deck);
    }

	free(*decks);
}
