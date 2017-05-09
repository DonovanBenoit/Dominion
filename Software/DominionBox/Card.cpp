// 
// 
// 

#include "Card.h"
#include "Arduino.h"


int Card::cardCount = 0;

Card::Card()
{
	cardCount++;
}

Card::Card(int id, int exp, bool potion, bool curse)
{
	_index = id;
	_expansion = exp;
	_potion = potion;
	_curse = curse;
	_isEvent = false;
	cardCount++;
}

Card::Card(int id, int exp, bool potion, bool curse, bool event)
{
	_index = id;
	_expansion = exp;
	_potion = potion;
	_curse = curse;
	_isEvent = event;
	_isLandmark = false;
	cardCount++;
}

Card::Card(int id, int exp, bool potion, bool curse, bool event, bool landmark)
{
	_index = id;
	_expansion = exp;
	_potion = potion;
	_curse = curse;
	_isEvent = event;
	_isLandmark = landmark;
	cardCount++;
}

bool Card::isKingdomCard()
{
	//86 = Potion, 115 = Colony, 114 = Platinum. None of these are Considered Kingdom Cards.
	if (_index == 86 || _index == 115 || _index == 114)
	{
		return false;
	}
	else
	{
		return !(_isEvent || _isLandmark);
	}
	
}

bool Card::requiresCurse()
{
	return _curse;
}

bool Card::requiresPotion()
{
	return _potion;
}

bool Card::isEvent()
{
	return _isEvent;
}

bool Card::isLandmark()
{
	return _isLandmark;
}

Card::~Card()
{
	cardCount--;
}

int Card::GetIndex()
{
	return _index;
}

int Card::GetExpansionID()
{
	return _expansion;
}

