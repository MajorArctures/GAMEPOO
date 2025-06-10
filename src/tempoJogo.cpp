#include "TempoJogo.hpp"


TempoJogo::TempoJogo(float duracao)
    : tempoTotal(duracao), tempoDecorrido(0), tempoAcabou(false) {}

void TempoJogo::Update(float deltaTime) {
    if (!tempoAcabou) {
        tempoDecorrido += deltaTime;
        if (tempoDecorrido >= tempoTotal) {
            tempoDecorrido = tempoTotal;
            tempoAcabou = true;
        }
    }
}

bool TempoJogo::TempoEsgotado() const {
    return tempoAcabou;
}

float TempoJogo::GetTempoDecorrido() const {
    return tempoDecorrido;
}

int TempoJogo::GetTempoRestante() const {
    return (int)(tempoTotal - tempoDecorrido);
}

void TempoJogo::Reset() {
    tempoDecorrido = 0;
    tempoAcabou = false;
}

void TempoJogo::Draw() const {
    int tempo = static_cast<int>(tempoDecorrido);

    // Formata o texto
    char tempoTexto[32];
    snprintf(tempoTexto, sizeof(tempoTexto), "Tempo: %02d s", tempo);

    // Posição - Canto superior direito
    int larguraTexto = MeasureText(tempoTexto, 20);
    int posX = GetScreenWidth() - larguraTexto - 20;
    int posY = 10;

    // Desenha na tela
    DrawText(tempoTexto, posX, posY, 20, WHITE);
}

bool TempoJogo::TempoExtraConcluido(float tempoExtra) {
    if (!tempoAcabou) return false;

    if (!tempoExtraAtivo) {
        tempoExtraAtivo = true;
        tempoDesdeFim = 0.0f;
        return false;
    }

    tempoDesdeFim += GetFrameTime();  // já que é específico de Raylib, não precisa passar deltaTime

    return tempoDesdeFim >= tempoExtra;
}
