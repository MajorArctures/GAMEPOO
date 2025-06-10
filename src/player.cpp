#include "player.hpp"
#include "item.hpp"
#include <vector>

// Construtor: carrega a textura e posi��o inicial do player
Player::Player() {

    //Carregamento das duas texturas (direita e esquerda) do astronauta
    Image imgLeft = LoadImage("./assets/images/astronautLeft.png");
    Image imgRight = LoadImage("./assets/images/astronautRight.png");
    //Armazenando as imagens nas variaveis textureLeft/textureRight
    textureLeft = LoadTextureFromImage(imgLeft);
    textureRight = LoadTextureFromImage(imgRight);

    //quando o personagem � criado ele olha p esquerda, por isso facingRight � falso
    facingRight = false;

    //carregando a imagem das vidas = cora��o
    Image heartImg = LoadImage("./assets/images/heart.png");
    heartTexture = LoadTextureFromImage(heartImg);

    //Define a textura inicial --- inicia virado p esquerda
    texture = textureLeft;
    //Posicionando no meio da tela horizontal/vertical
    position.x = (GetScreenWidth() - texture.width) / 2.0f;
    position.y = (GetScreenHeight() - texture.height) / 2.0f;

    //definindo a velocidade -- menos que a estrela mais que o asteroide
    speed = 200.0f;
    //vidas = definido no HPP -- constante
    lifes = MAX_LIFES;

    UnloadImage(heartImg);
    UnloadImage(imgLeft);
    UnloadImage(imgRight);
}

// Destrutor
Player::~Player() {
    UnloadTexture(textureLeft);
    UnloadTexture(textureRight);
    UnloadTexture(heartTexture);

}

// M�todo para desenhar o player na tela
void Player::Draw() const {
    DrawTexture(texture, position.x, position.y, RAYWHITE);
}

// Atualiza o jogador (movimento e colis�es)

//Usando um vector p trazer os itens -estrelinha/asteroide/roover --- AGREGA��O
void Player::Update(float deltaTime, const std::vector<Item*>& itens) {

    //come�a com movimento em falso = parado
    bool moved = false;

    //checa a tecla apertada, multiplica pelo delta time e move
    if (IsKeyDown(KEY_RIGHT)) {
        position.x += speed * deltaTime;
        facingRight = true; //vira o personagem p direita
        moved = true;
    }

    if (IsKeyDown(KEY_LEFT)) {
        position.x -= speed * deltaTime;
        facingRight = false; //vira o personagem  p esquerda
        moved = true;
    }
    /*Essa fun��o faz a troca entre as texturas
    quando moved = true
    ele pergunta:  facingRight? se sim, usa textureRight, sen�o textureLeft*/
    if (moved) {
        texture = facingRight ? textureRight : textureLeft;
    }

    CheckScreenLimits();
    CheckCollisions(itens);

    /*Limites verticais --- n�o ser� necess�rio
    if (position.y < 0) position.y = 0;
    if (position.y + texture.height > GetScreenHeight())
        position.y = GetScreenHeight() - texture.height;*/
}

/*--------------------------------------------------------------------------------*/
//Fun��o de checagem de colis�o com item
void Player::CheckCollisions(const std::vector<Item*>& itens) {

    // Loop para verificar colis�es com cada item
    for (Item* item : itens) {

        //Checa se o item est� ativo para que a colis�o s� seja valida se estiver ativo
        //Evita a perda de 2 vidas
        /*Antes --- o for estava checando item por item, mesmo os inativos, o que gerava mais de uma colis�o*/
        if (!item->EstaAtivo()) continue;

        // Reduzindo a caixinha de colis�o do jogador para 70% do total
        float colisaoLargura = texture.width * 0.7f;
        float colisaoAltura = texture.height * 0.7f;


        //Faz com que o retangulo do player fique no meio da imagem n�o nos cantos
        Rectangle playerRect = {
            position.x + (texture.width  - colisaoLargura) / 2,  // Centraliza a colis�o
            position.y + (texture.height - colisaoAltura) / 2,  // Centraliza a colis�o
            colisaoLargura,
            colisaoAltura
        };

        // Definindo a caixa de colis�o do item
        Rectangle itemRect = {
            //Pega a posi��o do item em x,y
            item->GetPosition().x,
            item->GetPosition().y,
            //Pega o tamanho da caixinha do item em x,y
            item->GetSize().x,
            item->GetSize().y
        };

        // Verifica a colis�o entre a caixa do jogador e a do item
        //Ou seja, checa a colis�o entre os retangulos
        if (CheckCollisionRecs(playerRect, itemRect)) {
            int resultado = item->Colidir();  // Checa qual � o item ao colidir

            // Se for um asteroide (resultado = 0)
            // Se for uma estrelinha (resultado > 0)
             if (resultado > 0) {
                ControleVidas(false, true);  // Retorna a colis�o com a estrelinha como verdadeira
            } else {
                ControleVidas(true, false);
            }
        }
    }
}
/*--------------------------------------------------------------------------------*/
//Fun��o de Controle de Vidas
//Recebe o true, false da fun��o de checagem de colis�o
int Player::ControleVidas(bool colidiuInimigo, bool pegouPowerUp) {
    if (colidiuInimigo && lifes >= 1) {
        //contador e vidas
        asteroidesColididos++;
        lifes--;
    } else if (pegouPowerUp && lifes < MAX_LIFES) {
        //contador e vidas
        estrelasColetadas++;
        lifes++;
    }

    //adicionar as p�ginas de ganhou e game over
    //if (lifes < 0) lifes = 0;
    //if (lifes > MAX_LIFES) lifes = MAX_LIFES;

    return lifes;
}

/*--------------------------------------------------------------------------------*/
//Checagem de limites
void Player::CheckScreenLimits() {
    // Limite esquerdo
    if (position.x < 0) position.x = 0;

    // Limite direito
    if (position.x + texture.width > GetScreenWidth()) {
        position.x = GetScreenWidth() - texture.width;
    }

}

/*--------------------------------------------------------------------------------*/
//Desenhar vidinhas
void Player::DrawVidas() const {
    for (int i = 0; i < lifes; i++) {
        //Desenho o cora��o, adiciona um espa�o e repete i vezes
        DrawTexture(heartTexture, 10 + i * (heartTexture.width + 10), 10, WHITE);
    }
}
/*--------------------------------------------------------------------------------*/
//Desenhar o contador (no canto superior direito)
void Player::DrawContador(Texture2D texEstC, Texture2D texAstC) const {
    DrawTexture(texEstC, 10, 60, WHITE);
    DrawText(TextFormat("%d", estrelasColetadas), 40, 60, 20, WHITE);

    DrawTexture(texAstC, 10, 100, WHITE);
    DrawText(TextFormat("%d", asteroidesColididos), 40, 100, 20, WHITE);
}
/*--------------------------------------------------------------------------------*/

//Retorno de vidas
int Player::GetLifes() const {
    return lifes;
}

/*--------------------------------------------------------------------------------*/
//Checa a colis�o do astronauta com a base final
Rectangle Player::GetBoundingBox() const {
    float colisaoLargura = texture.width * 0.7f;
    float colisaoAltura  = texture.height * 0.7f;

    return {
        position.x + (texture.width  - colisaoLargura) / 2,  // Centraliza a colis�o
        position.y + (texture.height - colisaoAltura) / 2,  // Centraliza a colis�o
        colisaoLargura,
        colisaoAltura
    };
}

