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
*   void setS0(double S0) - set current stock price
*   void setSigma(double sigma) - set volatility of the stock price
*   void setRate(double r) - set risk-free rate
*   void setStep(double dt) - set time step
*   void setNSteps(int nSteps) - set number of time steps 
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
}

PricePath::~PricePath() {
}

void PricePath::seedGenerator(unsigned seed) {
    _gen.seed(seed);
}

void PricePath::setS0(double S0) {
    _S0 = S0;
    _prices.assign(_nSteps+1, 0.0);
}

void PricePath::setSigma(double sigma) {
    _sigma = sigma;
    _prices.assign(_nSteps+1, 0.0);
}

void PricePath::setRate(double r) {
    _r = r;
    _prices.assign(_nSteps+1, 0.0);
}

void PricePath::setStep(double dt) {
    _dt = dt;
    _prices.assign(_nSteps+1, 0.0);
}

void PricePath::setNSteps(int nSteps) {
    _nSteps = nSteps;
    _prices.resize(_nSteps+1, 0.0);
}

void PricePath::generatePrices() {
    _prices[0] = _S0;
    _p1 = exp((_r - 0.5*_sigma*_sigma)*_dt);
    _p2 = exp(_sigma*sqrt(_dt));
    for (size_t i = 1; i < _prices.size(); ++i) {
        _prices[i] = _prices[i-1]*_p1*pow(_p2, _nDist(_gen));
    }
}

const std::vector<double>& PricePath::getPrices() const {
    return _prices;
}






