#ifndef ESTRELINHA_HPP
#define ESTRELINHA_HPP
#include "Item.hpp"
extern Sound somColeta; // Som de coleta


class Estrelinha : public Item {
public:
    Estrelinha(Vector2 pos, Vector2 dir, float vel, const Texture2D& tex);
    bool ChecarColisao(Rectangle alvo) override;
    int Colidir() override;


};



#endif
