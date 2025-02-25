#include "Personagem.h"

Personagem::Personagem(int x, int y) : QGraphicsRectItem(x, y, 30, 30), posX(x), posY(y) {
    setRect(0, 0, 30, 30);  // Define o tamanho do retângulo
}

void Personagem::setPosicao(int x, int y) {
    posX = x;
    posY = y;
    setPos(x, y);  // Atualiza a posição do QGraphicsRectItem
}
