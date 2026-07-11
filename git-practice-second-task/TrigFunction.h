#ifndef TRIGFUNCTION_H
#define TRIGFUNCTION_H

#include <QString>
#include <QColor>
#include <Qt>

class TrigFunction
{
public:
    TrigFunction();
    TrigFunction(const QString& type, int multiplier, const QColor& color, Qt::PenStyle style);

    QString getType() const;
    int getMultiplier() const;
    QColor getColor() const;
    Qt::PenStyle getStyle() const;

    double evaluate(double x) const;

private:
    QString m_type;
    int m_multiplier;
    QColor m_color;
    Qt::PenStyle m_style;
};

#endif