#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

double fder(double x){
    double a;
    a=1.1574074*0.00001*(-5*pow(x+0.125,4)+6*9*(x+0.125)*(x+0.125)-81);
    double b;
    b=1.1574074*0.00001*(-5*pow(x-0.125,4)+6*9*(x-0.125)*(x-0.125)-81);
    double ans = (a-b)/(0.25);
    return ans;
}
int main (){
    ofstream out("OutputTut10.txt");
    out << "Point                                  Deflection\n";
    double t=0;
    double V[25];
    V[0]=40.6901;
    V[24]=-148739;
    out << "0" << "                                     " << "0.0" << endl;
    double x[25];
    for (int i=0; i<25;i++){
        x[i]=i*0.125;
    }
    for (int i=0;i<23;i++){
        t+=0.125/6*(fx(x[i])+4*fx((x[i+1]+x[i])/2)+fx(x[i+1]));
        out << (i+1)*0.125 << "                                " << t << endl;
    }
    out << "3" << "                                     " << "0.0" << endl;
    out << "\n";
    out << "Point                                  Moment(N.m)\n";
    out << 0 << "                                " << 40.6901 << endl;
    for(int i=1;i<24;i++){
        out << i*0.125 << "                                " << 200*pow(10,9)*0.0003*fder(x[i]) << endl;
        V[i]=200*pow(10,9)*0.0003*fder(x[i]);
    }
    out << 3<< "                                " << -148739 << endl;
    out << "\n";
    out << "Point                                  Shear(N)\n"; 
    out << 3<< "                                " << 74728.7 << endl;  
    for(int i=1;i<24;i++){
        out << i*0.125 << "                                " << (-V[i-1]+V[i+1])/0.25 << endl;
    }
    out << 3<< "                                " << -276834 << endl;

    return 0;
}