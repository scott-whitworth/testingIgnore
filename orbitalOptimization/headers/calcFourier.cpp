#include "calcFourier.h"
#include <math.h> // used for sine and cosine functions
#include <iostream> // used for cout

template <class T> T calc_Series(T series[], const int series_size, const T & curTime, const T & timeFinal){
    T coeff = series[0];

    for(int i=1;i<=(series_size-1)/2;i++){
        coeff+=series[2*i-1]*cos(i*curTime/timeFinal)+series[2*i]*sin(i*curTime/timeFinal);
    }
    return coeff;
}

template <class T> T calc_gamma(coefficients<T> & coeff,const T & curTime, const T & timeFinal){
   return calc_Series(coeff.gamma, coeff.gammaSize, curTime, timeFinal);
}

template <class T> T calc_tau(coefficients<T> & coeff, const T & curTime, const T & timeFinal){
    return calc_Series(coeff.tau, coeff.tauSize, curTime, timeFinal);
}

template <class T> T calc_coast(coefficients<T> & coeff, const T & curTime, const T & timeFinal)
{
    // Use the fourier series for the coasting coefficients, then take the cos^2(coasting)
    T coastValue = pow(cos(calc_Series(coeff.coast, coeff.coastSize, curTime, timeFinal)),2);
    // if it is above the optimized threshold we return one for not coasting
    if(coastValue>=coeff.coastThreshold){
        return 1.0;
    }
    // otherwise 0
    else{
        return 0.0;
    }
}