#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    //carrega o tilemap
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
    //retorna a cor de um tile em uma posição especifica
    sf::Color getTileColor(sf::Vector2f position) const;
    //remove um tile na posição fornecida
    void removeTile(sf::Vector2f position);

private:
    //desenha o tilemap
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    //armazena os vertices do tilemap
    sf::VertexArray vertices;
    //textura do tilemap
    sf::Texture tileset;
    //imagem do tilemap, pega a cor dos tiles
    sf::Image tilemapImage;
    //dados do mapa de tiles
    const int* tileData;
    //dimensões do mapa
    unsigned int mapWidth, mapHeight;
};

#endif // TILEMAP_HPP
