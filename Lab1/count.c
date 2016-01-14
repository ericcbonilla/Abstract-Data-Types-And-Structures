//Eric Bonilla
//COEN 12
//Project 1: count the number of words in a text file
//9-25-14

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LENGTH 30

//Initialize function count, which will return the number of words in the file
int count(char *);

int main(int argc, char * argv[1]) {
    
    int c;
    
    //Making sure that the correct number of arguments were entered
    if (argc <2) {
        printf("Wrong number of arguments\n");
        return 0;
    }
    
    c = count(argv[1]);
    printf("%d\n", c);
}

int count(char * file) {
    
    //Initializing the file
    FILE *fp;
    int count = 0;
    
    char word[MAX_WORD_LENGTH];
    
    //Opening the file
    fp = fopen(file, "r");
              
    while (fscanf(fp, "%s", word) != EOF) {
        //Increment the count every time we scan one word
        count++;
    }
              
    //Close the file
    fclose(fp);
              
    return count;
}