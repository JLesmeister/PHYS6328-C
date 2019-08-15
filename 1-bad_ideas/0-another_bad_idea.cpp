#include <iostream>
using namespace std;

//goal:  Show buffer overflow in array
// remove returns sequentially from top to bottom to proceed.

double v[10];  //this is a vector of 10 elements

int main(){

	for(int i=0;i<10;i++){
		v[i]=(double)i;
	}
	//initialize the array
	
	
	for(int i=0;i<10;i++){
		cout<<v[i]<<" ";
	}
	cout<<"\n\n";
	//print the list of values
	
	//return 0;
	
	
	
	
	
	for(int i=0;i<=10;i++){
		cout<<v[i]<<" ";
	}
	cout<<"\n\n";
	//accidcentally overflow the buffer by 1
	
	//return 0;
	
	
	
	
	
	int i=0;
	while(true){
		cout<<i<<","<<v[i]<<"\n";
		i+=1;
	}
	//overflow the buffer badly.
	
	return 0;
}
