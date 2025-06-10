#ifndef GAMESTATE_H
#define GAMESTATE_H

enum class GameState {
    LOGO_IFSP, //Tela 1
    LOGO_RAYLIBCPP, // Tela 2
    MENU,
    OPCOES, //3.1
    CREDITOS, // 3.2
    JOGANDO, // 3.3
    SAIR, //3.4
    MENU_JOGANDO, // criar o segundo menu
    RESTART, //recomeçar o jogo
    GAMEOVER, // Tela de Game Over
    WIN_GAME // Tela de Vitória
};
#endif
