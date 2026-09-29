#include <cmath>
#include <cassert>

const double EPSILON = 1e-6;

/*!
    \brief Compares two double numbers

    \param [in] num1, num2 numbers to compare

    \return If they are within an EPSILON or they are both NAN it returns 1
    \return If not it returns 0

    \warning Do not use for infinite numbers
*/
int CompareDouble(double num1, double num2) {
    assert(!isinf(num1));
    assert(!isinf(num2));

    //printf(C_PURPLE "a = %lg, n = %lg\n" C_RESET, a, n);

    if (isnan(num1) && isnan(num2))
        return 1;

    return (fabs(num1 - num2) < EPSILON);
}
