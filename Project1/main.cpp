#include <iostream>
#include "Diocle.h"

int main() {
    int sw = 0, flag_for_end = 0;
    double radius, buf;
    double &dop = radius, &dop2 = buf;
    std::cout << "Enter the parameter that sets the Сissoid" << std::endl;
    Get_num(dop);
    Cissoid my_line(radius);

    while (!flag_for_end) {
        std::cout << "Select the action" << std::endl
                  << "1. Get curve parameter." << std::endl
                  << "2. Change cissoid parameter." << std::endl
                  << "3. Get the Y coordinate depending on X" << std::endl
                  << "4. Get the distance to the coordinate intersection center depending on the angle." << std::endl
                  << "5. Get cissoidal asymptote coefficient" << std::endl
                  << "6. Get the area of the strip between cissoid and its asymptote." << std::endl
                  << "7. Get the body volume obtained by rotating the strip from point 6 around the asymptote." << std::endl
                  << "8. To get the coefficients in the parabola equation such that the bases of perpendiculars lowered from the parabola apex to its tangents form this cissoid."<< std::endl
                  << "9. Finish the program." << std::endl;
        while (sw == 0) {
            Get_info(dop2);
            if (buf == (int)buf) sw = (int)buf;
            else std::cout << "Incorrect value. Try again:" << std::endl;
        }
        switch (sw) {
            case 1:
                std::cout << "The parameter of the cissoid equals " << my_line.getR() << std::endl;
                break;
            case 2:
                std::cout << "Enter new parameter:" << std::endl;
                Get_num(dop);
                my_line.setR(radius);
                break;
            case 3:
            {
                std::cout << "Enter the X coordinate:" << std::endl;
                Get_num(dop2);
                std::cout << "The Y coordinates: " << my_line.getY(buf) << " and " << -(my_line.getY(buf)) << std::endl;
                break;
            }
            case 4:
                std::cout << "Enter the angle:" << std::endl;
                Get_num(dop2);
                std::cout << "The distance to the coordinate intersection center = " << my_line.getDist(buf) << std::endl;
                break;
            case 5:
                std::cout << "Cissoidal asymptote coefficient = " << my_line.getRatio() << std::endl;
                break;
            case 6:
                std::cout << "The area of the strip between cissoid and its asymptote = " << my_line.getSquare() << std::endl;
                break;
            case 7:
                std::cout << "The body volume obtained by rotating the strip from point 6 around the asymptote = " << my_line.getVol() << std::endl;
                break;
            case 8:
                std::cout << "The coefficients in the parabola = " << my_line.getRatPar() << std::endl;
            case 9:
                std::cout << "Closing the program..." << std::endl;
                flag_for_end = 1;
                break;
            default:
                std::cout << "Action with this number doesn't exist." << std::endl;
        }
    }
    return 0;
}
