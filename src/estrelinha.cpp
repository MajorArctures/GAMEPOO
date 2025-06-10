#include "Estrelinha.hpp"

Estrelinha::Estrelinha(Vector2 pos, Vector2 dir, float vel, const Texture2D& tex)
    : Item(pos, dir, vel, tex) {}

bool Estrelinha::ChecarColisao(Rectangle alvo) {
    return true;
}

int Estrelinha::Colidir() {
    PlaySound(somColeta);
    //Respawn em nova posição
    Vector2 novaPos = {
        static_cast<float>(GetRandomValue(0, GetScreenWidth() - 32)),
        static_cast<float>(GetScreenHeight() + 32)
    };

    float dirX = static_cast<float>(GetRandomValue(-50, 50)) / 100.0f;
    Vector2 novaDir = Vector2Normalize({ dirX, -1.0f });

    Reativar(novaPos, novaDir, velocidade);

    return 1; // +1 vida
}
