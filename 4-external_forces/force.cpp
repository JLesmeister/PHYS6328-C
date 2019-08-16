
#include "header.h"

double externalPotential(double x,double y);
void externalForce(double x,double y, double & fx,double & fy);
//this will compute the force on a two-dimensional particle.
#ifdef OVERDAMPED
void overdamped_integrator(double & x,double & y,double fx,double fy);
//this will update the position of the 2D particle assuming the particle is overdamped
#endif
#ifdef FULLLANGEVIN
void langevin_integrator(double & x,double & y,double & xold, double & yold,double fx,double fy);
//this will update the current and old locations assuming underdamped dynamics
#endif


int main(){
	
	double x0=0;
	double y0=0;
	//init position
#ifdef FULLLANGEVIN
	double xold=x0;
	double yold=y0;
	//previous position, only needed in the underdamped case
#endif
	double x=x0;
	double y=y0;
	//current position
	double fx=0;
	double fy=0;
	//forces set to zero
	
	ofstream outfile;  //file that we will print data to.
#ifdef OVERDAMPED
	outfile.open("trajectory_overdamped.txt");
#endif
#ifdef FULLLANGEVIN
	outfile.open("trajectory_langevin.txt");  
#endif

	for(int step=0;step<nstep;step++){
		externalForce(x,y,fx,fy);
		//update the current force
#ifdef OVERDAMPED
		overdamped_integrator(x,y,fx,fy);
#endif
#ifdef FULLLANGEVIN
		langevin_integrator(x,y,xold,yold,fx,fy);
#endif
		outfile<<((double)step)*dt<<","<<x<<","<<y<<"\n";
	}
	outfile.close();
	
	
	return 0;
}

double externalPotential(double x,double y){
	//the potential is r^4-10r^2, with r^2=x^2+y^2, a mexican hat potential.
	double rsq=x*x+y*y;
	return rsq*rsq-10*rsq;
}

void externalForce(double x,double y, double & fx,double & fy){
	//the force is -grad U.  dU/dx=-20 x+4x(x^2+y^2).  Similar for y.
	double rsq=x*x+y*y;
	fx=20*x-4*x*rsq;
	fy=20*y-4*y*rsq;
}

#ifdef OVERDAMPED
void overdamped_integrator(double & x,double & y,double fx,double fy){
	double Rx=gran(rgen)*brownianVariance;
	double Ry=gran(rgen)*brownianVariance;
	//these are the random forces.  a normal distributed random variable with variance 1,
	// times a precomputed factor for brownian motion.
	x+=Rx;
	y+=Ry;
	//update the position
	x+=fx*brownianFactor;
	y+=fy*brownianFactor;
	//these are updates due to the external forces.  brownianFactor is the precomputed dt/zeta.
}
#endif

#ifdef FULLLANGEVIN
void langevin_integrator(double & x,double & y,double & xold, double & yold,double fx,double fy){
	double Rx=gran(rgen)*langevinVariance;
	double Ry=gran(rgen)*langevinVariance;
	//these are the random forces.  a normal distributed random variable with variance 1,
	double xnew=x+(x-xold)*langevinFactor1+(fx+Rx)*langevinFactor2;
	double ynew=y+(y-yold)*langevinFactor1+(fy+Ry)*langevinFactor2;
	xold=x;
	yold=y;
	x=xnew;
	y=ynew;
}
#endif
