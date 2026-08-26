#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f1(double x, double y, double z){
    double fx;
    fx=pow(x,2)+pow(y,2)+pow(z,2)-4;
    return fx;
}
double f2(double x, double y){
    double f;
    f=pow(x,2)+pow(y,2)-1;
    return f;
}
double f3(double y, double z){
    double f22;
    f22=pow(z,2)+ 4*(pow(y,2))-4;
    return f22;
}

int main(){
    FILE *outputFile = fopen("outputTut5.txt", "w");

    int n=3;
    double error[n];
    double terror[n];
    double x[n];
    double xnew[n];
    double xtrue =pow(0.75,0.5);
    double ytrue =0.5;
    double ztrue =pow(3,0.5);
    for(int i=0;i<n;i++){
        error[i]=0;
        terror[i]=0;
    }
    x[0] = 1.0;
    x[1] = 1.0;
    x[2] = 1.0;
    
    int check=n;
    int i=1;
    double J[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            J[i][j]=0;
        }
    }
    double fgroup[3];
    for(int i=0;i<3;i++){
        fgroup[i]=0;
    }
    double matrix[3][6];
    
    while (check>0){
        J[0][0]=2*x[0];
        J[0][1]=2*x[1];
        J[0][2]=2*x[2];
        J[1][0]=2*x[0];
        J[1][1]=2*x[1];
        J[1][2]=0;
        J[2][0]=0;
        J[2][1]=8*x[1];
        J[2][2]=2*x[2];
        fgroup[0]=f1(x[0],x[1],x[2]);
        fgroup[1]=f2(x[0],x[1]);
        fgroup[2]=f3(x[1],x[2]);
        for(int i=0;i<3;i++){
            for(int j=0;j<6;j++){
                matrix[i][j]=0;
            }
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                matrix[i][j]=J[i][j];
            }
        }
        matrix[0][3]=1;
        matrix[1][4]=1;
        matrix[2][5]=1;
        
        
        for(int i=0;i<2;i++){

            int max_row = i;
            for(int j=i+1;j<n;j++){
                if(fabs(matrix[max_row][i])<fabs(matrix[j][i])){
                    max_row=j;
                }
            }
            for(int k=i;k<=(5);k++){
                double temp;
                temp=matrix[i][k];
                matrix[i][k]=matrix[max_row][k];
                matrix[max_row][k]=temp;
            }
            double facden =matrix[i][i];
            for(int k=i;k<=5;k++){
                matrix[i][k]=(matrix[i][k]/facden);
            }
            double factor;
            for(int j=0;j<3;j++){
                if(j!=i){
                    factor =matrix[j][i];
                    for(int k=i;k<=(5);k++){
                        matrix[j][k]-=((factor)*matrix[i][k]);
                    }
                }
            }
        
        }
        double facden2 = matrix[2][2];
        for(int i=2;i<=(5);i++){ 
            matrix[2][i]/=facden2;
        }
        
        double last_factor;
        for(int j=0;j<2;j++){
            last_factor =matrix[j][2];
            for(int k=2;k<=(5);k++){
                matrix[j][k]-=((last_factor)*matrix[2][k]);    
            }
        }

        double Jinv[3][3];
        for(int i=0;i<3;i++){
	        for(int j=0;j<3;j++){
	            Jinv[i][j]=matrix[i][j+3];
	        }
	    }
        

        double kop[3];
        for(int i=0;i<3;i++){
            kop[i]=0;
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                kop[i]+=Jinv[i][j]*fgroup[j];
            }
        }

        for (int i=0;i<3;i++){
            xnew[i]=x[i]-kop[i];
        }
        
        for(int i=0;i<n;i++){
            error[i]=xnew[i]-x[i];
        } 
        terror[0]=xtrue-x[0];
        terror[1]=ytrue-x[1];
        terror[2]=ztrue-x[2];
        
        double max_error = 0.0;
        for (int i = 0; i < n; i++) {
            double current_error = fabs(xnew[i] - x[i]);
            if (current_error > max_error) {
                max_error = current_error;
            }
        }

        if (max_error < pow(10, -4)) {
            check = 0;
        }

        fprintf(outputFile,"Iteration %d : True error is X : %lf , Y : %lf , Z : %lf\n",i,terror[0],terror[1],terror[2]);
        fprintf(outputFile,"Iteration %d : Relative error is X : %lf , Y : %lf , Z : %lf\n",i,error[0],error[1],error[2]);
        

        for (int i=0;i<n;i++){
            x[i]=xnew[i];
        }
        
        i++;

    }
    fprintf(outputFile,"Solutions :\n");
    for (int i=0;i<3;i++){
        fprintf(outputFile,"%lf\n",x[i]);
    }

    return 0;
}
