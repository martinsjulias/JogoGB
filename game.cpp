#include "Game.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Game::Game()
    //inicializa console da sfml com um tamanho especifico e titulo tilemap game
    : window(sf::VideoMode(1024, 768), "Tilemap Game"), player(), score(0)
{
    //carrega texturas e exibe mensagem de erro se a imagem nao carregar
    if (!playerTexture.loadFromFile("assets/sprite.png")) {
        std::cerr << "Erro ao carregar a textura do jogador!" << std::endl;
    }
    if (!playerRedTexture.loadFromFile("assets/sprite_red.png")) {
        std::cerr << "Erro ao carregar a textura vermelha do jogador!" << std::endl;
    }
    if (!tilemapTexture.loadFromFile("assets/tilemap-1.png")) {
        std::cerr << "Erro ao carregar a textura do tilemap!" << std::endl;
    }

    //define textura do sprite para PlayerTexture
    player.getSprite().setTexture(playerTexture);
    //Define posição inicial
    player.setPosition(sf::Vector2f(100, 100));

    //abre o arquivo do map para leitura
    std::ifstream mapFile("assets/map.txt");
    //verifica se o mapa foi aberto com sucesso
    if (!mapFile) {
        std::cerr << "Erro ao abrir o arquivo de mapa!" << std::endl;
    }
    //se foi aberto com sucesso, continua execução
    else {
        std::string line;
        std::getline(mapFile, line);
        std::istringstream ss(line);
        std::string tileset;
        unsigned int tileSize, width, height;
        ss >> tileset >> tileSize >> width >> height;

        //aloca memoria para armazenar indices dos tiles
        int* tiles = new int[width * height];
        for (unsigned int i = 0; i < height; ++i) {
            //le linha atual do arquivo do mapa
            std::getline(mapFile, line);
            std::istringstream ss(line);
            for (unsigned int j = 0; j < width; ++j) {
                //le o indice do tile e armazena na matriz de tiles
                ss >> tiles[j + i * width];
            }
        }

        //tenta carregar  tilemap usando os dados do arquivo de mapa
        if (!tileMap.load("assets/" + tileset, sf::Vector2u(tileSize, tileSize), tiles, width, height)) {
            std::cerr << "Erro ao carregar o tilemap!" << std::endl;
        }

        delete[] tiles;
    }
}

void Game::run() {
    //mede tempo decorrido
    sf::Clock clock;
    while (window.isOpen()) {
        //chama metodo para processar eventos
        processEvents();
        sf::Time deltaTime = clock.restart();
        //chama metodo para atualizar a logica do jogo
        update(deltaTime);
        //metodo que renderiza os graficos do jogo
        render();
    }
}

void Game::processEvents() {
    //event para armazenar eventos da janela
    sf::Event event;
    //loop para processar todos os eventos da fila
    while (window.pollEvent(event)) {
        //verifica se o evento é fechamento da janela
        if (event.type == sf::Event::Closed)
            window.close();
    }
    //chama o metodo para lidar com a entrada do jogador
    player.handleInput();
}

void Game::update(sf::Time deltaTime) {
    //atualiza estado do jogador
    player.update(deltaTime);

    //obtem posição do jogador
    sf::Vector2f playerPosition = player.getPosition();
    //obtem a cor do tile na posição do jogador
    sf::Color tileColor = tileMap.getTileColor(playerPosition);

    //verifica se o tile é azul
    if (tileColor == sf::Color::Blue) {
        std::cout << "Você perdeu!" << std::endl;
        window.close();
    }
    //verifica se o tile é vermelho
    else if (tileColor == sf::Color::Red) {
        player.getSprite().setTexture(playerRedTexture);
    }
    //verifica se o tile é amarelo
    else if (tileColor == sf::Color::Yellow) {
        score++;
        std::cout << "Pontuação: " << score << std::endl;
        tileMap.removeTile(playerPosition);
        if (score >= 5) {
            std::cout << "Você ganhou!" << std::endl;
            window.close();
        }
    }
    else {
        player.getSprite().setTexture(playerTexture);
    }
}

void Game::render() {
    //limpa janela
    window.clear();
    //desenha tilemap na janela
    window.draw(tileMap);
    //desenha jogador na janela
    player.render(window);
    //atualiza janela com o novo desenho
    window.display();
}
