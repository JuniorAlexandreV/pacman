#include "PacMan.h"
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include "GameScene.h"

PacMan::PacMan(int x, int y) {
    setRect(0, 0, 30, 30); // Define o tamanho
    setPos(x, y);

    direcaoAtual = Qt::Key_Right; // direção inicial p/ a direita

    // Timer de movimento contínuo
    movimentoTimer = new QTimer(this);
    connect(movimentoTimer, &QTimer::timeout, this, &PacMan::movimentar);
    movimentoTimer->start(250); // Move a cada 250ms
}

void PacMan::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(QBrush(Qt::yellow));

    // Ajuste do ângulo de rotação da boca do Pac-Man
    int anguloInicial = 0;
    switch (direcaoAtual) {
    case Qt::Key_Up:    anguloInicial = 135; break;
    case Qt::Key_Down:  anguloInicial = -45; break;
    case Qt::Key_Left:  anguloInicial = 225; break;
    case Qt::Key_Right: anguloInicial = 45; break;
    }

    // Boca do pacman
    painter->drawPie(rect(), anguloInicial * 16, 270 * 16);
}

void PacMan::setDirecao(int novaDirecao) {
    if (novaDirecao == Qt::Key_Up || novaDirecao == Qt::Key_Down ||
        novaDirecao == Qt::Key_Left || novaDirecao == Qt::Key_Right) {
        proximaDirecao = novaDirecao; // Atualiza a direção desejada
    }
}

void PacMan::movimentar() {
    int dx = 0, dy = 0;

    // Obtém a cena do Pac-Man
    GameScene *scene = dynamic_cast<GameScene*>(this->scene());
    if (!scene) return;

    // Tenta mudar para a nova direção, se possível
    int dxTeste = 0, dyTeste = 0;
    switch (proximaDirecao) {
    case Qt::Key_Up:    dyTeste = -30; break;
    case Qt::Key_Down:  dyTeste = 30; break;
    case Qt::Key_Left:  dxTeste = -30; break;
    case Qt::Key_Right: dxTeste = 30; break;
    }

    QPointF novaPosicaoTeste = pos() + QPointF(dxTeste, dyTeste);
    if (!scene->verificarColisaoComParede(novaPosicaoTeste)) {
        direcaoAtual = proximaDirecao; // Atualiza a direção apenas se não houver parede
    }

    // Move na direção atual
    switch (direcaoAtual) {
    case Qt::Key_Up:    dy = -30; break;
    case Qt::Key_Down:  dy = 30; break;
    case Qt::Key_Left:  dx = -30; break;
    case Qt::Key_Right: dx = 30; break;
    }

    QPointF novaPosicao = pos() + QPointF(dx, dy);
    if (!scene->verificarColisaoComParede(novaPosicao)) {
        setPos(novaPosicao); // Move se não houver parede

        // Verifica se o Pac-Man coletou um ponto
        scene->verificarColisaoComPonto();

        // Verifica se o Pac-Man colidiu com um fantasma
        scene->verificarColisaoComFantasmas();
    }
}

void PacMan::keyPressEvent(QKeyEvent *event) {
    // Lida com a tecla pressionada para mudar a direção
    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down ||
        event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        setDirecao(event->key());
    }
}

void PacMan::keyReleaseEvent(QKeyEvent *event) {
    // Não faz nada ao soltar a tecla
    // O PacMan continua se movendo na direção até que uma nova tecla seja pressionada
}

QRectF PacMan::boundingRect() const {
    return QRectF(0, 0, 30, 30);  // Define o retângulo de colisão de 30x30
}
