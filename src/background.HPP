#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "raylib.h"

class Background {
public:
    void Init();
    void Update();
    void Draw();
    void Unload();

private:
    Texture2D background;
    Texture2D midground;
    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
};

#endif
