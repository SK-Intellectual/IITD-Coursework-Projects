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
     vector<double>re(7);
     ifstream in1("terminRe.txt");
     for(int i=0;i<7;i++){
        in1>>re[i];
     }
     for(int i=0;i<4;i++){
        in1>>kd[i];
     }
     ofstream out("g11.txt");
     ofstream outa("g11a.txt");
     ofstream out1("g12.txt");
     ofstream out1a("g12a.txt");
     double ro = 1000;
     double neu = 0.001;
     double D = 0.05;
     double L = 0.25;
     double delP = 100;
     double lw=2,w=0.000125;
     double lwa = 2;
     double theta = 1.2;
     double theta11 = 1.13;
     double theta1 =1.2;
     double theta12 =1.1;
     double rel_correction_factor=0.5;
     double rel_corection_factor=0.56;
     double rel_corection_factr=0.64;
     double rel_correction_factr=0.52;
   
     for(int i=0;i<7;i++){
        double c1=1024*L*w*neu*(neu/(ro*delP*D*D*lw))*kd[i]*(1-kd[0])/(lw-1);
        double c1a=1024*L*w*neu*(neu/(ro*delP*D*D*lwa))*kd[i]*(1-kd[2])/(lwa-1);
        double c1p=1024*L*w*neu*(neu/(ro*delP*D*D*lw))*kd[i]*(1-kd[1])/(lw-1);
        double c1pa=1024*L*w*neu*(neu/(ro*delP*D*D*lwa))*kd[i]*(1-kd[3])/(lwa-1);
         
        double c2=pow(theta,i)*neu*neu*L*L/(w*D*D*D*ro*delP*(pow((0.5-kd[0]),3)));
        double c2a=pow(theta11,i)*neu*neu*L*L/(0.98*w*D*D*D*ro*delP*(pow((0.5-kd[2]),3))); 
        double c2p=pow(theta1,i)*neu*neu*L*L/(w*D*D*D*ro*delP*(pow((0.5-kd[1]),3)));
        double c2pa=pow(theta12,i)*neu*neu*L*L/(0.98*w*D*D*D*ro*delP*(pow((0.5-kd[3]),3))); 
        fp[i]=1+((re[i]/64)*(c1+c2));
        fp1[i]=1+((re[i]/64)*(c1p+c2p));
        fpa[i]=1+((re[i]/64)*(c1a+c2a));
        fp1a[i]=1+((re[i]/64)*(c1pa+c2pa));
       
        out<<pow(re[i],-1)<<" "<<(fp[i]+rel_correction_factor)*(64/re[i])<<endl;
        outa<<pow(re[i],-1)<<" "<<(fpa[i]+rel_corection_factor)*(64/re[i])<<endl;
        out1<<pow(re[i],-1)<<" "<<(fp1[i]+rel_correction_factr)*(64/re[i])<<endl;
        out1a<<pow(re[i],-1)<<" "<<(fp1a[i]+rel_corection_factr)*(64/re[i])<<endl;
     }
    string command1 = "gnuplot -persist -e \""
    "set xlabel '1/Re';"
    "set ylabel 'f';"
    "plot 'g11.txt' with linespoints lc rgb 'black' title 'k/D = 0.005, lambda/w = 2',"
    " 'g11a.txt' with linespoints lc rgb 'blue' title 'k/D = 0.025, lambda/w = 2',"
    " 'g12a.txt' with linespoints lc rgb 'green' title 'k/D = 0.05 , lambda/w = 2',"
    " 'g12.txt' with linespoints lc rgb 'red' title 'k/D = 0.01, lambda/w = 2'\"";
system(command1.c_str());


return 0;
}