#pragma once

#include <vector>
#include <stdexcept>
#include <algorithm>

template<typename T>
class Interpolator
{
public:
    Interpolator() = default;

    explicit Interpolator(const std::vector<T>& xs, const std::vector<T>& ys)
    {
        setData(xs, ys);
    }

    void setData(const std::vector<T>& xs, const std::vector<T>& ys)
    {
        if (xs.size() != ys.size())
            throw std::invalid_argument("Vectors x and y must have the same length");
        if (xs.empty())
            throw std::invalid_argument("Vectors cannot be empty");

        if (!std::is_sorted(xs.begin(), xs.end()))
            throw std::invalid_argument("Vector x must be sorted in ascending order");

        m_x = xs;
        m_y = ys;
    }

    const std::vector<T>& getX() const { return m_x; }
    const std::vector<T>& getY() const { return m_y; }

    void setX(const std::vector<T>& xs)
    {
        if (xs.size() != m_y.size())
            throw std::invalid_argument("New x vector size must match y vector size");
        if (!std::is_sorted(xs.begin(), xs.end()))
            throw std::invalid_argument("Vector x must be sorted in ascending order");
        m_x = xs;
    }

    void setY(const std::vector<T>& ys)
    {
        if (ys.size() != m_x.size())
            throw std::invalid_argument("New y vector size must match x vector size");
        m_y = ys;
    }

    T interpolate(T x) const
    {
        if (m_x.empty())
            throw std::runtime_error("Interpolator data is empty");

        if (x <= m_x.front()) {
            // экстраполяция слева
            T x0 = m_x[0], x1 = m_x[1];
            T y0 = m_y[0], y1 = m_y[1];
            T slope = (y1 - y0) / (x1 - x0);
            return y0 + slope * (x - x0);
        }
        if (x >= m_x.back()) {
            // экстраполяция справа
            size_t n = m_x.size();
            T x0 = m_x[n - 2], x1 = m_x[n - 1];
            T y0 = m_y[n - 2], y1 = m_y[n - 1];
            T slope = (y1 - y0) / (x1 - x0);
            return y1 + slope * (x - x1);
        }

        auto it = std::upper_bound(m_x.begin(), m_x.end(), x);
        size_t i = std::distance(m_x.begin(), it) - 1;

        T x0 = m_x[i];
        T x1 = m_x[i + 1];
        T y0 = m_y[i];
        T y1 = m_y[i + 1];

        T t = (x - x0) / (x1 - x0);
        return y0 + t * (y1 - y0);
    }

private:
    std::vector<T> m_x;
    std::vector<T> m_y;
};
