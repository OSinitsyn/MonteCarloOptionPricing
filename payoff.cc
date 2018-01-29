/********************************************************************************************************
*
* FILENAME :
*     payoff.cc
*
* DESCRIPTION :
      Functors for the standard call and put pay-offs.

*     max(S - K, 0.0) - standard call
*     max(K - S, 0.0) - standard put
*
*     K - strike price
*     S - stock price
*     
* PUBLIC MEMBER FUNCTIONS :
*     double operator() (double S, double K) const;
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

#include "payoff.h"

PayOff::PayOff() {
}

PayOff::~PayOff() {
}

PayOffCall::PayOffCall() {
}

PayOffCall::~PayOffCall() {
}

double PayOffCall::operator() (double S, double K) const {
    return std::max(S - K, 0.0);
}

PayOffPut::PayOffPut() {
}

PayOffPut::~PayOffPut() {
}

double PayOffPut::operator() (double S, double K) const {
    return std::max(K - S, 0.0);
}

