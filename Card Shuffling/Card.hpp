// Card Shuffling
// Card.hpp
// Created on 2022-01-20 by Justyn Durnford
// Last modified on 2022-01-31 by Justyn Durnford
// Header file for the Card struct.

#pragma once

#include "IntegerTypedefs.hpp"

#include <compare>
#include <string>

struct Card
{
    enum SUIT : jlib::u8
    {
        SUIT_CLUB    = 0,
        SUIT_DIAMOND = 1,
        SUIT_HEART   = 2,
        SUIT_SPADE   = 3
    };

    enum RANK : jlib::u8
    {
        RANK_ACE   = 0,
        RANK_2     = 1,
        RANK_3     = 2,
        RANK_4     = 3,
        RANK_5     = 4,
        RANK_6     = 5,
        RANK_7     = 6,
        RANK_8     = 7,
        RANK_9     = 8,
        RANK_10    = 9,
        RANK_JACK  = 10,
        RANK_QUEEN = 11,
        RANK_KING  = 12
    };

    SUIT suit;
    RANK rank;

    // 
    Card();

    //
    Card(SUIT new_suit, RANK new_rank);

    //
    Card(const Card& other) = default;

    // 
    Card(Card&& other) = default;

    //
    Card& operator = (const Card& other) = default;

    // 
    Card& operator = (Card&& other) = default;

    //
    ~Card() = default;

    //
    void set(SUIT new_suit, RANK new_rank);

    // 
    std::string toString() const;
};

// 
bool operator == (Card A, Card B);

//
bool operator != (Card A, Card B);

//
bool operator < (Card A, Card B);

//
bool operator <= (Card A, Card B);

//
bool operator > (Card A, Card B);

//
bool operator >= (Card A, Card B);

//
std::strong_ordering operator <=> (Card A, Card B);