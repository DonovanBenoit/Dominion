/*
Deck.cpp
Written By: William Power, ©2017
Deck is intended to be a collection of Card objects
The Deck really only needs to generate an array of bits
that toggle on/off the associated LED.


*/

#ifndef _DECK_h
#define _DECK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Card.h"

class Deck
{
 protected:
	 byte _expansions[3];//Each bit represents an expansion.
	 byte _cards[64]; //Represents the cards included in the deck as a stream of bits.
	 int _size; //The size of the deck.
	 byte maskFromID(int);

 public:
	Deck();
	long Expansions; //Code for the available Expansions.
	bool Contains(Card &);
	bool Contains(int);//Checks to see if a card is contained within a deck.
	void AddCard(Card); //Adds a card to the deck
	void RemoveCard(Card); //Removes a card from the deck
	void AddExpansion(int); //Allows an Expansion to be used
	void RemoveExpansion(int); //Removes an Expansion from play.
	Deck CreateDeck(int); //Generates the LED output
	void GetExpansions(byte *expansions);
	void GetCards(byte *cards);
	int GetSize();



};


#endif

