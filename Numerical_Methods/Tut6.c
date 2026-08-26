#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    FILE *outputFile = fopen("outputTut6.txt", "w");

    double a0 = -4;
    double a1 = -4;
    double a2 = 1;
    double a3 = 1;
    double b0;
    double b1;
    double b2;
    double b3;
    double c1n;
    double c2n;
    double c3n;
    double r = 0;
    double s = 5;
    double rnew;
    double snew;
    double delr;
    double dels;
    double roots[3];
    double errr =1;
    double errs =1;
    int i =1;
    
    for(int i=0;i<3;i++){
        roots[i]=0;
    }

    while ((abs(errr)> pow(10,-5)) || (abs(errs)>pow(10,-5))){
        b3=a3;
        b2=a2+b3*r;
        b1=a1+b2*r+b3*s;
        b0=a0+b1*r+b2*s;
        c3n=b3;
        c2n=b2+c3n*r;
        c1n=b1+c2n*r+c3n*s;
        dels=(b1*c1n-b0*c2n)/(c2n*c2n-c1n*c3n);
        delr=(-1)*(b1+c3n*dels)/c2n;
        rnew=r+delr;
        snew=s+dels;
        errr = delr/r*100;
        errs = dels/s*100;
        r=rnew;
        s=snew;
        fprintf(outputFile,"Iteration : %d\n",i);
        fprintf(outputFile,"r : %lf\n",r);
        fprintf(outputFile,"s : %lf\n",s);
        fprintf(outputFile,"b3 : %lf\n",b3);
        fprintf(outputFile,"b2 : %lf\n",b2);
        fprintf(outputFile,"b1 : %lf\n",b1);
        fprintf(outputFile,"b0 : %lf\n",b0);
        fprintf(outputFile,"delr : %lf\n",delr);
        fprintf(outputFile,"dels : %lf\n",dels);
        fprintf(outputFile,"errs : %lf\n",errs);
        fprintf(outputFile,"errr : %lf\n",errr);
        i++;
    }
    fprintf(outputFile,"SOLUTIONS OF THE POLYNOMIAL 1 :\n");
    double D;
    roots[2] = -b2/b3;
    D=r*r+4*s;
    if(D>=0){
        roots[0]=(r+pow(D,0.5))/2;
        roots[1]=(r-pow(D,0.5))/2;
        for(int i=0;i<3;i++){
            if(roots[i]!=0){
                fprintf(outputFile,"%lf\n",roots[i]);
            }
        }
    }else{
        roots[0]=(r)/2;
        roots[1]=(r)/2;
        fprintf(outputFile,"%lf+%lfi\n%lf-%lfi\n%lf\n",roots[0],pow(abs(D),0.5)/2,roots[1],pow(abs(D),0.5)/2,roots[2]);
    }
    
    
    a0=-2;
    a1=4;
    a2=-0.5;
    a3=1;
    r= 0;
    s= 5;
    errr=1;
    errs=1;
    i=1;

    for(int i=0;i<3;i++){
        roots[i]=0;
    }

    while ((abs(errr)> pow(10,-5)) || (abs(errs)>pow(10,-5))){
        b3=a3;
        b2=a2+b3*r;
        b1=a1+b2*r+b3*s;
        b0=a0+b1*r+b2*s;
        c3n=b3;
        c2n=b2+c3n*r;
        c1n=b1+c2n*r+c3n*s;
        dels=(b1*c1n-b0*c2n)/(c2n*c2n-c1n*c3n);
        delr=(-1)*(b1+c3n*dels)/c2n;
        rnew=r+delr;
        snew=s+dels;
        errr = delr/r*100;
        errs = dels/s*100;
        r=rnew;
        s=snew;
        fprintf(outputFile,"Iteration : %d\n",i);
        fprintf(outputFile,"r : %lf\n",r);
        fprintf(outputFile,"s : %lf\n",s);
        fprintf(outputFile,"b3 : %lf\n",b3);
        fprintf(outputFile,"b2 : %lf\n",b2);
        fprintf(outputFile,"b1 : %lf\n",b1);
        fprintf(outputFile,"b0 : %lf\n",b0);
        fprintf(outputFile,"delr : %lf\n",delr);
        fprintf(outputFile,"dels : %lf\n",dels);
        fprintf(outputFile,"errs : %lf\n",errs);
        fprintf(outputFile,"errr : %lf\n",errr);
        i++;
    }
    fprintf(outputFile,"SOLUTIONS OF THE POLYNOMIAL 2 :\n");
    roots[2] = -b2/b3;
    D=r*r+4*s;
    if(D>=0){
        roots[0]=(r+pow(D,0.5))/2;
        roots[1]=(r-pow(D,0.5))/2;
        for(int i=0;i<3;i++){
            if(roots[i]!=0){
                fprintf(outputFile,"%lf\n",roots[i]);
            }
        }
    }else{
        roots[0]=(r)/2;
        roots[1]=(r)/2;
        fprintf(outputFile,"%lf+%lfi\n%lf-%lfi\n%lf\n",roots[0],pow(abs(D),0.5)/2,roots[1],pow(abs(D),0.5)/2,roots[2]);
    }
    

    return 0;
}