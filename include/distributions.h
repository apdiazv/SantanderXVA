//
// DESCRIPTION Statistical Distributions
//

#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H

#define TOL 10e-10

//static boost::random::mt19937 gen;

double cumNormalDist(double x);  //cumulative Normal Distribution
double invCumNormalDist(double u); //inverse Cumulative Normal Distribution
double uniforme(); //return a number between 0 and 1 
double uniforme(boost::random::mt19937 &gen); //return a number between 0 and 1 
double gauss ();//generate z, where z has distribution N(0,1)
double gauss (boost::random::mt19937 &gen);//generate z, where z has distribution N(0,1)

#endif