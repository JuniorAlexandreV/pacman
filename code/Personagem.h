#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <QGraphicsRectItem>
#include <QObject>

class Personagem : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    Personagem(int x, int y);
    void setPosicao(int x, int y);

protected:
    int posX, posY;
};

#endif // PERSONAGEM_H
