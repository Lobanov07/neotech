#pragma once
#include <string>
#include <cmath>

class Shape
{
public:
    Shape(const std::string& color = "black") : m_color(color) {}
    virtual ~Shape() = default;

    virtual double area() const { return 0.0; }
    virtual std::string type() const { return "Shape"; }

    const std::string& color() const { return m_color; }
    void setColor(const std::string& color) { m_color = color; }

private:
    std::string m_color;
};

class Circle : public Shape
{
public:
    Circle(double r = 1.0, const std::string& color = "black") : Shape(color), m_radius(r) {}

    void setRadius(double r) { m_radius = r; }
    double radius() const { return m_radius; }

    double area() const override { return M_PI * m_radius * m_radius; }
    std::string type() const override { return "Circle"; }

private:
    double m_radius;
};

class Rectangle : public Shape
{
public:
    Rectangle(double w = 1.0, double h = 1.0, const std::string& color = "black")
        : Shape(color), m_width(w), m_height(h) {}

    void setSize(double w, double h) { m_width = w; m_height = h; }
    double width() const { return m_width; }
    double height() const { return m_height; }

    double area() const override { return m_width * m_height; }
    std::string type() const override { return "Rectangle"; }

private:
    double m_width;
    double m_height;
};

template <typename Container>
double CalcSumArea(const Container& shapes)
{
    double sum = 0.0;
    for (const auto& shape_ptr : shapes)
    {
        if (shape_ptr)
            sum += shape_ptr->area();
    }
    return sum;
}
