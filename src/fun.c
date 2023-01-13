#include "../inc/poker.h"

// char *FACE[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
// static char *SUIT[] = {"H", "D", "C", "S"};

void print_rule(void){

    printf("\n\033[37m============================================================================================================\033[0m\n");
    printf("\033[37m|\033[0m\t\t\t\t \033[34m Welcome to the Poker-21 game! \033[0m\t\t\t\t\t\033[37m   |\033[0m\n");
    printf("\033[37m|\033[0m     21點是一種經典的撲克牌遊戲，每局的目的是讓手中的牌點數加起來等於或接近21點，但不能超過21點。         \033[37m|\033[0m\n");
    printf("\033[37m|\033[0m     遊戲開始後，玩家先行動，可以選擇要牌或停牌。若玩家選擇要牌，莊家就會從牌堆中給玩家一張牌             \033[37m|\033[0m\n");
    printf("\033[37m|\033[0m     ，玩家的牌點數會隨之增加。玩家可以一直要牌直到他們的牌點數等於或超過21點，此時玩家爆牌了，失去本局。 \033[37m|\033[0m\n");
    printf("\033[37m|\033[0m     最後，玩家和莊家的牌點數會被比較，如果玩家的牌點數比莊家高，玩家贏得本局；                           \033[37m|\033[0m\n");
    printf("\033[37m|\033[0m     如果玩家的牌點數等於莊家的牌點數，則是和局；否則莊家贏。                                             \033[37m|\033[0m\n");
    printf("\033[37m============================================================================================================\033[0m\n\n");
}

void print_station(int n, int player_t, float over21, float under21){

    printf("\n=========================================================================\n");
    printf("|\t\t\t\t \033[34m Information\033[0m \t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t|\n");
    printf("| You have used %d-set Poker cards.\t\t\t\t\t|\n", n);
    printf("| There are %d players.\t\t\t\t\t\t\t|\n", player_t+1);
    printf("| Betting odds under 21 is %2.2f.\t\t\t\t\t|\n", under21);
    printf("| Betting odds over 21 is %2.2f.\t\t\t\t\t\t|\n", over21);
    printf("=========================================================================\n\n");
}

void fillDeck_n(Card *deck, char *face[], char *suit[], int n)
{
    for (int i = 0; i < 52 * n; i++)
    {
        deck[i].face = face[i % 13];
        int j = ((int)(i / 13)) % 4;
        deck[i].suit = suit[j];
    }
    return;
}

// Shuffle all cards in deck[]
void shuffle_n(Card *deck, int n)
{

    // 52*n is not random enough, so I shuffled more time.
    for (int k = 0; k < 100; k++)
    {
        for (int i = 0; i < 52 * n; i++)
        {
            int j = rand() % (52 * n);
            Card temp = deck[i];
            deck[i] = deck[j];
            deck[j] = temp;
        }
    }

    return;
}
// Deal "m" cards to the player using n-set of cards from the "begin"th card
void deal_Poker21(Card *deck, Poker21 *one, int n, int begin, int m)
{
    if (begin + m >= 52 * n)
    {
        printf("ERROR:\t deal out all of the cards.\n");
        exit(0);
    }

    int j = one->card_n;
    for (int i = 0; i < m; i++)
    {
        one->sub[i + j] = deck[begin + i];
    }
    one->card_n += m;
}

// Calculate cards' credit
int credit(Card *oneCard)
{

    int i = 1, result = 0;

    while (i <= 13 & result == 0)
    {
        if (i <= 9 & strcmp(oneCard->face, FACE[i - 1]) == 0)
            result = i;
        if (i >= 10 & strcmp(oneCard->face, FACE[i - 1]) == 0)
            result = 10;
        i += 1;
    }

    return result;
}

// Show the player's cards & total credit
void show_player(Poker21 *one, int p)
{

    // Top of the card
    printf("\n\t\t");
    for (int i = 0; i < one->card_n; i++)
    {
        printf(" =====  ");
    }

    // Number of the card
    printf("\n\t\t");
    for (int i = 0; i < one->card_n; i++)
    {
        printf("|%s    | ", one->sub[i].face);
    }

    // Discription
    printf("\nThe Player#%d :\t", p);
    one->sum = 0;
    for (int i = 0; i < one->card_n; i++)
    {
        printf("|  ");

        switch (*(one->sub[i].suit))
        {
        case 'D':
            printf("\xe2\x97\x86");
            break;
        case 'S':
            printf("\xe2\x99\xa0");
            break;
        case 'C':
            printf("\xe2\x99\xa3");
            break;
        case 'H':
            printf("\xe2\x99\xa5");
            break;
        }
        printf("  | ");
        one->sum += credit(&(one->sub[i]));
    }
    printf("==> %d", one->sum);
    printf("\n\t\t");

    // Buttom of the card
    for (int i = 0; i < one->card_n; i++)
    {
        printf("|    %s| ", one->sub[i].face);
    }
    printf("\n\t\t");
    for (int i = 0; i < one->card_n; i++)
    {
        printf(" =====  ");
    }
    printf("\n\n");
    return;
}