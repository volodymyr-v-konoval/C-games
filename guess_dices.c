#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
    int dice1, dice2;
    int total1, total2;
    time_t t;
    char ans;

    srand(time(&t));
    dice1 = (rand() % 6) + 1;
    dice2 = (rand() % 6) + 1;
    total1 = dice1 + dice2;
    printf("The first dices: %d and %d, ", dice1, dice2);
    printf("total is: %d.\n\n\n", total1);
    do {
        puts("How do you think the next total will be ");
        puts("(H)More, (L)Less or (S)Equal?\n");
        puts("Input H, L or S.");
        scanf(" %c", &ans);
        ans = toupper(ans);
    } while ((ans != 'H') && (ans != 'L') && (ans != 'S'));
    dice1 = (rand() % 6) + 1;
    dice2 = (rand() % 6) + 1;
    total2 = dice1 + dice2;
    printf("\nThe second result is: %d and %d, ", dice1, dice2);
    printf("with total %d.\n\n", total2);
    if (ans == 'L')
    {
        if (total2 < total1)
        {
            printf("Good job! You were wright!\n");
            printf("%d less then %d\n", total2, total1);
        }
        else 
        {
            printf("Sorry! %d not less then %d\n\n", total2, total1);
        }
    }
    else if (ans == 'H')
    {
        if (total2 > total1)
        {
            printf("Good job! You were right!\n");
            printf("%d greate, then %d\n", total2, total1);
        }
        else
        {
            printf("Sorry! %d not greate, then %d\n\n", total2, total1);
        }
    }
    else if (ans == 'S')
    {
        if (total2 == total1)
        {
            printf("Good job! You were right!\n");
            printf("%d equal to %d\n\n", total2, total1);
        }
        else
        {
            printf("Sorry! %d not equal to %d\n\n", total2, total1);
        }
    }
    return(0);
}
