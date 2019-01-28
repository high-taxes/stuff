#include <stdio.h>
#include<stdlib.h>
//streamline, make actual functions, plug into homework assignment
int main() {

    char newline;
    char ** lines;
    int numLines = 0;
    int* lineLengths = (int*)malloc(2 * sizeof(int));
    int curLine = 0;
    lines = (char**)malloc(2 * sizeof(char*));

    FILE* fp = fopen("whoa.txt", "r");

    //function to read number of new line characters
    for (newline = getc(fp); newline != EOF; newline = getc(fp)){
        if(newline == '\n'){//case for finding a new line
            numLines++;
            lineLengths = realloc(lineLengths, numLines * sizeof(int)); //array to store length of each line
            curLine = 0;//reset length of each line for each new line
        }
        else{
            ++curLine;//keeps track of number of characters in current line
            lineLengths[numLines] = curLine+1;//sets number of characters in the tracking array, adds one for null
        }
    }
    
    //counts last line if it does not end with newline character
    if (newline != '\n'){
        numLines++;
    }

    printf("Number of lines in test.txt is %d\n\n", numLines);//just for testing
    lines = realloc(lines, numLines * sizeof(char*));//allocation for 2d array: in this case rows
   
    for(int i = 0; i < numLines; i++){//for loop to check if the tracking array has the correct number of characters for each line
    printf("The number of characters in line %d is %d\n", i+1, lineLengths[i]);
    lines[i]=realloc(lines[i], lineLengths[i]* sizeof(char));//allocates space for each individual line in the 2d array (each character)
    }
  
    //reset filepointer to the beginning
    fseek(fp, 0, SEEK_SET);

    int i = 0;

    do{//attempt at getting string from file and saving it to 2d array
    fgets(lines[i], lineLengths[i], fp);
    ++i;
    }while(!feof(fp));

    //attempt at printing the result
    for(int i = 0; i < numLines; ++i){
    printf("%s", lines[i]);
    }
 
    //free
for(int i = 0; i < numLines; ++i){
    free(lines[i]);
}
    free(lines);
    fclose(fp);
    return 0;
}
