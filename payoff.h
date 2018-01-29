/********************************************************************************************************
*
* FILENAME :
*     payoff.h
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


#ifndef PAYOFF_H_
#define PAYOFF_H_

#include <algorithm>

class PayOff {
protected:
public:
    PayOff();
    virtual ~PayOff();
    virtual double operator() (double S, double K) const = 0;
};

class PayOffCall : public PayOff {
public:
    PayOffCall();
    virtual ~PayOffCall();
    virtual double operator() (double S, double K) const;
};

class PayOffPut : public PayOff {
public:
    PayOffPut();
    virtual ~PayOffPut();
    virtual double operator() (double S, double K) const;
};

#endif // PAYOFF_H_
