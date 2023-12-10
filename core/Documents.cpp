//
// Created by Full-Hat on 09/12/2023.
//
#include "Documents.hpp"

#include <sstream>

QList<QObject *> Documents::getDocuments(uint16_t quarter, uint16_t year) {
    auto res = m_backend.GetDocuments(CurrentUser::Get().GetToken(), quarter, year);
    if (res.code != 200) {
        return {};
    }
    backend_cards.clear();
    for(const auto& data : res.datas) {
        std::shared_ptr<Document> bill = std::make_shared<Document>(
                data.hashId,
                QString(""),
                data.date,
                data.sum,
                backend::Api::toDocumentKind(data.kind)
        );
        backend_cards.append(bill);
    }

    QList<QObject *> qmlCards(backend_cards.size());
    for (int i = 0; i < backend_cards.size(); ++i) {
        qmlCards[i] = static_cast<QObject*>(backend_cards[i].get());
    }

    return qmlCards;
}

void Documents::onCurrentDocumentUpdate(const QString &newNumber) {
    this->currentDocumentNumber = newNumber;
}

void Documents::onAddDeclaration(double sum, QString date, QString file_path) {
    if (sum == 0) {
        emit showWarning("Wrong values");
        return;
    }

    std::tm date_tm;
    std::istringstream ss(date.toStdString());
    ss >> std::get_time(&date_tm, "%Y-%m-%d");
    auto res = m_backend.PostDocuments(CurrentUser::Get().GetToken(), sum, date_tm, backend::Api::DocumentKind::Declaration);

    if (res.code != 200) {
        emit showWarning(m_backend.getLastError());
        return;
    }

    auto code = m_backend.SendDocument(CurrentUser::Get().GetToken(), res.hashId, file_path);

    if (code != 200) {
        emit showWarning(m_backend.getLastError());
        return;
    }

    emit showOk();
}

void Documents::onAddActOfWorkPerformed(double sum, QString date, QString file_path) {
    if (sum == 0) {
        emit showWarning("Wrong values");
        return;
    }

    std::tm date_tm;
    std::istringstream ss(date.toStdString());
    ss >> std::get_time(&date_tm, "%Y-%m-%d");
    auto res = m_backend.PostDocuments(CurrentUser::Get().GetToken(), sum, date_tm, backend::Api::DocumentKind::ActOfWorkPerformed);

    if (res.code != 200) {
        emit showWarning(m_backend.getLastError());
        return;
    }

    auto code = m_backend.SendDocument(CurrentUser::Get().GetToken(), res.hashId, file_path);

    if (code != 200) {
        emit showWarning(m_backend.getLastError());
        return;
    }

    emit showOk();
}

void Documents::onUpdate(uint16_t quarter, uint16_t year) {
    auto res = m_backend.GetDocuments(CurrentUser::Get().GetToken(), quarter, year);
    assert(res.code == 200);
    if (res.code != 200) {
        emit showWarning(m_backend.getLastError());
        return;
    }

    auto &datas = res.datas;
    using api = backend::Api;
    for (auto &el : datas) {
        backend_cards.push_back(std::make_shared<Document>(
            el.hashId,
            "file",
            el.date,
            el.sum,
            api::toDocumentKind(el.kind)
        ));
    }

    QList<QObject*> objs;
    objs.reserve(backend_cards.size());
    for (auto &el : backend_cards) {
        objs.push_back(el.get());
    }

    emit documentsChanged(objs, true);
}

void Documents::onDownloadFile() {
    auto res = m_backend.GetDocument(CurrentUser::Get().GetToken(), currentDocumentNumber);
    if (res.code != 200) {
        emit showWarning(m_backend.getLastError());
        return;
    }

    emit showOk();
}


