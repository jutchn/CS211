#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

void print_matrix(int *matrix, int size) {
	for(int i = 0; i<size; i++) {
		for(int j = 0; j<size; j++) {
			printf("%d", matrix[(size * i) + j]);
			if(j < size -1) {
                printf(" ");	
            }
		}
	printf("\n");
    }
}

int *matrix_zero(int size) {
	int *zero = malloc((size * size) * sizeof(int));
	for(int i = 0; i< size; i++) {
        for (int j = 0; j < size; j++) { 
		    if((size*i) == j){
            zero[(size*i)+j] = 1;
            } else {
            zero[(size*i)+j] = 0;
            }
        }
    }  
	return zero;
}

int *matrix_multiply(int *matrix, int *matrix2, int size) {
	int *multiply_result = malloc((size * size) * sizeof(int));

    int i, j, k; 
    for (i = 0; i < size; i++) 
    { 
        for (j = 0; j < size; j++) 
        { 
            multiply_result[(size * i) + j] = 0; 
            for (k = 0; k < size; k++) 
                multiply_result[(size * i) + j] += matrix[(size * i) + k]*matrix2[(size * k) + j]; 
        } 
    }
    //print_matrix(multiply_result, size);
    //printf("\n%d\n\n", *(multiply_result+4));
    
    return multiply_result; 


	//for(int i = 0; i< size * size; i++) {
	//	add_result[i] = matrix[i] * times;
//}
//	return add_result;
}

int main(int argc, char **argv) {
    char *filename = argv[1];
    int *mult_result;
    //printf("%s\n",filename);
    FILE *fp;
    fp = fopen(filename, "r");
    
    if(fp == NULL){
        //printf("duck");
        perror(filename);
        return 0;
    }
    int size, exponent;
    fscanf(fp,"%d", &size);
    int *matrix = malloc((size * size) * sizeof(int));
    for(int i = 0; i< size; i++) {
        for(int j = 0; j <size; j++){
	    int num;
	    fscanf(fp, "%d", &num);
	    matrix[(size*i)+j] = num;
    }
}
    fscanf(fp,"%d", &exponent);
    if(exponent == 0){
        mult_result = matrix_zero(size);
    } else if(exponent == 1) {
        mult_result = matrix;
    } 
    else {
        mult_result = matrix_multiply(matrix, matrix, size);
        
        for(int i = 0; i<exponent-2; i++){
            mult_result = matrix_multiply(matrix, mult_result, size);
        }
    
    } print_matrix(mult_result, size);
    for(int i = 0; i< size; i++) {
        for(int j = 0; j <size; j++){
            free(*mult_result+(size*i)+j);
            free(*matrix+(size*i)+j);
        }
    }
}