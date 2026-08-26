#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

int main (){
    ofstream out("OutputTut7.txt");
    ifstream in("InputTut7.txt");
    int n;
    double a0,a1;
    in >> n;
    double x[n], y[n], yp[n], xsum, ysum, xysum, x2sum;
    xsum=0;
    ysum=0;
    x2sum=0;
    xysum=0;
    for(int i=0; i<n;i++){
        in >> x[i];
        in >> y[i];
    }
    
    for(int i=0; i<n;i++){
        xsum+=x[i];
        ysum+=y[i];
        x2sum+=x[i]*x[i];
        xysum+=x[i]*y[i];
    }
    
    a1=(n*xysum-xsum*ysum)/(n*x2sum-pow(xsum,2));
    a0=ysum/n-(xsum/n)*a1;

    for(int i=0; i<n;i++){
        yp[i]=a0+a1*x[i];
    }
    double Sr,St;
    Sr =0; St =0;
    
    for(int i=0; i<n;i++){
        Sr+=pow((y[i]-yp[i]),2);
        St+=pow((y[i]-ysum/n),2);
    }
    
    
    double r;
    r=sqrt(((St-Sr)/St));
    out << "Linear Regression Line by Summation Method : y = " << a0 << "+"<< a1 <<"x"<< endl ;
    out << "Correlation Coeffecient : " << r << endl;

    double X[7][2];
    for (int i=0;i<7;i++){
        X[i][0]=1;
        X[i][1]=i+1;
    }
    double Xtr[2][7];
    for (int i=0;i<2;i++){
        for(int j=0;j<7;j++){
            Xtr[i][j]=X[j][i];
        }
    }
    double XtX[2][2];
    for(int i=0;i<2;i++){
        for (int j=0;j<2;j++){
            for (int k=0;k<7;k++){
                XtX[i][j]+=Xtr[i][k]*X[k][j];
            }
        }
    }
    n=2;
    double matrix[n][2*n+1];
    for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			matrix[i][j]=XtX[i][j];
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

    double mat[n][n];
    for(int i=0;i<n;i++){
	    for(int j=0;j<n;j++){
	        mat[i][j]=matrix[i][j+n+1];
	    }
	}

    double XtXinvXt[2][7];
    for(int i=0;i<2;i++){
        for (int j=0;j<7;j++){
            XtXinvXt[i][j]=0;
            for (int k=0;k<2;k++){
                XtXinvXt[i][j]+=(mat[i][k]*Xtr[k][j]);
            }
        }
    }

    double XtXinvXtY[2][1];
    for(int i=0;i<2;i++){ 
        XtXinvXtY[i][0]=0;
        for (int k=0;k<7;k++){
            XtXinvXtY[i][0]+=XtXinvXt[i][k]*y[k];
        }
    }

    a0=XtXinvXtY[0][0];
    a1=XtXinvXtY[1][0];
    Sr=0;
    St=0;
    n=7;
    for(int i=0; i<n;i++){
        yp[i]=a0+a1*x[i];
        Sr+=pow((y[i]-yp[i]),2);
        St+=pow((y[i]-(ysum/n)),2);
    }

    r=sqrt(((St-Sr)/St));
    out << "Linear Regression Line by Matrix Method : y = " << a0 << "+"<< a1 <<"x"<< endl ;
    out << "Correlation Coeffecient : " << r << endl;

    

    return 0;

}