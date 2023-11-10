#include <iostream>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <stdexcept>
#include <iostream>
#include <QQmlContext>

#include "core/Login.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QQmlApplicationEngine qml_engine;

    qml_engine.load(QUrl("qrc:/main/frontend/LoginPage.qml"));

    if (qml_engine.rootObjects().isEmpty())
    {
        throw std::runtime_error("Cant setup qml engine");
    }

    Login LoginController;
    qml_engine.rootContext()->setContextProperty("CtrLogin", &LoginController);

    return app.exec();
}
