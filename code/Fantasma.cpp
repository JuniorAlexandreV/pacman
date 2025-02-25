#include "Fantasma.h"
#include <QRandomGenerator>  // Para gerar direções aleatórias

// Construtor
Fantasma::Fantasma(int x, int y, const QColor& cor)
    : cor(cor)  // Não é necessário definir a direção inicial aqui
{
    setRect(0, 0, 30, 30);  // Define o tamanho do fantasma
    setPos(x, y);           // Define a posição inicial
    setData(0, "fantasma"); // Identificador do fantasma

    // Chama novaDirecao para definir a direção inicial aleatória
    novaDirecao();
}

// Destruidor
Fantasma::~Fantasma() {

}

// Método para mover o fantasma
void Fantasma::mover() {
    int dx = 0, dy = 0;

    // Atualiza a posição do fantasma com base na direção
    switch (direcao) {
    case Qt::Key_Up:    dy = -30; break;
    case Qt::Key_Down:  dy = 30; break;
    case Qt::Key_Left:  dx = -30; break;
    case Qt::Key_Right: dx = 30; break;
    }

    // Move o fantasma
    setPos(x() + dx, y() + dy);

    // Muda a direção aleatoriamente após o movimento
    novaDirecao();
}

// Método para mudar a direção do fantasma aleatoriamente
void Fantasma::novaDirecao() {
    // Gera um número aleatório entre 0 e 3 para escolher a direção
    int direcaoAleatoria = QRandomGenerator::global()->bounded(4);

    // Define a direção baseada no valor gerado
    switch (direcaoAleatoria) {
    case 0: direcao = Qt::Key_Up; break;
    case 1: direcao = Qt::Key_Down; break;
    case 2: direcao = Qt::Key_Left; break;
    case 3: direcao = Qt::Key_Right; break;
    }
}

// Definir a direção do fantasma
void Fantasma::setDirecao(int dir) {
    direcao = dir;
}

//Obtém a direção do fantasma
int Fantasma::getDirecao() const {
    return direcao;
}

// Sobrescreve o método boundingRect para definir a área de colisão
QRectF Fantasma::boundingRect() const {
    return QRectF(0, 0, 30, 30);  // Tamanho do fantasma
}

void Fantasma::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(cor);
    painter->setPen(Qt::NoPen);

    QPainterPath path;

    // Parte superior arredondada do fantasma
    path.moveTo(0, 15);
    path.arcTo(0, 0, 30, 30, 180, -180); //cabeça

    // pés do fantasma
    path.lineTo(30, 30);
    path.lineTo(25, 25);
    path.lineTo(20, 30);
    path.lineTo(15, 25);
    path.lineTo(10, 30);
    path.lineTo(5, 25);
    path.lineTo(0, 30);

    path.closeSubpath();

    painter->drawPath(path);

    // Desenha os olhos do fantasma
    painter->setBrush(Qt::white);
    painter->drawEllipse(8, 10, 6, 6);
    painter->drawEllipse(18, 10, 6, 6);

    painter->setBrush(Qt::black);
    painter->drawEllipse(10, 12, 3, 3);
    painter->drawEllipse(20, 12, 3, 3);
}

