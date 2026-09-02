#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
using namespace std;
//Non- linear Regression
double a= 0.2;  
double b= 38;
double e = 2.71828183;
double fn(double x){
    return a *pow(e,(b*x)) ;
}
double fda(double x){
    return pow(e,(b*x)) ;
}
double fdb(double x){
    return a*b*x*pow(e,(b*x)) ;
}
int main(){
    ifstream in("DiffFvsKdData.txt");
    int n = 21;
    vector<double>x(n);
    vector<double>y(n);
    for(int i=0;i<n;i++){
        in>>x[i];
        in>>y[i];
    }
    in.close();
    vector<double>d(n);
    vector<double>dela(2);
    vector<vector<double>>z(n,vector<double>(2));
    double tol = 1e-10;
    double errmax = 1;
    int steps = 0;
    while(errmax>tol){
        steps++;
     for(int i=0;i<n;i++){
        d[i] = y[i] - fn(x[i]);
     }
     for(int i=0;i<n;i++){
        z[i][0] = fda(x[i]);
        z[i][1] = fdb(x[i]);
     }
     vector<vector<double>>zt(2,vector<double>(n));
     vector<vector<double>>ztz(2,vector<double>(2));
     vector<vector<double>>ztzinv(2,vector<double>(2));
     vector<vector<double>>ztzinvzt(2,vector<double>(n));
     for(int i=0;i<2;i++){
        for(int j=0;j<n;j++){
            zt[i][j]=z[j][i];
        }
     }
     for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<n;k++){
                ztz[i][j] += zt[i][k] * z[k][j];
            }
        }
     }
    double Detztz = (ztz[0][0]*ztz[1][1])-(ztz[0][1]*ztz[1][0]); // determinant of Yt*Y
    ztzinv[0][0] = (ztz[1][1])/Detztz;
    ztzinv[1][1] = (ztz[0][0])/Detztz;
    ztzinv[0][1] = (-1)*((ztz[0][1])/Detztz);
    ztzinv[1][0] = (-1)*((ztz[1][0])/Detztz);
    
    for( int i=0;i<2;i++){
        for( int j=0;j<n;j++){
            for(int k=0;k<2;k++){
                ztzinvzt[i][j] += ztzinv[i][k] * zt[k][j];
            }
        }
    }
    for(int i=0;i<2;i++){
        for (int j=0;j<n;j++){
            dela[i] += ztzinvzt[i][j] * d[j];
        }
    }
     if((dela[0]/a)>(dela[1]/b)){
        errmax = dela[0]/a; 
     }else{
        errmax = dela[1]/b;
     }
     a += dela[0];
     b += dela[1];
    }
    
    ofstream datacurve("expfnData.txt");
    for(int i=0;i<n;i++){
        datacurve << x[i] <<" "<< fn(x[i])<<endl;
    }
    
    datacurve.close();
    ofstream out("expfnoutput.txt");
    out<<"The equation is y = ("<<a<<")x*exp("<<b<<"x)\n";
    out<<"The number of iterations required = "<<steps<<endl;
    //plot
    string command ="gnuplot -persist -e \""
                    "set xlabel 'k/D';"
                    "set ylabel 'df/d(k/D)';"
                    "plot 'DiffFvsKdData.txt' with points title 'Actual Data',"
                    " 'expfnData.txt' with linespoints title 'Estimated Curve'\"";
    system(command.c_str());
    return 0;
}