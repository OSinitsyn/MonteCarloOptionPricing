/********************************************************************************************************
*
* FILENAME :
*     mcoptionprice.cc
*
* DESCRIPTION :
*     
*
* PUBLIC MEMBER FUNCTIONS :
*     
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

#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include "pricepath.h"
#include "payoff.h"
#include "options.h"

int main(int argc, const char * argv[]) {

    /**************************************************
    * Examples
    ***************************************************/

    double S0 = 50.0;
    double K = 50.0;
    double sigma = 0.3;
    double r = 0.05;
    double dt = 1.0/50.0;
    int nSteps = 50; 
    int nPaths = 100000;

    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
   
    PricePath pricePath(S0, sigma, r, dt, nSteps);
    pricePath.seedGenerator(seed);

    PayOff* payOff = new PayOffCall;

    VanillaEuroOption euroOpt(K, payOff, &pricePath, nPaths);

    ArithmeticAsianOption arithAsianOpt(K, payOff, &pricePath, nPaths);

    GeometricAsianOption geomAsianOpt(K, payOff, &pricePath, nPaths);

    std::cout << "Euro call price = " << euroOpt.getPrice() << std::endl
              << "Arithmetic Asian call price = " << arithAsianOpt.getPrice() << std::endl
              << "Geometric Asian call price = " << geomAsianOpt.getPrice() << std::endl;
    
    /**************************************************
    * 2. Option price vs stock price 
    ***************************************************/

    std::ofstream ofs;
    ofs.open("prvsstockpr.csv");
    if (ofs.is_open()) {
        ofs << std::fixed;
        ofs << std::setprecision(3);   
        double S0 = 10.0;
        double S0Max = 100.0;
        double S0Step = 5.0;
        while (S0 <= S0Max) {
            pricePath.setS0(S0);
            ofs << S0 << "," << euroOpt.getPrice() << std::endl;
            S0 += S0Step;
        }
        ofs.close();
    }
    S0 = 50.0;
    pricePath.setS0(S0);

    /**************************************************
    * 3. Option price vs volatility
    ***************************************************/

    ofs.open("prvsvolat.csv");
    if (ofs.is_open()) {
        ofs << std::fixed;
        ofs << std::setprecision(3);
        double sigma = 0.0;
        double sigmaMax = 0.5;
        double sigmaStep = 0.025;
        while (sigma <= sigmaMax) {
            pricePath.setSigma(sigma);
            ofs << sigma << "," << euroOpt.getPrice() << std::endl;
            sigma += sigmaStep;
        }
        ofs.close();
    }

    delete payOff; 
    return 0;
}
