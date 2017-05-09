/* DominionBox
©2017 William J. Power

Description:
This project is the logic controller for a custom Card Box for the board game
Dominion by RioGrand Games

It builds a game deck based on the following user inputs:
- Number of players (2 through 6)
- Available Expansions
- Available Promo Cards

The number of players, and the available expansions are set via hardware switches
included in the game box.

*/



#include "Deck.h"
#include "Card.h"
#include "LedControl.h"

//Pin Setup - This is currently configured for an Arduino UNO:

//Expansion Selection DIP Switches:
int PIN_ExpansionSerialIn = 2; //Input from Expansion Selection DIP switches via Shift Register.
int PIN_ExpansionLatch = 3; //Expansion Shift Register Latch Pin
int PIN_ExpansionClock = 4; //Expansion Shift Register Clock Pin
byte Expansion1; //Three bytes of data are required to hold the settings for 
byte Expansion2; //All 11 Decks, plus the 6 promo cards
byte Expansion3;

//Player Selection POT
int PIN_PlayerSelection = PIN_A0; //Input from The Player Selection POT. This is an Analog input

//New Game button:
int PIN_NewGameButton = 6;

//LEDs:
int PIN_LEDSerialOut = 7; //The Serial Out data Pin, Goes to MAX7219 LED Drivers.
int PIN_LEDLatch = 8; //Like a shift register, this is the Latch Pin for the MAX7219's
int PIN_LEDClock = 9; //Clock Pin for the MAX7219's
int PIN_LEDCs = 10; //The CS pin for the MAX7219 (connected to the first only).
LedControl ledControl = LedControl(PIN_LEDSerialOut, PIN_LEDClock, PIN_LEDCs, 6); //The Controller for the LED Array.

//Variables for game Logic:
bool Expansions[17]; //Controls which expansions are to be included or not.
bool usingCurse = false;
bool usingColony = false;
bool usingPotion = false;
bool usingPlat = false;
int CARD_INDEX_START = 0;
int CARD_INDEX_END = 336;
int MAX_EVENTS = 2;
int MAX_LANDMARKS = 2;
int MAX_PLAYERCOUNT = 6;
int MIN_PLAYERCOUNT = 2;
int playerCount = 2;
Deck gameDeck = Deck();
byte cardArray[64] = { 0 }; // This will be the array of LED ID's to turn on.


//Variables for required for Hardware:
int buttonDebounceDelay = 50;
int lastDebounce = 0;
int newGameButtonState;
int lastNewGameButtonState = LOW;
int LED_DRIVERS = 6; //This is a reference to the number of LED Drivers connected.


void setup() {
	//Set the PinModes:
	pinMode(PIN_ExpansionSerialIn, INPUT);
	pinMode(PIN_ExpansionLatch, OUTPUT);
	pinMode(PIN_ExpansionClock, OUTPUT);
	pinMode(PIN_PlayerSelection, INPUT);
	pinMode(PIN_NewGameButton, INPUT);
	pinMode(PIN_LEDSerialOut, OUTPUT);
	pinMode(PIN_LEDLatch, OUTPUT);
	pinMode(PIN_LEDClock, OUTPUT);

	//Clear the expansions array.
	for (int i = 0; i < sizeof(Expansions); i++)
	{
		Expansions[i] = false;
	}


}

void loop() {
	//All loop() has to do is monitor the 'New Game' button and re-roll the deck when it's pushed:
	int buttonRead = digitalRead(PIN_NewGameButton);

	if (buttonRead != lastNewGameButtonState)
	{
		lastDebounce = millis();
	}

	if (millis() - lastDebounce > buttonDebounceDelay)
	{
		if (buttonRead != newGameButtonState)
		{
			newGameButtonState = buttonRead;
			NewGame();
		}
	}

}

void NewGame()
{
	//Reset the expansion array:
	resetExpansion();
	//Clear the Current LED Array:
	clearLights();
	//Re-Populate the Expansions based on DIP switches:
	setExpansions();
	//Check # of Players:
	setPlayers();
	//Build The Deck:
	buildDeck();
	//Light The Lights:
	lightBoard();

}

