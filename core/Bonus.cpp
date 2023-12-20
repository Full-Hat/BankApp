//
// Created by Full-Hat on 20/12/2023.
//

#include "Bonus.hpp"

#include "core/User.hpp"

void BonusView::onUpdateCurrency(const QString &newCurrency) {

}

void BonusView::onAddBonus(QString currency, QString sum) {
    auto res = m_backend.SetRounding(CurrentUser::Get().GetToken(), sum, currency);

    if (res != 200) {
        emit showWarning("Server error");
        return;
    }

    emit
}

void BonusView::onBonusDecondAdd(double sum, int day, double amt, const QString &selectedBill) {

}

void BonusView::onUpdate(QString currensy) {
    auto res = m_backend.GetRounding(CurrentUser::Get().GetToken());
    auto it = std::find_if(res.datas.begin(), res.datas.end(), [&](auto el) {
        return el.currency == currensy;
    });

    bonusSecondArray.reset();
    bonusSecondArray = std::make_shared<Bonus>(it->currency, it->sum);

    auto res1 = m_backend.GetPeriodical(CurrentUser::Get().GetToken());
    auto it = std::find_if(res1.datas.begin(), res1.datas.end(), [&](auto el) {
        return el.hashId == currensy
    })
    QList<QObject*> objs;
    for (auto el : res.datas) {
        bonusArray.push_back(std::make_shared<Bonus>(el.currency, el.sum));
        objs.push_back(bonusArray.last().get());
    }
}
