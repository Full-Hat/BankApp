#include <iostream>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <stdexcept>
#include <iostream>
#include <QQmlContext>

#include "core/Login.hpp"
#include "core/Signup.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QQmlApplicationEngine qml_engine;

    qml_engine.load(QUrl("qrc:/main/frontend/Main.qml"));

    if (qml_engine.rootObjects().isEmpty())
    {
        throw std::runtime_error("Cant setup qml engine");
    }

    Login LoginController;
    qml_engine.rootContext()->setContextProperty("CtrLogin", &LoginController);

    LoginCode LoginCodeController;
    qml_engine.rootContext()->setContextProperty("CtrLoginCode", &LoginCodeController);

    Signup SignupController;
    qml_engine.rootContext()->setContextProperty("CtrSignup", &SignupController);

    return app.exec();
}
