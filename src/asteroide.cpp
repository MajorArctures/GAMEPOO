#include "Asteroide.hpp"
#include "Asteroide.hpp"


Asteroide::Asteroide(Vector2 pos, Vector2 dir, float vel, const Texture2D& tex)
    : Item(pos, dir, vel, tex) {}

bool Asteroide::ChecarColisao(Rectangle alvo) {
    return true;
}

int Asteroide::Colidir() {
    PlaySound(somDano);
    Destruir();
    return 0; // causa dano
}

