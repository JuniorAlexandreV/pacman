#include "GameScene.h"
#include "PacMan.h"
#include "Fantasma.h"
#include <QKeyEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QDebug>
#include <QRandomGenerator>

GameScene::GameScene(QObject *parent) : QGraphicsScene(parent), score(0), pontosRestantes(0), vidas(3) { //Constrtutor
    carregarLabirinto();

    pacman = new PacMan(0, 0);  //Cria um objeto chamado pacman a cena
    inicializarPacMan();
    addItem(pacman);

    scoreText = new QGraphicsTextItem("Score: 0"); // Item de texto para exibir a pontuação na cena
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setFont(QFont("Arial", 16));
    scoreText->setPos(40, 4);  // ajuste da posição
    addItem(scoreText);

    // Inicializa vidas
    vidasText = new QGraphicsTextItem("Vidas: 3");
    vidasText->setDefaultTextColor(Qt::white);
    vidasText->setFont(QFont("Arial", 16));
    vidasText->setPos(200, 4);  // Ajuste a posição
    addItem(vidasText);

    inicializarFantasmas();

    // timer para movimentar os fantasmas
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameScene::moverFantasmas); // Timer para o movimento dos fantasmas que chama a função mover fantasmas
    timer->start(250);
}

GameScene::~GameScene() {}

void GameScene::carregarLabirinto() {
    int tamanhoBloco = 30;             // definindo o tamanho de cada bloco do labirinto, que será no tamanho de 30 pixels
    for (int i = 0; i < 13; i++) { // para carregar 13 linhas e 30 colunas
        for (int j = 0; j < 30; j++) { // Paredes no valor 1 e pontos no valor 0
            if (labirinto[i][j] == 1) {
                QGraphicsRectItem *parede = new QGraphicsRectItem(j * tamanhoBloco, i * tamanhoBloco, tamanhoBloco, tamanhoBloco); //parede é um ponteiro para um objeto da classe QGraphicsRectItem, que representa um retângulo em na cena gráfica
                parede->setBrush(QBrush(Qt::blue)); //  Estilo de preenchimento do retangulo, no caso o Azul
                addItem(parede); //adiciona o bloco a cena
                paredes.append(parede); // Lista que armazena todos os blocos de parede, para permitir o acesso de todas as paredes
            } else if (labirinto[i][j] == 0) { // Para preencher a celuals vazias ou seja blocos igual 0 da matriz representa 1 ponto
                QGraphicsEllipseItem *ponto = new QGraphicsEllipseItem(j * tamanhoBloco + tamanhoBloco / 3,
                                                                       i * tamanhoBloco + tamanhoBloco / 3,
                                                                       tamanhoBloco / 3, tamanhoBloco / 3);
                ponto->setBrush(QBrush(Qt::yellow)); //pontos em amarelo
                addItem(ponto); // Adiciona o item a cena
                pontos.append(ponto);// Cria a lista para armazenar
                pontosRestantes++;
            }
        }
    }
}

bool GameScene::verificarColisaoComParede(QPointF novaPosicao) {
    int tamanhoBloco = 30;
    int posX = static_cast<int>(novaPosicao.x() / tamanhoBloco); //posição do jogador na tela, conversão para garantir que a posição seja do tipo inteiro
    int posY = static_cast<int>(novaPosicao.y() / tamanhoBloco);

    if (posX < 0 || posX >= 30 || posY < 0 || posY >= 13) { //Se posX ou posY estiver fora dos limmites o jogador saiu do labirinto, com base no tamanho máximo estabelicido para o labirinto
        return true;  // Colisão com o limite do labirinto
    }

    if (labirinto[posY][posX] == 1) {
        return true;  // Colisão com a parede
    }

    return false;  // Nenhuma colisão
}

void GameScene::inicializarPacMan() { //Definindo a posição inicial do pacman
    for (int i = 0; i < 13; i++) { // para percorrer as linhas e colunas do labirinto
        for (int j = 0; j < 30; j++) {
            if (labirinto[i][j] == 0) { // Verifica se a posição atual é uma espaço livre
                pacman->setPos(j * 30, i * 30); //posicionando o pacman
                return;
            }
        }
    }
}

void GameScene::inicializarFantasmas() {
    // Posições do centro do labirinto
    int xCentro = 15;  // Coluna 15, linha 6
    int yCentro = 6;   // Centro vertical

    //cores dos fantasmas
    QList<QColor> coresFantasmas = {
        Qt::red, Qt::cyan, Qt::green, Qt::white
    };

    // Inicializando fantasmas
    for (int i = 0; i < coresFantasmas.size(); ++i) { //Percorre a lista de cores para criar os fantasma
        // Coordenadas no centro do labirinto
        int x = xCentro + (i % 2 == 0 ? 1 : -1);  // Para distribuir horizontalmente - se i for par (adiciona 1) move para a direita, se for impar(subtrai 1) move para a esquerda
        int y = yCentro + (i / 2 == 0 ? 1 : -1);  // Para distribuir verticalmente

        // Verifica se a posição é válida não é uma parede)
        if (labirinto[y][x] == 0) {  // Apenas cria o fantasma em posições vazias no labirinto
            // Convertendo coordenadas do labirinto para pixels
            int pixelX = x * 30;  // Multiplica por 30 para obter a coordenada em pixels
            int pixelY = y * 30;  // Multiplica por 30 para obter a coordenada em pixels

            // Criando o fantasma com a posição e a cor definidas
            Fantasma* fantasma = new Fantasma(pixelX, pixelY, coresFantasmas[i]);

            // Adicionando o fantasma à cena
            addItem(fantasma);

            // Adicionando o fantasma à lista de fantasmas
            fantasmas.append(fantasma);
        }
    }
}



