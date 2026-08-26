#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

int main (){
    ofstream out("OutputTut7Q2.txt");
    ifstream in("InputTut7Q2.txt");
    int N;
    double a0,a1,a2,a3;
    in >> N;
    int n=N;
    double x[n] ,y[n] ,u[n], w[n];
    double xsum,ysum,usum,x2sum,uxsum,u2sum,xysum,yusum,wsum,wxsum,wusum,w2sum,ywsum;
    xsum =0; ysum =0; usum=0; x2sum=0; uxsum=0; u2sum=0; xysum=0; yusum=0; wsum=0; wxsum=0; wusum=0; w2sum=0; ywsum=0;
    
    for(int i=0; i<n;i++){
        in >> x[i];
        in >> u[i];
        in >> y[i];
        in >> w[i];
    }
    
    for(int i=0; i<n;i++){
        xsum+=x[i];
        ysum+=y[i];
        usum+=u[i];
        x2sum+=x[i]*x[i];
        u2sum+=u[i]*u[i];
        xysum+=x[i]*y[i];
        uxsum+=u[i]*x[i];
        yusum+=y[i]*u[i];
        wsum+=w[i];
        w2sum+=w[i]*w[i];
        wxsum+=w[i]*x[i];
        ywsum+=y[i]*w[i];
        wusum+=w[i]*u[i];

    }
    double matri[4][5];
    matri[0][0]=10;
    matri[0][1]=xsum;
    matri[0][2]=usum;
    matri[0][3]=wsum;
    matri[0][4]=ysum;
    matri[1][0]=xsum;
    matri[1][1]=x2sum;
    matri[1][2]=uxsum;
    matri[1][3]=wxsum;
    matri[1][4]=xysum;
    matri[2][0]=usum;
    matri[2][1]=uxsum;
    matri[2][2]=u2sum;
    matri[2][3]=wusum;
    matri[2][4]=yusum;
    matri[3][0]=wsum;
    matri[3][1]=wxsum;
    matri[3][2]=wusum;
    matri[3][3]=w2sum;
    matri[3][4]=ywsum;
    n=4;
    for(int i=0;i<n-1;i++){
        int max_row = i;
        for(int j=i+1;j<n;j++){
            if(fabs(matri[j][i])>fabs(matri[max_row][i])){
                max_row=j;
            }
        }
        for(int k=i;k<=n;k++){
            double temp;
            temp=matri[i][k];
            matri[i][k]=matri[max_row][k];
            matri[max_row][k]=temp;
        }
        double factor;
        for(int j=i+1;j<n;j++){
            factor =matri[j][i]/matri[i][i];
            for(int k=i;k<=n;k++){
                matri[j][k]-=((factor)*matri[i][k])
                ;
            }
        }
    }
    double vector[n];
    for(int j=n-1;j>=0;j--){
        double x;
        double sum=0;
        for(int p=n-1; p>j;p--){
            sum+=(matri[j][p]*vector[p]);
        }
        x=(matri[j][n]-sum)/matri[j][j];
        vector[j]=x;   
    }
    a0=vector[0];
    a1=vector[1];
    a2=vector[2];
    a3=vector[3];
    out << "Linear Regression Line by Summation Method : y1 = " << a0 << a1 <<"x1 " << a2 << "x2 " << a3 << "y2 "<< endl ;
    

    double X[10][4];
    for (int i=0;i<10;i++){
        X[i][0]=1;
        X[i][1]=x[i];
        X[i][2]=u[i];
        X[i][3]=w[i];
    }
    double Xtr[4][10];
    for (int i=0;i<4;i++){
        for(int j=0;j<10;j++){
            Xtr[i][j]=X[j][i];
        }
    }
    double XtX[4][4];
    for(int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            XtX[i][j]=0;
            for (int k=0;k<10;k++){
                XtX[i][j]+=Xtr[i][k]*X[k][j];
            }
        }
    }
    n=4;
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
                    matrix[j][k]-=((factor)*matrix[i][k]);
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

    double XtXinvXt[4][10];
    for(int i=0;i<4;i++){
        for (int j=0;j<10;j++){
            XtXinvXt[i][j]=0;
            for (int k=0;k<4;k++){
                XtXinvXt[i][j]+=(mat[i][k]*Xtr[k][j]);
            }
        }
    }

    double XtXinvXtY[4][1];
    for(int i=0;i<4;i++){ 
        XtXinvXtY[i][0]=0;
        for (int k=0;k<10;k++){
            XtXinvXtY[i][0]+=XtXinvXt[i][k]*y[k];
        }
    }

    a0=XtXinvXtY[0][0];
    a1=XtXinvXtY[1][0];
    a2=XtXinvXtY[2][0];
    a3=XtXinvXtY[3][0];

    out << "Linear Regression Line by Matrix Method : y1 = " << a0 << a1 <<"x1 " << a2 << "x2 " << a3 << "y2 "<< endl ;
    

    return 0;
}