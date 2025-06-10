// TempoJogo.hpp
#ifndef TEMPOJOGO_HPP
#define TEMPOJOGO_HPP

#include "raylib.h"
#include <cstdio>

class TempoJogo {
private:
    float tempoTotal;               // Tempo total em segundos=60
    float tempoDecorrido;           // Tempo desde o inicio que come�a o "jogando"
    bool tempoAcabou;               // Checa se o tempo acabou
    float tempoDesdeFim = 0.0f;     // Tempo at� a tela de vit�ria aparecer
    bool tempoExtraAtivo = false;   // Checa se o contador do tempo extra foi ativado

public:
    TempoJogo(float duracao = 60.0f);

    void Update(float deltaTime);
    bool TempoEsgotado() const;
    float GetTempoDecorrido() const;
    int GetTempoRestante() const;
    void Reset();
    void Draw() const;
    bool TempoExtraConcluido(float tempoExtra);

};

#endif
