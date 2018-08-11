#include <iostream>
#include <complex>
#include <'Matrix.h'>
using namespace std;

Matrix createFourierOfSize(double N);

int main() {

Matrix F = createFourierOfSize(2);

cout<<"This is the first entry: "<<F[0][0]<<endl;

    return 0;
}

Matrix createFourierOfSize(double N) {
    Matrix Fourier [N][N];
    int j,k;
    const double pi = std::acos(-1);
    const std::complex<double> i(0, 1);

    for(j=0; j<N; j++)
        for(k=0; k<N; k++)
            Fourier[j][k]=std::exp(i*pi*j*k/N)


return Fourier;
}