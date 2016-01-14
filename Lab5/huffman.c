//Eric Bonilla
//COEN 12
//11-30-14
//Lab 5
//Huffman Coding

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <ctype.h>
# include "tree.h"
# include "pack.h"

typedef struct tree TREE;

//Inserts the given node into a min heap
void insertHeap(TREE *temp[], TREE *node, int *count)
{
    int i;
    i =(*count)++;
    while(i>0  && getData(temp[(i-1)/2])>getData(node))
    {
        //(i-1)/2 designates the parent
        temp[i] = temp[(i-1)/2];
        i = (i-1)/2;
    }
    temp[i] = node;
}

//Removes and returns the minimum from the min heap
TREE *deleteMin(TREE *temp[], int *count)
{
    int i, child;
    TREE *min;
    TREE *node;
    min = temp[0];
    node = temp[--(*count)];
    temp[(*count)] = NULL;
    i = 0;

    while((i*2)+1<*count)
    {
        child = (i*2)+1; //Designates the left child
        if(((i*2)+2<(*count)) && (getData(temp[(i*2)+1]) > getData(temp[(i*2)+2])))
			child = (i*2)+2; //Designates the right child
		if(getData(node) > getData(temp[child])) {
			temp[i] = temp[child];
			i=child;
		}
		else
			break;
	}
	temp[i] = node;
	return min;
}

//Prints the bit representation of the given leaf
void printTree(TREE *temp)
{
    if(getParent(temp)!=NULL)
    {
        printTree(getParent(temp));
        
        //Left is 0, right is 1
        if(getLeft(getParent(temp))==temp)
            printf("0");
        else
            printf("1");
    }
}

int main(int argc, char *argv[])
{
    FILE *fpRead;
    int i, c, j;
    int count[257];
    TREE *leaves[257] = {NULL};
    TREE *heap[257] = {NULL};
    int heapCount = 0;
    
    //make sure read file and write file is specified
    if(argc < 3)
    {
        printf("Missing files");
        return 0;
    }
    
    //Open input file
    fpRead = fopen(argv[1], "r");
    
    //initialize charCount to zero
    for(i = 0; i < 257; i++)
    {
        count[i] = 0;
    }
    
    
    //Increment character count for each character in the file
    while((c=getc(fpRead))!=EOF)
    {
        count[c]++;
    }
    
    //Close input file
    fclose(fpRead);
    
    //Create and add leaves, set up to construct Huffman tree
    for(j = 0; j < 257; j++)
    {
        if(count[j]>0)
        {
            leaves[j] = createTree(count[j], NULL, NULL);
            insertHeap(heap, leaves[j], &heapCount);
        }
    }
    //add EOF char to the array by creating an empty tree
    leaves[256] = createTree(0, NULL, NULL);
    insertHeap(heap, leaves[256], &heapCount);
    
    //Remove 2 mins, create new tree with root as sum of both and add back in
    while(heapCount > 1)
    {
        TREE *smallMin = deleteMin(heap, &heapCount);
        TREE *bigMin = deleteMin(heap, &heapCount);
        TREE *combo = createTree(getData(smallMin)+getData(bigMin), smallMin, bigMin);
        insertHeap(heap, combo, &heapCount);
    }
    
    //Print the bit representations
    for(i = 0; i < 257; i++)
    {
        //Don't want to print all 256 so we only print the non-null ones
        if(leaves[i]!=NULL)
        {
            if(isprint(i))
                printf("'%c': %d\t", i, getData(leaves[i]));
            else
                printf("%03o: %d\t", i, getData(leaves[i]));
            printTree(leaves[i]);
            printf("\n");
        }
    }
    
    pack(argv[1] , argv[2], leaves);
}