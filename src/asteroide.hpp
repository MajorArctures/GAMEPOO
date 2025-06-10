#ifndef ASTEROIDE_HPP
#define ASTEROIDE_HPP
#include "Item.hpp"
extern Sound somDano; // Som de dano


class Asteroide : public Item {
public:
    Asteroide(Vector2 pos, Vector2 dir, float vel, const Texture2D& tex);
    bool ChecarColisao(Rectangle alvo) override;

    int Colidir() override;
};

#endif
