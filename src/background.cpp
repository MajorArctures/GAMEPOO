#include "Background.hpp"
#include "raylib.h"


void Background::Init() {
    background = LoadTexture("./assets/images/01BGback.png");
    midground  = LoadTexture("./assets/images/01BGmid.png");
}

void Background::Update() {
    scrollingBack -= 1.7f;
    scrollingMid  -= 2.1f;

    if (scrollingBack <= -background.height * 2) scrollingBack = 0;
    if (scrollingMid  <= -midground.height  * 2) scrollingMid  = 0;
}

void Background::Draw() {
    // Fundo
    DrawTextureEx(background, { 0, scrollingBack }, 0.0f, 2.0f, WHITE );
    DrawTextureEx(background, { 0, background.height * 2 + scrollingBack }, 0.0f, 2.0f, WHITE );
    // Meio
    DrawTextureEx(midground, { 20, scrollingMid }, 0.0f, 2.0f, WHITE );
    DrawTextureEx(midground, { 20, midground.height * 2 + scrollingMid }, 0.0f, 2.0f, WHITE );
}

void Background::Unload() {
    UnloadTexture(background);
    UnloadTexture(midground);
}
