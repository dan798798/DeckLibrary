// DeckLibrary.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DeckLibrary.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECKLIBRARY_EXPORTS

namespace DeckLibrary
{
	char *suit_string[] = { "S", "H", "D", "C" };
	char *rank_string[] = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" };

	class_deck deck;  // create a deck object for all the cards

	// constructor to initialize deck of card with correct values and shuffle
	class_deck::class_deck() {
		srand((unsigned int)time(NULL));  // randomize deck to current time
		int x = 0;
		for (int y = 0; y < NUM_SUITS; y++) { // loop for each suit
			for (int z = 0; z < NUM_CARDS_PER_SUIT; z++) { // loop for every card in suit
				cards[x].suit = (enum_suit)y;
				cards[x].rank = (enum_rank)z;
				if (z < NUM_NUMERIC_CARDS) {			// numeric cards
					cards[x].values[0] = z + INITIAL_CARD_VALUE;
					cards[x].num_values = 1;
				}
				else if (z + 1 == NUM_CARDS_PER_SUIT) { // ace
					cards[x].values[0] = ACE_VALUE0;
					cards[x].values[1] = ACE_VALUE1;
					cards[x].num_values = 2;
				}
				else {								// face cards
					cards[x].values[0] = FACE_VALUE;
					cards[x].num_values = 1;
				}
				x++;
			}
		}
		shuffle();
		index = -1; // reset current card
	};

	int class_deck::remaining_cards() { // 0 when cant get any new cards
		return MAX_CARDS - index - 1;
	}

	struct_card class_deck::next_card() {
		index++; // increment current card of deck, and validate value
		return current_card();
	}

	struct_card class_deck::current_card() {
		if (index >= MAX_CARDS) {
			index = MAX_CARDS - 1;
		}
		if (index < 0) {
			index = 0;
		}
		return cards[index];
	}

	// randomly draw a new card for every card in deck
	void class_deck::shuffle() {
		for (int x = 0; x < MAX_CARDS; x++) { // loop for all cards
			int rand_index = rand() % MAX_CARDS;
			struct_card temp_card = cards[x];	// swap current card with random card
			cards[x] = cards[rand_index];
			cards[rand_index] = temp_card;
		}
		index = -1;
	}

	// output to visual studio debug window
	void console(char *str) {
		strcat(str, "\n");
		wchar_t wstr[512];
		mbstowcs(wstr, str, strlen(str) + 1);//Plus null
		LPWSTR ptr = wstr;
		OutputDebugString(wstr);
	}

	// print deck to console
	void class_deck::print_deck() {
		char str[256] = "";
		for (int x = 0; x < MAX_CARDS; x++) {
			sprintf(str, "%d: value = %d ", x, cards[x].values[0]);
			strcat(str, suit_string[cards[x].suit]);
			strcat(str, " ");
			strcat(str, rank_string[cards[x].rank]);
			console(str);
		}
		sprintf(str, "index = %d ", index);
		console(str);
	}

	// simple test of deck with shuffle to console
	void test_deck() {
		class_deck deck;
		deck.print_deck();
		deck.next_card();
		deck.print_deck();
		for (int x = 1; x < MAX_CARDS + 1; x++) {
			deck.next_card();
		}
		deck.print_deck();
	}
}

void shuffle() {
	DeckLibrary::deck.shuffle();
}

int remaining_cards() {
	return DeckLibrary::deck.remaining_cards();
}

struct_card next_card() {
	return DeckLibrary::deck.next_card();
}

struct_card current_card() {
	return DeckLibrary::deck.current_card();
}


