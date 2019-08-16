#include <iostream>
using namespace std;

//goal:  Comment out the first break to show infinte loop and also overflow.

int main(){
	int i=0;
	while(true){
		if(i%10000000==0){
			cout<<i<<"\n";
		}
		i+=1;
		if(i>100){
			//break;
		}
	}
	
	return 0;
}
