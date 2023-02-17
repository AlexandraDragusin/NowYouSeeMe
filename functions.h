// Copyright (C) Dragusin Daniela-Alexandra (311CA / 2021-2022)
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "utils.h"
#include "del.h"

void shuffle_deck(list_t *decks, int index);
void reverse_deck(list_t *decks, int index);
void merge_decks(list_t *decks, int index1, int index2);
void sort_deck(list_t *decks, int index);
void split_deck(list_t *decks, int index_deck, int index_split);
void exit_program(list_t **decks);

#endif  // FUNCTIONS_H_
