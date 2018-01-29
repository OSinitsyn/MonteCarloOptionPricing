/********************************************************************************************************
*
* FILENAME : 
*     pricepath.h 
*
* DESCRIPTION :
*     Stock price path generation. The prices are
*     modeled via Geometric Brownian Motion.
*
*     S(t) = S(0)*exp((r - 0.5*sigma^2)*dt + sigma*sqrt(dt)*N(0,1))
*
*     S0 - current stock price
*     sigma - volatility of the stock price 
*     r - risk-free rate
*     dt - time step
*     nSteps - number of time steps
*     N(0, 1) - the standard normal
*
* PUBLIC MEMBER FUNCTIONS :
*   void seedGenerator(unsigned seed)  - seed the random number generator 
*   void generatePrices()  -  generate stock prices for the given set of parameters 
*   const std::vector<double>& getPrices() const  -  return const reference to the generated price vector
*
* NOTES :
*
* AUTHOR : Oleksandr Sinitsyn
*
* START DATE : 20 Jan 2018
*
* CHANGES :
*
**********************************************************************************************************/

#ifndef PRICEPATH_H_
#define PRICEPATH_H_

#include <vector>
#include <cmath>
#include <random>

class PricePath {
 friend class VanillaEuroOption;
 friend class ArithmeticAsianOption;
 friend class GeometricAsianOption;
    double _S0;
    double _sigma;
    double _r;
    double _dt;
    int _nSteps;
    std::default_random_engine _gen;
    std::normal_distribution<double> _nDist;
    std::vector<double> _prices;
    double _p1;
    double _p2;
    PricePath(const PricePath&);
    PricePath& operator=(const PricePath&);
 public:
    PricePath(double S0, double sigma, double r, double dt, int nSteps);
    ~PricePath();
    void seedGenerator(unsigned seed);
    void generatePrices();
    const std::vector<double>& getPrices() const;
};

#endif // PRICEPATH_H_
