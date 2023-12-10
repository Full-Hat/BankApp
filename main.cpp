#include <iostream>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <stdexcept>
#include <iostream>
#include <QQmlContext>
#include <QFontDatabase>

#include "core/Login.hpp"
#include "core/Signup.hpp"
#include "core/Cards.hpp"
#include "core/Bills.hpp"
#include "core/User.hpp"
#include "core/Credits.hpp"
#include "core/Documents.hpp"

#include <QFile>
#include <QIODevice>
#include <fstream>

#include "backend/Api.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
//    backend::Api api;
//    api.testConnection();
    //exit(0);
    QQmlApplicationEngine qml_engine;

    // Set context
    Login LoginController;
    qml_engine.rootContext()->setContextProperty("CtrLogin", &LoginController);

    LoginCode LoginCodeController;
    qml_engine.rootContext()->setContextProperty("CtrLoginCode", &LoginCodeController);

    Signup SignupController;
    qml_engine.rootContext()->setContextProperty("CtrSignup", &SignupController);

    SignupCode SignupCodeController;
    qml_engine.rootContext()->setContextProperty("CtrSignupCode", &SignupCodeController);

    CardsArray CardsController;
    qml_engine.rootContext()->setContextProperty("CtrCards", &CardsController);

    Bills BillsController;
    qml_engine.rootContext()->setContextProperty("CtrBills", &BillsController);

    Credits CreditsController(BillsController);
    qml_engine.rootContext()->setContextProperty("CtrCredits", &CreditsController);

    Documents DocumentsController;
    qml_engine.rootContext()->setContextProperty("CtrDocuments", &DocumentsController);

    CurrentUser::Get().SetToken("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxIiwiZW1haWwiOiJjcmF6eXRodHBsYXlAZ21haWwuY29tIiwianRpIjoiYjQxMTNkNjQtZTdmYS00Mzc3LWFiM2YtNDM1YmMyNDk3ZWFjIiwibmJmIjoxNzAxODAyMjczLCJleHAiOjE3MzMzMzgyNzMsImlhdCI6MTcwMTgwMjI3NH0.4XQ0OJB4Kv6_FKrfLHi7RmzYaZNeAgGs5orIdAmFSbc");
    // Load frontend
    qml_engine.load(QUrl("qrc:/main/frontend/Main.qml"));

    int id = QFontDatabase::addApplicationFont(":/main/frontend/fonts/Markdown.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont monospace(family);

    if (qml_engine.rootObjects().isEmpty())
    {
        throw std::runtime_error("Cant setup qml engine");
    }

    return app.exec();
}
