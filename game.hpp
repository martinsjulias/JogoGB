// previnem multiplas inclusoes do cabe�alho
#ifndef GAME_HPP
#define GAME_HPP

//inclusao da bib do sfml que fornece classes e fun��es para gr�ficos
#include <SFML/Graphics.hpp>
#include "Player.hpp" //defini��o classe player
#include "TileMap.hpp" //defini��o classe tilemap

class Game {
public:
    Game();
    void run();

private:
    //processa os eventos da janela
    void processEvents();
    //atualiza a l�gica do jogo
    void update(sf::Time deltaTime);
    //desenha os elementos da janela
    void render();

    //RenderWindow � um obj da sfml que representa a janela do jogo
    sf::RenderWindow window;
    //Instancias das classes player e tilemap
    Player player;
    TileMap tileMap;
    //armazena pontua��o
    int score;

    //textura para o sprite do jogador azul e vermelho
    sf::Texture playerTexture;
    sf::Texture playerRedTexture;
    //textura para o tilemap
    sf::Texture tilemapTexture;
};

#endif // GAME_HPP
