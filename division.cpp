#include <iostream>
#include <math.h>
 
using namespace std;

double evalPolyDiv(int N[],int Ndeg, int D[], int Ddeg, int point);
 
// does:  prints all members of vector
// input: c - ASCII char with the name of the vector
//        d - degree of vector
//        A - pointer to vector
void Print(char c, int d, double* A) {
	int i;
 
	for (i=0; i < d+1; i++)
			cout << c << "[" << i << "]= " << A[i] << endl;
	cout << "Degree of " << c << ": " << d << endl << endl;
}

int main() {
		// vectors - N / D = q       N % D = r
	int dN, dD;	// degrees of vectors
	int i;					// iterators
 
// setting the degrees of vectors
	cout << "Enter the degree of N:";
	cin >> dN;
	cout << "Enter the degree of D:"; 
	cin >> dD;
 
 
// allocation and initialization of vectors
	int N[dN+1];					
	cout << "Enter the coefficients of N:"<<endl;  
	for ( i = 0; i < dN+1; i++ ) {
		cout << "N[" << i << "]= " << endl;
		cin >> N[i];
	}
 
	int D[dD+1];
	cout << "Enter the coefficients of D:"<<endl;	
	for ( i = 0; i < dD+1; i++ ) {
		cout << "D[" << i << "]= " << endl;
		cin >> D[i];
	}


bool alwaysZero=true;

for(int i=0; i<dN+2;i++){
   if(evalPolyDiv(N,dN+1,D,dD+1,i)!=0)
    alwaysZero=false;
}

if(alwaysZero)
    cout<<"always Zero"<<endl;

 

    return 0;
}

double evalPolyDiv(int N[],int Ndeg, int D[], int Ddeg, int point){
     int Neval=0;
    int Deval=0;

    for(int i=0; i<Ndeg; i++){
        Neval+=N[i]*pow(point,i);
    }

    for(int i=0; i<Ddeg; i++){
        Deval+=D[i]*pow(point,i);
    }

    cout<<"Neval"<<Neval<<endl;
    cout<<"Deval"<<Deval<<endl;

    return Neval%Deval;

}