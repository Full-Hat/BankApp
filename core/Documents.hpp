//
// Created by Full-Hat on 10/12/2023.
//

#pragma once

//
// Created by Full-Hat on 08/12/2023.
//

#pragma once

#include "backend/Api.hpp"
#include "core/Bills.hpp"

#include <QObject>
#include <memory>
#include <utility>

class Document : public QObject {
Q_OBJECT

public:
    Q_PROPERTY(QString hashId READ getHashId WRITE setHashId)
    Q_PROPERTY(QString file READ getFile WRITE setFile)
    Q_PROPERTY(QString date READ getDate WRITE setDate)
    Q_PROPERTY(double sum READ getSum WRITE setSum)
    Q_PROPERTY(backend::Api::DocumentKind kind READ getKind WRITE setKind)
    Q_PROPERTY(QString kindStr READ getKindStr)

private:
    QString m_hashId;
    QString m_file;
    QString m_date;
    double m_sum;
    backend::Api::DocumentKind m_kind;

public:
    QString getHashId() const { return m_hashId; }
    void setHashId(const QString &hashId) { m_hashId = hashId; }

    QString getFile() const { return m_file; }
    void setFile(const QString &file) { m_file = file; }

    QString getDate() const { return m_date; }
    void setDate(QString date) { m_date = date; }

    double getSum() const { return m_sum; }
    void setSum(double sum) { m_sum = sum; }

    QString getKindStr() { return backend::Api::toString(m_kind); }

    backend::Api::DocumentKind getKind() const { return m_kind; }
    void setKind(backend::Api::DocumentKind kind) { m_kind = kind; }

    Document(QString hashId, QString file, QString date, double sum, backend::Api::DocumentKind kind, QObject *parent = nullptr)
            : QObject(parent), m_hashId(std::move(hashId)), m_file(std::move(file)), m_date(std::move(date)), m_sum(sum), m_kind(kind) {}
};

class Documents : public QObject {
Q_OBJECT

protected:

    QList<std::shared_ptr<Document>> backend_cards;

    Q_PROPERTY(QString currentDocumentNumber READ getDocumentNumber WRITE setDocumentNumber)
    QString currentDocumentNumber;

public:
    Documents(QObject *parent = nullptr) : QObject(parent) {}

    [[nodiscard]]
    QString getDocumentNumber() const { return currentDocumentNumber; };
    void setDocumentNumber(const QString &cardNumber) { currentDocumentNumber = cardNumber; };

    // Iterated through array to get pointers, need to be cached
    [[nodiscard]]
    QList<QObject*> getDocuments(uint16_t quarter, uint16_t year);

public slots:
    void onCurrentDocumentUpdate(const QString& newNumber);

    void onAddActOfWorkPerformed(double sum, QString date, QString file_path);
    void onAddDeclaration(double sum, QString date, QString file_path);

    void onDownloadFile();

    void onUpdate(uint16_t quarter, uint16_t year);

signals:
    void documentsChanged(QList<QObject*> documents, bool saveCurrent);
    void showWarning(QString message);
    void showOk();
    void updateBills(QList<QObject*> bills);

protected:
    mutable backend::Api m_backend;
};
