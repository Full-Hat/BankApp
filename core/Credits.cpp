//
// Created by Full-Hat on 08/12/2023.
//

#include "Credits.hpp"

Credit::Credit(QString hashId, QString date, int years, double interstrait, double bodySum, double sum,
                 double payedSum, QObject *parent) {
    this->hashId = hashId;
    this->date = date;
    this->years = years;
    this->interstrait = interstrait;
    this->bodySum = bodySum;
    this->sum = sum;
    this->payedSum = payedSum;
}

CreditsArray::CreditsArray(QObject *parent) : QObject(parent) {
}

QList<QObject *> CreditsArray::getCredits() {

}

std::shared_ptr<Credit> CreditsArray::getByNum(QString number) {
    return std::shared_ptr<Credit>();
}
