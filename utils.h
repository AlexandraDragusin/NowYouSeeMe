// Copyright (C) Dragusin Daniela-Alexandra (311CA / 2021-2022)
#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SYMBOL 8
#define MAX_STRING 20

/*Structura ce defineste tipul unei carti
  si retine valoarea si simbolul acesteia.*/
typedef struct card_t
{
	int value;
	char symbol[MAX_SYMBOL];
} card_t;

/*Structura generica ce defineste un nod (pachet de carti/carte).
  Informatia continuta de acest nod este in cazul pachetului o lista de carti,
  iar in cazul cartii, o structura de tip carte.
  Aceasta structura permite accesarea nodului anterior sau urmator.*/
typedef struct node_t
{
	void* data;
	struct node_t* next;
	struct node_t* prev;
} node_t;

/*Structura generica ce defineste fie o lista de pachete, fie una de carti.
  Contine nodul de inceput al listei, dimensiunea datelor si numarul
  elementelor existente.*/
typedef struct list_t
{
	node_t* head;
	int data_size;
	int size;
} list_t;

list_t* create_list(int data_size);
node_t* create_node(const void *data, int data_size);
node_t* get_nth_node(list_t* list, int n);
node_t* remove_nth_card(list_t *cards, int n);
void add_card(list_t *cards, int n, int value, char symbol[MAX_SYMBOL]);
int verify_deck_index(list_t *decks, int index);
int verify_card_index(list_t *cards, int index);
void deck_number(list_t *decks);
void deck_len(list_t *decks, int index);
int compare_symbol(char symb1[], char symb2[]);
void swap(card_t *data1, card_t *data2);
void free_list(list_t** list);
int verify_buff();

#endif  // UTILS_H_