//All Possible Cards
Card Card::CardDeck[337] =
{
	Card(0,0,false,false), //Cellar
	Card(1,0,false,false), //Chapel
	Card(2,0,false,false), //Moat
	Card(3,0,false,false), //Chancellor
	Card(4,0,false,false), //Village
	Card(5,0,false,false), //WoodCutter
	Card(6,0,false,false), //Workshop
	Card(7,0,false,false), //Bureaucrat
	Card(8,0,false,false), //Feast
	Card(9,0,false,false), //Gardens
	Card(10,0,false,false), //Militia
	Card(11,0,false,false), //Moneylender
	Card(12,0,false,false), //Remodel
	Card(13,0,false,false), //Smithy
	Card(14,0,false,false), //Spy
	Card(15,0,false,false), //Thief
	Card(16,0,false,false), //Throne Room
	Card(17,0,false,false), //Council Room
	Card(18,0,false,false), //Festival
	Card(19,0,false,false), //Laboratory
	Card(20,0,false,false), //Library
	Card(21,0,false,false), //Market
	Card(22,0,false,false), //Mine
	Card(23,0,false,true), //Witch
	Card(24,0,false,false), //Adventurer
	Card(25,1,false,false), //Courtyard
	Card(26,1,false,false), //Pawn
	Card(27,1,false,false), //Secret Chamber
	Card(28,1,false,false), //Great Hall
	Card(29,1,false,false), //Masquerade
	Card(30,1,false,false), //Shanty Town
	Card(31,1,false,false), //Steward
	Card(32,1,false,false), //Swindler
	Card(33,1,false,false), //Wishing Well
	Card(34,1,false,false), //Baron
	Card(35,1,false,false), //Bridge
	Card(36,1,false,false), //Conspirator
	Card(37,1,false,false), //Coppersmith
	Card(38,1,false,false), //Ironworks
	Card(39,1,false,false), //Mining Village
	Card(40,1,false,false), //Scout
	Card(41,1,false,false), //Duke
	Card(42,1,false,false), //Minion
	Card(43,1,false,false), //Saboteur
	Card(44,1,false,true), //Torturer
	Card(45,1,false,false), //Trading Post
	Card(46,1,false,false), //Tribute
	Card(47,1,false,false), //Upgrade
	Card(48,1,false,false), //Harem
	Card(49,1,false,false), //Nobles
	Card(50,2,false,true), //Embargo
	Card(51,2,false,false), //Haven
	Card(52,2,false,false), //Lighthouse
	Card(53,2,false,false), //Native Village
	Card(54,2,false,false), //Pearl Diver
	Card(55,2,false,false), //Ambassador
	Card(56,2,false,false), //Fishing Village
	Card(57,2,false,false), //Lookout
	Card(58,2,false,false), //Smugglers
	Card(59,2,false,false), //Warehouse
	Card(60,2,false,false), //Caravan
	Card(61,2,false,false), //Cutpurse
	Card(62,2,false,false), //Island
	Card(63,2,false,false), //Navigator
	Card(64,2,false,false), //Pirate Ship
	Card(65,2,false,false), //Salvager
	Card(66,2,false,true), //Sea Hag
	Card(67,2,false,false), //Treasure Map
	Card(68,2,false,false), //Bazaar
	Card(69,2,false,false), //Explorer
	Card(70,2,false,false), //Ghost Ship
	Card(71,2,false,false), //Merchant Ship
	Card(72,2,false,false), //Outpost
	Card(73,2,false,false), //Tactician
	Card(74,2,false,false), //Treasury
	Card(75,2,false,false), //Wharf
	Card(76,3,true,false), //Transmute
	Card(77,3,true,false), //Vineyard
	Card(78,3,true,false), //Apothecary
	Card(79,3,false,false), //Herbalist
	Card(80,3,true,false), //Scrying Pool
	Card(81,3,true,false), //University
	Card(82,3,true,false), //Alchemist
	Card(83,3,true,true), //Familiar
	Card(84,3,true,false), //Philosopher's Stone
	Card(85,3,true,false), //Golem
	Card(86,3,false,false), //Potion
	Card(87,3,false,false), //Apprentice
	Card(88,3,true,false), //Possession
	Card(89,4,false,false), //Loan
	Card(90,4,false,false), //Trade Route
	Card(91,4,false,false), //Watchtower
	Card(92,4,false,false), //Bishop
	Card(93,4,false,false), //Monument
	Card(94,4,false,false), //Quarry
	Card(95,4,false,false), //Talisman
	Card(96,4,false,false), //Worker's Village
	Card(97,4,false,false), //City
	Card(98,4,false,false), //Contraband
	Card(99,4,false,false), //Counting House
	Card(100,4,false,false), //Mint
	Card(101,4,false,true), //Mountebank
	Card(102,4,false,false), //Rabble
	Card(103,4,false,false), //Royal Seal
	Card(104,4,false,false), //Vault
	Card(105,4,false,false), //Venture
	Card(106,4,false,false), //Goons
	Card(107,4,false,false), //Grand Market
	Card(108,4,false,false), //Hoard
	Card(109,4,false,false), //Bank
	Card(110,4,false,false), //Expand
	Card(111,4,false,false), //Forge
	Card(112,4,false,false), //King's Court
	Card(113,4,false,false), //Peddler
	Card(114,4,false,false), //Platinum
	Card(115,4,false,false), //Colony
	Card(116,5,false,false), //Bag of Gold
	Card(117,5,false,false), //Diadem
	Card(118,5,false,true), //Followers
	Card(119,5,false,false), //Princess
	Card(120,5,false,false), //Trusty Steed
	Card(121,5,false,false), //Hamlet
	Card(122,5,false,true), //Fortune Teller
	Card(123,5,false,false), //Menagerie
	Card(124,5,false,false), //Farming Village
	Card(125,5,false,false), //Horse Trader
	Card(126,5,false,false), //Remake
	Card(127,5,false,false), //Tournament
	Card(128,5,false,true),  //Young Witch
	Card(129,5,false,false), //Harvest
	Card(130,5,false,false), //Horn of Plenty
	Card(131,5,false,false), //Hunting Party
	Card(132,5,false,true), //Jester
	Card(133,5,false,false), //Fairgrounds
	Card(134,6,false,false), //Crossroads
	Card(135,6,false,false), //Duchess
	Card(136,6,false,false), //Fool's Gold
	Card(137,6,false,false), //Develop
	Card(138,6,false,false), //Oasis
	Card(139,6,false,false), //Oracle
	Card(140,6,false,false), //Scheme
	Card(141,6,false,false), //Tunnel
	Card(142,6,false,false), //Jack of All Trades
	Card(143,6,false,false), //Noble Brigand
	Card(144,6,false,false), //Nomand Camp
	Card(145,6,false,false), //Silk Road
	Card(146,6,false,false), //Spice Merchant
	Card(147,6,false,false), //Trader
	Card(148,6,false,false), //Cache
	Card(149,6,false,false), //Cartographer
	Card(150,6,false,false), //Embassy
	Card(151,6,false,false), //Haggler
	Card(152,6,false,false), //Highway
	Card(153,6,false,true), //Ill-Gotten Gains
	Card(154,6,false,false), //Inn
	Card(155,6,false,false), //Mandarin
	Card(156,6,false,false), //Margrave
	Card(157,6,false,false), //Stables
	Card(158,6,false,false), //Border Village
	Card(159,6,false,false), //Farmland
	Card(160,7,false,false), //Ruins - This covers Abandoned Mine,Ruined Library, Ruined Market, Ruined Village, Survivors
	Card(161,7,false,false), //Madman
	Card(162,7,false,false), //Mercenary
	Card(163,7,false,false), //Spoils
	Card(164,7,false,false), //Hovel
	Card(165,7,false,false), //Necropolis
	Card(166,7,false,false), //Overgrown Estate
	Card(167,7,false,false), //Poor House
	Card(168,7,false,false), //Beggar
	Card(169,7,false,false), //Squire
	Card(170,7,false,true), //Vagrant
	Card(171,7,false,false), //Forager
	Card(172,7,false,false), //Hermit
	Card(173,7,false,false), //Market Square
	Card(174,7,false,false), //Sage
	Card(175,7,false,false), //Storeroom
	Card(176,7,false,false), //Urchin
	Card(177,7,false,false), //Armory
	Card(178,7,false,false), //Death Cart
	Card(179,7,false,false), //Feodum
	Card(180,7,false,false), //Fortress
	Card(181,7,false,false), //Ironmonger
	Card(182,7,false,false), //Marauder
	Card(183,7,false,false), //Procession
	Card(184,7,false,false), //Rats
	Card(185,7,false,false), //Scavenger
	Card(186,7,false,false), //Knight - This covers all Knights
	Card(187,7,false,false), //Wandering Minstrel
	Card(188,7,false,false), //Band of Misfits
	Card(189,7,false,false), //Bandit Camp
	Card(190,7,false,false), //Catacombs
	Card(191,7,false,false), //Count
	Card(192,7,false,false), //Counterfeit
	Card(193,7,false,false), //Cultist
	Card(194,7,false,false), //Graverobber
	Card(195,7,false,false), //Junk Dealer
	Card(196,7,false,false), //Mystic
	Card(197,7,false,false), //Pillage
	Card(198,7,false,false), //Rebuild
	Card(199,7,false,false), //Rouge
	Card(200,7,false,false), //Altar
	Card(201,7,false,false), //Hunting Grounds
	Card(202,8,false,false), //Candlestick Maker
	Card(203,8,false,false), //Stonemason
	Card(204,8,false,false), //Doctor
	Card(205,8,false,false), //Masterpiece
	Card(206,8,false,false), //Advisor
	Card(207,8,false,false), //Herald
	Card(208,8,false,false), //Plaza
	Card(209,8,false,false), //Taxman
	Card(210,8,false,false), //Baker
	Card(211,8,false,false), //Butcher
	Card(212,8,false,false), //Journeyman
	Card(213,8,false,false), //Merchant Guild
	Card(214,8,false,true), //Soothsayer
	Card(215,9,false,false), //Coin of the Realm
	Card(216,9,false,false), //Page
	Card(217,9,false,false), //Peasant
	Card(218,9,false,false), //Ratcatcher
	Card(219,9,false,false), //Raze
	Card(220,9,false,false), //Amulet
	Card(221,9,false,false), //Caravan Guard
	Card(222,9,false,false), //Dungeon
	Card(223,9,false,false), //Gear
	Card(224,9,false,false), //Guide
	Card(225,9,false,false), //Duplicate
	Card(226,9,false,false), //Magpie
	Card(227,9,false,false), //Messenger
	Card(228,9,false,false), //Miser
	Card(229,9,false,false), //Port
	Card(230,9,false,false), //Ranger
	Card(231,9,false,false), //Transmogrify
	Card(232,9,false,false), //Artificer
	Card(233,9,false,false), //Bridge Troll
	Card(234,9,false,false), //Distant Lands
	Card(235,9,false,true), //Giant
	Card(236,9,false,false), //Haunted Woods
	Card(237,9,false,false), //Lost City
	Card(238,9,false,false), //Relic
	Card(239,9,false,false), //Royal Carriage
	Card(240,9,false,false), //Storyteller
	Card(241,9,false,true), //Swamp Hag
	Card(242,9,false,false), //Treasure Trove
	Card(243,9,false,false), //Wine Merchant
	Card(244,9,false,false), //Hireling
	Card(245,9,false,false), //Soldier
	Card(246,9,false,false), //Fugitive
	Card(247,9,false,false), //Disciple
	Card(248,9,false,false), //Teacher
	Card(249,9,false,false), //Treasure Hunter
	Card(250,9,false,false), //Warrior
	Card(251,9,false,false), //Hero
	Card(252,9,false,false), //Champion
	Card(253,9,false,false,true), //Alms **Event
	Card(254,9,false,false,true), //Borrow **Event
	Card(255,9,false,true,true), //Quest **Event
	Card(256,9,false,false,true), //Save **Event
	Card(257,9,false,false,true), //Scouting Party **Event
	Card(258,9,false,false,true),  //Travelling Fair **Event
	Card(259,9,false,false,true), //Bonfire **Event
	Card(260,9,false,false,true), //Expedition **Event
	Card(261,9,false,false,true), //Ferry **Event
	Card(262,9,false,false,true), //Plan **Event
	Card(263,9,false,false,true), //Mission **Event
	Card(264,9,false,false,true), //Pilgrimage **Event
	Card(265,9,false,false,true), //Ball **Event
	Card(266,9,false,false,true), //Raid **Event
	Card(267,9,false,false,true), //Seaway **Event
	Card(268,9,false,false,true), //Trade **Event 
	Card(269,9, false,false,true), //Lost Arts **Event
	Card(270,9,false,false,true), //Training **Event
	Card(271,9,false,false,true), //Inheritance **Event
	Card(272,9,false,false,true), //Pathfinding **Event
	Card(273,10,false,false), //City Quarter
	Card(274,10,false,false), //Engineer
	Card(275,10,false,false), //Overlord
	Card(276,10,false,false), //Royal Blacksmith
	Card(277,10,false,false), //Encampment/Plunder Split Stack
	Card(278,10,false,false), //Patrician/Emporium Split Stack
	Card(279,10,false,false), //Settlers/Bustling Village Split Stack
	Card(280,10,false,false), //Castles
	Card(281,10,false,false), //Catapult/Rocks, Split Stack
	Card(282,10,false,false), //Chariot Race
	Card(283,10,false,false), //Enchantress
	Card(284,10,false,false), //Farmers' Market
	Card(285,10,false,false), //Gladiator/Fortune Split Stack
	Card(286,10,false,false), //Sacrifice
	Card(287,10,false,false), //Temple
	Card(288,10,false,false), //Villa
	Card(289,10,false,false), //Archive
	Card(290,10,false,false), //Capital
	Card(291,10,false,false), //Charm
	Card(292,10,false,false), //Crown
	Card(293,10,false,false), //Forum
	Card(294,10,false,false), //Groundskeeper
	Card(295,10,false,false), //Legionary
	Card(296,10,false,false), //Wild Hunt
	Card(297,10,false,false,true), //Advance
	Card(298,10,false,false,true), //Annex
	Card(299,10,false,false,true), //Donate
	Card(300,10,false,false,true), //Triumph
	Card(301,10,false,false,true), //Delve
	Card(302,10,false,false,true), //Tax
	Card(303,10,false,false,true), //Banquet
	Card(304,10,false,true,true), //Ritual
	Card(305,10,false,false,true), //Salt The Earth
	Card(306,10,false,false,true), //Wedding
	Card(307,10,false,false,true), //Windfall
	Card(308,10,false,false,true), //Conquest
	Card(309,10,false,false,true), //Dominate
	Card(310,10,false,false,false,true), //Aqueduct
	Card(311,10,false,false,false,true), //Arena
	Card(312,10,false,false,false,true), //Bandit Fort
	Card(313,10,false,false,false,true), //Basilica
	Card(314,10,false,false,false,true), //Baths
	Card(315,10,false,false,false,true), //Battlefield
	Card(316,10,false,false,false,true), //Colonnade
	Card(317,10,false,true,false,true), //Defiled Shrine
	Card(318,10,false,false,false,true), //Fountain
	Card(319,10,false,false,false,true), //Keep
	Card(320,10,false,false,false,true), //Labyrinth
	Card(321,10,false,false,false,true), //Mountain Pass
	Card(322,10,false,false,false,true), //Museum
	Card(323,10,false,false,false,true), //Obelisk
	Card(324,10,false,false,false,true), //Orchard
	Card(325,10,false,false,false,true), //Palace
	Card(326,10,false,false,false,true), //Tomb
	Card(327,10,false,false,false,true), //Tower
	Card(328,10,false,false,false,true), //Triumphal Arch
	Card(329,10,false,false,false,true), //Wall
	Card(330,10,false,false,false,true), //Wolf Den
	Card(331, 11, false, false),	//Black Market
	Card(332, 12, false, false),	//Envoy
	Card(333, 13, false, false),	//WalledVillage
	Card(334, 14, false, false),	//Governor
	Card(335, 15, false, false),	//Stash
	Card(336, 16, false, false)		//Prince
};

