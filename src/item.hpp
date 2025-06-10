#ifndef ITEM_HPP
#define ITEM_HPP

#include "raylib.h"
#include "raymath.h"
#pragma once

extern Sound somColeta;
extern Sound somDano;
class Item {
protected:
    Vector2 posicaoInicial;     // Posi��o inicial dos itens
    Vector2 tamanho;            // Tamanho das imagens dos itens
    float velocidade;           // Velocidade do item
    Vector2 direcao;            // Dire��o --- para ir p cima
    const Texture2D* textura;   // Ponteiro para evitar c�pia e preservar a textura original
    bool ativo = true;          // Checa se o item est� ativo, na tela, ou n�o

public:
    //construtor
    Item(Vector2 pos, Vector2 dir, float vel, const Texture2D& tex);
    //destrutor
    virtual ~Item();

    virtual void Update(float deltaTime);           // Atualiza
    virtual void Draw() const;                      // Desenhar itens
    virtual bool ChecarColisao(Rectangle alvo);     // Checagem de colis�o
    virtual void Destruir();                        // Destroi quando n�o utilizado
    virtual int Colidir();                     // retorna: 0 (dano), +1 (cura)

    // Pooling (reuso de itens)
    virtual void Reativar(Vector2 novaPos, Vector2 novaDir, float novaVel);
    virtual void Desativar();
    virtual bool EstaAtivo() const;

    // Acesso
    virtual Rectangle GetBoundingBox() const;       // Pegar a box
    virtual Vector2 GetPosition() const;            // Pegar posi��o
    virtual Vector2 GetSize() const;                // Pegar tamanho
};

#endif