void GameScene::moverFantasmas() {
    for (Fantasma* fantasma : fantasmas) { //percorre a lista de fantasmas para mover cada um individualmente
        QPointF posAtual = fantasma->pos(); //obtém a posição atual do fantasma e inicializa com nova posição
        QPointF novaPos = posAtual;

        // Vetores de movimento: {dx, dy}
        QVector<QPointF> direcoes = { // Define um vetor de direções possiveis
            {  0, -30 }, // Cima
            {  0,  30 }, // Baixo
            { -30,  0 }, // Esquerda
            {  30,  0 }  // Direita
        };

        // Obter direção atual
        int direcaoAtual = fantasma->getDirecao(); //obtém a direção que o fantasma está se movendo atualmente
        QVector<int> direcoesValidas;

        // Verifica todas as direções possíveis
        for (int i = 0; i < direcoes.size(); i++) {
            QPointF tentativa = posAtual + direcoes[i];

            // Se a posição for válida (não colide com a parede)
            if (!verificarColisaoComParede(tentativa)) { //testa as 4 direções, calcula tentativa, posição caso o fantasma se mova em uma determinada direção
                // Se for o oposto da direção atual, ignore
                if (direcaoAtual >= 0 && i == (direcaoAtual ^ 1)) { //se a direção for o oposto da direção atual, ela é ignorada
                    continue;
                }
                direcoesValidas.append(i);//se houver pelo menos uma direção válida, uma nova direção será escolhida
            }
        }

        // se houver várias direções válidas, escolha uma aleatória
        if (!direcoesValidas.isEmpty()) { // Se houver mais de duas direções válidas, significa que o fantasma está em um cruzamento,
            int novaDirecao;


            if (direcoesValidas.size() > 2) { // nesse caso, é feita uma escolha aleatória, evitando repetir a direção anterior.
                do {
                    novaDirecao = direcoesValidas[QRandomGenerator::global()->bounded(direcoesValidas.size())];
                } while (novaDirecao == direcaoAtual);  // garante que não vai repetir a direção anterior
            }
            else {
                novaDirecao = direcoesValidas[QRandomGenerator::global()->bounded(direcoesValidas.size())];
            }

            // Atualiza a direção do fantasma
            fantasma->setDirecao(novaDirecao);
            novaPos = posAtual + direcoes[novaDirecao];
        }
        else {
            // se não houver direções válidas, reverte a direção atual para evitar travar
            if (direcaoAtual >= 0) {
                int direcaoInversa = direcaoAtual ^ 1; // inverte direção
                novaPos = posAtual + direcoes[direcaoInversa];
                fantasma->setDirecao(direcaoInversa);
            }
        }

        // Move o fantasma para a nova posição
        fantasma->setPos(novaPos);
    }
}


void GameScene::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;

    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down ||
        event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        pacman->setDirecao(event->key());
    }
}

void GameScene::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;
}

void GameScene::verificarColisaoComPonto() {
    for (int i = 0; i < pontos.size(); ++i) {
        QGraphicsEllipseItem *ponto = pontos[i];
        if (pacman->collidesWithItem(ponto)) {
            removeItem(ponto);
            pontos.removeAt(i);
            delete ponto;

            score += 10;
            pontosRestantes--;
            scoreText->setPlainText("Score: " + QString::number(score));

            if (pontosRestantes == 0) {
                scoreText->setPlainText("Você Venceu! Score Final: " + QString::number(score));
                encerrarJogo();
            }

            qDebug() << "Ponto coletado!";
            break;
        }
    }
}

void GameScene::verificarColisaoComFantasmas() {
    // verificando colisões com os fantasmas
    for (Fantasma* fantasma : fantasmas) {
        // converter as posições do PacMan e do fantasma para coordenadas de bloco
        int pacmanBlocoX = static_cast<int>(pacman->x() / 30);
        int pacmanBlocoY = static_cast<int>(pacman->y() / 30);

        int fantasmaBlocoX = static_cast<int>(fantasma->x() / 30);
        int fantasmaBlocoY = static_cast<int>(fantasma->y() / 30);

        // Vverifica se ambos estão no mesmo bloco
        if (pacmanBlocoX == fantasmaBlocoX && pacmanBlocoY == fantasmaBlocoY) {

            if (pacman->collidesWithItem(fantasma)) {

                qDebug() << "Colisão com fantasma!";

                vidas--;  // decrementa as vidas
                atualizarVidas();  // atualiza o texto de vidas

                // Reseta a posição do PacMan
                pacman->setPos(30, 30);  // Você pode ajustar para a posição inicial se desejar

                if (vidas == 0) {
                    // Quando as vidas forem 0, exibe Game Over
                    scoreText->setPlainText("GAME OVER! Score Final: " + QString::number(score));
                    encerrarJogo();
                }
                break;  // Sai do loop ao detectar a primeira colisão
            }
        }
    }
}

void GameScene::atualizarVidas() {
    vidasText->setPlainText("Vidas: " + QString::number(vidas));  // Atualiza o texto de vidas
}

void GameScene::encerrarJogo() {
    clear();  // Limpa a cena

    // Exibe o Game Over com o Score Final
    QGraphicsTextItem* gameOverText = new QGraphicsTextItem("Game Over! Score Final: " + QString::number(score));
    gameOverText->setFont(QFont("Arial", 24));
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setPos(200, 300);  // Ajusta a posição do texto
    addItem(gameOverText);
    qDebug() << "Jogo encerrado!";
}
