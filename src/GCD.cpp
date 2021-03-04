#include "GCD.hpp"

#include <stdexcept>
#include <cmath>
#include <utility>

namespace ospray_util
{
    float gcd(float a, float b, float epsilon)
    {
        if (epsilon <= 0.0f)
        {
            throw std::invalid_argument("epsilon has to be greater than zero");
        }

        // gcd(a, b) = gcd(a, -b) = gcd(-a, b) = gcd(-a, -b)
        float m = std::abs(a);
        float n = std::abs(b);

        // gcd(a, b) = gcd(b, a)
        if (m < n)
        {
            std::swap(m, n);
        }

        while (n >= epsilon)
        {
            m = fmodf(m, n);
            std::swap(m, n);
        }

        return m;
    }
}