/*
clearLights turns off all of the LED's on the card selection grid.
*/
void clearLights()
{
	//This will need to send an 'OFF' command to every LED
	for (int i = 0; i < LED_DRIVERS; i++)
	{
		ledControl.clearDisplay(i); //not sure if the address is 0 indexed or not!
	}

}

void buildDeck()
{
	bool deckComplete = false;
	int kingdomCards = 0;
	int landMarkCards = 0;
	int eventCards = 0;
	int prosperityCards = 0;
	//This is the deck building logic.
	byte cardArray[64] = { 0 }; // This will be the array of LED ID's to turn on.
	for (int i = 0; i < sizeof(Expansions); i++)
	{
		if (Expansions[i])
		{
			gameDeck.AddExpansion(i); //Add the required Expansions to the deck.
		}
	}
	while (!deckComplete)
	{
		//Roll a random number:
		int roll = (int)random(CARD_INDEX_START, CARD_INDEX_END); //This will be the attempted card ID.
		//Check the roll against known Prosperity / Alchemy Cards:
		if (roll == 86 || roll == 115 || roll == 114) continue; //86 = Potion, 115 = Colony, and 114 = Platinum. These cards are added later if needed.

		//Check if ID is already in the game deck:
		if(!gameDeck.Contains(roll))
		{
			Card c = Card::CardDeck[roll];
			//Validate Card Selection:
			if (c.GetExpansionID() < sizeof(Expansions) - 1)
			{
				if (!Expansions[c.GetExpansionID()]) continue; //Make sure the expansion is in use, if not jump out of loop.
			} 
			if (c.isEvent() && eventCards >= MAX_EVENTS) continue; //If the card is an Event and we've already included the maximum events, skip.
			if (c.isLandmark() && landMarkCards >= MAX_LANDMARKS) continue; //If the card is a Landmark and we've exceed the landmark limit, skip.
			
			//Card is a valid pick, check for special conditions:
			if (c.requiresCurse()) usingCurse = true; //Put Curses in the game.
			if (c.requiresPotion()) usingPotion = true; //Put Potions in the game.
			
			gameDeck.AddCard(c); //Add the card to the deck.
			if (c.isKingdomCard())
			{
				kingdomCards++; //Not all cards are considered Kingdom Cards.
				if (c.GetExpansionID() == 4)
				{
					prosperityCards++; //Need to track how many prosperity cards are being used.
				}
			}
		}
		if (kingdomCards >= 10) deckComplete = true;
	}
	//Last thing to do is to check for Expansion specific modifiers: 
	//i.e. are Platinum & Colony included:
	if (Expansions[4]) //Prosperity is included:
	{
		int tempDeck[10] = { 0 };
		int prosperityCount = prosperityCards;
		for (int i = 0; i < 10; i++)
		{
			//This loop builds a randomizer deck weighted by the number of prosperity cards in play.
			//The greater the number of prosperity cards, the more likely Colony & Platinum will be included.
			//This is how the instructions direct Colony / Platinum should be included.
			if (prosperityCount > 0)
			{
				tempDeck[i] = 1; //Prosperity Cards will be represented by 1's.
				prosperityCount--; //Decrement the prosperity count.
			}
			else
			{
				tempDeck[i] = 0; //All other cards are represented by 0's
			}
		}
		//Roll for Platinum:
		int shuffle = (int)random(0, 9); //This will grab a random index from our tempDeck
		if (shuffle < sizeof(tempDeck))
		{
			if (tempDeck[shuffle] == 1) //We drew a prosperity card thus Platinum is included.
			{
				gameDeck.AddCard(Card::CardDeck[114]); 
			}
		}
		//Roll again for Colony:
		shuffle = (int)random(0, 9);
		if (shuffle < sizeof(tempDeck))
		{
			if (tempDeck[shuffle] == 1) //We drew another prosperity card, so Colony is included.
			{
				gameDeck.AddCard(Card::CardDeck[115]);
			}
		}
	}
	//The game deck is finished:
	gameDeck.GetCards(cardArray); //Copies the decks' Card Array into the local version.

}

/*
resetExpansion just clears the Expansion[] array back to
all 'false' status. Used to reset to startup.
*/
void resetExpansion()
{
	for (int i = 0; i < sizeof(Expansions); i++)
	{
		Expansions[i] = false;
	}
}

