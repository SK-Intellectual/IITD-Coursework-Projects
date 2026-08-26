#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x){
    double fx;
    fx=x-pow(2.7182818284590,x)/3;
    return fx;
}
double fprime(double k){
    double fp;
    fp=1-pow(2.7182818284590,k)/3;
    return fp;
}
double g(double y){
    double gx;
    gx =pow(2.7182818284590,y)/3;
    return gx;
}

int main() {
    FILE *outputFile = fopen("outputtut4.txt", "w");
    double xl=0;
    double xr=1;
    double xi;
    while(fabs(xl-xr)>0.0001){
        xi=(xl+xr)/2;
        if(f(xl)*f(xi)<0){
            xr=xi;
        }else{
            xl=xi;
        }
    }
    fprintf(outputFile,"The roots of the function by the Bisection method\n");
    fprintf(outputFile,"%lf\n",xl);
    xl=1;
    xr=2;
    while(fabs(xl-xr)>0.0001){
        xi=(xl+xr)/2;
        if(f(xl)*f(xi)<0){
            xr=xi;
        }else{
            xl=xi;
        }
    }
    fprintf(outputFile,"%lf\n",xl);
    
    xl=0;
    xr=1;
    xi=1;
    while(fabs(f(xi))>0.0001){
        xi= xl-(f(xl)*(xr-xl)/(f(xr)-f(xl)));
        if(f(xl)*f(xi)<0){
            xr=xi;
        }else{
            xl=xi;
        }
    }
    fprintf(outputFile,"The roots of the function by the Regula Falsi method\n");
    fprintf(outputFile,"%lf\n",xi);

    xl=1;
    xr=2;
    xi=1;
    while(fabs(f(xi))>0.0001){
        xi= xl-(f(xl)*(xr-xl)/(f(xr)-f(xl)));
        if(f(xl)*f(xi)<0){
            xr=xi;
        }else{
            xl=xi;
        }
    }
    fprintf(outputFile,"%lf\n",xi);

    double x0=1;
    double x1=2;
    xi=1.16861534;
    double xi1;
    double temp=1.16861534;
    while(fabs(xi1-xi)>0.0001){
        xi=temp;
        xi1= xi-(f(xi)*(xi-x1)/(f(xi)-f(x1)));
        x1=xi;
        temp=xi1;
    }
    fprintf(outputFile,"The roots of the function by the Secant method\n");
    fprintf(outputFile,"%lf\n",xi1);

    x0=0;
    x1=1;
    xi=0.78019663;
    temp=0.78019663;
    while(fabs(xi1-xi)>0.0001){
        xi=temp;
        xi1= xi-(f(xi)*(xi-x1)/(f(xi)-f(x1)));
        x1=xi;
        temp=xi1;
    }
    fprintf(outputFile,"%lf\n",xi1);
    
    xi=1;
    temp=1;
    while(fabs(xi1-xi)>0.0001){
        xi=temp;
        xi1= g(xi);
        temp=xi1;
    }
    fprintf(outputFile,"The roots of the function by the Fixed Point Iteration method\n");
    fprintf(outputFile,"%lf\n",xi1);

    xi=1;
    temp=1;
    while(fabs(xi1-xi)>0.0001){
        xi=temp;
        xi1= log(3*xi);
        temp=xi1;
    }
    fprintf(outputFile,"%lf\n",xi1);

    xi=2;
    temp=2;
    while(fabs(xi1-xi)>0.0001){
        xi=temp;
        xi1= xi-(f(xi)/fprime(xi));
        temp=xi1;
    }
    fprintf(outputFile,"The roots of the function by the Newton Raphson method\n");
    fprintf(outputFile,"%lf\n",xi1);

    xi=0;
    temp=0;
    while(fabs(xi1-xi)>0.0001){
        xi=temp;
        xi1= xi-(f(xi)/fprime(xi));
        temp=xi1;
    }
    fprintf(outputFile,"%lf\n",xi1);

    fclose(outputFile);

    return 0;
}