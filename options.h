/********************************************************************************************************
*
* FILENAME :
*     options.h
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

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <numeric>
#include "pricepath.h"
#include "payoff.h"

class Option {
protected:
    double _K;
    const PayOff* _payOff;
    PricePath* _pricePath;
    int _nPaths;
public:
    Option(double K, const PayOff* payOff, PricePath* pricePath, int nPaths);
    virtual ~Option();
    virtual double getPrice() const = 0;
};

class VanillaEuroOption : public Option {
public:
    VanillaEuroOption(double K, const PayOff* payOff, PricePath* pricePath, int nPaths);
    virtual ~VanillaEuroOption();
    virtual double getPrice() const;
};

class ArithmeticAsianOption : public Option {
public:
    ArithmeticAsianOption(double K, const PayOff* payOff, PricePath* pricePath, int nPaths);
    virtual ~ArithmeticAsianOption();
    virtual double getPrice() const;
};

class GeometricAsianOption : public Option {
public:
    GeometricAsianOption(double K, const PayOff* payOff, PricePath* pricePath, int nPaths);
    virtual ~GeometricAsianOption();
    virtual double getPrice() const;
};

#endif // OPTIONS_H_
