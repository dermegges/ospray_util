#pragma once

#include <map>

namespace ospray_util
{
    template <std::size_t N>
    class PiecewiseLinearFunction
    {
    public:
        void clearControlPoints();
        bool insertControlPoint(float x, const std::array<float, N>& y);
        std::array<float, N> lerp(float x) const;

    private:
        std::map<float, std::array<float, N>> controlPoints;
    };

    template <std::size_t N>
    void PiecewiseLinearFunction<N>::clearControlPoints()
    {
        controlPoints.clear();
    }

    template <std::size_t N>
    bool PiecewiseLinearFunction<N>::insertControlPoint(float x, const std::array<float, N>& y)
    {
        const auto p = std::make_pair(x, y);

        return controlPoints.insert(p).second;
    }

    template <std::size_t N>
    std::array<float, N> PiecewiseLinearFunction<N>::lerp(float x) const
    {
        if (controlPoints.empty())
        {
            throw std::domain_error("function is undefined");
        }

        const auto it = controlPoints.upper_bound(x);

        if (it == controlPoints.end())
        {
            return controlPoints.rbegin()->second;
        }

        if (it == controlPoints.begin())
        {
            return it->second;
        }

        const float x0 = std::prev(it)->first;
        const float x1 = it->first;

        const auto y0 = std::prev(it)->second;
        const auto y1 = it->second;

        // weight to linearly interpolate between y0 and y1
        const float t = (x - x0) / (x1 - x0);

        std::array<float, N> y;

        for (std::size_t i = 0; i < N; ++i)
        {
            y[i] = y0[i] + t * (y1[i] - y0[i]);
        }

        return y;
    }
}
