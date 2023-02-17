// Copyright (C) Dragusin Daniela-Alexandra (311CA / 2021-2022)
#include "utils.h"

/*Functie ce creeaza o lista, ce va reprezenta fie o lista de pachete,
  fie una de carti*/
list_t* create_list(int data_size)
{
	list_t *list = malloc(sizeof(list_t));

	if (!list) {
		fprintf(stdout, "Failed to alloc memory for the list.\n");
		return NULL;
	}

	list->head = NULL;
	list->size = 0;
	list->data_size = data_size;

	return list;
}

/*Functie ce creeaza un nou nod, ce va reprezenta ulterior un pachet de carti
  sau o carte dintr-un pachet*/
node_t* create_node(const void *data, int data_size)
{
	node_t *new = (node_t*)malloc(sizeof(node_t));

	if (!new) {
		fprintf(stdout, "Failed to alloc memory for the new node.\n");
		return NULL;
	}

	new->next = NULL;
	new->prev = NULL;
	new->data = malloc(data_size);

	if (!new->data) {
		fprintf(stdout, "Failed to alloc memory for the new data.\n");
		return NULL;
	}

	memcpy(new->data, data, data_size);

	return new;
}

/*Functie ce intoarce al n-lea nod dintr-o lista*/
node_t* get_nth_node(list_t* list, int n)
{
	node_t *aux = list->head;

	for(int i = 0; i < n; i++)
		aux = aux->next;

	return aux;
}

/*Functie ce sterge a n-a carte dintr-un pachet de carti si intoarce
  continutul cartii respective prin intermediul unui pointer.
  A fost folosita functia get_nth_node pentru a ajunge la cartea dorita.*/
node_t* remove_nth_card(list_t *cards, int n)
{
	node_t *garbage_card;

	if (n == 0) {
		garbage_card = cards->head;

		if(cards->size > 1) {
			cards->head = garbage_card->next;
			garbage_card->next->prev = NULL;
			garbage_card->next = NULL;
		}
	} else {
		node_t *aux_card = get_nth_node(cards, n - 1);
		garbage_card = aux_card->next;

		if(n == cards->size - 1) {
			aux_card->next = NULL;
		} else {
			aux_card->next = garbage_card->next;
			garbage_card->next->prev = aux_card;
		}
		garbage_card->next = NULL;
		garbage_card->prev = NULL;
	}

	(cards->size)--;

	return garbage_card;
}

/*Functie ce adauga o carte intr-un pachet pe pozitia n.
  Este folosita o structura auxiliara ce retine valoarea si simbolul cartii
  pentru a crea noua carte.
  Sunt tratate cazurile in care cartea este adaugata la
  inceputul/mijlocul/finalul listei.
  Este eliberata memoria alocata pentru informatiile cartii.*/

void add_card(list_t *cards, int n, int value, char symbol[MAX_SYMBOL])
{
	card_t *info = malloc(sizeof(card_t));

	if (!info) {
		fprintf(stdout, "Failed to alloc memory for the new info.\n");
		return;
	}

	info->value = value;
	strcpy(info->symbol, symbol);

	node_t *new_card = create_node(info, sizeof(card_t));

	if (cards->size == 0) {
		new_card->next = NULL;
		new_card->prev = NULL;
		cards->head = new_card;
		cards->size++;
		free(info);
		return;
	}

	if (n == 0) {
		cards->head->prev = new_card;
		new_card->next = cards->head;
		cards->head = new_card;
		new_card->prev = NULL;
	}

	if (n == cards->size) {
		node_t *aux = get_nth_node(cards, n - 1);
		aux->next = new_card;
		new_card->prev = aux;
	}

	if (n > 0 && n < cards->size) {
		node_t *aux = get_nth_node(cards, n - 1);
		new_card->next = aux->next;
		aux->next->prev = new_card;
		new_card->prev = aux;
		aux->next = new_card;
	}

	cards->size++;
	free(info);
}

/*Functie ce verifica daca indexul pachetului este corect.*/
int verify_deck_index(list_t *decks, int index)
{
	if(index > decks->size - 1 || index < 0)
		return 0;

	return 1;
}

/*Functie ce verifica daca indexul cartii este corect.*/
int verify_card_index(list_t *cards, int index)
{
	if(index > cards->size - 1 || index < 0)
		return 0;

	return 1;
}

/*Functie ce afiseaza numarul pachetelor de carti existente.*/
void deck_number(list_t *decks)
{
	int number = decks->size;
	printf("The number of decks is %d.\n", number);
}

/*Functie ce afiseaza numarul de carti existente intr-un pachet,
  al carui index este primit ca parametru.*/
void deck_len(list_t *decks, int index)
{
	if(!verify_deck_index(decks, index)) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}

	node_t *deck = get_nth_node(decks, index);
	list_t *cards = deck->data;

	int length = cards->size;
	printf("The length of deck %d is %d.\n", index, length);
}

/*Functie ce interschimba informatiile continute de 2 carti.
  Este folosita o carte auxiliara pentru care se aloca memorie.
  Memoria este eliberata la finalul interschimbarii.*/
void swap(card_t *data1, card_t *data2)
{
	card_t *aux = malloc(sizeof(card_t));
    if (!aux) {
		fprintf(stdout, "Failed to alloc memory for the auxiliary card.\n");
		return;
	}

	aux->value = data2->value;
	strcpy(aux->symbol, data2->symbol);

	data2->value = data1->value;
	strcpy(data2->symbol, data1->symbol);

	data1->value = aux->value;
	strcpy(data1->symbol, aux->symbol);

	free(aux);
}

/*Functie ce compara lexicografic doua siruri de caractere,
  ce reprezinta simbolurile a doua carti.*/
int compare_symbol(char symb1[], char symb2[])
{
	int val1, val2;
	char v[4][MAX_SYMBOL] = {"HEART", "SPADE", "DIAMOND", "CLUB"};

	for (int i = 0; i < 4 ; i++) {
		if (!strcmp(symb1, v[i]))
			val1 = i;
		if (!strcmp(symb2, v[i]))
			val2 = i;
	}

	if (val1 > val2)
		return 0;

	return 1;
}

/*Functie ce elibereaza memoria ocupata de un pachet de carti.*/
void free_list(list_t** list)
{
	int n = (*list)->size;
	node_t *garbage = (*list)->head;
	node_t *aux;

	for (int i = 0; i < n; i++) {
		aux = garbage->next;
		free(garbage->data);
		free(garbage);
		garbage = aux;
    }

	(*list)->size = 0;
	(*list)->head = 0;
	(*list)->data_size = 0;

	free(*list);
}

/*Functie folosita in urma citirii parametrilor necesari fiecarei comenzi.
  Rolul acesteia este de a verifica daca o comanda primeste mai multi
  parametri decat are nevoie. In caz afirmativ, afiseaza un mesaj specific.*/
int verify_buff()
{
	char buff[100];
	fgets(buff, 100, stdin);

	if(strlen(buff) != 1) {
		printf("Invalid command. Please try again.\n");
		return 0;
	}

	return 1;
}
