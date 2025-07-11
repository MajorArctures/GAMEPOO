#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "raylib.h"
#include<vector>
#include "item.hpp"

const int MAX_LIFES = 5;

class Player {
private:
    //texturas para direita e esquerda
    Texture2D texture;          // Variavel geral de textura
    Texture2D textureLeft;      // Variavel com a textura do astronauta virado p esquerda
    Texture2D textureRight;     // Variavel com a textura do astronauta virado p direita
    Texture2D heartTexture;     // Textura do cora��o
    Vector2 position;           // Posi��o do Player na tela
    bool facingRight;           // Variavel que controla qual das texturas (l - r) est� ativa
    float speed;                // Velocidade de movimenta��o
    int lifes;                  // Quantidade de vidas do player
    int estrelasColetadas = 0;  // Variavel de contador de estrelinhas
    int asteroidesColididos = 0;// Variavel de contar de asteroides

public:
    // Construtor: carrega a textura e define a posicao inicial do player
    Player();

    // Destrutor: descarrega a textura do player
    ~Player();

    // M�todo para desenhar o player na tela
    void Draw() const;

    // M�todo para atualizar o player
    void Update(float deltaTime, const std::vector<Item*>& itens);

    // M�todo para controlar asvidas
    int ControleVidas(bool colidiuInimigo, bool pegouPowerUp);

    // M�todo para desenhar as vidas na tela
    void DrawVidas() const;

    // M�todo que verifica se o player colidiu com as bordas da tela
    void CheckScreenLimits();

    // M�todo que verifica colis�es com os itens
    void CheckCollisions(const std::vector<Item*>& itens);

    //M�todo que desenha o contador
    void DrawContador(Texture2D texEstC, Texture2D texAstC) const;

    //Fun��o que retorna vidas
    int GetLifes() const;

    //Para checar a colis�o do player com a base
    Rectangle GetBoundingBox() const;

    //resetar para jogar de novo
    void Reset() {
    // Posiciona o jogador no centro da tela (mesma l�gica do construtor)
    position.x = (GetScreenWidth() - texture.width) / 2.0f;
    position.y = (GetScreenHeight() - texture.height) / 2.0f;

    // Restaurar os valores iniciais
    lifes = MAX_LIFES;
    estrelasColetadas = 0;
    asteroidesColididos = 0;

    facingRight = false;
    texture = textureLeft;  // Come�a olhando para a esquerda
}




};

#endif
