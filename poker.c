#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

void printGreeting();
int getBet();
char getSuit(int suit);
const char *getRankStr(int rank);
void getFirstHand(int cardRank[], int cardSuit[]);
void getFinalHand(int cardRank[], int cardSuit[], int finalRank[], int finalSuit[], int ranksinHand[], int suitsinHand[]);
int analyzeHand(int ranksinHand[], int suitsinHand[]);
void clearHand(int ranksinHand[], int suitsinHand[]);

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
    const char *rankStr;
    char suitChar;
    char stillPlay;

    printGreeting();

    do {
        bet = getBet();
        /* seed RNG once per round */
        t = time(NULL);
        srand((unsigned)t);

        getFirstHand(cardRank, cardSuit);
        printf("Your five cards: \n");
        for (i = 0; i < 5; i++)
        {
            suitChar = getSuit(cardSuit[i]);
            rankStr = getRankStr(cardRank[i]);
            printf("Card #%d: %s%c\n", i + 1, rankStr, suitChar);
        }

        /* zero counters */
        for (i = 0; i < 4; i++)
            suitsinHand[i] = 0;
        for (i = 0; i < 13; i++)
            ranksinHand[i] = 0;

        getFinalHand(cardRank, cardSuit, finalRank, finalSuit, ranksinHand, suitsinHand);
        printf("Your last set of cards: \n");
        for (i = 0; i < 5; i++)
        {
            suitChar = getSuit(finalSuit[i]);
            rankStr = getRankStr(finalRank[i]);
            printf("Card #%d: %s%c\n", i+1, rankStr, suitChar);
        }
        winnings = analyzeHand(ranksinHand, suitsinHand);
        printf("You have won %d!\n", bet*winnings);
        bank = bank - bet + (bet * winnings);
        printf("\nThere are %d in your bank!\n", bank);
        if (bank <= 0) {
            printf("You have no credits left. Game over.\n");
            break;
        }
        printf("\nWould you like to play one more time? (Y/N) ");
        scanf(" %c", &stillPlay);
    } while (toupper((unsigned char)stillPlay) == 'Y');
    return 0;
}
/**********************************************************************/
void printGreeting()
{
    printf("****************************************************************\n");
    printf("\n\n\tWelcome to casino for dummies!\n\n");
    printf("\tHouse of video poker with change\n\n");
    printf("****************************************************************\n");
    printf("The rules are:\n");
    printf("Your start balance is 100 credits, you have to do ");
    printf("a bet from 1 to 5 credits.\n");
    printf("You are given 5 cards, you choose which to keep and which ");
    printf("to change.\n");
    printf("You have to get the best combination.\n");
    printf("Here you can see a table with combinations:\n");
    printf("\nA pair\t\t\t\t1 credit");
    printf("\nTwo pairs\t\t\t2 credits");
    printf("\nThree of a kind\t\t\t3 credits ");
    printf("\nStraight\t\t\t4 credits");
    printf("\nFlush\t\t\t\t5 credits");
    printf("\nFull house\t\t\t8 credits");
    printf("\nFour of a kind\t\t\t10 credits");
    printf("\nRoyal flush\t\t\t20 credits");
    printf("\n\nHave fun!!\n\n");
}

/* A function to give cards */
void getFirstHand(int cardRank[], int cardSuit[])
{
    int i, j;
    int cardDup;
    for (i=0; i<5; i++)
    {
        do {
            cardDup = 0;
            cardRank[i] = (rand() % 13);
            cardSuit[i] = (rand() % 4);
            for (j=0; j<i; j++)
            {
                if ((cardRank[i] == cardRank[j]) && (cardSuit[i] == cardSuit[j]))
                {
                    cardDup = 1;
                    break;
                }
            }
        } while (cardDup == 1);
    }
}
/* A function, who changes the number of the suit to the letter for the suit */
char getSuit(int suit)
{
    switch (suit)
    {
        case 0:
            return 'D';
        case 1:
            return 'S';
        case 2:
            return 'H';
        case 3:
            return 'C';
        default:
            return '?';
    }
}

/* Return rank as string (so "10" is handled) */
const char *getRankStr(int rank)
{
    switch (rank)
    {
        case 0:
            return "A";
        case 1:
            return "2";
        case 2:
            return "3";
        case 3:
            return "4";
        case 4:
            return "5";
        case 5:
            return "6";
        case 6:
            return "7";
        case 7:
            return "8";
        case 8:
            return "9";
        case 9:
            return "10";
        case 10:
            return "J";
        case 11:
            return "Q";
        case 12:
            return "K";
        default:
            return "?";
    }
}