//Below Are the Expansions split into static arrays. No longer used.
/*

//The cards:
//These massive Arrays are driving up the Minimum Memory Usage.
//There are 11 Decks (expansions) and 6 Promo Cards, 17 Total 'Expansions'
Card Dominion[25]
{
	Card(0,0,false,false), //Cellar
	Card(1,0,false,false), //Chapel
	Card(2,0,false,false), //Moat
	Card(3,0,false,false), //Chancellor
	Card(4,0,false,false), //Village
	Card(5,0,false,false), //WoodCutter
	Card(6,0,false,false), //Workshop
	Card(7,0,false,false), //Bureaucrat
	Card(8,0,false,false), //Feast
	Card(9,0,false,false), //Gardens
	Card(10,0,false,false), //Militia
	Card(11,0,false,false), //Moneylender
	Card(12,0,false,false), //Remodel
	Card(13,0,false,false), //Smithy
	Card(14,0,false,false), //Spy
	Card(15,0,false,false), //Thief
	Card(16,0,false,false), //Throne Room
	Card(17,0,false,false), //Council Room
	Card(18,0,false,false), //Festival
	Card(19,0,false,false), //Laboratory
	Card(20,0,false,false), //Library
	Card(21,0,false,false), //Market
	Card(22,0,false,false), //Mine
	Card(23,0,false,true), //Witch
	Card(24,0,false,false) //Adventurer
};

Card Intrigue[25]
{
	Card(25,1,false,false), //Courtyard
	Card(26,1,false,false), //Pawn
	Card(27,1,false,false), //Secret Chamber
	Card(28,1,false,false), //Great Hall
	Card(29,1,false,false), //Masquerade
	Card(30,1,false,false), //Shanty Town
	Card(31,1,false,false), //Steward
	Card(32,1,false,false), //Swindler
	Card(33,1,false,false), //Wishing Well
	Card(34,1,false,false), //Baron
	Card(35,1,false,false), //Bridge
	Card(36,1,false,false), //Conspirator
	Card(37,1,false,false), //Coppersmith
	Card(38,1,false,false), //Ironworks
	Card(39,1,false,false), //Mining Village
	Card(40,1,false,false), //Scout
	Card(41,1,false,false), //Duke
	Card(42,1,false,false), //Minion
	Card(43,1,false,false), //Saboteur
	Card(44,1,false,true), //Torturer
	Card(45,1,false,false), //Trading Post
	Card(46,1,false,false), //Tribute
	Card(47,1,false,false), //Upgrade
	Card(48,1,false,false), //Harem
	Card(49,1,false,false) //Nobles
};

Card Seaside[26]
{
	Card(50,2,false,true), //Embargo
	Card(51,2,false,false), //Haven
	Card(52,2,false,false), //Lighthouse
	Card(53,2,false,false), //Native Village
	Card(54,2,false,false), //Pearl Diver
	Card(55,2,false,false), //Ambassador
	Card(56,2,false,false), //Fishing Village
	Card(57,2,false,false), //Lookout
	Card(58,2,false,false), //Smugglers
	Card(59,2,false,false), //Warehouse
	Card(60,2,false,false), //Caravan
	Card(61,2,false,false), //Cutpurse
	Card(62,2,false,false), //Island
	Card(63,2,false,false), //Navigator
	Card(64,2,false,false), //Pirate Ship
	Card(65,2,false,false), //Salvager
	Card(66,2,false,true), //Sea Hag
	Card(67,2,false,false), //Treasure Map
	Card(68,2,false,false), //Bazaar
	Card(69,2,false,false), //Explorer
	Card(70,2,false,false), //Ghost Ship
	Card(71,2,false,false), //Merchant Ship
	Card(72,2,false,false), //Outpost
	Card(73,2,false,false), //Tactician
	Card(74,2,false,false), //Treasury
	Card(75,2,false,false) //Wharf
};

Card Alchemy[13]
{
	Card(76,3,true,false), //Transmute
	Card(77,3,true,false), //Vineyard
	Card(78,3,true,false), //Apothecary
	Card(79,3,false,false), //Herbalist
	Card(80,3,true,false), //Scrying Pool
	Card(81,3,true,false), //University
	Card(82,3,true,false), //Alchemist
	Card(83,3,true,true), //Familiar
	Card(84,3,true,false), //Philosopher's Stone
	Card(85,3,true,false), //Golem
	Card(86,3,false,false), //Potion
	Card(87,3,false,false), //Apprentice
	Card(88,3,true,false), //Possession
};

Card Prosperity[27]
{
	Card(89,4,false,false), //Loan
	Card(90,4,false,false), //Trade Route
	Card(91,4,false,false), //Watchtower
	Card(92,4,false,false), //Bishop
	Card(93,4,false,false), //Monument
	Card(94,4,false,false), //Quarry
	Card(95,4,false,false), //Talisman
	Card(96,4,false,false), //Worker's Village
	Card(97,4,false,false), //City
	Card(98,4,false,false), //Contraband
	Card(99,4,false,false), //Counting House
	Card(100,4,false,false), //Mint
	Card(101,4,false,true), //Mountebank
	Card(102,4,false,false), //Rabble
	Card(103,4,false,false), //Royal Seal
	Card(104,4,false,false), //Vault
	Card(105,4,false,false), //Venture
	Card(106,4,false,false), //Goons
	Card(107,4,false,false), //Grand Market
	Card(108,4,false,false), //Hoard
	Card(109,4,false,false), //Bank
	Card(110,4,false,false), //Expand
	Card(111,4,false,false), //Forge
	Card(112,4,false,false), //King's Court
	Card(113,4,false,false), //Peddler
	Card(114,4,false,false), //Platinum
	Card(115,4,false,false) //Colony
};

Card Cornucopia[18]
{
	Card(116,5,false,false), //Bag of Gold
	Card(117,5,false,false), //Diadem
	Card(118,5,false,true), //Followers
	Card(119,5,false,false), //Princess
	Card(120,5,false,false), //Trusty Steed
	Card(121,5,false,false), //Hamlet
	Card(122,5,false,true), //Fortune Teller
	Card(123,5,false,false), //Menagerie
	Card(124,5,false,false), //Farming Village
	Card(125,5,false,false), //Horse Trader
	Card(126,5,false,false), //Remake
	Card(127,5,false,false), //Tournament
	Card(128,5,false,true),  //Young Witch
	Card(129,5,false,false), //Harvest
	Card(130,5,false,false), //Horn of Plenty
	Card(131,5,false,false), //Hunting Party
	Card(132,5,false,true), //Jester
	Card(133,5,false,false) //Fairgrounds

};

Card Hinterlands[26]
{
	Card(134,6,false,false), //Crossroads
	Card(135,6,false,false), //Duchess
	Card(136,6,false,false), //Fool's Gold
	Card(137,6,false,false), //Develop
	Card(138,6,false,false), //Oasis
	Card(139,6,false,false), //Oracle
	Card(140,6,false,false), //Scheme
	Card(141,6,false,false), //Tunnel
	Card(142,6,false,false), //Jack of All Trades
	Card(143,6,false,false), //Noble Brigand
	Card(144,6,false,false), //Nomand Camp
	Card(145,6,false,false), //Silk Road
	Card(146,6,false,false), //Spice Merchant
	Card(147,6,false,false), //Trader
	Card(148,6,false,false), //Cache
	Card(149,6,false,false), //Cartographer
	Card(150,6,false,false), //Embassy
	Card(151,6,false,false), //Haggler
	Card(152,6,false,false), //Highway
	Card(153,6,false,true), //Ill-Gotten Gains
	Card(154,6,false,false), //Inn
	Card(155,6,false,false), //Mandarin
	Card(156,6,false,false), //Margrave
	Card(157,6,false,false), //Stables
	Card(158,6,false,false), //Border Village
	Card(159,6,false,false) //Farmland
};

Card DarkAges[42]
{
	Card(160,7,false,false), //Ruins - This covers Abandoned Mine,Ruined Library, Ruined Market, Ruined Village, Survivors
	Card(161,7,false,false), //Madman
	Card(162,7,false,false), //Mercenary
	Card(163,7,false,false), //Spoils
	Card(164,7,false,false), //Hovel
	Card(165,7,false,false), //Necropolis
	Card(166,7,false,false), //Overgrown Estate
	Card(167,7,false,false), //Poor House
	Card(168,7,false,false), //Beggar
	Card(169,7,false,false), //Squire
	Card(170,7,false,true), //Vagrant
	Card(171,7,false,false), //Forager
	Card(172,7,false,false), //Hermit
	Card(173,7,false,false), //Market Square
	Card(174,7,false,false), //Sage
	Card(175,7,false,false), //Storeroom
	Card(176,7,false,false), //Urchin
	Card(177,7,false,false), //Armory
	Card(178,7,false,false), //Death Cart
	Card(179,7,false,false), //Feodum
	Card(180,7,false,false), //Fortress
	Card(181,7,false,false), //Ironmonger
	Card(182,7,false,false), //Marauder
	Card(183,7,false,false), //Procession
	Card(184,7,false,false), //Rats
	Card(185,7,false,false), //Scavenger
	Card(186,7,false,false), //Knight - This covers all Knights
	Card(187,7,false,false), //Wandering Minstrel
	Card(188,7,false,false), //Band of Misfits
	Card(189,7,false,false), //Bandit Camp
	Card(190,7,false,false), //Catacombs
	Card(191,7,false,false), //Count
	Card(192,7,false,false), //Counterfeit
	Card(193,7,false,false), //Cultist
	Card(194,7,false,false), //Graverobber
	Card(195,7,false,false), //Junk Dealer
	Card(196,7,false,false), //Mystic
	Card(197,7,false,false), //Pillage
	Card(198,7,false,false), //Rebuild
	Card(199,7,false,false), //Rouge
	Card(200,7,false,false), //Altar
	Card(201,7,false,false) //Hunting Grounds
};

Card Guilds[13]
{
	Card(202,8,false,false), //Candlestick Maker
	Card(203,8,false,false), //Stonemason
	Card(204,8,false,false), //Doctor
	Card(205,8,false,false), //Masterpiece
	Card(206,8,false,false), //Advisor
	Card(207,8,false,false), //Herald
	Card(208,8,false,false), //Plaza
	Card(209,8,false,false), //Taxman
	Card(210,8,false,false), //Baker
	Card(211,8,false,false), //Butcher
	Card(212,8,false,false), //Journeyman
	Card(213,8,false,false), //Merchant Guild
	Card(214,8,false,true) //Soothsayer
};

Card Adventures[58]
{
	Card(215,9,false,false), //Coin of the Realm
	Card(216,9,false,false), //Page
	Card(217,9,false,false), //Peasant
	Card(218,9,false,false), //Ratcatcher
	Card(219,9,false,false), //Raze
	Card(220,9,false,false), //Amulet
	Card(221,9,false,false), //Caravan Guard
	Card(222,9,false,false), //Dungeon
	Card(223,9,false,false), //Gear
	Card(224,9,false,false), //Guide
	Card(225,9,false,false), //Duplicate
	Card(226,9,false,false), //Magpie
	Card(227,9,false,false), //Messenger
	Card(228,9,false,false), //Miser
	Card(229,9,false,false), //Port
	Card(230,9,false,false), //Ranger
	Card(231,9,false,false), //Transmogrify
	Card(232,9,false,false), //Artificer
	Card(233,9,false,false), //Bridge Troll
	Card(234,9,false,false), //Distant Lands
	Card(235,9,false,true), //Giant
	Card(236,9,false,false), //Haunted Woods
	Card(237,9,false,false), //Lost City
	Card(238,9,false,false), //Relic
	Card(239,9,false,false), //Royal Carriage
	Card(240,9,false,false), //Storyteller
	Card(241,9,false,true), //Swamp Hag
	Card(242,9,false,false), //Treasure Trove
	Card(243,9,false,false), //Wine Merchant
	Card(244,9,false,false), //Hireling
	Card(245,9,false,false), //Soldier
	Card(246,9,false,false), //Fugitive
	Card(247,9,false,false), //Disciple
	Card(248,9,false,false), //Teacher
	Card(249,9,false,false), //Treasure Hunter
	Card(250,9,false,false), //Warrior
	Card(251,9,false,false), //Hero
	Card(252,9,false,false), //Champion
	Card(253,9,false,false,true), //Alms **Event
	Card(254,9,false,false,true), //Borrow **Event
	Card(255,9,false,true,true), //Quest **Event
	Card(256,9,false,false,true), //Save **Event
	Card(257,9,false,false,true), //Scouting Party **Event
	Card(258,9,false,false,true),  //Travelling Fair **Event
	Card(259,9,false,false,true), //Bonfire **Event
	Card(260,9,false,false,true), //Expedition **Event
	Card(261,9,false,false,true), //Ferry **Event
	Card(262,9,false,false,true), //Plan **Event
	Card(263,9,false,false,true), //Mission **Event
	Card(264,9,false,false,true), //Pilgrimage **Event
	Card(265,9,false,false,true), //Ball **Event
	Card(266,9,false,false,true), //Raid **Event
	Card(267,9,false,false,true), //Seaway **Event
	Card(268,9,false,false,true), //Trade **Event 
	Card(269,9, false,false,true), //Lost Arts **Event
	Card(270,9,false,false,true), //Training **Event
	Card(271,9,false,false,true), //Inheritance **Event
	Card(272,9,false,false,true) //Pathfinding **Event
};

Card Empires[58]
{
	Card(273,10,false,false), //City Quarter
	Card(274,10,false,false), //Engineer
	Card(275,10,false,false), //Overlord
	Card(276,10,false,false), //Royal Blacksmith
	Card(277,10,false,false), //Encampment/Plunder Split Stack
	Card(278,10,false,false), //Patrician/Emporium Split Stack
	Card(279,10,false,false), //Settlers/Bustling Village Split Stack
	Card(280,10,false,false), //Castles
	Card(281,10,false,false), //Catapult/Rocks, Split Stack
	Card(282,10,false,false), //Chariot Race
	Card(283,10,false,false), //Enchantress
	Card(284,10,false,false), //Farmers' Market
	Card(285,10,false,false), //Gladiator/Fortune Split Stack
	Card(286,10,false,false), //Sacrifice
	Card(287,10,false,false), //Temple
	Card(288,10,false,false), //Villa
	Card(289,10,false,false), //Archive
	Card(290,10,false,false), //Capital
	Card(291,10,false,false), //Charm
	Card(292,10,false,false), //Crown
	Card(293,10,false,false), //Forum
	Card(294,10,false,false), //Groundskeeper
	Card(295,10,false,false), //Legionary
	Card(296,10,false,false), //Wild Hunt
	Card(297,10,false,false,true), //Advance
	Card(298,10,false,false,true), //Annex
	Card(299,10,false,false,true), //Donate
	Card(300,10,false,false,true), //Triumph
	Card(301,10,false,false,true), //Delve
	Card(302,10,false,false,true), //Tax
	Card(303,10,false,false,true), //Banquet
	Card(304,10,false,true,true), //Ritual
	Card(305,10,false,false,true), //Salt The Earth
	Card(306,10,false,false,true), //Wedding
	Card(307,10,false,false,true), //Windfall
	Card(308,10,false,false,true), //Conquest
	Card(309,10,false,false,true), //Dominate
	Card(310,10,false,false,false,true), //Aqueduct
	Card(311,10,false,false,false,true), //Arena
	Card(312,10,false,false,false,true), //Bandit Fort
	Card(313,10,false,false,false,true), //Basilica
	Card(314,10,false,false,false,true), //Baths
	Card(315,10,false,false,false,true), //Battlefield
	Card(316,10,false,false,false,true), //Colonnade
	Card(317,10,false,true,false,true), //Defiled Shrine
	Card(318,10,false,false,false,true), //Fountain
	Card(319,10,false,false,false,true), //Keep
	Card(320,10,false,false,false,true), //Labyrinth
	Card(321,10,false,false,false,true), //Mountain Pass
	Card(322,10,false,false,false,true), //Museum
	Card(323,10,false,false,false,true), //Obelisk
	Card(324,10,false,false,false,true), //Orchard
	Card(325,10,false,false,false,true), //Palace
	Card(326,10,false,false,false,true), //Tomb
	Card(327,10,false,false,false,true), //Tower
	Card(328,10,false,false,false,true), //Triumphal Arch
	Card(329,10,false,false,false,true), //Wall
	Card(330,10,false,false,false,true) //Wolf Den
};

//Promo Cards
Card BlackMarket = Card(331, 11, false, false);
Card Envoy = Card(332, 12, false, false);
Card WalledVillage = Card(333, 12, false, false);
Card Governor = Card(334, 13, false, false);
Card Stash = Card(335, 14, false, false);
Card Prince = Card(336, 15, false, false);

*/



