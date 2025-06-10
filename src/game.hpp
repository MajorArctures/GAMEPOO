#ifndef GAME_HPP
#define GAME_HPP

#include "Background.hpp"  // Inclui o fundo para usar no game

class Game {
public:
    void Init();
    void Update();
    void Draw();
    void Unload();
    bool ShouldClose();

private:
    Background background;  // O game "contém" um Background
};

#endif
