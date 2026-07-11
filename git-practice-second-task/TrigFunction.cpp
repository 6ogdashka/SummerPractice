#include "TrigFunction.h"
#include <cmath>

TrigFunction::TrigFunction()
    : m_type("sin"), m_multiplier(1), m_color(Qt::blue), m_style(Qt::SolidLine)
{
}

TrigFunction::TrigFunction(const QString& type, int multiplier, const QColor& color, Qt::PenStyle style)
    : m_type(type), m_multiplier(multiplier), m_color(color), m_style(style)
{
}

QString TrigFunction::getType() const { return m_type; }
int TrigFunction::getMultiplier() const { return m_multiplier; }
QColor TrigFunction::getColor() const { return m_color; }
Qt::PenStyle TrigFunction::getStyle() const { return m_style; }

double TrigFunction::evaluate(double x) const
{
    if (m_type == "sin") return std::sin(m_multiplier * x);
    if (m_type == "cos") return std::cos(m_multiplier * x);
    if (m_type == "tan") return std::tan(m_multiplier * x);
    return 0.0;
}