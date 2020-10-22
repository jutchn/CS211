#include <stdio.h>
#include <stdlib.h>

void print_matrix(double *matrix, int k, int n) {
	for(int i = 0; i<n; i++) {
		for(int j = 0; j<k; j++) {
			printf("%.0lf ", matrix[((k) * i) + j]);
			//if(j < n +1) {
            //    printf(" ");	
            //}
		}
	printf("\n");
    }
}

double *matrix_zero(double *zoop,int size) {
	//printf("duck");

    for(int i = 0; i< size; i++) {
        for (int j = 0; j < size; j++) { 
		    //printf("%d ",(size*i));
            //printf("%d\n",j);
            if(i == j){
                zoop[(size*i)+j] = 1;
            } else {
                zoop[(size*i)+j] = 0;
            }
        }
    }  
	return zoop;
}

double *matrix_multiply(double *multiply_result, double *matrix, double *matrix2,int row1, int col1, int row2, int col2) {
	//double *multiply_result = malloc((col * col) * sizeof(double));
//printf("shit");
    //printf("row1: %d row2: %d\n",row1,row2);
    //printf("col1: %d col2: %d\n",col1,col2);
    
    int i, j, k; 
    for (i = 0; i < row1; i++) { 
        for (j = 0; j < col2; j++) {  
            multiply_result[(col2 * i) + j] = 0;
            for (k = 0; k < col1; k++) 
                multiply_result[(col2 * i) + j] += matrix[(row2 * i) + k] * matrix2[(col2 * k) + j]; 
        } 
    }
    return multiply_result; 
}
double *matrix_invert(double *inverse, double *product, double *identity, int n){
    for(int p = 0; p< n; p++){
        double f = product[(p*n)+p];
        for(int row = 0; row< n; row++){
            product[(n*p)+row] = product[(n*p)+row]/f;
            identity[(n*p)+row] = identity[(n*p)+row]/f;
        }
            for(int i =p+1;i<n; i++){
                f = product[(i*n)+p];
                for(int row = 0; row< n; row++){
                product[(n*i)+row] = product[(n*i)+row] - (product[(n*p)+row]*f);
                identity[(n*i)+row] = identity[(n*i)+row] - (identity[(n*p)+row]*f);
                }
            }     
    }
    for(int p = n-1; p>=0; p--){
        for(int i = p-1; i>=0; i--){
            double f2 = product[(i*n)+p];
            for(int row = 0; row< n; row++){
                product[(n*i)+row] = product[(n*i)+row] - (product[(n*p)+row]*f2);
                identity[(n*i)+row] = identity[(n*i)+row] - (identity[(n*p)+row]*f2);
                }
        }
    }
    //print_matrix(product,n,n);
    //printf("\n\n");
    inverse = identity;
    return inverse;
}

int main(int argc, char **argv) {
    
    char *tfilename = argv[1];
    char *datafilename = argv[2];
    
    FILE *fp;
    fp = fopen(tfilename, "r");
    FILE *fp2;
    fp2 = fopen(datafilename, "r");
    
    char gahbage[100];
    char gahbage2[100];
    int k, n, k2, n2;
    fscanf(fp,"%s", gahbage);
    fscanf(fp,"%d", &k);
    fscanf(fp,"%d", &n);
    
    double *matt = malloc(((k+1)*n) * sizeof(double));
    double *mprice = malloc((n) * sizeof(double));
    double *transmatt = malloc((n*(k+1)) * sizeof(double));
    double *product = malloc(((k+1) * (k+1)) * sizeof(double));
    double *identity = malloc(((k+1)*(k+1)) * sizeof(double));
    double *inverse = malloc(((k+1)*(k+1)) * sizeof(double));
    double *product2 = malloc((k+1) * sizeof(double));
    double *product3 = malloc((k+1) * sizeof(double));
 //   printf("%d\n",k);
 //   printf("%d\n",n);
    
    for(int i = 0; i< n; i++) {
        for(int j = 1; j <k+1; j++){
	        double num;
	        fscanf(fp, "%lf", &num);
            //printf("|%d|",((k+1)*i)+j);
	        matt[((k+1)*i)+j] = num;
            //printf("|%f|",num);
    }
    double price;
    fscanf(fp, "%lf", &price);
    mprice[i] = price;
    }

    //setting collumn 1 to 1 
    for(int i = 0; i<n; i++){
        //printf("|%d|\n",i*(k+1));
        matt[i*(k+1)] = 1.0;
    }

    fscanf(fp2,"%s", gahbage2);
    fscanf(fp2,"%d", &k2);
    fscanf(fp2,"%d", &n2);

    double *matt2 = malloc(((k2+1)*n2) * sizeof(double));
    //printf("k: %d\n",k2);
    //printf("n: %d\n",n2);
    for(int i = 0; i< n2; i++) {
        for(int j = 1; j <k2+1; j++){
	        double num;
	        fscanf(fp2, "%lf", &num);
            //printf("|%d|",((k+1)*i)+j);
	        matt2[((k2+1)*i)+j] = num;
            //printf("|%f|",num);
        }
    }
    for(int i = 0; i<n2; i++){
        //printf("|%d|\n",i*(k+1));
        matt2[i*(k2+1)] = 1.0;
    }
    double *output = malloc((n2) * sizeof(double));
    
    //making matrix tranverse   
    for(int i = 0; i< k+1; i++) {
        for(int j = 0; j <n; j++){
            transmatt[(n*i)+j] = matt[((k+1)*j)+i];
        }
    }
    product = matrix_multiply(product, transmatt,matt,k+1,n,n,k+1);
    print_matrix(product, 5,5);
    printf("\n");
    //free(matt);
    identity = matrix_zero(identity, k+1);
    
    inverse = matrix_invert(inverse, product, identity, k+1);
    print_matrix(inverse, 4,4);
    //free(identity);
    product2 = matrix_multiply(product2, transmatt,mprice,k+1,n,n,1);
    //free(transmatt);
    //free(mprice);
    //print_matrix(product2, k ,2);
    product3 = matrix_multiply(product3,inverse,product2,k+1,k+1,k+1,1);
    //print_matrix(product3, k, 1);

    output = matrix_multiply(output,matt2,product3,n2,k2+1,k+1,1);

    print_matrix(output,1,n2);
    /*
    free(matt);
    free(mprice);
    free(transmatt);
    free(product);
    free(identity);
    free(inverse);
    free(product2);
    free(product3);
    free(matt2);
    free(output);
    */
    return 0;
}