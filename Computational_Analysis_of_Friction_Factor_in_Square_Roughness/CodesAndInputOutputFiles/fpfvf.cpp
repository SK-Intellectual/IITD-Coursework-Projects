#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
using namespace std;
int main(){
    ifstream in("kd.txt");
    int n=14;
    vector<double>kd(n);
    for(int i=0;i<n;i++){
        in>>kd[i];
    }
    double Re = 1000;
    double lw1=2.0;
    double fvBC=64.0/(100*Re),fp,fvDA,fv;
    ofstream fvbc("fvbc.txt");
    ofstream fvda("fvda.txt");
    ofstream fpp("fp.txt");
    ofstream fvv("fv.txt");
    for(int i=0;i<n;i++){
        fp = 3000*(pow(kd[i],2))*(1/Re);
        fvDA = (520-(35*lw1))*kd[i]*(1/Re);
        fvbc<<kd[i]<<" "<<fvBC<<endl;
        fpp<<kd[i]<<" "<<fp<<endl;
        fvda<<kd[i]<<" "<<fvDA<<endl;
        fvv << kd[i] << " " << fvDA+fvBC << endl;
    }
    string command1 = "gnuplot -persist -e \""
    "set xlabel 'k/D';"
    "set ylabel 'f';"
    "plot 'fvbc.txt' with linespoints lc rgb 'red' title 'fvBC,Re = 200, lambda/w = 2',"
    " 'fvda.txt' with linespoints lc rgb 'blue' title 'fvDA,Re = 200, lambda/w = 2',"
    " 'fp.txt' with linespoints lc rgb 'cyan' title 'fp,Re = 200, lambda/w = 2',"
    " 'fv.txt' with linespoints lc rgb 'green' title 'fv,Re = 200, lambda/w = 2'\"";
    system(command1.c_str());

    return 0;
}