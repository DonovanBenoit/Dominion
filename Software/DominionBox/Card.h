/*
Card.cpp
Written by William Power, ©2017
This is an object for holding the ID and properties of each Dominion game Card.

*/

#ifndef _CARD_h
#define _CARD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Card 
{

private:
	int _index; //This represents the position of the LED in the box.
	int _expansion; //This is the expansion ID the Card belongs to.
	bool _potion; //Requires Potion
	bool _curse; //Uses the Curse Card.
	bool _isEvent; //is this an Event Card?
	bool _isLandmark; //is this a landmark card?

public:
	
	Card();
	Card(int, int, bool, bool);
	Card(int, int, bool, bool, bool);
	Card(int, int, bool, bool, bool, bool);
	~Card();
	bool isKingdomCard();
	bool isLandmark();
	bool isEvent();
	bool requiresCurse();
	bool requiresPotion();
	int GetIndex();
	int GetExpansionID();

	static int cardCount;
	static Card CardDeck[];
	/*
	static Card Dominion[];
	static Card Intrigue[];
	static Card Seaside[];
	static Card Alchemy[];
	static Card Prosperity[];
	static Card Cornucopia[];
	static Card Hinterlands[];
	static Card DarkAges[];
	static Card Guilds[];
	static Card Adventures[];
	static Card Empires[];
	static Card BlackMarket;
	static Card Envoy;
	static Card WalledVillage;
	static Card Governor;
	static Card Stash;
	static Card Prince;
	*/
};

#endif

