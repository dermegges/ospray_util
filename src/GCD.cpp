#include "ospray_util/GCD.hpp"

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

    float gcd(const std::vector<float>& v, float epsilon)
    {
        float result = 0.0f;

        // gcd(a1, a2, a3, ..., aN) = gcd(gcd(a1, a2), a3, ..., aN)
        for (float x : v)
        {
            result = gcd(x, result, epsilon);
        }

        return result;
    }
}
