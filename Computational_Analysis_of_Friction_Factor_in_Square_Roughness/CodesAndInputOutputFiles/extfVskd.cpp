#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
using namespace std;
int main(){
    ifstream in("g11fvskd.txt");
    ifstream in2("g12fvskd.txt");
    int n=21; //no of data points
    // the derivative values are stored in Matrix M, theta is the current values of f*Re/64
    vector<double>M(n);
    vector<double>M1(n);// for different Re
    vector<double>theta(n);
    vector<double>theta1(n);
    vector<double>kd(n);
    vector<double>kd1(n);
    for(int i=0;i<n;i++){
        in>>kd[i];
        in>>theta[i];
    }
    for(int i=0;i<n;i++){
        in2>>kd1[i];
        in2>>theta1[i];
    }
    double Re = 2000;
    double Re1 = 1200;
    //calculate the derivative of end pts by 3pt fwd/bwd diff method
    M[0] = (64/Re)*(((-3*theta[0])+(4*theta[1])-theta[2])/0.01);
    M1[0] = (64/Re1)*(((-3*theta1[0])+(4*theta1[1])-theta1[2])/0.01);
    M[n-1] = (64/Re)*(((3*theta[n-1])+(-4*theta[n-2])+theta[n-3])/0.01);
    M1[n-1] = (64/Re1)*(((3*theta1[n-1])+(-4*theta1[n-2])+theta1[n-3])/0.01);
    //all other pts by 3pt central difference
    for(int i=1;i<n-1;i++){
        M[i] = (64/Re)*((theta[i+1]-theta[i-1])/0.01);
        M1[i] = (64/Re1)*((theta1[i+1]-theta1[i-1])/0.01);
    }
    ofstream out("DiffFvsKdData.txt");
    ofstream out2("DiffFvsKdDataLowRe.txt");
    for(int i=0;i<n;i++){
        out<<kd[i]<<" "<<M[i]<<endl;
        out2<<kd1[i]<<" "<<M1[i]*2.778<<endl;
    }
    string command1 = "gnuplot -persist -e \""
    "set xlabel 'k/D';"
    "set ylabel 'df/d(k/D)';"
    "plot 'DiffFvsKdData.txt' with linespoints lc rgb 'cyan' title 'Re=2000',"
    " 'DiffFvsKdDataLowRe.txt' with linespoints lc rgb 'magenta' title 'Re=1200'\"";
    system(command1.c_str());
    return 0;
}