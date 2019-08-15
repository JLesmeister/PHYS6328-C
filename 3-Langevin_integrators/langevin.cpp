#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <math.h>

using namespace std;

mt19937 rgen (1);
//initialize the generator
uniform_real_distribution<double> uran (0.0, 1.0);
//uniform distribution between 0 and 1
normal_distribution<double> gran (0.0,1.0);
//normal distribution with 0 mean and 1 variance.

//to get a uniform number between 0 and 1, use uran(rgen);
//to get a normally distributed number, use gran(rgen)


#define kT 4.1				//room temperature, kT in pN nm
#define zeta 20		  		//friction coefficient in pN us / nm.
							//this is an approx value for a 1um sphere
							//in water.
#define m 0.21				//mass in pg of a polystyrene bead of radius 1um.

#define dt 0.02				//timestep in us.   This should be chosen to be
							//"small enough" as in the brownian case, but now
							//there is a requirement that zeta*dt/m is
							// "small enough".



#define nstep 1000  		//number of timesteps to simulate


double externalForce(double x);

int main(){
	
	
	double x0=0;			//initial position
	double x=x0;			//current position
	double xold=x0;			//position at previous timestep
	double xnew=x0;			//updated position

	
	
	ofstream outfile;
	outfile.open("trajectory_langevin.txt");
	for(int i=0;i<nstep;i++){
		double f=externalForce(x);
		//compute the external forces due to the current position
		double R=gran(rgen)*sqrt(2*zeta*kT/dt);
		//compute a random number with gaussian distribution.
		//The factor sqrt(2*\zeta*kT/dt) shifts the random number to have the
		//correct variance.
		
		xnew=x;  //start at new position
		xnew+=(x-xold)*(1-zeta*dt/2/m)/(1+zeta*dt/2/m); //update location based on velocity
		xnew+=(f+R)*dt*dt/m/(1+zeta*dt/2/m);  //update location based on forces
		
		xold=x;		//update the old location
		x=xnew;		//update the current location
		
		outfile<<((double)(i+1))*dt<<","<<(x-x0)*(x-x0)<<"\n";
	}
	outfile.close();
	
	
	return 0;
}

double externalForce(double x){
	return 0;
}
