#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

void printGreeting();
int getBet();
char getSuit(int suit);
char getRank(int rank);
void getFirstHand(int cardRank[], int cardSuit[]);
void getFinalHand(int cardRank[], int cardSuit[], int finalRank[], int finalSuit[], int ranksinHand[], int suitsinHandp[]);
int analyzeHand(int ranksinHand[], int suitsinHand[]);

int main()
{
    int bet;
    int bank = 100;
    int i;
    int cardRank[5];
    int cardSuit[5];
    int finalRank[5];
    int finalSuit[5];
    int ranksinHand[13];
    int suitsinHand[4];
    int winnings;
    time_t t;
    char suit, rank, stillPlay;

    printGreeting();

    do {
        bet = getBet();
        srand(time(&t));
        getFirstHand(cardRank, cardSuit);
        printf("Your five cards: \n");
        for (i = 0; i < 5; i++)
        {
            suit = getSuit(cardSuit[i]);
            rank = getRank(cardRank[i]);
            printf("Card #%d: %c%c\n", i + 1, rank, suit);
        }
        for (i = 0; i < 4; i++)
        {
            suitsinHand[i] = 0;
        }
        for (i = 0; i <13; i++)
        {
            ranksinHand[i] = 0;
        }
        getFinalHand(cardRank, cardSuit, finalRank, finalSuit, ranksinHand, suitsinHand);
        printf("Your last set of cards: \n");
        for (i = 0; i < 5; i++)
        {
            suit = getSuit(finalSuit[i]);
            rank = getRank(finalRank[i]);
            printf("Card #%d: %c%c\n", i+1, rank, suit);
        }
        winnings = analyzeHand(ranksinHand, suitsinHand);
        printf("You have won %d!\n", bet*winnings);
        bank = bank - bet + (bet * winnings);
        printf("\nThere are %d in your bank!\n", bank);
        printf("\nWould you like to play one more time?");
        scanf(" %c", &stillPlay);
    } while (toupper(stillPlay) == 'Y');
    return 0;
}
/**********************************************************************/
void printGreeting()
{
    printf("****************************************************************\n");
    printf("\n\n\tWelcome to casino for dummies!\n\n");
    printf("\tHouse of video poker with change\n\n");
    printf("****************************************************************\n");
    printf("The rulse are:\n");
    printf("Your start balance is 100 credits, you have to do ");
    printf("a bit from 1 to 5 credits.\n");
    printf("Your were given 5 cards, you have to choose, which of them ");
    printf("you want to keep, and which of them you want to change.\n");
    printf("You have to get the best combination.\n");
    printf("Here you can see a table with cominations ");
    printf("\nA pare\t\t\t\t1 credit");
    printf("\nTwo pares\t\t\t2 credits");
    printf("\nThree cards of a tipe\t\t\t3 credits ");
    printf("\nStreet\t\t\t4 credits");
    printf("\nFlash\t\t\t\t5 credits");
    printf("\nFool house\t\t\t8 credits");
    printf("\nFour cards of a tipe\t\t\t10 credits");
    printf("\nFlash royal\t\t\t20 credits");
    printf("\n\nHave fun!!\n\n");
}

