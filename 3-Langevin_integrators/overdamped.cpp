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
#define zeta 20		  	//friction coefficient in pN us / nm.
							//this is an approx value for a 1um sphere
							//in water.

#define dt 0.02				//choose a us timescale.  This should be chosen to be
							//"small enough" that the particle does not move "too far"
							//in one timestep, where "too far" means the external forces
							//become very large.  Without an external force,
							//any value of dt is just as good as any other.



#define nstep 1000  		//number of timesteps to simulate

double externalForce(double x);

int main(){
	
	ofstream outfile;  //this declares a file that we will print data to.
	outfile.open("trajectory_overdamped.txt");  //this opens the file with a particular name.

	double x0=0; //this is the particle's initial position.
	double x=x0;  //this is the partcle's current position in one dimension.
	double t=0;
	for(int i=0;i<nstep;i++){
		double f=externalForce(x);
		//compute the force on the particle.  In this simulation,
		//there is no external force, but you can easily add one.
		x+=f/zeta*dt;
		//this is the new position of the particle.

		
		//for an overdamped simulation, we have
		// x(t)=x(0)+\sqrt(2kT t/zeta) * R(0)
		// with R(0) randomly distributed with unit variance.
		x+=sqrt(2*kT*dt/zeta)*gran(rgen);
		//this is our updated position given that rule

		t=((double)(i+1))*dt;
		//update the time.
		outfile<<t<<","<<(x-x0)*(x-x0)<<"\n";
		//store the data for (x-x0)^2 for this trajectory.
		//Recall that we expect <(x-x0)^2>=2Dt
	}
	outfile.close();
	
	

	
	
	return 0;
}



double externalForce(double x){
	return 0;
}
