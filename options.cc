/********************************************************************************************************
*
* FILENAME :
*     options.cc
*
* DESCRIPTION :
*     Monte Carlo option pricing models for the  Vanilla European,
*     Arithmetic Asian and Geometric Asian options. 
*
* PUBLIC MEMBER FUNCTIONS :
*     double getPrice() const
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

#include "options.h"


Option::Option(double K, const PayOff* payOff, PricePath* pricePath, int nPaths)
: _K(K),
  _payOff(payOff),
  _pricePath(pricePath),
  _nPaths(nPaths) {
}

Option::~Option() {
}

VanillaEuroOption::VanillaEuroOption(double K, const PayOff* payOff, PricePath* pricePath, int nPaths)
: Option(K, payOff, pricePath, nPaths) {
}

VanillaEuroOption::~VanillaEuroOption() {
}

double VanillaEuroOption::getPrice() const {
    double payOffSum = 0.0; 
    for (int i = 0; i < _nPaths; ++i) {
        _pricePath->generatePrices();
        payOffSum += (*_payOff)(_pricePath->_prices[_pricePath->_nSteps], _K);    
    }
    payOffSum /= static_cast<double>(_nPaths);
    return payOffSum*exp(-_pricePath->_r*_pricePath->_nSteps*_pricePath->_dt);
}

ArithmeticAsianOption::ArithmeticAsianOption(double K, const PayOff* payOff, PricePath* pricePath, int nPaths)
: Option(K, payOff, pricePath, nPaths) {
}

ArithmeticAsianOption::~ArithmeticAsianOption() {
}

double ArithmeticAsianOption::getPrice() const {
   double payOffSum = 0.0;
   for (int i = 0; i < _nPaths; ++i) {
       _pricePath->generatePrices();
       double meanPrice = std::accumulate(_pricePath->_prices.begin(), _pricePath->_prices.end(), 0.0);
       meanPrice /= static_cast<double>(_pricePath->_prices.size());
       payOffSum += (*_payOff)(meanPrice, _K);
   }
   payOffSum /= static_cast<double>(_nPaths);
   return payOffSum*exp(-_pricePath->_r*_pricePath->_nSteps*_pricePath->_dt); 
}

GeometricAsianOption::GeometricAsianOption(double K, const PayOff* payOff, PricePath* pricePath, int nPaths)
: Option(K, payOff, pricePath, nPaths) {
}

GeometricAsianOption::~GeometricAsianOption() {
}

double GeometricAsianOption::getPrice() const {
   double payOffSum = 0.0;
   for (int i = 0; i < _nPaths; ++i) {
       _pricePath->generatePrices();
       double geomMeanPrice = 0.0; 
       for (size_t j = 0; j < _pricePath->_prices.size(); ++j) {
           geomMeanPrice += log(_pricePath->_prices[j]);
       } 
       geomMeanPrice = exp(geomMeanPrice/static_cast<double>(_pricePath->_prices.size()));
       payOffSum += (*_payOff)(geomMeanPrice, _K);
   }
   payOffSum /= static_cast<double>(_nPaths);
   return payOffSum*exp(-_pricePath->_r*_pricePath->_nSteps*_pricePath->_dt);
}
