#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

int main (){
    ofstream out("OutputTut8Q1.txt");
    ifstream in("InputTut8Q1.txt");
    int n;
    in >> n;
    
    double a0,a1;
    double c[n],k[n],c2[n],kinv[n],c2sum,kinvsum,c2sqsum,c2kinvsum;
    c2sqsum=0;
    c2sum=0;
    kinvsum=0;
    c2kinvsum=0;
    for(int i=0;i<n;i++){
        in >> c[i];
        in >> k[i];
    }

    for (int i=0;i<n;i++){
        c2[i]=1/(pow(c[i],2));
        kinv[i]=1/k[i];
    }
    
    for (int i=0;i<n;i++){
        c2sum+=c2[i];
        kinvsum+=kinv[i];
        c2sqsum+=c2[i]*c2[i];
        c2kinvsum+=c2[i]*kinv[i];
    }
    a1=(n*c2kinvsum-c2sum*kinvsum)/(n*c2sqsum-pow(c2sum,2));
    a0=kinvsum/n-(c2sum/n)*a1;

    double cs,kmax;
    kmax=1/a0;
    cs=a1*kmax;
    out << "Value of cs : " << cs << " and Kmax : " << kmax << endl;
    out << "Growth rate at c=2mg/L : " << (kmax*4)/(cs+4);


    return 0;
}