#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../../AbstractWindow.h"
#include <map>
#include "../../../../tank-lib/include/Bullet.h"

#ifndef PROI_PROJEKT_BULLETSGRAPHIC_H
#define PROI_PROJEKT_BULLETSGRAPHIC_H


class Bullet;


/**
 * @brief Class responsible for bullets updates and render
 *
 * Fetchs bullets positions and redners its on the screen
 * Defines enum TextureType for matching textures with bullet type
 * Defines struct RenderObject for storing matched texture together with bullet coords
 * Stores paths to textures in a std::map<TextureType, std::string>
 */
class BulletsGraphic : public AbstractWindow
{
protected:

    /// @brief Sturct that links object position with its texture
    struct RenderObject
    {
        sf::Vector2f coords;
        Bullet::BulletType textureType;
        Direction direction;
        RenderObject(sf::Vector2f pos, Direction direction, Bullet::BulletType type=Bullet::Enemy);
    };


    /// @brief Maps texture types to actual paths to textures
    std::unordered_map<Bullet::BulletType, std::string> pathMap
    {
        {Bullet::Enemy, "../src/graphic-lib/bulletsImages/bullet.png"},
        {Bullet::Friendly, "../src/graphic-lib/bulletsImages/bullet.png"}
    };

    /// @brief Maps texture types to actual textures
    std::unordered_map<Bullet::BulletType, sf::Texture> textureMap{};

    std::vector<Bullet*>* bullets;

    std::vector<RenderObject> renderBullets;
    /**
     * @brief Makes RenderObjects vector from tanks list
     *
     * @return std::vector<RenderObject>
     */
    std::vector<RenderObject> makeRenderBullets() const;

      /// @brief Loads textures into the textureMap
    void loadTextures();

    /// @brief Returns angle in degrees from given direction
    float getAngle(Direction direction) const;

    /// @brief Sets tank's appropriate rotation
    void setBulletRotation(sf::Sprite& sprite, float angle);

    /**
     * @brief Makes RenderObjects vector from tanks list
     *
     * Stores made RenderObjects vector in vector renderTanks
     */
    void makeRenderBullets();

public:

    /// @brief Renders all objects on the screen in given order
    virtual void render() override;


    // /// @brief Updates its objects
    // void update(std::vector<Bullet*> bullets);


    /**
     * @brief Get the RenderObjects object in a vector
     *
     * @return std::vector<sf::Vector2f>
     */
    std::vector<RenderObject> getRenderBullets(std::vector<Bullet*>* bullets);


    /**
     * @brief Construct a new BulletsGraphic object
     *
     * Positions the view in the window.
     *
     * @param window
     * @param TanksGraphic
     */
    BulletsGraphic(const WindowView& windowView, std::vector<Bullet*>* bullets);
};

#endif //PROI_PROJEKT_BULLETSGRAPHIC_H