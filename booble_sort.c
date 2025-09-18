#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int ctr, inner, outer, didSwap, temp;
    int nums[10];
    time_t t;
    
    srand(time(&t));
    for (ctr = 0; ctr < 10; ctr++)
    {
        nums[ctr] = ((rand() % 99) + 1);
    }
    puts("\nThe list before sorting: ");
    for (ctr = 0; ctr < 10; ctr++)
    {
        printf("%d\n", nums[ctr]);
    }
    for (outer = 0; outer < 9; outer++)
    {
        didSwap = 0;
        for (inner = 0; inner < 9 - outer; inner++)
        {
            if (nums[inner] > nums[inner + 1])
            {
                temp = nums[inner];
                nums[inner] = nums[inner + 1];
                nums[inner + 1 ] = temp;
                didSwap = 1;
            }
        }
        if (didSwap == 0)
        {
            break;
        }
    }
    puts("\nThe list of numbers after sort: ");
    for (ctr = 0; ctr < 10; ctr++)
    {
        printf("%d\n", nums[ctr]);
    }
    return 0;
}
