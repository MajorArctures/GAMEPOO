#ifndef BASEFINAL_HPP
#define BASEFINAL_HPP

#include "raylib.h"

class BaseFinal {
private:
    Texture2D base;
    Texture2D rover;
    Vector2 posBase;
    Vector2 posRover;
    bool ativo;
    float offsetY;                 // Distância vertical para animação de subida
    float velocidadeSubida = 60.0f; // Pixels por segundo
    float alturaBase;              // Altura visual da base

public:
    BaseFinal(Texture2D baseTex, Texture2D roverTex);
    void Update(float deltaTime);
    void Ativar();
    void Draw() const;
    void Reset();
    bool VerificaColisao(Rectangle jogador);
};

#endif
