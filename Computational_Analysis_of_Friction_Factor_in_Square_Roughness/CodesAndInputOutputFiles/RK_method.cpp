#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;
int main(){
    double h[30];
    double D = 0.024;
    double delP = -100;
    double mu = 0.001;
    double L=2;
    double r=0;
    double kd=0.005;
    double kd1=0.025;
    double kd2=0.05;
    double kd3=0.01;
    double r0=D*(0.5-kd);
    double yi1a[30];
    double yi1b[30];
    double yi1c[30];
    double yi1d[30]; 
    double yi=-delP*D*D*pow((0.5-kd),2)/(4*mu*L);
    ofstream o1a("da1a.txt");
    ofstream o1b("da1b.txt");
    ofstream o1c("da1c.txt");
    ofstream o1d("da1d.txt");
    ofstream oOrig("daOriginal.txt");
    for(int i=0; i<30;i++){
        if(i>=15){
            h[i]=((i-15)*r0)/15;
            yi1a[i]=yi+(1)*h[i]*h[i]*delP/(4*mu*L);
            o1a<<h[i]<<" "<<yi1a[i]<<endl;
            r0=D*(0.5-kd1);
            h[i]=((i-15)*r0)/15;
            yi=-delP*D*D*pow((0.5-kd1),2)/(4*mu*L);
            yi1b[i]=yi+(1)*h[i]*h[i]*delP/(4*mu*L);
            o1b<<h[i]<<" "<<yi1b[i]<<endl;
            r0=D*(0.5-kd2);
            h[i]=((i-15)*r0)/15;
            yi=-delP*D*D*pow((0.5-kd2),2)/(4*mu*L);
            yi1c[i]=yi+(1)*h[i]*h[i]*delP/(4*mu*L);
            o1c<<h[i]<<" "<<yi1c[i]<<endl;
            r0=D*(0.5-kd3);
            h[i]=((i-15)*r0)/15;
            yi=-delP*D*D*pow((0.5-kd3),2)/(4*mu*L);
            yi1d[i]=yi+(1)*h[i]*h[i]*delP/(4*mu*L);
            o1d<<h[i]<<" "<<yi1d[i]<<endl;
        }
              
    }
    delP=100;
    vector<double>v(15);
    for(int i=0;i<15;i++){
        r= i*D/30;
        v[i] = delP*(pow(r0,2)-(r*r))/(4*mu*L);
        oOrig<<r<<" "<<v[i]<<endl;
    }
    o1a.close();
    o1b.close();
    o1c.close();
    o1d.close();
    oOrig.close();
     
    string command1 = "gnuplot -persist -e \""
    "set xlabel 'h(RK-Classic 4 Method)';"
    "set ylabel 'Vz';"
    "plot 'da1a.txt' with linespoints lc rgb 'red' title 'k/D = 0.005',"
    " 'da1b.txt' with linespoints lc rgb 'blue' title 'k/D = 0.025',"
    " 'da1c.txt' with linespoints lc rgb 'green' title 'k/D = 0.05',"
    " 'daOriginal.txt' with linespoints lc rgb 'black' title 'k/D = 0.05',"
    " 'da1d.txt' with linespoints lc rgb 'cyan' title 'k/D = 0.01'\"";
    system(command1.c_str());

    return 0;
}