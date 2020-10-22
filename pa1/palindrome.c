#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char **argv)
{
    int bool = 0;
    char *input = argv[1];
    char input2[1000] = "";
    int i;
    int j;
    for(i = 2; i<argc; i++){
        strcat(input, argv[i]);
    }
    
    char a;
    for (j = 0; j < strlen(input); j++)
    {
        if(isalpha(*(input+j))){
                //printf("%c", *(input+j));
                a = *(input+j);     
                //printf(input2);
                //printf("\n");
                a = tolower(a);
                strncat(input2,&a,1);
                    
        }
    }

    //printf("%c",input2[0]); 
    //printf("%c",input2[strlen(input2)-1]);
    for(int i = 0; i < (strlen(input2)+1)/2; i++){
        if(input2[i] == input2[strlen(input2)-1-i]){
            bool = 1;
        } else {
            bool = 0;
            break;
        }
    }
    if(bool == 1) {
        printf("yes");
    } else {
        printf("no");
    }
    //printf(" ur mom %s and %d", input2, strlen(input2));
    return 0;
}