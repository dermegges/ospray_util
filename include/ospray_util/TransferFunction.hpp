#pragma once

#include "PiecewiseLinearFunction.hpp"

#include "ospray/ospray.h"
#include "rkcommon/math/vec.h"

namespace ospray_util
{
    class TransferFunction
    {
    public:
        TransferFunction();

        void setValueRange(const rkcommon::math::vec2f& valueRange);

        void clearColorControlPoints();
        void addColorControlPoint(float value, const rkcommon::math::vec3f& color);
        void setColorControlPoints(const std::vector<std::pair<float, rkcommon::math::vec3f>>& colors);
        OSPData getColorOSPData() const;

        void clearOpacityControlPoints();
        void addOpacityControlPoint(float value, float opacity);
        void setOpacityControlPoints(const std::vector<std::pair<float, float>>& opacities);
        OSPData getOpacityOSPData() const;

    private:
        float minValue;
        float maxValue;

        bool isValueRangeInDescendingOrder;

        PiecewiseLinearFunction<3> colorFunction;
        PiecewiseLinearFunction<1> opacityFunction;
    };
}
