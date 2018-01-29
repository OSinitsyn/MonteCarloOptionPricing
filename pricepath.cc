/********************************************************************************************************
*
* FILENAME : 
*     pricepath.cc 
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

#include "pricepath.h"

PricePath::PricePath(double S0, double sigma, double r, double dt, int nSteps)
: _S0(S0),
  _sigma(sigma),
  _r(r),
  _dt(dt),
  _nSteps(nSteps),
  _nDist(0.0, 1.0),
  _prices(nSteps+1, 0.0) {
    _p1 = exp((r - 0.5*sigma*sigma)*dt);
    _p2 = exp(sigma*sqrt(dt));
}

PricePath::~PricePath() {
}

void PricePath::seedGenerator(unsigned seed) {
    _gen.seed(seed);
}

void PricePath::generatePrices() {
    _prices[0] = _S0;
    for (size_t i = 1; i < _prices.size(); ++i) {
        _prices[i] = _prices[i-1]*_p1*pow(_p2, _nDist(_gen));
    }
}

const std::vector<double>& PricePath::getPrices() const {
    return _prices;
}






