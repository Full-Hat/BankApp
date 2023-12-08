//
// Created by System Administrator on 11/20/23.
//

#pragma once

#include <QString>
#include <QObject>

class History : public QObject {
    Q_OBJECT

public:
    Q_PROPERTY(QString source READ getSource)
    QString source;

    Q_PROPERTY(QString target READ getTarget)
    QString target;

    Q_PROPERTY(double value READ getValue)
    double value;

    Q_PROPERTY(QString date READ getDate)
    QString date;

public:
    [[nodiscard]]
    QString getSource() const { return source; }

    [[nodiscard]]
    QString getTarget() const { return target; };

    [[nodiscard]]
    double getValue() const { return value; }

    [[nodiscard]]
    QString getDate() const { return date; }
};
