    #include "Item.hpp"

    //Construtor
    Item::Item(Vector2 pos, Vector2 dir, float vel, const Texture2D& tex)
        : posicaoInicial(pos), direcao(dir), velocidade(vel), textura(&tex), ativo(true) {
        //o tamanho do item é pego pelo tamanho da textura
        tamanho = { (float)tex.width, (float)tex.height };
    }
    //Destrutor
    Item::~Item() {
    }

    //Atualização do Item
    void Item::Update(float deltaTime) {
        if (!ativo) return;

        // Movimento baseado em direção e velocidade
        posicaoInicial.x += direcao.x * velocidade * deltaTime;
        posicaoInicial.y += direcao.y * velocidade * deltaTime;
    }

    //Desenhar os itens quando ativos
    void Item::Draw() const {
        if (ativo && textura != nullptr) {
            DrawTextureV(*textura, posicaoInicial, WHITE);
        }
    }

    //Checar se houve colisão
    bool Item::ChecarColisao(Rectangle alvo) {
        return CheckCollisionRecs(GetBoundingBox(), alvo);
    }

    //Destruir item quando não usado
    void Item::Destruir() {
        ativo = false;
    }

    //Quando colidi o item desaparece
    int Item::Colidir() {
        return 0;
    }

    //Reativa o item que sai da tela, não precisa criar novos
    void Item::Reativar(Vector2 novaPos, Vector2 novaDir, float novaVel) {
        posicaoInicial = novaPos;   // Nova posição inicial
        direcao = novaDir;          // Nova direção de movimento
        velocidade = novaVel;       // Nova velocidade ---- velocidade asteroide <> estrelinha
        ativo = true;               // O item tem que estar ativo
    }

    //Função que desativa o item
    void Item::Desativar() {
        ativo = false;
    }

    //Checa se o item está ativo
    bool Item::EstaAtivo() const {
        return ativo;
    }

    //Retorna a posição e o tamanho do item (no caso do retangulo de colisão)
    Rectangle Item::GetBoundingBox() const {
        return { posicaoInicial.x, posicaoInicial.y, tamanho.x, tamanho.y };
    }

    //Posição inicial do item
    Vector2 Item::GetPosition() const {
        return posicaoInicial;
    }

    //Tamanho do item
    Vector2 Item::GetSize() const {
        return tamanho;
    }
