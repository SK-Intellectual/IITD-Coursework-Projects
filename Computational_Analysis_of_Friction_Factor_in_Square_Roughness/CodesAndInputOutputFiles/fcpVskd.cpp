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
     ifstream in("termin.txt");
     for(int i=0;i<6;i++){
        in>>kd[i];
     }
     ofstream out("g11.txt");
     ofstream outa("g11a.txt");
     ofstream out1("g12.txt");
     ofstream out1a("g12a.txt");
     double ro = 1000;
     double re = 2000;
     double re1 =2000;
     double neu = 0.001;
     double D = 0.025;

     double L = 0.25;
     double delP = 100;
     double lw=2,w=0.000125;
     double lw1 = 6;
     double lwa1 = 8;
     double lwa = 4;
     double theta = 1.28;
     double theta11 = 1.15;
     double theta1 =1.2;
     double theta12 =1.1;
     double rel_correction_factor=-0.00553;
     
     for(int i=0;i<6;i++){
        
        double c1=1024*L*w*neu*(neu/(ro*delP*D*D*lw))*kd[i]*(1-kd[i])/(lw-1);
        double c1a=1024*L*w*neu*(neu/(ro*delP*D*D*lwa))*kd[i]*(1-kd[i])/(lwa-1);
        double c1p=1024*L*w*neu*(neu/(ro*delP*D*D*lw))*kd[i]*(1-kd[i])/(lw-1);
        double c1pa=1024*L*w*neu*(neu/(ro*delP*D*D*lwa))*kd[i]*(1-kd[i])/(lwa-1);
         
        double c2=pow(theta,i)*neu*neu*L*L/(1.05*w*D*D*D*ro*delP*(pow((0.5-kd[i]),3)));
        double c2a=pow(theta11,i)*neu*neu*L*L/(0.97*w*D*D*D*ro*delP*(pow((0.5-kd[i]),3))); 
        double c2p=pow(theta1,i)*neu*neu*L*L/(w*D*D*D*ro*delP*(pow((0.5-kd[i]),3)));
        double c2pa=pow(theta12,i)*neu*neu*L*L/(0.51*w*D*D*D*ro*delP*(pow((0.5-kd[i]),3))); 
        fp[i]=1+((re/64)*(c1+c2));
        fp1[i]=1+((re1/64)*(c1p+c2p));
        fpa[i]=1+((re/64)*(c1a+c2a));
        fp1a[i]=1+((re1/64)*(c1pa+c2pa));
         
        out<<kd[i]<<" "<<(fp[i])*(pow((1-(2*kd[i])),5))*(64/re)*(1+(0.0136*lw))<<endl;
        outa<<kd[i]<<" "<<(fpa[i])*(pow((1-(2*kd[i])),5))*(64/re)*(1+(0.0136*lwa1))<<endl;
        out1<<kd[i]<<" "<<fp1[i]*(pow((1-(2*kd[i])),5))*(64/re)*(1+(0.0136*lwa))<<endl;
        out1a<<kd[i]<<" "<<fp1a[i]*(pow((1-(2*kd[i])),5))*(64/re)*(1+(0.0136*lw1))<<endl;
     }
    string command1 = "gnuplot -persist -e \""
    "set xlabel 'k/D';"
    "set ylabel 'fcp/(64/Re)';"
    "plot 'g11.txt' with linespoints lc rgb 'black' title 'Re = 2000, lambda/w = 2',"
    " 'g11a.txt' with linespoints lc rgb 'blue' title 'Re = 2000, lambda/w = 6',"
    " 'g12a.txt' with linespoints lc rgb 'green' title 'Re = 2000, lambda/w = 8',"
    " 'g12.txt' with linespoints lc rgb 'red' title 'Re = 2000, lambda/w = 4'\"";
system(command1.c_str());


return 0;
}