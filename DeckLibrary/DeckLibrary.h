#pragma once  

#ifdef DECKLIBRARY_EXPORTS  
#define DECKLIBRARY_API __declspec(dllexport)   
#else  
#define DECKLIBRARY_API __declspec(dllimport)   
#endif  

extern "C" {
	enum enum_suit { spades, hearts, diamonds, clubs };
	enum enum_rank { n2, n3, n4, n5, n6, n7, n8, n9, n10, jack, queen, king, ace };

	const int MAX_VALUES = 2; // for ace with 2 values

	const int MAX_CARDS = 52;

	struct struct_card { // private card for internal deck use
		enum_suit suit;
		enum_rank rank;
		int num_values;
		int values[MAX_VALUES];
	};

	DECKLIBRARY_API void shuffle();
	DECKLIBRARY_API int remaining_cards();
	DECKLIBRARY_API struct_card next_card();
	DECKLIBRARY_API struct_card current_card();

}

namespace DeckLibrary
{
	// This class is exported from the DeckLibrary.dll  
	void test_deck();

	class class_deck {
		const int NUM_SUITS = 4;
		const int NUM_CARDS_PER_SUIT = MAX_CARDS / NUM_SUITS;
		const int INITIAL_CARD_VALUE = 2;
		const int NUM_NUMERIC_CARDS = 9;
		const int ACE_VALUE0 = 1;
		const int ACE_VALUE1 = 11;
		const int FACE_VALUE = 10;

		struct_card cards[MAX_CARDS];
		int index = -1;  // current card of deck

	public:
		class_deck();
		void print_deck();  // print deck to console for debugging

							// commands for deck
		void shuffle();
		int remaining_cards();
		struct_card next_card();
		struct_card current_card();

	};

}