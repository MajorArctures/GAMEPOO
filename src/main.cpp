#include "raylib.h"
#include "Background.hpp"
#include "gamestate.hpp"
#include "player.hpp"
#include "factory.hpp"
#include "tempoJogo.hpp"
#include "baseFinal.hpp"
#include <clocale>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstdio>

// Variáveis globais
GameState estadoAtual = GameState::LOGO_IFSP;
int opcaoSelecionada = 0;
double tempoTotal = 0.0;
TempoJogo tempo(10.0f);
char tempoDigitado[8] = "";     // Armazena texto digitado
int tempoCharIndex = 0;         // Posição no array
bool tempoEditando = false;     // Controle de edição
float novoTempo = 10.0f;        // Tempo padrão

 //sons -- tem que ser globais
Sound somColeta;
Sound somDano;
Sound somWin;
Sound somGameOver;

int main() {
    //Tamanho da tela e nome do jogo
    InitWindow(720, 560, "Lost Astronaut");
    //audios
    InitAudioDevice();

    //carrega o Som
    Font fontAstro = LoadFont("assets/fonts/fontAstro.ttf");


    somColeta   = LoadSound("assets/sounds/coleta.mp3");
    somDano     = LoadSound("assets/sounds/dano.mp3");
    somWin      = LoadSound("assets/sounds/win.mp3");
    somGameOver = LoadSound("assets/sounds/gameOver.mp3");

    SetTargetFPS(60);

    // Carregamento de texturas dos itens e contador
    Texture2D texAst = LoadTexture("assets/images/asteroide.png");
    Texture2D texEst = LoadTexture("assets/images/powerup.png");
    Texture2D texAstC = LoadTexture("assets/images/asteroideCont.png");
    Texture2D texEstC = LoadTexture("assets/images/powerupCont.png");
    Texture2D texBase = LoadTexture("assets/images/base.png");
    Texture2D texRover = LoadTexture("assets/images/rover.png");
    Texture2D gameoverscreen = LoadTexture("assets/images/gameOver.png");
    Texture2D winscreen = LoadTexture("assets/images/WIN.png");


    //Objetivo = base e rover
    BaseFinal base(texBase, texRover);

    //Chama a função de criação de itens
    Factory factory(texAst, texEst);

    //Cria o objeto bg e inicia
    Background bg;
    bg.Init();

    //Cria o objeto jogador
    Player jogador;

    //carregamento da música
    Music musicaFundo = LoadMusicStream("assets/sounds/musica_fundo.mp3");


    while (!WindowShouldClose()) {

        //definindo volume
        SetSoundVolume(somColeta, 1.0f); // volume máximo
        SetSoundVolume(somDano, 1.0f);
        SetSoundVolume(somWin, 1.0f);
        SetSoundVolume(somGameOver, 1.0f);


        //comando p música funcionar
        UpdateMusicStream(musicaFundo);

        //Para atualização frame a frame
        float deltaTime = GetFrameTime();
        tempoTotal += deltaTime;

        //Atualiza o bg
        bg.Update();

        //Começa a "desenhar o jogo aqui"
        BeginDrawing();
        ClearBackground(WHITE);

        switch (estadoAtual) {
/*----------------------------------------------------------------------------------------------*/
        //Tela 1 - Logo do IF
        case GameState::LOGO_IFSP:
            DrawTextEx(fontAstro, "IFSP - Campus Campos do Jordao",
           (Vector2){100, 250}, 30, 2, BLACK);
            if (tempoTotal >= 3.0) {
                estadoAtual = GameState::LOGO_RAYLIBCPP;
                tempoTotal = 0.0;
            }
            break;
/*----------------------------------------------------------------------------------------------*/
        //Tela 2 - Raylib e CPP
        case GameState::LOGO_RAYLIBCPP:
            DrawTextEx(fontAstro, "Feito com Raylib e C++",
           (Vector2){180, 250}, 30, 2, PINK);
            if (tempoTotal >= 5.0) {
                estadoAtual = GameState::MENU;
                tempoTotal = 0.0;
            }
            break;
/*----------------------------------------------------------------------------------------------*/
        //Tela 3 - Menu Principal
        case GameState::MENU: {
            //opcaoSelecionada - conta as opções disponíveis
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) opcaoSelecionada++;
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) opcaoSelecionada--;
            if (opcaoSelecionada > 3) opcaoSelecionada = 0;
            if (opcaoSelecionada < 0) opcaoSelecionada = 3;

            if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
                switch (opcaoSelecionada) {
                case 0: tempo.Reset();
                        jogador.Reset();
                        factory.Reset();
                        base.Reset();
                        //inicia a música
                        PlayMusicStream(musicaFundo);
                        tempo = TempoJogo(novoTempo);
                        estadoAtual = GameState::JOGANDO;
                break;
                case 1: estadoAtual = GameState::OPCOES; break;
                case 2: estadoAtual = GameState::CREDITOS; break;
                case 3: estadoAtual = GameState::SAIR; break;
                }
            }
            //Deixa a opção seleiconada/escolhida em vermelho
            Color cor[4] = {
                (opcaoSelecionada == 0) ? PINK : BLACK,
                (opcaoSelecionada == 1) ? PINK : BLACK,
                (opcaoSelecionada == 2) ? PINK : BLACK,
                (opcaoSelecionada == 3) ? PINK : BLACK
            };

            //"Desenha" o texto na tela
            DrawTextEx(fontAstro, "Jogar",    (Vector2){300, 200}, 20, 2, cor[0]);
            DrawTextEx(fontAstro, "Opcoes",   (Vector2){300, 240}, 20, 2, cor[1]);
            DrawTextEx(fontAstro, "Creditos", (Vector2){300, 280}, 20, 2, cor[2]);
            DrawTextEx(fontAstro, "Sair",     (Vector2){300, 320}, 20, 2, cor[3]);

            break;
        }