// A function to give cards
void getFirstHand(int cardRank[], int cardSuit[])
{
    int i, j;
    int cardDup;
    for (i=0; i<5; i++)
    {
        cardDup = 0;
        do {
            cardRank[i] = (rand() % 13);
            cardSuit[i] = (rand() % 4);
            for (j=0; j<i; j++)
            {
                if ((cardRank[i] == cardRank[j]) && (cardSuit[i] == cardSuit[j]))
                {
                    cardDup = 1;
                }
            }
        } while (cardDup == 1);
    }
}
// A function, who changes the number of the suit to the letter for the suit
char getSuit(int suit)
{
    switch (suit)
    {
        case 0:
            return('💎D');
        case 1:
            return('♠️ S');
        case 2:
            return('❤️ H');
        case 3:
            return('♣️ C');
    }
    return(' ');
}
// A function, who changes an integer of the nominal
// of the card, for a letter, representing the nominal
char getRank(int rank)
{
    switch (rank)
    {
        case 0:
            return('A');
        case 1:
            return('2');
        case 2:
            return('3');
        case 3:
            return('4');
        case 4:
            return('5');
        case 5:
            return('6');
        case 6:
            return('7');
        case 7:
            return('8');
        case 8:
            return('9');
        case 9:
            return('10');
        case 10:
            return('J');
        case 11:
            return('Q');
        case 12:
            return('K');
    }
    return(' ');
}
// A function to get a user's bet (from 1 to 5)
int getBet()
{
    int bet;
    do {
        printf("What is your bet? (Enter an integer from ");
        printf("1 to 5 or 0 to exit from the game): ");
        scanf(" %d", &bet);
        if (bet >= 1 && bet <= 5)
        {
            return(bet);
        }
        else if (bet == 0)
        {
            exit(1);
        }
        else
        {
            printf("\n\nEnter an integer from 1 to 5, please, or ");
            printf("0 to exit from the game.\n");
        }
    } while ((bet < 0) || (bet > 5));
    return bet;
}
// A reviev of the last given to player cards
int analyzeHand(int ranksinHand[], int suitsinHand[])
{
    int num_consec = 0;
    int i, rank, suit;
    int straight = FALSE;
    int flush = FALSE;
    int four = FALSE;
    int three = FALSE;
    int pairs = 0;
    for (suit = 0; suit < 4; suit++)
        if (suitsinHand[suit] == 5)
            flush = TRUE;
        rank = 0;
        while (ranksinHand[rank] == 0)
            rank++;
            while (ranksinHand[rank] == 0)
                rank++;
            for (; rank < 13 && ranksinHand[rank]; rank++)
                num_consec++;
            if (num_consec == 5) 
            {
                straight = TRUE;
            }
            for (rank = 0; rank < 13; rank++) 
            {
                if (ranksinHand[rank] == 4)
                    four = TRUE;
                if (ranksinHand[rank] == 3)
                    three = TRUE;
                if (ranksinHand[rank] == 2)
                    pairs++;
            }
            if (straight && flush) 
            {   
                printf("Flesh-royal\n\n");
                return (20);
            }
            else if (four) 
            {
                printf("Four of a type\n\n");
                return (10);
            }
            else if (three && pairs == 1) 
            {
                printf("Full house\n\n");
                return (8);
            }
            else if (flush) 
            {
                printf("Flush\n\n");
                return (5);
            }
            else if (straight) 
            {
                printf("Straight\n\n");
                return (4);
            }
            else if (three) 
            {
                printf("Three of a type\n\n");
                return (3);
            }
            else if (pairs == 2) 
            {
                printf("Two pairs\n\n");
                return (2);
            }
            else if (pairs == 1)
            {
                printf("A pair\n\n");
                return (1);
            }
            else 
            {
                printf("A highest card \n\n");
                return (0);
            }
}

void getFinalHand(int cardRank[], int cardSuit[], int finalRank[], int finalSuit[], int ranksinHand[], int suitsinHand[])
{
    int i, j, cardDup;
    char suit, rank, ans;
    for (i = 0; i < 5; i++)
    {
        suit = getSuit(cardSuit[i]);
        rank = getRank(cardRank[i]);
        printf("Do you wand to hold the card #%d: %c%c?", i+1, rank, suit);
        printf("\nAnswer, please (Y/N): ");
        scanf(" %c", &ans);
        if (toupper(ans) == 'Y')
        {
            finalRank[i] = cardRank[i];
            finalSuit[i] = cardSuit[i];
            ranksinHand[finalRank[i]]++;
            suitsinHand[finalSuit[i]]++;
            continue;
        }
        else if (toupper(ans) == 'N')
        {
            cardDup = 0;
            do {
                cardDup = 0;
                finalRank[i] = (rand() % 13);
                finalSuit[i] = (rand() % 4);
                for (j = 0; j < 5; j++)
                {
                    if ((finalRank[i] == cardRank[j]) && (finalSuit[i] == cardSuit[j]))
                    {
                        cardDup = 1;
                    }
                }
                for (j = 0; j < i; j++)
                {
                    if ((finalRank[i] == finalRank[j]) && (finalSuit[i] == finalSuit[j]))
                    {
                        cardDup = 1;
                    }
                }
            } while (cardDup == 1);
            ranksinHand[finalRank[i]]++;
            suitsinHand[finalSuit[i]]++;
        }
    }
}
