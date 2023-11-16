#include <iostream>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <stdexcept>
#include <iostream>
#include <QQmlContext>

#include "core/Login.hpp"
#include "core/Signup.hpp"
#include "core/Cards.hpp"
#include "core/Bills.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QQmlApplicationEngine qml_engine;

    // Set context
    Login LoginController;
    qml_engine.rootContext()->setContextProperty("CtrLogin", &LoginController);

    LoginCode LoginCodeController;
    qml_engine.rootContext()->setContextProperty("CtrLoginCode", &LoginCodeController);

    Signup SignupController;
    qml_engine.rootContext()->setContextProperty("CtrSignup", &SignupController);

    Cards CardsController;
    qml_engine.rootContext()->setContextProperty("CtrCards", &CardsController);

    Bills BillsController;
    qml_engine.rootContext()->setContextProperty("CtrBills", &BillsController);

    // Load frontend
    qml_engine.load(QUrl("qrc:/main/frontend/Main.qml"));

    if (qml_engine.rootObjects().isEmpty())
    {
        throw std::runtime_error("Cant setup qml engine");
    }

    return app.exec();
}
