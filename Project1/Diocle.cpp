#include <stdexcept>
#include <cmath>
#include "Diocle.h"

Cissoid::Cissoid(double rad)
{
    if (rad == 0)
        throw std::out_of_range("Invalid radius.");
    r = rad;
}

Cissoid& Cissoid::setR(double r0)
{
    if (r0 == 0)
        throw std::out_of_range("Invalid radius.");
    r = r0;
    return *this;
}

double Cissoid::getY(double x) const {
    if (((r > 0) && ((x < 0) || (x >= 2*r))) || ((r < 0) && ((x > 0) || (x <= 2*r))))
        throw std::out_of_range("Invalid X coordinate.");
    double y = (pow(x, 3))/(2 * r - x);
    return sqrt(y);
}

double Cissoid::getDist(double angle) const {// посмотреть при угле равном 90
    int dop = (int)angle;
    if (((r > 0) && ((dop % 360) > 90) && ((dop % 360) < 270)) || ((r < 0) && (((dop % 360) < 90) || ((dop % 360) > 270))) || ((dop == angle) && (abs((dop % 180)) == 90)))
        throw std::out_of_range("Invalid angle.");
    return (2 * r * pow(sin(angle * M_PI / 180), 2))/(cos(angle * M_PI / 180));
}