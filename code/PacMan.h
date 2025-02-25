#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QObject>
#include <QTimer>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class PacMan : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    PacMan(int x, int y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setDirecao(int novaDirecao);
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    QRectF boundingRect() const override;  // Declaração do boundingRect()

private:
    QTimer *movimentoTimer;
    int direcaoAtual;
    int proximaDirecao;
    void movimentar();  // Função de movimentação
};

#endif