/* A function to get a user's bet (from 1 to 5) */
int getBet()
{
    int bet;
    do {
        printf("What is your bet? (Enter an integer from ");
        printf("1 to 5 or 0 to exit from the game): ");
        if (scanf(" %d", &bet) != 1) {
            /* clear invalid input */
            int ch;
            while ((ch = getchar()) != EOF && ch != '\n') {}
            bet = -1;
        }
        if (bet >= 1 && bet <= 5)
        {
            return(bet);
        }
        else if (bet == 0)
        {
            exit(0);
        }
        else
        {
            printf("\n\nEnter an integer from 1 to 5, please, or ");
            printf("0 to exit from the game.\n");
        }
    } while ((bet < 0) || (bet > 5));
    return bet;
}

/* zero counters */
void clearHand(int ranksinHand[], int suitsinHand[])
{
    int i;
    for (i = 0; i < 13; i++) ranksinHand[i] = 0;
    for (i = 0; i < 4; i++) suitsinHand[i] = 0;
}

/* A reviev of the last given to player cards */
int analyzeHand(int ranksinHand[], int suitsinHand[])
{
    int i, rank, suit;
    int straight = FALSE;
    int flush = FALSE;
    int four = FALSE;
    int three = FALSE;
    int pairs = 0;

    /* flush? (some suit has 5 cards) */
    for (suit = 0; suit < 4; suit++) {
        if (suitsinHand[suit] == 5) {
            flush = TRUE;
            break;
        }
    }

    /* straight? check every possible start (including Ace-low) */
    for (i = 0; i < 13; i++) {
        int k, ok = 1;
        for (k = 0; k < 5; k++) {
            int idx = (i + k) % 13;
            if (ranksinHand[idx] == 0) { ok = 0; break; }
        }
        if (ok) { straight = TRUE; break; }
    }

    /* counts for pairs/three/four */
    for (rank = 0; rank < 13; rank++) 
    {
        if (ranksinHand[rank] == 4)
            four = TRUE;
        else if (ranksinHand[rank] == 3)
            three = TRUE;
        else if (ranksinHand[rank] == 2)
            pairs++;
    }

    /* Royal flush detection: A,10,J,Q,K of same suit implies straight+flush,
       but we specifically check the ranks set for royal */
    if (straight && flush) 
    {
        if (ranksinHand[0] && ranksinHand[9] && ranksinHand[10] && ranksinHand[11] && ranksinHand[12]) {
            printf("Royal flush\n\n");
            return 20;
        } else {
            printf("Straight flush\n\n");
            return 9; /* you may choose payout for straight flush; here 9 (example) */
        }
    }
    else if (four) 
    {
        printf("Four of a kind\n\n");
        return 10;
    }
    else if (three && pairs == 1) 
    {
        printf("Full house\n\n");
        return 8;
    }
    else if (flush) 
    {
        printf("Flush\n\n");
        return 5;
    }
    else if (straight) 
    {
        printf("Straight\n\n");
        return 4;
    }
    else if (three) 
    {
        printf("Three of a kind\n\n");
        return 3;
    }
    else if (pairs == 2) 
    {
        printf("Two pairs\n\n");
        return 2;
    }
    else if (pairs == 1)
    {
        printf("A pair\n\n");
        return 1;
    }
    else 
    {
        printf("High card\n\n");
        return 0;
    }
}

void getFinalHand(int cardRank[], int cardSuit[], int finalRank[], int finalSuit[], int ranksinHand[], int suitsinHand[])
{
    int i, j, cardDup;
    char suitChar;
    const char *rankStr;
    char ans;

    clearHand(ranksinHand, suitsinHand);

    for (i = 0; i < 5; i++)
    {
        suitChar = getSuit(cardSuit[i]);
        rankStr = getRankStr(cardRank[i]);
        printf("Do you want to hold the card #%d: %s%c?", i+1, rankStr, suitChar);
        printf("\nAnswer, please (Y/N): ");
        scanf(" %c", &ans);
        if (toupper((unsigned char)ans) == 'Y')
        {
            finalRank[i] = cardRank[i];
            finalSuit[i] = cardSuit[i];
            ranksinHand[finalRank[i]]++;
            suitsinHand[finalSuit[i]]++;
            continue;
        }
        else /* draw a new random non-duplicate card among final cards */ 
        {
            do {
                cardDup = 0;
                finalRank[i] = (rand() % 13);
                finalSuit[i] = (rand() % 4);
                for (j = 0; j < i; j++)
                {
                    if ((finalRank[i] == finalRank[j]) && (finalSuit[i] == finalSuit[j]))
                    {
                        cardDup = 1;
                        break;
                    }
                }
            } while (cardDup == 1);
            ranksinHand[finalRank[i]]++;
            suitsinHand[finalSuit[i]]++;
        }
    }
}

