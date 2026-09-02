 #include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
using namespace std;
int main() {
     vector<double>kd(6);
     vector<double>fp(6);
     vector<double>fp1(6);
     vector<double>fpa(6);
     vector<double>fp1a(6);
     vector<double>lw(9);
     ifstream in("terminlw.txt");
     for(int i=0;i<9;i++){
        in>>lw[i];
     }
     for(int i=0;i<2;i++){
        in>>kd[i];
     }
     ofstream out("g11.txt");
     ofstream outa("g11a.txt");

     double ro = 1000;
     double re = 200;
     double neu = 0.001;
     double D = 0.025;
     double L = 2;
     double delP = 100;
     double w=0.0004;
     double w1=0.000200;
     double theta = 1;
     double theta11 = 0.93;
     double rel_correction_factor=2e8;
     
     for(int i=0;i<7;i++){
        double c1=1024*L*w*neu*(neu/(ro*delP*D*D*lw[i]))*kd[0]*(1-kd[0])/(lw[i]-1)*rel_correction_factor;
        double c1a=1024*L*w1*neu*(neu/(ro*delP*D*D*lw[i]))*kd[1]*(1-kd[1])/(lw[i]-1)*rel_correction_factor;
        double c2=pow(theta,1)*neu*neu*L*L/(w*D*D*D*ro*delP*(pow((0.5-kd[0]),3)));
        double c2a=pow(theta11,i)*neu*neu*L*L/(w1*D*D*D*ro*delP*(pow((0.5-kd[1]),3)));
        fp[i]=1+((re/64)*(c1+c2));
        fpa[i]=1+((re/64)*(c1a+c2a));
       
        out<<pow(lw[i],1)<<" "<<fp[i]*(64/re)<<endl;
        outa<<pow(lw[i],1)<<" "<<fpa[i]*(64/re)<<endl;
     }
    string command1 = "gnuplot -persist -e \""
    "set xlabel 'Lamda/w';"
    "set ylabel 'f';"
    "plot 'g11.txt' with linespoints lc rgb 'black' title 'Re = 200, k/D = 0.04',"
    " 'g11a.txt' with linespoints lc rgb 'red' title 'Re = 200, k/D= 0.05'\"";
system(command1.c_str());


return 0;
}