#include <iostream>
#include <fstream>
#include <random>
#include <math.h>
using namespace std;





#define kT 4.1				//room temperature, kT in pN nm
#define zeta 20		  		//friction coefficient in pN us / nm.
#define dt 0.02				//timestep in us
#define m 0.21				//mass in pg



#define nstep 10000



//#define OVERDAMPED




#ifdef OVERDAMPED
double brownianVariance=sqrt(2*kT*dt/zeta);
double brownianFactor=dt/zeta;
int ranseed=2;
#else
#define FULLLANGEVIN
double langevinVariance=sqrt(2*kT*zeta/dt);
double langevinFactor1=(1-zeta*dt/2/m)/(1+zeta*dt/2/m);
double langevinFactor2=dt*dt/m/(1+zeta*dt/2/m);
int ranseed=1;
#endif



mt19937 rgen (ranseed);
//initialize the generator
uniform_real_distribution<double> uran (0.0, 1.0);
//uniform distribution between 0 and 1
normal_distribution<double> gran (0.0,1.0);
//normal distribution with 0 mean and 1 variance.
//to get a uniform number between 0 and 1, use uran(rgen);
//to get a normally distributed number, use gran(rgen)
