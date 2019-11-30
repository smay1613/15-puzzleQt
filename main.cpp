#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gameboard.h"
#include "gamecontroller.h"
#include "movecounter.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<GameBoard>     ("Game", 1, 0, "GameBoard_qml"     );
    qmlRegisterType<GameController>("Game", 1, 0, "GameController_qml");
    qmlRegisterType<MoveCounter>("Game", 1, 0, "MoveCounter_qml");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                        if (!obj && url == objUrl)
                            QCoreApplication::exit(-1);
                    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
