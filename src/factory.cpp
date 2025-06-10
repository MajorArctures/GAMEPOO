#include "factory.hpp"
#include "raymath.h"
#include <cstdlib>
#include <ctime>

//Arquivo p spawn de itens
/*-------------------------------------------------------------------------------*/

//Construtor -- texturas, tempo entre spawn, contador de tempo e spawn
Factory::Factory(Texture2D texturaAst, Texture2D texturaEst)
    : texturaAsteroide(texturaAst), texturaEstrelinha(texturaEst),
      tempoSpawn(0.5f), tempoDecorrido(0), contadorSpawn(0) {
    //para criar de forma aleatória
    std::srand(std::time(nullptr));
}

//Destrutor
Factory::~Factory() {
    for (auto item : itens) {
        delete item;
    }
    itens.clear();
}

//Atualização
void Factory::Update(float deltaTime) {
    //Contagem de tempo --- p spawn
    tempoDecorrido += deltaTime;

    //Quando chega a 0,5 segundos spawnna e reinicia o tempo
    if (tempoDecorrido >= tempoSpawn) {
        tempoDecorrido = 0;

        // Gerar posição inicial (embaixo da tela)
        // Para criar o item dentro da tela em um ponto e não no canto
        float x = static_cast<float>(GetRandomValue(0, GetScreenWidth() - 32));
        // Para criar o item fora da tela
        float y = static_cast<float>(GetScreenHeight() + 32);

        Vector2 pos = { x, y };

        // Direção aleatória (para cima e com inclinação lateral)
        float dirX = static_cast<float>(GetRandomValue(-50, 50)) / 100.0f;
        float dirY = -1.0f; // sempre sobe
        Vector2 dir = Vector2Normalize({ dirX, dirY });

        // Decide se é Asteroide ou Estrelinha
        Item* novoItem;
        // A cada 9 asteroides = 1 estrelinha
        if (contadorSpawn % 9 == 0) {
            novoItem = new Estrelinha(pos, dir, 200.0f, texturaEstrelinha); // estrelinha: mais rapido
        } else {
            novoItem = new Asteroide(pos, dir, 150.0f, texturaAsteroide); // asteroide: mais lento
        }

        //Volta e cria de novo em loop
        itens.push_back(novoItem);
        contadorSpawn++;
    }

    // Atualizar e remover asteroides desativados
    for (auto it = itens.begin(); it != itens.end(); ) {
        (*it)->Update(deltaTime);

        // Só deletar se for um Asteroide inativo
        Asteroide* ast = dynamic_cast<Asteroide*>(*it);
        if (ast && !ast->EstaAtivo()) {
            delete *it;
            it = itens.erase(it);
        } else {
            ++it;
        }
    }
}

//Desenhar os itens
void Factory::DrawItens() const {
    for (const auto& item : itens) {
        //Só vai desenhar se estiver ativo
        if (item->EstaAtivo()) {
            item->Draw();
        }
    }
}

//Resetar
void Factory::Reset() {
    // Apaga todos os itens criados
    for (auto item : itens) {
        delete item;
    }
    itens.clear();

    // Zera o contador e o temporizador
    tempoDecorrido = 0.0f;
    contadorSpawn = 0;
}
//Retorna os itens --- util para checagem de colisão
std::vector<Item*>& Factory::GetItens() {
    return itens;
}

