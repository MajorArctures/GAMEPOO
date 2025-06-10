#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <vector>
#include "item.hpp"
#include "estrelinha.hpp"
#include "asteroide.hpp"
#include "raylib.h"

class Factory {
private:
    std::vector<Item*> itens;
    Texture2D texturaEstrelinha;
    Texture2D texturaAsteroide;

    float tempoSpawn;
    float tempoDecorrido;
    int contadorSpawn; // usado para manter proporção de 9:1

public:
    Factory(Texture2D texturaAst, Texture2D texturaEst);
    ~Factory();

    void Update(float deltaTime);
    void DrawItens() const;
    void Reset();

    std::vector<Item*>& GetItens();
};

#endif
