//Isolated version of Polynomial Division Code

#include <iostream>
#include <math.h>

using namespace std;

// does:  prints all members of matrix
// input: c - ASCII char with the name of the matrix
//        d - degree of matrix
//        A - matrix
void Print(char c, int d, double A[]) {
	int i;

	for (i=0; i < d+1; i++)
			cout << c << "[" << i << "]= " << A[i];
	cout << "Degree of " << c << ": " << d << endl << endl;
}

int main() {
	int dN, dD, dd, dq, dr;	// degrees of matrices

// setting the degrees of matrices
	cout << "Enter the degree of N:";
	cin >> dN;
	cout << "Enter the degree of D:";
	cin >> dD;
	dq = dN-dD;
	dr = dN-dD;


// allocation and initialization of matrices
	 double N[dN+1];					
	cout << "Enter the coefficients of N:"<<endl;
	for (int i = 0; i < dN+1; i++ ) {
		cout << "N[" << i << "]= " << endl;
		cin >> N[i];
	}

	double D[dN+1];
	cout << "Enter the coefficients of D:"<<endl;	
	for (int i = 0; i < dD+1; i++ ) {
		cout << "D[" << i << "]= " << endl;
		cin >> D[i];
	}

	 double d[dN+1];
	for(int i = dD+1 ; i < dN+1; i++ ) {
		D[i] = 0;
	}

	double q[dq+1];
	for(int i = 0 ; i < dq + 1 ; i++ ) {
		q[i] = 0;
	}

	double r[dr+1];
	for(int i = 0 ; i < dr + 1 ; i++ ) {
		r[i] = 0;
	}

	if( dD < 0) {
		cout << "Degree of D is less than zero. Error!";
	}

	cout << "-- Procedure --" << endl << endl;
	if( dN >= dD ) {
		while(dN >= dD) {
// d equals D shifted right
			for( int i = 0 ; i < dN + 1 ; i++ ) {
				d[i] = 0;
			}
			for(int i = 0 ; i < dD + 1 ; i++ ) {
				d[i+dN-dD] = D[i];
			}
			dd = dN;

			Print( 'd', dd, d );

// calculating one element of q
			q[dN-dD] = N[dN]/d[dd];

			Print( 'q', dq, q );

// d equals d * q[dN-dD]
			for( int i = 0 ; i < dq + 1 ; i++ ) {
				d[i] = d[i] * q[dN-dD];
			}

			Print( 'd', dd, d );

// N equals N - d
			for(int i = 0 ; i < dN + 1 ; i++ ) {
				N[i] = N[i] - d[i];
			}
			dN--;
			for(int j=dN; j>-1; j--){
				if(N[j]!=0){
					dN=j;
					j=-1;
				}
			}

			Print( 'N', dN, N );
			cout << "-----------------------" << endl << endl;

		}

	}

// r equals N
	for(int i = 0 ; i < dN + 1 ; i++ ) {
		r[i] = N[i];
	}
	dr = dN;

	cout << "=========================" << endl << endl;
	cout << "-- Result --" << endl << endl;

	Print( 'q', dq, q );
	Print( 'r', dr, r );

}