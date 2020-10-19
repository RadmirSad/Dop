//
// Created by radmi on 04.10.2020.
//

#ifndef PROJECT2_2A_DIOCLE_H
#define PROJECT2_2A_DIOCLE_H
#define _USE_MATH_DEFINES

//#include "gtest/gtest_prod.h"
#include <math.h>
#include <iostream>
#include <sstream>


class Cissoid{
private:
    double r;
public:
    explicit Cissoid (double rad = 1);
    // get
    double getR() const { return r; };
    // set
    Cissoid& setR(double r0);
    // other
    double getY (double x) const;
    double getDist (double angle) const;
    double getRatio () const { return 2*r; }
    double getSquare () const { return 3*M_PI*abs(r); }
    double getVol () const { return 2*M_PI*M_PI*r*r*abs(r); }
    double getRatPar () const { return 4*r; }
};


template <class number>
int Get_info(number& a)
{
    int flag = 0;
    std::string dop;
    getline(std::cin, dop);
    if (dop.length() == 0) return 0;
    for (int i = 0; i < dop.length(); i++)
        if (((dop[i] < 48) && (dop[i] != 46)) || (dop[i] > 57)) flag = 1;
    if (flag) return 0;
    std::stringstream ss;
    ss << dop;
    ss >> a;
    return 1;
}

template <class number>
void Get_num(number &num)
{
    int flag = 0;
    while (!flag)
        if (Get_info(num) > 0) flag = 1;
        else std::cout << "Incorrect symbols. Try again:" << std::endl;
}

#endif //PROJECT2_2A_DIOCLE_H
