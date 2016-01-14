//Eric Bonilla
//COEN 12
//11-9-14
//Lab 4
//Radix sorting

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <curses.h>
# include <stdbool.h>
# include <math.h>

# include "deque.h"

# define r 10

int main(int argc, char *argv[])
{
    
    int max = 0;
    int input, digits, i, j, k, itemCount, temp, divisor, bucketCount;
    DEQUE *bucket[r];
    DEQUE *dp = createDeque(); //O(1)
    
    printf("Insert a number. Insert a letter to begin sort: \n"); //prompt for input
    while(scanf("%d", &input)==1)
    {
        //Input must not be negative
        assert(input>=0);
        addFirst(dp, input);
        
        //Must keep track of the max input
        if(input>max)
            max=input;
        printf("Insert a number. Insert a letter to begin sort: \n");
    }
    
    digits=ceil(log(max+1)/log(r));
    itemCount = numItems(dp); //O(1) store num items in main deque so we don't keep calling
    
    for(i = 0; i < r; i++)
    {
        //bucket[i]=malloc(sizeof(struct deque));
        bucket[i]=createDeque();
    }
    
    //Sorting
    divisor = 1;
    for(i = 0; i < digits; i++)
    {
        for(j = 0; j < itemCount; j++)
        {
            temp=removeFirst(dp);
            addLast(bucket[(temp/divisor)%10], temp);
        }
        
        //Put numbers from buckets back into the main deque
        for (j=0; j<r; j++)
        {
            bucketCount = numItems(bucket[j]);
            for(k = 0; k < bucketCount; k++)
            {
                addLast(dp, removeFirst(bucket[j]));
            }
        }
        divisor*=10;
    }
    
    //Print numbers in order
    for(j = 0; j < itemCount; j++)
    {
        printf("%d\n", getFirst(dp));
        addLast(dp, removeFirst(dp));
    }
    
    //Free memory
    destroyDeque(dp);
    for(i = 0; i < r; i++)
    {
        destroyDeque(bucket[i]);
    }
    return 0;
}