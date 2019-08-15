#include <iostream>
#include <random>
#include <chrono>

using namespace std;

#define N 50  //size of the matrix.
#define m 20  //power of matrix to compute





void createMatrices(double oldMatrix[N][N],double newMatrix[N][N],double tempMatrix[N][N]);
void simpleMultiply(double oldMatrix[N][N],double newMatrix[N][N],double tempMatrix[N][N]);
//this function multiplies the two matrices rasonably quickly.  This is not a theoretical
//optimum, but is "good enough" for an example.  There are MANY ways to improve on
//this algorithm.



//we will need a random number generator for this.  We define it globally, so that it is
//easily shared amongst functions.

//  Random number generators are determininistic.  We must supply them with a SEED.
 // Once the generator is seeded, the future sequence will be determined.  Random number
 // generators produce real numbers uniformly distributed over [0,1]

mt19937 rgen (1);
//if you are doing a stochastic simulation (eventually you will), you need
//to change the seed for each simulation (otherwise, you'd get the same
//set of random numbers.  One way to do that is to use:
/*
 mt19937 mersenne(random_device{}());
 */
//  This asks your computer for a random inital seed, so every simulation will be different.

uniform_real_distribution<double> uran (0.0, 1.0);
//this creates a uniform random distribution.  To get a random number uniformly distributed
//between zero and 1, call uran(rgen).

int main(){
	

	
	
	

	
	
	
	
	double oldMatrix[N][N]; //this will be where we store the matrix we want to multiply
	double newMatrix[N][N]; //this will be where we store oldMatrix raised to a power
	double tempMatrix[N][N];// this is stracthspace, where we temporarily store values.

	/* to multiply matrices, we need to generate the old matrix.
	 oldMatrix^0 = IdentityMatrix, which is what we store in newMatrix
	 tempMatrix should be all 0's, since this is scratch space.
	 */
	createMatrices(oldMatrix,newMatrix,tempMatrix);
	
	
	
	
	
	//do a sanity check.  Do we have elements that "look" reasonable (e.g. aren't
	// negative, aren't huge, aren't zero)?
	cout<<"a few of the initial elements are :\n";
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			cout<<oldMatrix[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n";
	
	
	cout<<"\nHit any key\n";
	getchar();
	//this pauses until the user hits a key.

	/*  It's helpful to know how long the program took.  The program starts by checking
	 on the current time, stored as t0.  At the end of the program, we'll check the time
	 again (called tf at the end) to determine the difference.*/

	auto t0=chrono::steady_clock::now();  //store the current time
	
	
	
	
	
	/*to perform the matrix power, we'll multiply the matrix by itself m times.
	 This uses the fact that matrix^m = matrix . matrix^(m-1)
	 so we compute
	 newmat=oldmat . newmat  //newmat is now the same as oldmat
	 newmat=oldmat . newmat  //newmat is now oldmat^2
	 newmat=oldmat . newmat // newmat is now oldmat^3
	 ...
	 */
	
	for(int iter=0;iter<m;iter++){  //iterate over values from 1 to m
		simpleMultiply(oldMatrix,newMatrix,tempMatrix);
		//perform the multiplication using our function.
	}
	
	
	
	auto tf=chrono::steady_clock::now();//compute the final time.

	//dealing with time is often annoying in C++.  The code below computes the
	//time difference in microseconds.  This is the sort of thing the web is
	//very helpful in doing, as the commands aren't particularly obvious.
	auto timediff=chrono::duration_cast<chrono::microseconds>(tf-t0);
	cout<<"program took "<<((double)(timediff.count()))/1000<<" ms\n";  //print the time it took
	
	
	//do a santity check:  are do the product elelements "look" reasonable?
	cout<<"a few of the elements are :\n";
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			cout<<newMatrix[i][j]<<" ";
		}
		cout<<"\n";
	}

	
	//note:  I've not deleted the matrices at the end here.  These are static, and
	// do not need to be deleted.  The memory associated
	//with those matricies is allocated until the program ends.
	// since the program is ending here, this is not a problem.
	
	
	
	return 0;


	
}


void createMatrices(double oldMatrix[N][N],double newMatrix[N][N],double tempMatrix[N][N]){
	
	
	// first, we must define the matrix to multiply.  We will choose a
	//random matrix whose rows sum to 1 (it turns out, this will ensure
	//convergence.
	for(int i=0;i<N;i++){
		//for each row
		double tmp=0;
		//define the row sum
		for(int j=0;j<N;j++){
			//for each column
			oldMatrix[i][j]=uran(rgen);
			//put a random number for M_{ij}.
			tmp+=oldMatrix[i][j];
			//update the row sum
		}
		for(int j=0;j<N;j++){
			oldMatrix[i][j]/=tmp;
			//divide all columns in this row by the row sum
		}
	}
	//we're done.  the original matrix (oldMatrix) M_{ij} is random, whose
	//rows sum to 1.
	
	
	//initialize M^0.  This one is easy: it's the identity matrix
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(i==j){
				newMatrix[i][j]=1;
				//1's on the diagonal
			}
			else{
				newMatrix[i][j]=0;
				//0's otherwise
			}
		}
	}
	
	//initialize the scratch space to be zero.  This is, in fact, an unnecessary step
	//but it is always safer to initialize everything to zero.
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			tempMatrix[i][j]=0;
		}
	}
	
}

void simpleMultiply(double oldMatrix[N][N],double newMatrix[N][N],double tempMatrix[N][N]){
	//this is the most basic way to approach matrix multiplication:  just do it the
	// way one would on paper.  We are going to store the values in the
	
	for(int i=0;i<N;i++){			//for every matrix element i,j
		for(int j=0;j<N;j++){
			tempMatrix[i][j]=0;		//clear the temp matrix value
			for(int k=0;k<N;k++){	//looping over interior indices
				tempMatrix[i][j]+=oldMatrix[i][k]*newMatrix[k][j];  //compute the matrix product
			}
		}
	}
	
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			newMatrix[i][j]=tempMatrix[i][j];  //save the matrix product in newMatrix
		}
	}
	
	
}
