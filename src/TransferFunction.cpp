#include "ospray_util/TransferFunction.hpp"
#include "ospray_util/GCD.hpp"

namespace ospray_util
{
    TransferFunction::TransferFunction()
    {
        minValue = 0.0f;
        maxValue = 0.0f;

        isValueRangeInDescendingOrder = false;
    }

    void TransferFunction::setValueRange(const rkcommon::math::vec2f& valueRange)
    {
        if (valueRange.x <= valueRange.y)
        {
            minValue = valueRange.x;
            maxValue = valueRange.y;

            isValueRangeInDescendingOrder = false;
        }
        else
        {
            minValue = valueRange.y;
            maxValue = valueRange.x;

            isValueRangeInDescendingOrder = true;
        }
    }

    void TransferFunction::clearColorControlPoints()
    {
        colorFunction.clearControlPoints();
    }

    void TransferFunction::addColorControlPoint(float value, const rkcommon::math::vec3f& color)
    {
        const float x = value;
        const std::array<float, 3> y = {color[0], color[1], color[2]};

        colorFunction.insertControlPoint(x, y);
    }

    void TransferFunction::setColorControlPoints(const std::vector<std::pair<float, rkcommon::math::vec3f>>& colors)
    {
        clearColorControlPoints();

        for (const auto& c : colors)
        {
            addColorControlPoint(c.first, c.second);
        }
    }

    OSPData TransferFunction::getColorOSPData() const
    {
        auto deltas = colorFunction.getDomainOfControlPointsInInterval(minValue, maxValue);

        for (std::size_t i = 0; i < deltas.size(); ++i)
        {
            deltas[i] -= minValue;
        }

        deltas.push_back(maxValue - minValue);

        // epsilon hard-coded for the moment
        const float offset = gcd(deltas, 0.001f);

        float currentValue = minValue;

        static std::vector<rkcommon::math::vec3f> equidistantColors;
        equidistantColors.clear();

        while (currentValue <= maxValue)
        {
            try
            {
                const auto color = colorFunction.lerp(currentValue);
                equidistantColors.push_back(rkcommon::math::vec3f(color[0], color[1], color[2]));
            }
            catch (const std::domain_error&)
            {
                return nullptr;
            }

            if (offset == 0.0f)
            {
                break;
            }

            currentValue += offset;
        }

        if (isValueRangeInDescendingOrder)
        {
            std::reverse(equidistantColors.begin(), equidistantColors.end());
        }

        OSPData colorData = ospNewSharedData(equidistantColors.data(), OSP_VEC3F, equidistantColors.size());

        return colorData;
    }

    void TransferFunction::clearOpacityControlPoints()
    {
        opacityFunction.clearControlPoints();
    }

    void TransferFunction::addOpacityControlPoint(float value, float opacity)
    {
        const float x = value;
        const std::array<float, 1> y = {opacity};

        opacityFunction.insertControlPoint(x, y);
    }

    void TransferFunction::setOpacityControlPoints(const std::vector<std::pair<float, float>>& opacities)
    {
        clearOpacityControlPoints();

        for (const auto& o : opacities)
        {
            addOpacityControlPoint(o.first, o.second);
        }
    }

    OSPData TransferFunction::getOpacityOSPData() const
    {
        auto deltas = opacityFunction.getDomainOfControlPointsInInterval(minValue, maxValue);

        for (std::size_t i = 0; i < deltas.size(); ++i)
        {
            deltas[i] -= minValue;
        }

        deltas.push_back(maxValue - minValue);

        // epsilon hard-coded for the moment
        const float offset = gcd(deltas, 0.001f);

        float currentValue = minValue;

        static std::vector<float> equidistantOpacities;
        equidistantOpacities.clear();

        while (currentValue <= maxValue)
        {
            try
            {
                const auto opacity = opacityFunction.lerp(currentValue);
                equidistantOpacities.push_back(opacity[0]);
            }
            catch (const std::domain_error&)
            {
                return nullptr;
            }

            if (offset == 0.0f)
            {
                break;
            }

            currentValue += offset;
        }

        if (isValueRangeInDescendingOrder)
        {
            std::reverse(equidistantOpacities.begin(), equidistantOpacities.end());
        }

        OSPData opacityData = ospNewSharedData(equidistantOpacities.data(), OSP_FLOAT, equidistantOpacities.size());

        return opacityData;
    }
}
