#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
using namespace std;
int main() {
     int n=21;
     vector<double>kd(n);
     vector<double>fp(n);
     vector<double>fp1(n);
     vector<double>fpa(n);
     vector<double>fp1a(n);
     ifstream in("termin.txt");
     for(int i=0;i<n;i++){
        in>>kd[i];
     }
     ofstream out("g11fvskd.txt");
     ofstream outa("g11afvskd.txt");
     ofstream out1("g12fvskd.txt");
     ofstream out1a("g12afvskd.txt");
     double ro = 1000;
     double re = 2000;
     double re1 = 1200;
     double neu = 0.001;
     double D = 0.025;
     double L = 0.25;
     double delP = 100;
     double lw=2,w=0.000125;
     double lwa = 4;
     double theta = 1.2;
     double theta11 = 1.13;
     double theta1 =1.2;
     double theta12 =1.1;
     double rel_correction_factor=-0.00553;
     
     for(int i=0;i<n;i++){
        double c1=1024*L*w*neu*(neu/(ro*delP*D*D*lw))*kd[i]*(1-kd[i])/(lw-1);
        double c1a=1024*L*w*neu*(neu/(ro*delP*D*D*lwa))*kd[i]*(1-kd[i])/(lwa-1);
        double c1p=1024*L*w*neu*(neu/(ro*delP*D*D*lw))*kd[i]*(1-kd[i])/(lw-1);
        double c1pa=1024*L*w*neu*(neu/(ro*delP*D*D*lwa))*kd[i]*(1-kd[i])/(lwa-1);
         
        double c2=pow(theta,i)*neu*neu*L*L/(w*D*D*D*ro*delP*(pow((0.5-kd[i]),3)));
        double c2a=pow(theta11,i)*neu*neu*L*L/(0.98*w*D*D*D*ro*delP*(pow((0.5-kd[i]),3))); 
        double c2p=pow(theta1,i)*neu*neu*L*L/(w*D*D*D*ro*delP*(pow((0.5-kd[i]),3)));
        double c2pa=pow(theta12,i)*neu*neu*L*L/(0.98*w*D*D*D*ro*delP*(pow((0.5-kd[i]),3))); 
        fp[i]=1+((re/64)*(c1+c2));
        fp1[i]=1+((re1/64)*(c1p+c2p));
        fpa[i]=1+((re/64)*(c1a+c2a));
        fp1a[i]=1+((re1/64)*(c1pa+c2pa));
       
        out<<pow(kd[i],1)<<" "<<(fp[i]+rel_correction_factor)<<endl;
        outa<<pow(kd[i],1)<<" "<<(fpa[i]+rel_correction_factor)<<endl;
        out1<<pow(kd[i],1)<<" "<<fp1[i]<<endl;
        out1a<<pow(kd[i],1)<<" "<<fp1a[i]<<endl;
     }
    string command1 = "gnuplot -persist -e \""
    "set xlabel 'k/D';"
    "set ylabel 'f/(64/Re)';"
    "plot 'g11fvskd.txt' with linespoints lc rgb 'red' title 'Re = 2000, lambda/w = 2',"
    " 'g11afvskd.txt' with linespoints lc rgb 'blue' title 'Re = 2000, lambda/w = 4',"
    " 'g12afvskd.txt' with linespoints lc rgb 'blue' title 'Re = 1200, lambda/w = 4',"
    " 'g12fvskd.txt' with linespoints lc rgb 'red' title 'Re = 1200, lambda/w = 2'\"";
    system(command1.c_str());


return 0;
}