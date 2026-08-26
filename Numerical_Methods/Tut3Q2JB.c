#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    FILE *inputFile = fopen("inputQ1A.txt", "r");
    FILE *outputFile = fopen("output_Q2B.txt", "w");
    int n;

    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }
    
    fscanf(inputFile, "%d", &n);
    
    double matrix[n][n + 1];
    double A[n][n], b[n];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(inputFile, "%lf", &A[i][j]);
        }
    }
    
    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%lf", &b[i]);
    }
    
    fclose(inputFile);
    

    for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			matrix[i][j]=A[i][j];
		}
	}
    for(int i=0;i<n;i++){
        matrix[i][n]=b[i];
    }
    for(int i=0;i<n-1;i++){
        int max_row = i;
        for(int j=i+1;j<n;j++){
            if(fabs(matrix[max_row][i])<fabs(matrix[j][i])){
                max_row=j;
            }
        }
        for(int k=i;k<=n;k++){
            double temp;
            temp=matrix[i][k];
            matrix[i][k]=matrix[max_row][k];
            matrix[max_row][k]=temp;
        }
    }
    
    double error[n];
    double x[n];
    double xnew[n];
    for(int i=0;i<n;i++){
        x[i]=0;
        error[i]=0;
    }
    
    int check=n;
    int i=0;
    while (check>0){
        for (int i = 0; i < n; i++) {
            double sum1 = 0;
            double sum2 =0;
            for (int j = 0; j < n; j++) {
                if (j < i) {
                    sum1 += matrix[i][j] * x[j];
                }
                if (j>i){
                    sum2 += matrix[i][j] * x[j];
                }
            }
            xnew[i] = (b[i] - sum1- sum2) / matrix[i][i];
        }
        
        for(int i=0;i<n;i++){
            error[i]=xnew[i]-x[i];
        }  
        double rmserr=0;
        for(int i=0;i<n;i++){
            rmserr+=error[i]*error[i];
        }
        
        int small_check = 0;
        for (int i = 0; i < n; i++) {
            if (fabs(xnew[i] - x[i]) < pow(10, -4)) {
                small_check += 1;
            }
        }

        if (small_check == n) {
            check = 0;
        }
        for (int i=0;i<n;i++){
            x[i]=xnew[i];
        }
        if (i<25){
            fprintf(outputFile,"The rms value of Error in Jacobian method in %d iteration is: %lf\n",(i+1),pow(rmserr,0.5));
        }
        i++;

    }

    fclose(outputFile);



    return 0;
}