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
    backend_declaration.reset();
    for(const auto& data : res.datas) {
        if (data.kind == backend::Api::toString(backend::Api::DocumentKind::Declaration)) {
            backend_declaration = std::make_shared<Document>(
                    data.hashId,
                    QString(""),
                    data.date,
                    data.sum,
                    backend::Api::toDocumentKind(data.kind)
            );
            continue;
        }
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

bool containsNonLatin(const QString& str) {
    for (int i = 0; i < str.length(); ++i) {
        if (str[i].unicode() > 0x00FF) {
            return true;
        }
    }
    return false;
}

void Documents::onAddDeclaration(double sum, QString date, QString file_path) {
    if (sum == 0) {
        emit showWarning("Wrong values");
        return;
    }

    if (file_path.contains(' ') || containsNonLatin(file_path)) {
        emit showWarning("Invalid symbols in path");
        return;
    }

    if (QFileInfo(file_path).size() > 10 * 1024 * 1024) {
        emit showWarning("File is too large");
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

    emit closeDialog();
    getDocuments(current_quarter, current_year);
    emit documentsChanged(getDocuments(current_quarter, current_year), backend_declaration.get(), true);
    emit showOk();
}

void Documents::onAddActOfWorkPerformed(double sum, QString date, QString file_path) {
    if (sum == 0) {
        emit showWarning("Wrong values");
        return;
    }

    if (file_path.contains(' ') || containsNonLatin(file_path)) {
        emit showWarning("Invalid symbols in path");
        return;
    }

    auto fileSize = QFileInfo(QUrl::fromUserInput(file_path).toLocalFile()).size();
    if (fileSize > 10 * 1024 * 1024) {
        emit showWarning("File is too large");
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

    emit closeDialog();
    getDocuments(current_quarter, current_year);
    emit documentsChanged(getDocuments(current_quarter, current_year), backend_declaration.get(), true);
    emit showOk();
}

void Documents::onUpdate(uint16_t quarter, uint16_t year) {
    current_quarter = quarter;
    current_year = year;

    emit documentsChanged(getDocuments(quarter, year), backend_declaration.get(), true);
}

void Documents::onDownloadFile() {
    auto res = m_backend.GetDocument(CurrentUser::Get().GetToken(), currentDocumentNumber);
    if (res.code != 200) {
        emit showWarning(m_backend.getLastError());
        return;
    }

    emit showOk();
}

void Documents::onDownloadFile(QString hashId) {
    auto res = m_backend.GetDocument(CurrentUser::Get().GetToken(), hashId);
    if (res.code != 200) {
        emit showWarning(m_backend.getLastError());
        return;
    }

    emit showOk();
}

void Documents::onDeleteFile(QString hash) {
    auto code = m_backend.RemoveDocument(CurrentUser::Get().GetToken(), hash);
    if (code != 200) {
        emit showWarning(m_backend.getLastError());
        return;
    }

    emit documentsChanged(getDocuments(current_quarter, current_year), backend_declaration.get(), false);
    emit showOk();
}
