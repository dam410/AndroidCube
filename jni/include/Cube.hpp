#ifndef CUBE_HPP
#define CUBE_HPP

#include <SFML/System/Vector2.hpp>
#include <array>

class Cube
{
    public:
        Cube(float size = 0.1);
        void draw() const;
        void update(float time);

        float size;

        sf::Vector3f V;
        float theta;
        bool wasDown;

        sf::Vector2f angle;
        sf::Vector2f speed;
        sf::Vector2f maxSpeed;

        sf::Vector2i previousPosition;

        std::array<float, 36> face1;
        std::array<float, 36> face2;
        std::array<float, 36> face3;
};

#endif // CUBE_HPP
