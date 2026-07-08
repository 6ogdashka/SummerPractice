#include "TrigFunction.h"
#include <cmath>

TrigFunction::TrigFunction()
    : m_type("sin"), m_amplitude(1.0), m_frequency(1.0), m_color(Qt::blue), m_thickness(2), m_style(Qt::SolidLine)
{
}

TrigFunction::TrigFunction(const QString& type, double amplitude, double frequency, const QColor& color, int thickness, Qt::PenStyle style)
    : m_type(type), m_amplitude(amplitude), m_frequency(frequency), m_color(color), m_thickness(thickness), m_style(style)
{
}

QString TrigFunction::getType() const { return m_type; }
double TrigFunction::getAmplitude() const { return m_amplitude; }
double TrigFunction::getFrequency() const { return m_frequency; }
QColor TrigFunction::getColor() const { return m_color; }
int TrigFunction::getThickness() const { return m_thickness; }
Qt::PenStyle TrigFunction::getStyle() const { return m_style; }

double TrigFunction::evaluate(double x) const
{
    if (m_type == "sin") return m_amplitude * std::sin(m_frequency * x);
    if (m_type == "cos") return m_amplitude * std::cos(m_frequency * x);
    if (m_type == "tan") return m_amplitude * std::tan(m_frequency * x);
    return 0.0;
}