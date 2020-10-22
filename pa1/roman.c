#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
    int input, hcounter, tcounter, ocounter, digit;
    char output[40];
    input = atoi(argv[1]);
    //printf("\nThe value of a : %d", input);
    while(input>999){
        input = input-1000;
        printf("M");
    }
    
    if(input>99){
        hcounter = input / 100;
        //printf("\n the value of hcounter : %d  ", hcounter);
        if(hcounter == 10){
            printf("CM");
        } else if(hcounter == 4) {
            printf("CD");
        } else {
            if(hcounter>4){
                printf("D");
                hcounter = hcounter-5;
            }
            for(int i = 0; i<hcounter; i++){
                printf("C");
            }
        }
        while(input>99){
            input = input-100;
        }
    }

    if(input>9){
        tcounter = input / 10;
        if(tcounter == 9){
            printf("XC");
        } else if(tcounter == 4) {
            printf("XL");
        } else {
            if(tcounter>4){
                printf("L");
                tcounter = tcounter-5;
            }
            for(int i = 0; i<tcounter; i++){
                printf("X");
            }
        }
        while(input>9){
            input = input-10;
        }
    }

    if(input>0) {
        ocounter = input;
        if(ocounter == 9){
            printf("IX");
        } else if(ocounter == 4) {
            printf("IV");
        } else {
            if(ocounter>4){
                printf("V");
                ocounter = ocounter-5;
            }
            for(int i = 0; i<ocounter; i++){
                printf("I");
            }
        }
    }
}