// Card Shuffling
// Card.cpp
// Created on 2022-01-20 by Justyn Durnford
// Last modified on 2022-01-31 by Justyn Durnford
// Source file for the Card struct.

#include "Card.hpp"

#include <compare>
using std::strong_ordering;

#include <string>
using std::string;

Card::Card()
{
	suit = SUIT_CLUB;
	rank = RANK_ACE;
}

Card::Card(SUIT new_suit, RANK new_rank)
{
	suit = new_suit;
	rank = new_rank;
}

void Card::set(SUIT new_suit, RANK new_rank)
{
	suit = new_suit;
	rank = new_rank;
}

string Card::toString() const
{
	string str;

	switch (rank)
	{
		case RANK_ACE:
			str += "Ace of ";
		break;

		case RANK_2:
			str += "2 of ";
		break;

		case RANK_3:
			str += "3 of ";
		break;

		case RANK_4:
			str += "4 of ";
		break;

		case RANK_5:
			str += "5 of ";
		break;

		case RANK_6:
			str += "6 of ";
		break;

		case RANK_7:
			str += "7 of ";
		break;

		case RANK_8:
			str += "8 of ";
		break;

		case RANK_9:
			str += "9 of ";
		break;

		case RANK_10:
			str += "10 of ";
		break;

		case RANK_JACK:
			str += "Jack of ";
		break;

		case RANK_QUEEN:
			str += "Queen of ";
		break;

		case RANK_KING:
			str += "King of ";
		break;

		default: break;
	}

	switch (suit)
	{
		case SUIT_CLUB:
			str += "Clubs";
		break;

		case SUIT_DIAMOND:
			str += "Diamonds";
		break;

		case SUIT_HEART:
			str += "Hearts";
		break;

		case SUIT_SPADE:
			str += "Spades";
		break;

		default: break;
	}

	return str;
}

bool operator == (Card A, Card B)
{
	return (A.suit == B.suit && A.rank == B.rank);
}

bool operator != (Card A, Card B)
{
	return (A.suit != B.suit || A.rank != B.rank);
}

bool operator < (Card A, Card B)
{
	if (A.suit < B.suit)
		return true;
	if (A.suit > B.suit)
		return false;

	return A.rank < B.rank;
}

bool operator <= (Card A, Card B)
{
	if (A.suit < B.suit)
		return true;
	if (A.suit > B.suit)
		return false;

	return A.rank <= B.rank;
}

bool operator > (Card A, Card B)
{
	if (A.suit < B.suit)
		return false;
	if (A.suit > B.suit)
		return true;

	return A.rank > B.rank;
}

bool operator >= (Card A, Card B)
{
	if (A.suit < B.suit)
		return false;
	if (A.suit > B.suit)
		return true;

	return A.rank >= B.rank;
}

strong_ordering operator <=> (Card A, Card B)
{
	if (A.suit < B.suit)
		return strong_ordering::less;
	if (A.suit > B.suit)
		return strong_ordering::greater;

	return A.rank <=> B.rank;
}