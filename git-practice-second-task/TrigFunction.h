#ifndef TRIGFUNCTION_H
#define TRIGFUNCTION_H

#include <QString>
#include <QColor>
#include <Qt>

class TrigFunction
{
public:
    TrigFunction();
    TrigFunction(const QString& type, double amplitude, double frequency, const QColor& color, int thickness, Qt::PenStyle style);

    QString getType() const;
    double getAmplitude() const;
    double getFrequency() const;
    QColor getColor() const;
    int getThickness() const;
    Qt::PenStyle getStyle() const;

    double evaluate(double x) const;

private:
    QString m_type;
    double m_amplitude;
    double m_frequency;
    QColor m_color;
    int m_thickness;
    Qt::PenStyle m_style;
};

#endif