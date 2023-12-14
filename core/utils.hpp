//
// Created by Full-Hat on 14/12/2023.
//

#pragma once

#include <QObject>

#include "backend/Api.hpp"

class Currency : public QObject {
    Q_OBJECT

public:
    Q_PROPERTY(QString currency READ currency WRITE setCurrency)

    QString currency() const {
        return m_currency;
    }

    void setCurrency(const QString &newCurrency) {
        m_currency = newCurrency;
    }

protected:
    QString m_currency;
};

class Utils : public QObject {
    Q_OBJECT

public:
    QList<std::shared_ptr<Currency>> m_currencies;

public slots:
    void onCurrencyUpdate() {
        QList<QString> currencies;
        m_currencies.clear();

        QList<QObject*> objs;

        for (auto el : currencies) {
            auto temp = std::make_shared<Currency>();
            temp->setCurrency(el);
            m_currencies.push_back(temp);

            objs.push_back(m_currencies.last().get());
        }

        emit currencyUpdateSignal(objs);
    }

signals:
    void currencyUpdateSignal(QList<QObject*> objs);

protected:
    backend::Api m_backend;
};
