#include <QApplication>
#include <QGraphicsView>
#include "GameScene.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Cria a cena
    GameScene scene;

    // Cria a view e associa a cena
    QGraphicsView view(&scene);
    view.setScene(&scene);
    view.setSceneRect(0, 0, 900, 390);  // define o tamanho da cena
    view.show();  // exibe a view

    return app.exec();
}
