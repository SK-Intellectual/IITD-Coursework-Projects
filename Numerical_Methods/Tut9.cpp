#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
double flagarange(double s){
    double mp[8],y[8];
    double p=0;
    double pi=3.1415926535898;
    for (int i=0;i<8;i++){
        mp[i]=(pi)*(i)*(2.0/7);
        y[i]=sin(mp[i])*sin(mp[i]);
    }  
    for(int i=0;i<8;i++){
        double t=1;
        for (int j=0;j<8;j++){
            if (i!=j){
                t=t*(s-mp[j])/(mp[i]-mp[j]);
            } 
        }
        p+=y[i]*t;
    }
    return p;
}

double fNDD(double s){
    double x[8],y[8];
    double pi=3.1415926535898;
    for (int j=0;j<8;j++){
        x[j]=(pi)*(j)*(2.0/7);
        y[j]=sin(x[j])*sin(x[j]);
    }
    double b0[8],b1[7],b2[6],b3[5],b4[4],b5[3],b6[2],b7[1];
    for (int i=0;i<8;i++){
        b0[i]=y[i];
    }
    for (int i=0;i<7;i++){
        b1[i]=(b0[i+1]-b0[i])/(x[i+1]-x[i]);
    }
    for (int i=0;i<6;i++){
        b2[i]=(b1[i+1]-b1[i])/(x[i+2]-x[i]); 
    }
    for (int i=0;i<5;i++){
        b3[i]=(b2[i+1]-b2[i])/(x[i+3]-x[i]);
    }
    for (int i=0;i<4;i++){
        b4[i]=(b3[i+1]-b3[i])/(x[i+4]-x[i]);
    }
    for (int i=0;i<3;i++){
        b5[i]=(b4[i+1]-b4[i])/(x[i+5]-x[i]);
    }
    for (int i=0;i<2;i++){
        b6[i]=(b5[i+1]-b5[i])/(x[i+6]-x[i]);
    }
    for (int i=0;i<1;i++){
        b7[i]=(b6[i+1]-b6[i])/(x[i+7]-x[i]);
    }
    return (b0[0]+b1[0]*(s-x[0])+b2[0]*(s-x[0])*(s-x[1])+b3[0]*(s-x[0])*(s-x[1])*(s-x[2])+b4[0]*(s-x[0])*(s-x[1])*(s-x[2])*(s-x[3])+b5[0]*(s-x[0])*(s-x[1])*(s-x[2])*(s-x[3])*(s-x[4])+b6[0]*(s-x[0])*(s-x[1])*(s-x[2])*(s-x[3])*(s-x[4])*(s-x[5])+b7[0]*(s-x[0])*(s-x[1])*(s-x[2])*(s-x[3])*(s-x[4])*(s-x[5])*(s-x[6]));
    
}
double fPoly(double s){
    double x[8],y[8],X[8][8],Xinv[8][8],phi[8],matrix[8][17];
    double pi=3.1415926535898;
    int n=8;
    for (int j=0;j<8;j++){
        x[j]=(pi)*(j)*(2.0/7);
        y[j]=sin(x[j])*sin(x[j]);
    }
    for (int i=0; i<8;i++){
        for (int j=0;j<8;j++){
            X[i][j]=pow(x[i],j);
        }
    }
    
    for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			matrix[i][j]=X[i][j];
		}
	}
    for(int i=0;i<n;i++){
        matrix[i][n]=1;
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

    for(int i=0;i<n;i++){
	    for(int j=0;j<n;j++){
	        Xinv[i][j]=matrix[i][j+n+1];
	    }
	}
    for (int i=0;i<8;i++){
        phi[i]=0;
        for (int k=0;k<8;k++){
            phi[i]+=Xinv[i][k]*y[k];
        }
    }
    return (phi[0]+phi[1]*s+phi[2]*s*s+phi[3]*pow(s,3)+phi[4]*pow(s,4)+phi[5]*pow(s,5)+phi[6]*pow(s,6)+phi[7]*pow(s,7));
}
int main (){
    ofstream out("OutputTut9.txt");
    double x[50],ylag[50],yndd[50],ypoly[50];
    double pi=3.1415926535898;
    for (int j=0;j<50;j++){
        x[j]=(pi)*(j)*(2.0/49);
        ylag[j]=flagarange(x[j]);
        yndd[j]=fNDD(x[j]);
        ypoly[j]=fPoly(x[j]);
    }
    for (int i=0;i<50;i++){

        out << x[i]<< endl;
    }
    for (int i=0;i<50;i++){
        out << yndd[i]<< endl;
    }
    for (int i=0;i<50;i++){
        out << ypoly[i]<< endl;
    }
    



    return 0;
}