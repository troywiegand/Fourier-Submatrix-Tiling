#include <iostream>
#include <complex>
using namespace std;


int main() {

    double N=2;

double **F=new double**[N][N];

    double j,k;
    const double pi = acos(-1);
    const std::complex<double> i(0, 1);

    for(j=0; j<N; j++)
        for(k=0; k<N; k++)
            F[j][k]= exp(i*pi*j*k/N)


cout<<"This is the first entry: "<<F[0][0]<<endl;

    return 0;
}

