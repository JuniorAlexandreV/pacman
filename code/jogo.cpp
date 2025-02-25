#include <iostream>
#include "personagem.h"

int main() {
    // Criando um objeto Personagem na posição (0, 0)
    Personagem p(0, 0);

    // Movimentando o personagem para a direita e para baixo
    p.movimentar(1, 0);  // Movimento para a direita (x + 1)
    p.movimentar(0, 1);  // Movimento para baixo (y + 1)

    // Imprimir a posição do personagem
    std::cout << "Posição do personagem: (" << p.posicaoX << ", " << p.posicaoY << ")" << std::endl;

    return 0;
}

