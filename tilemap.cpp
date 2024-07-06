#include "TileMap.hpp"
#include <iostream>

//recebe o caminho do arquivo do tileset, tamanho dos tiles, um ponteiro para os dados dos tiles, largura e altura do mapa
bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height) {
    //tenta carregar textura do tileset
    if (!this->tileset.loadFromFile(tileset)) {
        std::cerr << "Erro ao carregar o tileset!" << std::endl;
        return false;
    }

    //tenta carregar imagem do tileset para obter cor
    if (!tilemapImage.loadFromFile(tileset)) {
        std::cerr << "Erro ao carregar a imagem do tileset!" << std::endl;
        return false;
    }
    //armazena os dados dos tiles, largura do mapa e altura do mapa
    this->tileData = tiles;
    this->mapWidth = width;
    this->mapHeight = height;

    //define o tipo de primitiva que sao usadas para desenhar os tiles
    vertices.setPrimitiveType(sf::Quads);
    //redimensiona o arraz para acomodar todos os tiles do mapa
    vertices.resize(width * height * 4);

    //calcula  fator de escala para altura e largura de tiles
    float scaleX = 1024.0f / tileSize.x;
    float scaleY = 768.0f / tileSize.y;
    float scale = std::min(scaleX, scaleY);
    float offsetX = (1024 - tileSize.x * scale) / 2;
    float offsetY = (768 - tileSize.y * scale) / 2;

    //itera sobre largura e altura do mapa
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            //obtem o numero do tile atual
            int tileNumber = tiles[i + j * width];
            sf::Vertex* quad = &vertices[(i + j * width) * 4];


            //posição dos vértices
            quad[0].position = sf::Vector2f(i * tileSize.x * scale + offsetX, j * tileSize.y * scale + offsetY);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x * scale + offsetX, j * tileSize.y * scale + offsetY);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x * scale + offsetX, (j + 1) * tileSize.y * scale + offsetY);
            quad[3].position = sf::Vector2f(i * tileSize.x * scale + offsetX, (j + 1) * tileSize.y * scale + offsetY);

            //calcula coordenadas
            int tu = tileNumber % (this->tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (this->tileset.getSize().x / tileSize.x);

            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    //aplica transformação da entidade
    states.transform *= getTransform();
    //define textura do estado para o tileset
    states.texture = &tileset;
    //desenha a matriz dos vertices
    target.draw(vertices, states);
}

sf::Color TileMap::getTileColor(sf::Vector2f position) const {
    //verifica se a posição esta fora dos limites da imagem.
    if (position.x < 0 || position.y < 0 || position.x >= tilemapImage.getSize().x || position.y >= tilemapImage.getSize().y) {
        //se estiver fora, retorna a cor preta
        return sf::Color::Black;
    }
    return tilemapImage.getPixel(static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y));
}

void TileMap::removeTile(sf::Vector2f position) {
    //converte a posição fornecida para coordenadas de tile
    sf::Vector2u tilePosition(static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y));
    //altera a cor do pixel na posição para verde
    tilemapImage.setPixel(tilePosition.x, tilePosition.y, sf::Color::Green);
}
