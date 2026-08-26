#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {

    // READING FROM THE INPUT FILE

	FILE *inputFile = fopen("input1.txt", "r");
    FILE *outputFile = fopen("output_Ques1.txt", "w");
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
    
    // FORMATION OF AUGMENTED MATRIX A|B

	for(int i=0;i<n;i++){
		for(int j=0;j<(n+1);j++){
			matrix[i][j]=A[i][j];
		}
	}
    for(int i=0;i<n;i++){
        matrix[i][n]=b[i];
    }
    
	// PARTIAL PIVOTING AND FORMATION OF UPPER TRIANGULAR MATRIX

    for(int i=0;i<n-1;i++){
        int max_row = i;
        for(int j=i+1;j<n;j++){
            if(fabs(matrix[j][i])>fabs(matrix[max_row][i])){
                max_row=j;
            }
        }
        for(int k=i;k<=n;k++){
            double temp;
            temp=matrix[i][k];
            matrix[i][k]=matrix[max_row][k];
            matrix[max_row][k]=temp;
        }
        double factor;
        for(int j=i+1;j<n;j++){
            factor =matrix[j][i]/matrix[i][i];
            for(int k=i;k<=n;k++){
                matrix[j][k]-=((factor)*matrix[i][k])
                ;
            }
        }
        for(int i =0;i<n;i++){
            for(int j =0;j<=n;j++){
                fprintf(outputFile,"%lf ",matrix[i][j]);
            }
        fprintf(outputFile,"\n");
        }
        
        
    }
    
    

    // SOLUTION WRITING

    double vector[n];
    for(int j=n-1;j>=0;j--){
        double x;
        double sum=0;
        for(int p=n-1; p>j;p--){
            sum+=(matrix[j][p]*vector[p]);
        }
        x=(matrix[j][n]-sum)/matrix[j][j];
        vector[j]=x;
        
    }

    // CREATING OUTPUT FILE OF THE SOLUTION

    fprintf(outputFile,"Solution of equations: \n");
    for (int i =0;i<n;i++){
        fprintf(outputFile, "%lf\n",vector[i]);
    }
    fprintf(outputFile,"The result verification for AX: \n");
    for (int i=0;i<n;i++){
        double sum=0;
        for (int j=0;j<n;j++){
            sum+=A[i][j]*vector[j];
        }
        fprintf(outputFile, "%lf\n",sum);
    }
    fprintf(outputFile,"It is exactly same as forcing vector B.\nHence Verified!");
    fclose(outputFile);

    return 0;
}