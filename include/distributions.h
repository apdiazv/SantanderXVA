//
// DESCRIPTION Statistical Distributions
//

#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H

#define TOL 10e-10

double cumNormalDist(double x); // cumulative Normal Distribution
double invCumNormalDist(double u); //inverse Cumulative Normal Distribution
double uniforme(); //return a number between 0 and 1 
double gauss ();//generate z, where z has distribution N(0,1)

#endif