#pragma once

#include <vector>

namespace ospray_util
{
    float gcd(float a, float b, float epsilon);
    float gcd(const std::vector<float>& v, float epsilon);
}