/*
setExpansions checks the DIP switch configuration
and sets the true/false flags on the Expanison[] array.
*/
void setExpansions()
{
	byte mask = B10000000; //the bitmask used to compare against the shift register data.
	byte data[3] = { B0,B0,B0 }; //We need 3 bytes of data the 17 Expansion states.
	int expIndex = 0;

	//Get the Expansions being used:
	digitalWrite(PIN_ExpansionLatch, 1); //Pulse the latch pin.
	delayMicroseconds(20);
	digitalWrite(PIN_ExpansionLatch, 0);

	//Read in the 17 DIP switches via the 75HC165 Shift Register:
	data[0] = shiftIn(PIN_ExpansionSerialIn, PIN_ExpansionClock, LSBFIRST); //This will be Dominion to DarkAges
	data[1] = shiftIn(PIN_ExpansionSerialIn, PIN_ExpansionClock, LSBFIRST); //This will be Guilds to Stash
	data[2] = shiftIn(PIN_ExpansionSerialIn, PIN_ExpansionClock, LSBFIRST); //This will only be Prince

	//Now we'll set the state of the expansions to use using bitwise math.
	for (int i = 0; i < sizeof(data); i++)
	{
		for (unsigned j = 0; j < 8; j++)
		{
			if (expIndex < sizeof(Expansions)) { //make sure our index hasn't outgrown the expansion array
				mask >> j; //mask starts at B10000000, the >> operator shifts it j places to the right.
				if (data[i] & mask) //the single & is a bitwise comparison.
				{
					Expansions[expIndex] = true; //if both the mask and the bit are 1, return true, this expansion is included.
				}
				else {
					Expansions[expIndex] = false; //otherwise this expansion is not included.
				}
				expIndex++;
			}
			mask = B10000000; //Reset the mask for the next pass.
		}
	}

	expIndex = 0;
}
/*
setPlayers checks the input from the player select knob, and sets the player Count.
*/
void setPlayers()
{
	//The player toggle is a potentiometer on Analog Pin 0.
	//Minimum number of players = 2, Maximum players = 6.
	int playerInput = analogRead(PIN_PlayerSelection); //Read in the current value.
	int analogDivisons = 0;
	delayMicroseconds(100); //Give it time to read the value;
	if (MAX_PLAYERCOUNT - MIN_PLAYERCOUNT + 1 > 0) { //The if statement protects agains Div by 0.
		analogDivisons = 1023 / (MAX_PLAYERCOUNT - MIN_PLAYERCOUNT + 1);
	}
	else
	{
		analogDivisons = 1024; //Default to 2 players.
	}
	//playerInput will be between 0 - 1023; 1023 = 2 players, 0 = 6 players.
	//1024 / 5 positions ~ 208 per position.
	playerCount = (playerInput / analogDivisons) + MIN_PLAYERCOUNT; //Integer division will drop the remainder.

	//And just make sure the playerCount is within range:
	if (playerCount > MAX_PLAYERCOUNT)
	{
		playerCount = MAX_PLAYERCOUNT;
	}

	if (playerCount < MIN_PLAYERCOUNT)
	{
		playerCount = MIN_PLAYERCOUNT;
	}

}

/*
This will be the function that lights up the card selections based on their ID.
*/
void lightBoard()
{
	byte mask = B00000001;
	int controllerID = 0;
	for (int i = 0; i < sizeof(cardArray); i++)
	{
		//i is the Byte of Data we're in from the CardArray
		for (int j = 0; j < 8; j++)
		{
			int index = (i * 8) + j; //This is the bit position within CardArray. Which should be 0 to 511
			//j is the bit index within the byte.
			if (cardArray[index] & (mask >> j))
			{
				int controllerID = getControllerID(index);
				ledControl.setLed(controllerID, i / 8, j, true);
			}
		}		
	}

}

//Returns the LED Driver Controller Index based on Card Index.
int getControllerID(int index)
{
	//Each MAX7219 drives 64 LED's in an 8x8 array. We have 6 of them.
	//Index will be 0 to 511
	//So the Controller ID = index / 64
	return index / 64;

	//Say index = 212 -> 212 / 64 = 3 -> Controller 3

}




