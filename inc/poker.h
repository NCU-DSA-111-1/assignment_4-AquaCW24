#ifndef _POKER_H
#define _POKER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char *FACE[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
static char *SUIT[] = {"H", "D", "C", "S"};

struct card{
    char *face;
    char *suit;
};
typedef struct card Card;

struct poker21
{
    int card_n;     // Card number
    int sum;        // Total cards' credit
    float stake;      // player's stake
    float purse ;     // player's purse
    Card sub[6];
};
typedef struct poker21 Poker21;

void print_rule(void);
void print_station(int n, int player_t, float over21, float under21);
void fillDeck_n(Card *, char *[], char *[], int);
void shuffle_n(Card *, int);
void deal_Poker21(Card *, Poker21 *, int, int, int);
void show_player(Poker21 *, int);

#endif