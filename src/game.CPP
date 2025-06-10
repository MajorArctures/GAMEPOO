#include "Game.hpp"
#include "raylib.h"

void Game::Init() {
    InitWindow(720, 560, "Sunken Astronaut");
    SetTargetFPS(60);

    background.Init();  // Inicia o fundo também
}

void Game::Update() {
    background.Update();  // Atualiza o fundo
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(WHITE);
    background.Draw();  // Desenha o fundo

    EndDrawing();
}

void Game::Unload() {
    background.Unload();  // Libera o fundo
    CloseWindow();
}

bool Game::ShouldClose() {
    return WindowShouldClose();
}
