#include<iostream>
#include<cmath>

double uniform() {return (double)rand()/(RAND_MAX);}
double getPoisson(double lambda)
{
    int t = 0;
    double p = exp(-lambda);
    double f = p;
    double u = uniform();
    while(true)
    {
        if(f > u)
            break;
        t++;
        p = p*lambda/t;
        f+=p;
    }
    return t;
}
double getExponential(double lambda)
{
    return -log(1 - uniform()) /lambda;
}