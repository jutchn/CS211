#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char **argv)
{
    char *input = argv[1];
    int bool = 0;
    int len = strlen(input);
    int counter;
    char count[100];
    //printf("%d",inlen);
    char* output; 
    output = (char*) malloc(len+1);
    //printf("%d   ",&output[0]);
    //printf("%d   ",&output[1]);
    //printf("%d   ",&output[2]);
    
    int j = 0;
    for(int i = 0; i < len;i++){
        //printf("%c",input[i]);
        output[j++] = input[i];
        if(isdigit(input[i])){
            bool = 1; 
        }
        //printf("\n");
        counter = 1;
        while(i+1<len && input[i] == input[i+1]) {
            counter++;
            i++;
        }
        sprintf(count, "%d", counter);

        for (int k = 0; *(count+k); k++, j++) {
            output[j] = count[k];
        }
        
    }
    output[j] = '\0';
    if(bool == 1){
        printf("error");
    }
    else if(strlen(output)>len){
        printf("%s", input);
    } else {
        printf("%s", output);
    }
    free(output);
}