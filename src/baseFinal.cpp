#include "baseFinal.hpp"

BaseFinal::BaseFinal(Texture2D baseTex, Texture2D roverTex)
    : base(baseTex), rover(roverTex), ativo(false) {

    alturaBase = GetScreenHeight() / 3.0f;

    posBase = { 0, GetScreenHeight() - alturaBase };

    posRover = {
        (GetScreenWidth() / 2.0f) - (rover.width / 2.0f),
        posBase.y - rover.height + 10
    };

    offsetY = GetScreenHeight(); // Começa fora da tela, embaixo
}


void BaseFinal::Ativar() {
    ativo = true;
}

void BaseFinal::Update(float deltaTime) {
    if (ativo && offsetY > 0) {
        offsetY -= velocidadeSubida * deltaTime;
        if (offsetY < 0) offsetY = 0;
    }
}

void BaseFinal::Draw() const {
    if (ativo) {
        Rectangle source = { 0, 0, (float)base.width, (float)base.height };
        Rectangle dest = {
            posBase.x,
            posBase.y + offsetY,  // soma para simular subida
            (float)GetScreenWidth(),
            alturaBase
        };
        Vector2 origin = { 0, 0 };

        DrawTexturePro(base, source, dest, origin, 0.0f, WHITE);

        // Rover sobe junto com a base
        DrawTexture(rover, posRover.x, posRover.y + offsetY, WHITE);
    }
}

void BaseFinal::Reset() {
    ativo = false;
    offsetY = GetScreenHeight();
}

bool BaseFinal::VerificaColisao(Rectangle jogador) {
    if (!ativo || offsetY > 0) return false;

    Rectangle roverRec = {
        posRover.x,
        posRover.y - offsetY,
        (float)rover.width,
        (float)rover.height
    };

    return CheckCollisionRecs(jogador, roverRec);
}
