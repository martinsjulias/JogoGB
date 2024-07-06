#ifndef PLAYER_HPP
#define PLAYER_HPP

//inclusao da bib do sfml que fornece classes e funções para gráficos
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    //lida com a entrada do jogador
    void handleInput();
    //atualiza o estado do jogador
    void update(sf::Time deltaTime);
    //desenha o jogador na janela
    void render(sf::RenderWindow& window);
    //retorna posição do jogador
    sf::Vector2f getPosition() const;
    //define posição do jogador
    void setPosition(sf::Vector2f position);
    //retorna sprite do jogador
    sf::Sprite& getSprite();

private:
    //objeto da sfml que representa o sprite do jogador
    sf::Sprite sprite;
    //armazena velocidade do jogador
    float speed;
};

#endif // PLAYER_HPP
