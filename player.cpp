#include "Player.hpp"

//incializa a velocidade do jogador
Player::Player() : speed(200.0f) {}

void Player::handleInput() {
    // Implementa lógica de entrada do jogador
}

//atualiza estado do jogador
void Player::update(sf::Time deltaTime) {
    //inicializa vetor de movimento
    sf::Vector2f movement(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= speed * deltaTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += speed * deltaTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= speed * deltaTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += speed * deltaTime.asSeconds();
    }
    //move o jogador de acordo com o movimento calculado
    sprite.move(movement);
}

//desenha o jogador na janela
void Player::render(sf::RenderWindow& window) {
    //desenha o sprite do jogador na janela
    window.draw(sprite);
}

//retorna a posição do jogador
sf::Vector2f Player::getPosition() const {
    //retorna a posição do sprite do jogador
    return sprite.getPosition();
}

//define a posição do  jogador
void Player::setPosition(sf::Vector2f position) {
    sprite.setPosition(position);
}

//retorna o sprite do jogador
sf::Sprite& Player::getSprite() {
    return sprite;
}
