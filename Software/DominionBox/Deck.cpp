/*
Deck.cpp
Written By: William Power, ©2017
Deck is intended to be a collection of Card objects
The Deck really only needs to generate an array of bits
that toggle on/off the associated LED.


*/
#include "Deck.h"
#include "Card.h"

byte _expansions[3];
byte _cards[64] = {0}; //_cards is a 64-Byte array (512bits), indicating which LED ID's should be on/off. This is stored as a Byte array to avoid having to resize the array.
int _size = 0;

//Returns the byte array of current expansions
//*expansions is a pointer to the result array.
void Deck::GetExpansions(byte *expansions)
{
	if (sizeof(_expansions) > sizeof(expansions)) //Make sure we don't overflow our index.
	{
		//if we currently have more expansions in _expansions than the result array can handle, 
		//just fill up the result array with the first i entries of _expansions
		for (int i = 0; i < sizeof(expansions); i++)
		{
			expansions[i] = _expansions[i];
		}
	}
	else {
		//Otherwise, just pass the full array back.
		expansions = _expansions; 
	}
}

//Returns the byte array of cards currently in play
//*cards is a pointer to the result array.
void Deck::GetCards(byte *cards)
{
	if (sizeof(_cards) > sizeof(cards)) //Make sure we don't overflow our index.
	{
		for (int i = 0; i < sizeof(cards); i++)
		{
			cards[i] = _cards[i];
		}
	}
	else {
		cards = _cards;
	}
}

int Deck::GetSize()
{
	return _size;
}


Deck::Deck()
{

	//Right now this is building the full size deck right out of the gate.
	//It should really pick which expansions to include based on the setup.
	for (int i = 0; i < sizeof(_expansions); i++)
	{
		_expansions[i] = 0;
	}
	for (int i = 0; i < sizeof(_cards); i++)
	{
		_cards[i] = 0;
	}
	//By Default the Deck should contain all Base game Cards and the Cards from Dominion
	//So the first bit of _expansions must be 1.
	AddExpansion(0);
	
}

bool Deck::Contains(Card &c)
{
	int cardIndex = c.GetIndex();
	return Contains(cardIndex);
}

bool Deck::Contains(int id)
{
	int cardIndex = id;
	int cardArrayIndex = cardIndex / 8; //0-64, represents the Byte id from _cards[]
	//All I have to do is go to the bit at cardID and compare it.
	byte mask = maskFromID(cardIndex);
	return (_cards[cardArrayIndex] & mask);
}

void Deck::AddCard(Card c)
{
	byte mask = maskFromID(c.GetIndex());
	int cardArrayIndex = c.GetIndex() / 8;
	_cards[cardArrayIndex] = _cards[cardArrayIndex] | mask;
}

void Deck::RemoveCard(Card c)
{
	byte mask = maskFromID(c.GetIndex());
	int cardArrayIndex = c.GetIndex() / 8;
	_cards[cardArrayIndex] = _cards[cardArrayIndex] ^ mask;
}


void Deck::AddExpansion(int id)
{
	//the id represents the bit index for the expansion
	//Dominion = 0, Intrigue = 1, Alchemy = 2, etc.
	int expansionIndex = id / 8; //Determines which byte bank to access.
	byte mask = maskFromID(id);
	if (expansionIndex > sizeof(_expansions))
	{
		//This avoids accidental index out of range errors.
		expansionIndex = sizeof(_expansions) - 1;
	}
	_expansions[expansionIndex] = _expansions[expansionIndex] | mask; //Bitwise OR will set the appropriate value.
}

byte Deck::maskFromID(int id)
{
	unsigned bitIndex = id % 8;
	byte mask = B10000000 >> bitIndex;
	return mask;
}


void Deck::RemoveExpansion(int id)
{

}

Deck Deck::CreateDeck(int size)
{

}



