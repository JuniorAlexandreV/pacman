#ifndef FANTASMA_H
#define FANTASMA_H

#include <QGraphicsRectItem>
#include <QColor>
#include <QPainter>
#include <QRandomGenerator>  // Para gerar direções aleatórias

class Fantasma : public QGraphicsRectItem {
public:
    // Construtor
    Fantasma(int x, int y, const QColor& cor);

    ~Fantasma();

    // Método para mover o fantasma
    void mover();

    // Define e obtem a direção do movimento
    void setDirecao(int dir);
    int getDirecao() const;

    //o método boundingRect para definir a área de colisão
    QRectF boundingRect() const override;

    // método paint para desenhar o fantasma
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Método para mudar a direção do fantasma aleatoriamente
    void novaDirecao();

private:
    int direcao; // Direção do movimento do fantasma
    QColor cor;  // Cor do fantasma
};

#endif