/*----------------------------------------------------------------------------------------------*/
        //Tela - OPCOES - Som e Música
        case GameState::OPCOES:{
            DrawText("Som e idioma em breve!", 200, 200, 20, DARKGRAY);
            DrawText("[Space] Voltar", 10, 520, 15, GRAY);

           // Texto explicativo
            DrawText("Tempo de jogo (segundos):", 200, 250, 20, BLACK);
            DrawText("Digite enter + tempo em segundos + enter!",200, 290, 15, DARKGRAY);

            // Mostra campo de entrada abaixo do texto, retângulo rosa
            DrawRectangleLines(200, 320, 280, 30, PINK);

            // Texto digitado dentro do retângulo, ajustado verticalmente
            DrawText(tempoDigitado[0] == '\0' ? "..." : tempoDigitado, 210, 325, 20, PINK);

            // Ativa modo de edição ao pressionar ENTER
            if (IsKeyPressed(KEY_ENTER)) {
                if (tempoEditando) {
                    int valor = atoi(tempoDigitado);
                    if (valor > 0) {
                        novoTempo = static_cast<float>(valor);
                    }
                }
                tempoEditando = !tempoEditando; // Alterna modo edição
            }

            // Edição do campo
            if (tempoEditando) {
                int key = GetKeyPressed();
                while (key > 0) {
                    if ((key >= KEY_ZERO && key <= KEY_NINE) && tempoCharIndex < 7) {
                        tempoDigitado[tempoCharIndex++] = static_cast<char>(key);
                        tempoDigitado[tempoCharIndex] = '\0';
                    }
                    if (key == KEY_BACKSPACE && tempoCharIndex > 0) {
                        tempoDigitado[--tempoCharIndex] = '\0';
                    }
                    key = GetKeyPressed();
                }
            }

            // Voltar ao menu principal
            if (IsKeyPressed(KEY_SPACE)) {
                estadoAtual = GameState::MENU;
            }

            break;
        }

/*----------------------------------------------------------------------------------------------*/
        //Tela - CREDITOS
        case GameState::CREDITOS:
            DrawText("Beatriz Helena - CJ3025799", 200, 200, 20, PINK);
            DrawText("Analise e Desenvolvimento de Sistemas", 200, 250, 20, DARKGRAY);
            DrawText("4o. Semestre", 200, 280, 20, DARKGRAY);
            DrawText("Professor: Paulo Giovanni", 200, 310, 20, BLACK);
            DrawText("Programacao Orientada a Objetos", 200, 340, 20, DARKGRAY);
            DrawText("[Backspace] Voltar", 10, 520, 15, GRAY);
            if (IsKeyPressed(KEY_BACKSPACE)) estadoAtual = GameState::MENU;
            break;
/*----------------------------------------------------------------------------------------------*/
        //Tela - JOGO AQUI!
        case GameState::JOGANDO:
            //Atualiza o tempo de jogo
            tempo.Update(deltaTime);
            //Desenha o tempo no canto superior direito

            //Desenha o background
            bg.Draw();
            base.Draw();


            //Atualiza os itens (movimento e spawn)
            factory.Update(deltaTime);

            //Atualiza o jogador (movimento) e verifica colisões
            jogador.Update(deltaTime, factory.GetItens());
            jogador.CheckCollisions(factory.GetItens());
            tempo.Draw();

            //Desenha os contadores (estrelas e asteroides)
            jogador.DrawContador(texEstC, texAstC);

            //Desenha os itens na tela
            factory.DrawItens();

            //Desenha o jogador na tela
            jogador.Draw();

            //Desenha a quantidade de vidas restantes
            jogador.DrawVidas();

             if (jogador.GetLifes() != 0) {
                if (tempo.TempoEsgotado()) {
                    base.Ativar();
                    base.Update(deltaTime);

                    if (tempo.TempoExtraConcluido(3.0f) &&
                        base.VerificaColisao(jogador.GetBoundingBox())) {
                        estadoAtual = GameState::WIN_GAME;
                    }
                }
            } else {
                estadoAtual = GameState::GAMEOVER;
            }

            break;
/*----------------------------------------------------------------------------------------------*/
         //Tela - Vitória
        case GameState::WIN_GAME:
            StopMusicStream(musicaFundo);
            PlaySound(somWin);
            DrawTexture(winscreen, -4.0, 0.0, WHITE);

            DrawText("Pressione [Enter] para voltar ao menu", 150, 520, 20, DARKGRAY);
            if (IsKeyPressed(KEY_ENTER)) {
                estadoAtual = GameState::MENU;
            }
            break;
/*----------------------------------------------------------------------------------------------*/
         //Tela - GAME OVER
        case GameState::GAMEOVER:
            StopMusicStream(musicaFundo);
            PlaySound(somGameOver);
            DrawTexture(gameoverscreen, -33.0, 0.0, WHITE);

            DrawText("Pressione [Enter] para voltar ao menu", 150, 520, 20, DARKGRAY);
            if (IsKeyPressed(KEY_ENTER)) {
                estadoAtual = GameState::MENU;
            }
            break;
/*----------------------------------------------------------------------------------------------*/
        //Descarrega as texturas e todas as funções se for selecionado o sair
        case GameState::SAIR:
            UnloadTexture(texAst);
            UnloadTexture(texEst);
            UnloadTexture(texAstC);
            UnloadTexture(texEstC);
            UnloadTexture(texBase);
            UnloadTexture(texRover);
            CloseAudioDevice();
            CloseWindow();
            return 0;
        }

        EndDrawing(); // <-- Garantido fora do switch
    }

    CloseWindow(); // fallback de segurança
    return 0;
}
