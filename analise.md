# Análise orientada a objeto

![Pac-Man](https://upload.wikimedia.org/wikipedia/en/5/59/Pac-man.png))

## Descrição Geral do domínio do problema

O jogador controla um personagem em formato de círculo amarelo (Pac-Man) dentro de um labirinto. O objetivo é coletar todos os pontos espalhados pelo mapa enquanto evita ser capturado por inimigos (fantasmas) que se movem no labirinto.  

A implementação deste jogo utilizará a linguagem C++ com o framework Qt para desenvolver a interface gráfica e gerenciar os elementos do jogo. O desenvolvimento seguirá o modelo de orientação a objeto, garantindo modularidade e reutilização de código.  

---

## **Requisitos Funcionais**  

 **Movimentação do Pac-Man**  
   - O jogador deve ser capaz de mover o Pac-Man utilizando as teclas direcionais.  
   - O Pac-Man só pode se movimentar dentro do labirinto e não pode atravessar paredes.  

**Fantasmas (Inimigos)**  
   - O jogo deve incluir inimigos (fantasmas) que se movimentam no labirinto.  
   - Os fantasmas devem ter movimento autônomo 

 **Pontos e Pontuação**  
   - O Pac-Man deve coletar pontos ao passar por cima deles(comer).  
   - A pontuação do jogador deve ser atualizada conforme os pontos são coletados.  
 

**Condições de Vitória e Derrota**  
   - O jogo deve terminar quando todos os pontos do labirinto forem coletados (vitória).  
   - O jogo termina se o Pac-Man perder todas as vidas ao ser capturado pelos fantasmas (derrota).  

**Interface Gráfica**  
   - O jogo deve apresentar gráficos básicos representando o labirinto, os fantasmas e o Pac-Man.  
   - A interface deve ser intuitiva e incluir um placar de pontuação.  

---

## Diagrama de Casos de Uso

![Diagrama caso de uso](https://lucid.app/publicSegments/view/b7b94213-ac2b-4ed0-8739-9dbd283790f4/image.png)
# Caso de Uso: Pac-Man

## 1.1 Objetivo  
Este caso de uso descreve a lógica principal do jogo Pac-Man.

## 1.2 Requisitos  
- Jogar o jogo Pac-Man

## 1.3 Atores  
- **Jogador**

## 1.4 Prioridade  
- **ALTA**

## 1.5 Pré-condições  
- O jogo deve estar inicializado com o labirinto carregado e os personagens posicionados corretamente.

## 1.6 Freqüência de uso  
- Não se aplica.

## 1.7 Criticalidade  
- **ALTA**

## 1.8 Condição de Entrada  
- O jogador solicita o início de uma nova partida.

## 1.9 Fluxo Principal  

1. O sistema posiciona Pac-Man e os fantasmas nas posições iniciais dentro do labirinto.  
2. O jogo inicia e Pac-Man pode ser movido pelo jogador através das teclas direcionais.  
3. Os fantasmas começam a se movimentar seguindo um comportamento aleatório.  
4. Quando Pac-Man se move, ele coleta pontos ao passar pelas células do labirinto.  
5. Se Pac-Man colide com um fantasma, ele perde uma vida.  
6. O jogo continua até que Pac-Man perca todas as vidas ou o jogador colete todos os pontos do labirinto.  
7. O sistema exibe o resultado da partida.  

## 1.10 Pós-condições  
- Após a execução deste caso de uso, o sistema registra o resultado da partida e atualiza a pontuação do jogador.

## 1.11 Regras de Negócio  

- O jogador inicia o jogo com um número pré-determinado de vidas.  
- Os fantasmas seguem padrões de movimentação específicos.  
- O jogador deve evitar os fantasmas para continuar jogando.  
- A pontuação é baseada no número de pontos coletados no labirinto.  
- Se Pac-Man perder todas as vidas, a partida termina.  


 
## Diagrama de Domínio do problema

![Diagrama caso de uso](https://lucid.app/publicSegments/view/e0fac5c9-59c5-4756-a1bc-d9cd86e8e071/image.png)


<div align="center">

[Retroceder](README.md) | [Avançar](projeto.md)

</div>
