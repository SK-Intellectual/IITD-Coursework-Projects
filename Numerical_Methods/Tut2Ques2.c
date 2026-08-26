 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main() {

    // READING FORM THE INPUT FILE

	FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output_Ques2.txt", "w");
    
    int n;
    fscanf(inputFile, "%d", &n);
    double matrix[n][2 * n + 1];
    double A[n][n], b[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(inputFile, "%lf", &A[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%lf", &b[i]);
    }

    //FORMATION OF AUGMENTED MATRIX A|B|I

    for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			matrix[i][j]=A[i][j];
		}
	}
    for(int i=0;i<n;i++){
        matrix[i][n]=b[i];
    }
	for(int i=0;i<n;i++){
		for(int j=n+1;j<((2*n)+1);j++){
			if(j==(i+n+1)){
                matrix[i][j]=1;
            }
            else{
                matrix[i][j]=0;
            }
		}
	}

    // MAIN FUNCTIONAL CODE OF THE PROGRAM

    for(int i=0;i<n-1;i++){
        int max_row = i;
        for(int j=i+1;j<n;j++){
            if(fabs(matrix[max_row][i])<fabs(matrix[j][i])){
                max_row=j;
            }
        }
        for(int k=i;k<=(2*n);k++){
            double temp;
            temp=matrix[i][k];
            matrix[i][k]=matrix[max_row][k];
            matrix[max_row][k]=temp;
        }
        double facden =matrix[i][i];
        for(int k=i;k<=(2*n);k++){
            matrix[i][k]=(matrix[i][k]/facden);
        }
        double factor;
        for(int j=0;j<n;j++){
            if(j!=i){
                factor =matrix[j][i];
                for(int k=i;k<=(2*n);k++){
                    matrix[j][k]-=((factor)*matrix[i][k])
                    ;
                }
            }
        }
        
    }
    double facden2 = matrix[n-1][n-1];
    for(int i=n-1;i<=(2*n);i++){ 
        matrix[n-1][i]/=facden2;
    }
    double last_factor;
    for(int j=0;j<n-1;j++){
        last_factor =matrix[j][n-1];
        for(int k=n-1;k<=(2*n);k++){
            matrix[j][k]-=((last_factor)*matrix[n-1][k]);    
        }
    }

    // MAKING INVERSE MATRIX A-1

    double mat[n][n];
    for(int i=0;i<n;i++){
	    for(int j=0;j<n;j++){
	        mat[i][j]=matrix[i][j+n+1];
	    }
	}

    // VERIFYING AA-1 = I

	double Verify[n][n];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            Verify[i][j] = 0.0;
        }
    }
	
	for (int i=0;i<n;i++){
	    for (int j=0;j<n;j++){
	        for (int k=0;k<n;k++){
	            Verify[i][j]+=A[i][k]*mat[k][j];
	        }
	    }
	}

    // CREATING OUTPUT FILE

    fprintf(outputFile, "Solutions of equations: \n");
    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "%lf\n", matrix[i][n]);
    }

    fprintf(outputFile, "A-1 :\n");

    for (int i = 0; i < n; i++) {
        for (int j = n + 1; j < 2 * n + 1; j++) {
            fprintf(outputFile, "%lf ", matrix[i][j]);
        }
        fprintf(outputFile, "\n");
    }

	fprintf(outputFile,"Verified Result AA-1: \n");
	for(int i=0;i<n;i++){
	    for (int j=0;j<n;j++){
	        fprintf(outputFile,"%lf ",Verify[i][j]);
	    }
	    fprintf(outputFile,"\n");
	}
    

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}